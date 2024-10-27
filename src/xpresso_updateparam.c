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
int i,start,succes,nb_messages,lastid,idfirst,idlast;
char *query,*reponse,*totpcode,*totpsecret;
char *nom,*mdp,*site,*code,*titrecomplet,*urlaccueil,*urlfavicon,*urlapropos,*urlrss,*urlpubaccueil,*linkpubaccueil,*urlpubarticle,*linkpubarticle,*nombrecommaccueil,*nombreartaccueil;
char *copyright,*chemintheme;

envoi=read_POST();
succes=0;
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
titrecomplet=(char*)malloc(query_size);
urlaccueil=(char*)malloc(query_size);
urlfavicon=(char*)malloc(query_size);
urlapropos=(char*)malloc(query_size);
urlrss=(char*)malloc(query_size);
urlpubaccueil=(char*)malloc(query_size);
linkpubaccueil=(char*)malloc(query_size);
urlpubarticle=(char*)malloc(query_size);
linkpubarticle=(char*)malloc(query_size);
nombrecommaccueil=(char*)malloc(query_size);
nombreartaccueil=(char*)malloc(query_size);
copyright=(char*)malloc(query_size);
chemintheme=(char*)malloc(query_size);
totpsecret=(char*)malloc(40);
totpcode=(char*)malloc(40);
reponse=(char*)malloc(200);
query=(char*)malloc(20000+query_size);
get_chaine(envoi,17,nom);
tamb(nom);
get_chaine(envoi,16,mdp);
tamb(mdp);
get_chaine(envoi,15,site);
tamb(site);
get_chaine(envoi,14,code);
tamb(code);
get_chaine(envoi,13,titrecomplet);
tamb(titrecomplet);
get_chaine(envoi,12,urlaccueil);
tamb(urlaccueil);
get_chaine(envoi,11,urlfavicon);
tamb(urlfavicon);
get_chaine(envoi,10,urlapropos);
tamb(urlapropos);
get_chaine(envoi,9,urlrss);
tamb(urlrss);
get_chaine(envoi,8,urlpubaccueil);
tamb(urlpubaccueil);
get_chaine(envoi,7,linkpubaccueil);
tamb(linkpubaccueil);
get_chaine(envoi,6,urlpubarticle);
tamb(urlpubarticle);
get_chaine(envoi,5,linkpubarticle);
tamb(linkpubarticle);
get_chaine(envoi,4,nombrecommaccueil);
tamb(nombrecommaccueil);
get_chaine(envoi,3,nombreartaccueil);
tamb(nombreartaccueil);
get_chaine(envoi,2,copyright);
tamb(copyright);
get_chaine(envoi,1,chemintheme);
tamb(chemintheme);
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
			sprintf(query,"select * from auteur where pseudo=\'%s\' and mdp=\'%s\' and site=\'%s\' and actif=\'oui\';",nom,mdp,site);
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
					sprintf(query,"update site set titrecomplet=\'%s\', urlaccueil=\'%s\', urlfavicon=\'%s\', urlapropos=\'%s\', urlrss=\'%s\', urlpubaccueil=\'%s\',linkpubaccueil=\'%s\', urlpubarticle=\'%s\', linkpubarticle=\'%s\', nombrecommaccueil=\'%s\', nombreartaccueil=\'%s\', copyright=\'%s\', chemintheme=\'%s\' where titrecourt=\'%s\';",titrecomplet,urlaccueil,urlfavicon,urlapropos,urlrss,urlpubaccueil,linkpubaccueil,urlpubarticle,linkpubarticle,nombrecommaccueil,nombreartaccueil,copyright,chemintheme,site);
					db_query(handler,query);
					db_clear_result(result);
					strcpy(reponse,"Les paramètres de site ont été mis à jour ...");
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
   <div data-role=\"page\" data-theme=\"b\">\n",site);
printf("%s\n",reponse);
printf("<div data-role=\"footer\" data-position=\"fixed\" data-theme=\"b\">\n\
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