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

int main()
{
char *envoi;
int i,start,id, succes,nbcategories;
char *query,*res,*reponse,*jour,*mois,*annee,*heures,*minutes,*secondes,*totpsecret,*totpcode;
char *nom,*mdp,*site,*code,*article,*titre,*contenu,*urlmisenavant,*horodatage;
time_t tim;
struct tm *TM;

envoi=read_POST();
start=strlen(envoi);
nbcategories=0;
for(i=0;i<start;i++)
	{
	if(envoi[i]<32) envoi[i]=0;
	if(envoi[i]=='=') nbcategories++;
	}
nbcategories -= 8;
query_size=atoi(getenv("CONTENT_LENGTH"));
nom=(char*)malloc(query_size);
mdp=(char*)malloc(query_size);
code=(char*)malloc(query_size);
site=(char*)malloc(query_size);
article=(char*)malloc(query_size);
contenu=(char*)malloc(1000+query_size);
titre=(char*)malloc(query_size);
urlmisenavant=(char*)malloc(query_size);
res=(char*)malloc(100);
reponse=(char*)malloc(1000);
jour=(char*)malloc(4);
mois=(char*)malloc(4);
heures=(char*)malloc(4);
minutes=(char*)malloc(4);
annee=(char*)malloc(5);
secondes=(char*)malloc(4);
totpsecret=(char*)malloc(40);
totpcode=(char*)malloc(40);
horodatage=(char*)malloc(100);
query=(char*)malloc(20000+query_size);
get_chaine(envoi,nbcategories+8,nom);
tamb(nom);
get_chaine(envoi,7+nbcategories,mdp);
tamb(mdp);
get_chaine(envoi,6+nbcategories,site);
tamb(site);
get_chaine(envoi,5+nbcategories,code);
tamb(code);
get_chaine(envoi,4+nbcategories,article);
tamb(article);
get_chaine(envoi,3+nbcategories,titre);
tamb(titre);
get_chaine(envoi,2+nbcategories,contenu);
tamb(contenu);
get_chaine(envoi,1+nbcategories,urlmisenavant);
url_decode(urlmisenavant);
prepare_contenu(urlmisenavant);
succes=0;
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
      		if(strcmp(totpsecret,"")==0) succes=1;
      		else
         		{
         		if(strcmp(totpcode,code)==0) succes=1;
         		else
            		{
            		strcpy(reponse,"Erreur : Code de vérification erroné ...");
            		sleep(2);
            		}
         		}
         	if(succes==1)
         		{
         		if(atoi(article)>0)
         			{
         			// mise à jour
         			sprintf(query,"delete from categorieallouee where site=\'%s\' and article=\'%s\';",site,article);
         			db_query(handler,query);
         			db_clear_result(result);
         			sprintf(query,"select jour,mois,annee,heure,minute from article where site=\'%s\' and id=\'%s\';",site,article);
         			db_query(handler,query);
         			if(db_ntuples(result)==1)
         				{
         				db_getvalue(result,0,0,jour,4);
         				db_getvalue(result,0,1,mois,4);
         				db_getvalue(result,0,2,annee,5);
         				db_getvalue(result,0,3,heures,4);
         				db_getvalue(result,0,4,minutes,4);
         				}
         			db_clear_result(result);
         			sprintf(query,"delete from article where site=\'%s\' and id=\'%s\';",site,article);
         			db_query(handler,query);
         			id=atoi(article);
         			db_clear_result(result);
         			}
         		else
         			{
         			// nouvel article
						sprintf(query,"select id from article where site=\'%s\' order by id desc;",site);
						db_query(handler,query);
						if(db_ntuples(result)==0) id=1;
						else
							{
							db_getvalue(result,0,0,reponse,1000);
							id=atoi(reponse)+1;
							}
						db_clear_result(result);
						TM=(struct tm *)malloc(sizeof(struct tm));
						time(&tim);
						TM=localtime(&tim);
						magiczero(TM->tm_mday,jour);
						magiczero(TM->tm_mon+1,mois);
						magiczero(TM->tm_hour,heures);
						magiczero(TM->tm_min,minutes);
						magiczero(TM->tm_sec,secondes);
						sprintf(annee,"%d",TM->tm_year+1900);
						}
					do
						{
						sprintf(query,"insert into article values (\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',%d);",site,titre,jour,mois,annee,heures,minutes,urlmisenavant,contenu,nom,id);
						db_query(handler,query);
						db_clear_result(result);
						sprintf(query,"select * from article where auteur=\'%s\' and site=\'%s\' and id=%d;",nom,site,id);
						db_query(handler,query);
						if(db_ntuples(result)==1) succes=1;
						else id++;
						db_clear_result(result);
						}
					while(succes==0);
					for(i=0;i<nbcategories;i++)
						{
						get_chaine2(envoi,i+1,reponse);
						tamb(reponse);
						sprintf(query,"insert into categorieallouee values (\'%s\',\'%s\',%d);",reponse,site,id);
						db_query(handler,query);
						db_clear_result(result);
						}
					}
				}
			}
		}
	}
if(succes==0)
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
               </li>\n",site,nom,mdp,site,code);
printf("</ul>\n\
         </div>\n\
         </div>\n\
      <div role=\"main\" class=\"ui-content\" data-theme=\"b\">\n\
      L'article a été publié ...\n\
      </div>\n\
      <div data-role=\"footer\" data-position=\"fixed\" data-theme=\"b\">\n\
         <div data-role=\"navbar\">\n\
            <ul>\n\
               <li>\n\
                  <form action=\"/cgi-bin/xpresso_dashboard.cgi\" method=\"post\" id=\"form-profil\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-mdp\" id=\"txt-mdp\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-enter\" id=\"txt-enter\" value=\"n\">\n\
                  <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"d\" data-icon=\"home\" class=\"ui-shadow\">Dashboard</button>\n\
                  </form>\n\
               </li>\n\
            </ul>\n\
         </div>\n\
      </div>\n\
   </div>\n\
</body>\n\
</html>",nom,mdp,site,code);
	}
}
