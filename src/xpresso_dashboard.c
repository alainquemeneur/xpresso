#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define __USE_XOPEN
#include <time.h>
#include "mysql.h"
#include "mysql.c"
#include "commun.c"
#include "password.h"
#include "totp.c"

int main()
{
char *envoi;
int i,start,success;
char *query,*reponse,*totpsecret,*totpcode;
char *nom,*mdp,*site,*code,*enter;
struct Site *st;
time_t tim,comp,t_of_day;
struct tm *TM,t,*COMP;
struct Vue v;

envoi=read_POST();
success=0;
start=strlen(envoi);
for(i=0;i<start;i++)
	{
	if(envoi[i]<32) envoi[i]=0;
	}
query_size=atoi(getenv("CONTENT_LENGTH"));
nom=(char*)malloc(query_size);
mdp=(char*)malloc(query_size);
site=(char*)malloc(query_size);
code=(char*)malloc(query_size);
enter=(char*)malloc(query_size);
reponse=(char*)malloc(1000);
totpsecret=(char*)malloc(40);
totpcode=(char*)malloc(40);
query=(char*)malloc(20000+query_size);
st=(struct Site *)malloc(sizeof(struct Site));
get_chaine(envoi,5,nom);
tamb(nom);
get_chaine(envoi,4,mdp);
tamb(mdp);
get_chaine(envoi,3,site);
tamb(site);
get_chaine(envoi,2,code);
tamb(code);
get_chaine(envoi,1,enter);
tamb(enter);
if((handler=db_opendatabase("xpresso","localhost","xpresso",PASSWORD))==NULL)
	{
	strcpy(reponse,"Erreur : Impossible d'accéder à la base de données");
	}
else
	{
	sprintf(query,"select * from auteur where pseudo=\'%s\' and site=\'%s\';",nom,site);
	db_query(handler,query);
	if(db_ntuples(result)==0)
		{
		strcpy(reponse,"Erreur : Ce compte n'existe pas ...");
		db_clear_result(result);
		db_close(handler);
		}
	else
		{
		db_clear_result(result);
		sprintf(query,"select * from auteur where pseudo=\'%s\' and mdp=\'%s\' and site=\'%s\';",nom,mdp,site);
		db_query(handler,query);
		if(db_ntuples(result)==0)
			{
			strcpy(reponse,"Erreur : Mauvais mot de passe ...");
			db_clear_result(result);
			db_close(handler);
			sleep(2);
			}
		else
			{
			db_clear_result(result);
			sprintf(query,"select * from auteur where pseudo=\'%s\' and mdp=\'%s\' and actif=\'oui\' and site=\'%s\';",nom,mdp,site);
			db_query(handler,query);
			if(db_ntuples(result)==0)
				{
				strcpy(reponse,"Erreur : Votre compte n'a pas été activé par l'administrateur ...");
				db_clear_result(result);
				db_close(handler);
				}
			else
				{
				db_clear_result(result);
				sprintf(query,"select totpsecret,totpcode from auteur where pseudo=\'%s\' and site=\'%s\';",nom,site);
				db_query(handler,query);
				db_getvalue(result,0,0,totpsecret,40);
				db_getvalue(result,0,1,totpcode,40);
				db_clear_result(result);
				success=1;
				if(strcmp(totpsecret,"")!=0)
					{
					if(strcmp(enter,"y")==0)
						{
						if(checkcode(totpsecret,code)==0)
							{
							sprintf(query,"update auteur set totpcode=\'%s\' where pseudo=\'%s\' and site=\'%s\';",code,nom,site);
							db_query(handler,query);
							db_clear_result(result);
							}
						else 
							{
							strcpy(reponse,"Erreur : Code de vérification erroné ...");
							success=0;
							sleep(2);
							}
						}
					else
						{
						if(strcmp(totpcode,code)!=0)
							{
							strcpy(reponse,"Erreur : Code de vérification erroné ...");
							success=0;
							sleep(2);
							}
						}
					}
				if(success==1)
					{
					sprintf(query,"select titrecomplet, copyright from site where titrecourt=\'%s\';",site);
					db_query(handler,query);
					db_getvalue(result,0,0,reponse,1000);
					st->titrecomplet=(char *)malloc(strlen(reponse)+2);
					strcpy(st->titrecomplet,reponse);
					db_getvalue(result,0,1,reponse,1000);
					st->copyright=(char *)malloc(strlen(reponse)+2);
					strcpy(st->copyright,reponse);
					db_clear_result(result);
					TM=(struct tm *)malloc(sizeof(struct tm));
					time(&tim);
					TM=localtime(&tim);
					}
				}
			}
		}
	}
if(success==0)
	{
	printf("Content-Type: text/html\n\n\
<!DOCTYPE html>\n\
<html>\n\
<head>\n\
<title>XpressO</title>\n\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\
<meta charset=\"utf-8\">\n\
  <meta http-equiv=\"cache-control\" content=\"no-cache, must-revalidate, post-check=0, pre-check=0\" />\n\
  <meta http-equiv=\"cache-control\" content=\"max-age=0\" />\n\
  <meta http-equiv=\"expires\" content=\"0\" />\n\
  <meta http-equiv=\"expires\" content=\"Tue, 01 Jan 1980 1:00:00 GMT\" />\n\
  <meta http-equiv=\"pragma\" content=\"no-cache\" />\n\
<link rel=\"icon\" type=\"image/x-icon\" href=\"/xpresso/mini.png\">\n\
<link rel=\"stylesheet\" href=\"/xpresso/themes/press.min.css\" />\n\
<link rel=\"stylesheet\" href=\"/xpresso/themes/jquery.mobile.icons.min.css\" />\n\
<link rel=\"stylesheet\" href=\"/jq/jquery.mobile.structure-1.4.5.min.css\" />\n\
<script src=\"/jq/demos/js/jquery.min.js\"></script>\n\
<script src=\"/jq/jquery.mobile-1.4.5.min.js\"></script>\n\
</head>\n\
<body>\n\
%s\n\
</body>\n\
</html>\n",reponse);	
	}
else
	{
	printf("Content-Type: text/html\n\n\
		<!DOCTYPE html>\n\
<html>\n\
<head>\n\
<title>%s</title>\n\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\
<meta charset=\"utf-8\">\n\
  <meta http-equiv=\"cache-control\" content=\"no-cache, must-revalidate, post-check=0, pre-check=0\" />\n\
  <meta http-equiv=\"cache-control\" content=\"max-age=0\" />\n\
  <meta http-equiv=\"expires\" content=\"0\" />\n\
  <meta http-equiv=\"expires\" content=\"Tue, 01 Jan 1980 1:00:00 GMT\" />\n\
  <meta http-equiv=\"pragma\" content=\"no-cache\" />\n\
<link rel=\"icon\" type=\"image/x-icon\" href=\"/xpresso/mini.png\">\n\
<link rel=\"stylesheet\" href=\"/xpresso/themes/press.min.css\" />\n\
<link rel=\"stylesheet\" href=\"/xpresso/themes/jquery.mobile.icons.min.css\" />\n\
<link rel=\"stylesheet\" href=\"/jq/jquery.mobile.structure-1.4.5.min.css\" />\n\
<script src=\"/jq/demos/js/jquery.min.js\"></script>\n\
<script src=\"/jq/jquery.mobile-1.4.5.min.js\"></script>\n\
</head>\n\
<body>\n\
   <div data-role=\"page\" data-theme=\"b\">\n\
      <div data-role=\"header\" data-position=\"fixed\" data-theme=\"b\">\n\
         <div data-role=\"navbar\">\n\
            <ul>\n\
               <li>\n\
                  <form action=\"/cgi-bin/xpresso_articles.cgi\" method=\"post\" id=\"form-articles\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-mdp\" id=\"txt-mdp\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"%s\">\n\
                  <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"d\" data-icon=\"bars\" class=\"ui-shadow\">Articles</button>\n\
                  </form>\n\
               </li>\n\
               <li>\n\
                  <form action=\"/cgi-bin/xpresso_auteurs.cgi\" method=\"post\" id=\"form-auteurs\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-mdp\" id=\"txt-mdp\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"%s\">\n\
                  <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"d\" data-icon=\"user\" class=\"ui-shadow\">Auteurs</button>\n\
                  </form>\n\
               </li>\n\
               <li>\n\
                  <form action=\"/cgi-bin/xpresso_commentaires.cgi\" method=\"post\" id=\"form-commentaires\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-mdp\" id=\"txt-mdp\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"%s\">\n\
                  <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"d\" data-icon=\"comment\" class=\"ui-shadow\">Commentaires</button>\n\
                  </form>\n\
               </li>\n\
            </ul>\n\
         </div>\n",st->titrecomplet,nom,mdp,site,code,nom,mdp,site,code,nom,mdp,site,code);
         printf("<h1>%s</h1>\n</div>\n",st->titrecomplet);
      printf("<div role=\"main\" class=\"ui-content\" data-theme=\"b\">\n");
      sprintf(query,"select * from vue where site=\'%s\' and jour=%d and mois=%d and annee=%d;",site,TM->tm_mday,TM->tm_mon+1,TM->tm_year+1900);
      db_query(handler,query);
      v.lectures=db_ntuples(result);
      db_clear_result(result);
      sprintf(query,"select distinct adresseip from vue where site=\'%s\' and jour=\'%d\' and mois=\'%d\' and annee=\'%d\';",site,TM->tm_mday,TM->tm_mon+1,TM->tm_year+1900);
      db_query(handler,query);
      v.lecteurs=db_ntuples(result);
      db_clear_result(result);
      printf("<h3>Statistiques du site</h3>\n\
            Aujourd'hui :\n\
            <ul>\n\
               <li>Nombre de pages lues : %d</li>\n\
               <li>Nombre de lecteurs : %d</li>\n\
            </ul>\n",v.lectures,v.lecteurs);
      time(&tim);
      tim -= 24*3600;
		TM=localtime(&tim);
		sprintf(query,"select * from vue where site=\'%s\' and jour=%d and mois=%d and annee=%d;",site,TM->tm_mday,TM->tm_mon+1,TM->tm_year+1900);
      db_query(handler,query);
      v.lectures=db_ntuples(result);
      db_clear_result(result);
      sprintf(query,"select distinct adresseip from vue where site=\'%s\' and jour=\'%d\' and mois=\'%d\' and annee=\'%d\';",site,TM->tm_mday,TM->tm_mon+1,TM->tm_year+1900);
      db_query(handler,query);
      v.lecteurs=db_ntuples(result);
      db_clear_result(result);
      printf("Hier :\n\
            <ul>\n\
               <li>Nombre de pages lues : %d</li>\n\
               <li>Nombre de lecteurs : %d</li>\n\
            </ul>\n",v.lectures,v.lecteurs);
      time(&tim);
      time(&comp);
      comp -= 24*3600*7;
		TM=localtime(&tim);
		COMP=localtime(&comp);
		sprintf(query,"select jour,mois,annee,adresseip from vue where site=\'%s\';",site);
      db_query(handler,query);
      v.lecteurs=v.lectures=0;
      for(i=0;i<db_ntuples(result);i++)
      	{
      	db_getvalue(result,i,2,reponse,1000);
      	t.tm_year = atoi(reponse)-1900;
    		db_getvalue(result,i,1,reponse,1000);
    		t.tm_mon = atoi(reponse)-1;
    		db_getvalue(result,i,0,reponse,1000);
    		t.tm_mday = atoi(reponse);
    		t.tm_hour = 1;
    		t.tm_min = 1;
    		t.tm_sec = 1;
    		t.tm_isdst = 1;
    		t_of_day = mktime(&t);
    		if(t_of_day>=comp) v.lectures++;
      	}
      db_clear_result(result);
      sprintf(query,"select  distinct jour,mois,annee,adresseip from vue where site=\'%s\';",site);
      db_query(handler,query);
      for(i=0;i<db_ntuples(result);i++)
      	{
      	db_getvalue(result,i,2,reponse,1000);
      	t.tm_year = atoi(reponse)-1900;
    		db_getvalue(result,i,1,reponse,1000);
    		t.tm_mon = atoi(reponse)-1;
    		db_getvalue(result,i,0,reponse,1000);
    		t.tm_mday = atoi(reponse);
    		t.tm_hour = 1;
    		t.tm_min = 1;
    		t.tm_sec = 1;
    		t.tm_isdst = 1;
    		t_of_day = mktime(&t);
    		if(t_of_day>=comp) v.lecteurs++;
      	}
      db_clear_result(result);
      printf("Sur 7 jours :\n\
            <ul>\n\
               <li>Nombre de pages lues : %d</li>\n\
               <li>Nombre de lecteurs : %d</li>\n\
               <li>Moyenne jour pages lues : %d</li>\n\
               <li>Moyenne jour lecteurs : %d</li>\n\
            </ul>\n",v.lectures,v.lecteurs,v.lectures/7,v.lecteurs/7);
      time(&tim);
      time(&comp);
      comp -= 24*3600*30;
		TM=localtime(&tim);
		COMP=localtime(&comp);
		sprintf(query,"select jour,mois,annee,adresseip from vue where site=\'%s\';",site);
      db_query(handler,query);
      v.lecteurs=v.lectures=0;
      for(i=0;i<db_ntuples(result);i++)
      	{
      	db_getvalue(result,i,2,reponse,1000);
      	t.tm_year = atoi(reponse)-1900;
    		db_getvalue(result,i,1,reponse,1000);
    		t.tm_mon = atoi(reponse)-1;
    		db_getvalue(result,i,0,reponse,1000);
    		t.tm_mday = atoi(reponse);
    		t.tm_hour = 1;
    		t.tm_min = 1;
    		t.tm_sec = 1;
    		t.tm_isdst = 1;
    		t_of_day = mktime(&t);
    		if(t_of_day>comp) v.lectures++;
      	}
      db_clear_result(result);
      sprintf(query,"select  distinct jour,mois,annee,adresseip from vue where site=\'%s\';",site);
      db_query(handler,query);
      for(i=0;i<db_ntuples(result);i++)
      	{
      	db_getvalue(result,i,2,reponse,1000);
      	t.tm_year = atoi(reponse)-1900;
    		db_getvalue(result,i,1,reponse,1000);
    		t.tm_mon = atoi(reponse)-1;
    		db_getvalue(result,i,0,reponse,1000);
    		t.tm_mday = atoi(reponse);
    		t.tm_hour = 1;
    		t.tm_min = 1;
    		t.tm_sec = 1;
    		t.tm_isdst = 1;
    		t_of_day = mktime(&t);
    		if(t_of_day>comp) v.lecteurs++;
      	}
      db_clear_result(result);
      printf("Sur 30 jours :\n\
            <ul>\n\
               <li>Nombre de pages lues : %d</li>\n\
               <li>Nombre de lecteurs : %d</li>\n\
               <li>Moyenne jour pages lues : %d</li>\n\
               <li>Moyenne jour lecteurs : %d</li>\n\
            </ul>\n",v.lectures,v.lecteurs,v.lectures/30,v.lecteurs/30);
      time(&tim);
      time(&comp);
      comp -= 24*3600*365;
		TM=localtime(&tim);
		COMP=localtime(&comp);
		sprintf(query,"select jour,mois,annee,adresseip from vue where site=\'%s\';",site);
      db_query(handler,query);
      v.lecteurs=v.lectures=0;
      for(i=0;i<db_ntuples(result);i++)
      	{
      	db_getvalue(result,i,2,reponse,1000);
      	t.tm_year = atoi(reponse)-1900;
    		db_getvalue(result,i,1,reponse,1000);
    		t.tm_mon = atoi(reponse)-1;
    		db_getvalue(result,i,0,reponse,1000);
    		t.tm_mday = atoi(reponse);
    		t.tm_hour = 1;
    		t.tm_min = 1;
    		t.tm_sec = 1;
    		t.tm_isdst = 1;
    		t_of_day = mktime(&t);
    		if(t_of_day>comp) v.lectures++;
      	}
      db_clear_result(result);
      sprintf(query,"select  distinct jour,mois,annee,adresseip from vue where site=\'%s\';",site);
      db_query(handler,query);
      for(i=0;i<db_ntuples(result);i++)
      	{
      	db_getvalue(result,i,2,reponse,1000);
      	t.tm_year = atoi(reponse)-1900;
    		db_getvalue(result,i,1,reponse,1000);
    		t.tm_mon = atoi(reponse)-1;
    		db_getvalue(result,i,0,reponse,1000);
    		t.tm_mday = atoi(reponse);
    		t.tm_hour = 1;
    		t.tm_min = 1;
    		t.tm_sec = 1;
    		t.tm_isdst = 1;
    		t_of_day = mktime(&t);
    		if(t_of_day>comp) v.lecteurs++;
      	}
      db_clear_result(result);
      printf("Sur 12 mois :\n\
            <ul>\n\
               <li>Nombre de pages lues : %d</li>\n\
               <li>Nombre de lecteurs : %d</li>\n\
               <li>Moyenne jour pages lues : %d</li>\n\
               <li>Moyenne jour lecteurs : %d</li>\n\
            </ul>\n",v.lectures,v.lecteurs,v.lectures/365,v.lecteurs/365);
		sprintf(query,"select jour,mois,annee,adresseip from vue where site=\'%s\';",site);
      db_query(handler,query);
      v.lecteurs=v.lectures=0;
      for(i=0;i<db_ntuples(result);i++)
      	{
      	db_getvalue(result,i,2,reponse,1000);
      	t.tm_year = atoi(reponse)-1900;
    		db_getvalue(result,i,1,reponse,1000);
    		t.tm_mon = atoi(reponse)-1;
    		db_getvalue(result,i,0,reponse,1000);
    		v.lectures++;
      	}
      db_clear_result(result);
      sprintf(query,"select  distinct jour,mois,annee,adresseip from vue where site=\'%s\';",site);
      db_query(handler,query);
      for(i=0;i<db_ntuples(result);i++)
      	{
      	db_getvalue(result,i,2,reponse,1000);
      	t.tm_year = atoi(reponse)-1900;
    		db_getvalue(result,i,1,reponse,1000);
    		t.tm_mon = atoi(reponse)-1;
    		db_getvalue(result,i,0,reponse,1000);
    		v.lecteurs++;
      	}
      db_clear_result(result);
      printf("Total :\n\
            <ul>\n\
               <li>Nombre de pages lues :%d</li>\n\
               <li>Nombre de lecteurs : %d</li>\n\
            </ul>\n",v.lectures,v.lecteurs);
      printf("</div>\n\
      <div data-role=\"footer\" data-position=\"fixed\" data-theme=\"b\">\n\
         <div data-role=\"navbar\">\n\
            <ul>\n\
               <li>\n\
                  <form action=\"/cgi-bin/xpresso_param.cgi\" method=\"post\" id=\"form-param\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-mdp\" id=\"txt-mdp\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"%s\">\n\
                  <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"d\" data-icon=\"gear\" class=\"ui-shadow\">Paramètres</button>\n\
                  </form>\n\
               </li>\n\
               <li>\n\
                  <form action=\"/cgi-bin/xpresso_categories.cgi\" method=\"post\" id=\"form-catégories\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-mdp\" id=\"txt-mdp\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"%s\">\n\
                  <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"d\" data-icon=\"bullets\" class=\"ui-shadow\">Catégories</button>\n\
                  </form>\n\
               </li>\n\
               <li>\n\
                  <form action=\"/cgi-bin/xpresso_editprofile.cgi\" method=\"post\" id=\"form-profil\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-mdp\" id=\"txt-mdp\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"%s\">\n\
                  <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"d\" data-icon=\"info\" class=\"ui-shadow\">Profil</button>\n\
                  </form>\n\
               </li>\n\
            </ul>\n\
         </div>\n\
         <h4>%s</h4>\n\
      </div>\n\
   </div>\n\
</body>\n\
</html>",nom,mdp,site,code,nom,mdp,site,code,nom,mdp,site,code,st->copyright);
	}
}