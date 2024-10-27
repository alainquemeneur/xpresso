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
int i,start,success,max;
char *query,*reponse,*totpsecret,*totpcode;
char *nom,*mdp,*site,*code,*id, *article,*pseudo,*horodatage;
struct Site *st;

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
reponse=(char*)malloc(1000);
article=(char*)malloc(1000);
pseudo=(char*)malloc(1000);
horodatage=(char*)malloc(1000);
totpsecret=(char*)malloc(40);
totpcode=(char*)malloc(40);
id=(char*)malloc(40);
query=(char*)malloc(20000+query_size);
st=(struct Site *)malloc(sizeof(struct Site));
get_chaine(envoi,4,nom);
tamb(nom);
get_chaine(envoi,3,mdp);
tamb(mdp);
get_chaine(envoi,2,site);
tamb(site);
get_chaine(envoi,1,code);
tamb(code);
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
      		if(strcmp(totpsecret,"")==0) success=1;
      		else
         		{
         		if(strcmp(totpcode,code)==0) success=1;
         		else
            		{
            		strcpy(reponse,"Erreur : Code de vérification erroné ...");
            		sleep(2);
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
                  <form action=\"/cgi-bin/xpresso_commentaire_valider.cgi\" method=\"post\" id=\"form-valider\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-mdp\" id=\"txt-mdp\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-comm-valid-article\" id=\"txt-comm-valid-article\" value=\"\">\n\
                  <input type=\"hidden\" name=\"txt-comm-valid-pseudo\" id=\"txt-comm-valid-pseudo\" value=\"\">\n\
                  <input type=\"hidden\" name=\"txt-comm-valid-horo\" id=\"txt-comm-valid-horo\" value=\"\">\n\
                  <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"d\" data-icon=\"forward\" class=\"ui-shadow\">Valider</button>\n\
                  </form>\n\
               </li>\n\
               <li>\n\
                  <form action=\"/cgi-bin/xpresso_commentaire_supprimer.cgi\" method=\"post\" id=\"form-supprimer\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-mdp\" id=\"txt-mdp\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-comm-del-article\" id=\"txt-comm-del-article\" value=\"\">\n\
                  <input type=\"hidden\" name=\"txt-comm-del-pseudo\" id=\"txt-comm-del-pseudo\" value=\"\">\n\
                  <input type=\"hidden\" name=\"txt-comm-del-horo\" id=\"txt-comm-del-horo\" value=\"\">\n\
                  <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"d\" data-icon=\"delete\" class=\"ui-shadow\">Supprimer</button>\n\
                  </form>\n\
               </li>\n\
            </ul>\n\
         </div>\n",st->titrecomplet,nom,mdp,site,code,nom,mdp,site,code);
         printf("<h1>%s</h1>\n",st->titrecomplet);
         printf("<h1>Commentaires à valider</h1>\n</div>\n");
      printf("<div role=\"main\" class=\"ui-content\" data-theme=\"b\">\n");
      sprintf(query,"select article, pseudo, email, urlavatar, horodatage, contenu from commentaire where site=\'%s\' and valide=\'non\';",site);
      db_query(handler,query);
      for(i=0;i<db_ntuples(result);i++)
      	{
      	db_getvalue(result,i,4,reponse,1000);
      	printf("Le %s, ",reponse);
      	strcpy(horodatage,reponse);
      	db_getvalue(result,i,1,reponse,1000);
      	strcpy(pseudo,reponse);
      	printf("%s (email : ",reponse);
      	db_getvalue(result,i,2,reponse,1000);
      	printf("%s)",reponse);
      	db_getvalue(result,i,3,reponse,1000);
      	if(strcmp(reponse,"")!=0) printf(" (avatar : <img src=\"%s\">)",reponse);
      	printf(" a commenté :<br><br>\n");
      	db_getvalue(result,i,5,reponse,1000);
      	printf("%s<br>\n",reponse);
      	db_getvalue(result,i,0,reponse,1000);
      	printf("<button onclick=\"document.getElementById('txt-comm-valid-article').value = '%s';document.getElementById('txt-comm-valid-pseudo').value = '%s';document.getElementById('txt-comm-valid-horo').value = '%s';document.getElementById('txt-comm-del-article').value = '%s';document.getElementById('txt-comm-del-pseudo').value = '%s';document.getElementById('txt-comm-del-horo').value = '%s';\" data-inline=\"true\" data-theme=\"d\" data-mini=\"true\">Sélectionner</button>\n<hr>\n",reponse,pseudo,horodatage,reponse,pseudo,horodatage);
      	}
      db_clear_result(result);
      printf("</div>\n\
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
         <h4>%s</h4>\n\
      </div>\n\
   </div>\n\
</body>\n\
</html>",nom,mdp,site,code,st->copyright);
	}
}