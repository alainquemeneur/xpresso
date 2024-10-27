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
int i,start,success;
char *query,*reponse,*totpsecret;
char *nom,*mdp,*site;

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
totpsecret=(char*)malloc(40);
reponse=(char*)malloc(200);
query=(char*)malloc(20000+query_size);
get_chaine(envoi,3,nom);
tamb(nom);
get_chaine(envoi,2,mdp);
tamb(mdp);
get_chaine(envoi,1,site);
tamb(site);
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
				sprintf(query,"select totpsecret from auteur where pseudo=\'%s\' and site=\'%s\';",nom,site);
				db_query(handler,query);
				db_getvalue(result,0,0,totpsecret,40);
				db_clear_result(result);
				db_close(handler);
				if(strcmp(totpsecret,"")==0) success=1;
				else success=2;
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
if(success==1) 
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
<div data-role=\"page\" data-theme=\"b\">\n\
<div role=\"main\" class=\"ui-content\" data-theme=\"b\">\n");
	printf("Votre compte n'est pas protégé par un deuxième facteur d'authentification, ce qui améliorerait pourtant sa sécurité. Vous pouvez activer cette fonctionnalité depuis la page de votre profil<br>\n\
						<form action=\"/cgi-bin/xpresso_dashboard.cgi\" method=\"post\" id=\"form-connect\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-password\" id=\"txt-password\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"\">\n\
                  <input type=\"hidden\" name=\"txt-enter\" id=\"txt-enter\" value=\"n\">\n\
                  <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"c\" data-icon=\"action\" class=\"ui-shadow\">Accéder au dashboard</button>\n\
                  </form>\n\
                  </div>\n\
                  </body>\n\
                  </html>",nom,mdp,site);
	}
if(success==2) 
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
<body>\n");
	printf("<div data-role=\"page\" data-theme=\"b\">\n\
<div role=\"main\" class=\"ui-content\" data-theme=\"b\">\n\
<form autocomplete=\"off\" action=\"/cgi-bin/xpresso_dashboard.cgi\" method=\"post\" id=\"form\" data-transition=\"none\" data-rel=\"dialog\">\n\
            <input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
            <input type=\"hidden\" name=\"txt-password\" id=\"txt-password\" value=\"%s\">\n\
            <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
            <div data-role=\"fieldcontain\">\n\
               <label for=\"txt-code\">Code de vérification</label>\n\
               <input type=\"text\" name=\"txt-code\" maxlength=\"6\" id=\"txt-code\" value=\"\">\n\
            </div>\n\
            <input type=\"hidden\" name=\"txt-enter\" id=\"txt-enter\" value=\"y\">\n\
            <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"c\" data-icon=\"action\">Accéder au dashboard</button>\n\
         </form>\n\
         </div>\n\
         </div>\n\
         </body>\n\
         </html>",nom,mdp,site);
	sprintf(reponse,"rm /var/www/html/xpresso/qr/qr%s.png",nom);
	system(reponse);
	}
}