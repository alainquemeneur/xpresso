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
int i,start,succes;
char *query,*res,*reponse,*totpsecret,*totpcode;
char *nom,*mdp,*site,*code;

envoi=read_POST();
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
res=(char*)malloc(100);
reponse=(char*)malloc(200);
totpsecret=(char*)malloc(40);
totpcode=(char*)malloc(40);
query=(char*)malloc(20000+query_size);
get_chaine(envoi,4,nom);
tamb(nom);
get_chaine(envoi,3,mdp);
tamb(mdp);
get_chaine(envoi,2,site);
tamb(site);
get_chaine(envoi,1,code);
tamb(code);
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
      		if(strcmp(totpsecret,"")==0) succes=2;
      		else
         		{
         		if(strcmp(totpcode,code)==0) succes=3;
         		else
            		{
            		strcpy(reponse,"Erreur : Code de vérification erroné ...");
            		sleep(2);
            		}
         		}
         	if(succes==1)
         		{
         		}
         	}
         }
      }
	}
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
if(succes==2) 
	{
	printf("<form action=\"/cgi-bin/xpresso_confirmactivetotp.cgi\" method=\"post\" id=\"form-totp\" data-transition=\"none\" data-rel=\"dialog\">\n\
		<input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
        <input type=\"hidden\" name=\"txt-password\" id=\"txt-password\" value=\"%s\">\n\
        <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
        <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"%s\">\n\
		<button type=\"submit\" data-theme=\"c\" data-mini=\"true\" data-inline=\"true\" data-icon=\"lock\">Activer l'authentification 2FA</button>\n\
		</form>",nom,mdp,site,code);
	succes=1;
	}
if(succes==3) 
	{
	printf("<form action=\"/cgi-bin/xpresso_confirmdesactivetotp.cgi\" method=\"post\" id=\"form-totp\" data-transition=\"none\" data-rel=\"dialog\">\n\
		<input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
        <input type=\"hidden\" name=\"txt-password\" id=\"txt-password\" value=\"%s\">\n\
        <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
        <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"%s\">\n\
		<button type=\"submit\" data-theme=\"c\" data-mini=\"true\" data-inline=\"true\" data-icon=\"lock\">Désactiver l'authentification 2FA</button>\n\
		</form>",nom,mdp,site,code);
	succes=1;
	}
if(succes==1)
	{
	printf("<p style=\"text-align:center\"><strong>Mon profil</strong></p>\n\
               <form autocomplete=\"off\" action=\"/cgi-bin/xpresso_updateprofile.cgi\" method=\"post\" id=\"form-update\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-password\" id=\"txt-password\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"%s\">\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-nom\">Pseudo *</label>\n\
                  <input type=\"text\" name=\"txt-nom\" id=\"txt-nom\" maxlength=\"99\" value=\"%s\" disabled>\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-oldpassword\">Mot de passe (actuel)</label>\n\
                  <input type=\"password\" name=\"txt-oldpassword\" maxlength=\"99\" id=\"txt-oldpassword\" value=\"\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-password\">Mot de passe (nouveau)</label>\n\
                  <input type=\"password\" name=\"txt-password\" maxlength=\"99\" id=\"txt-password\" value=\"\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-confirm\">Confirmation du mot de passe</label>\n\
                  <input type=\"password\" name=\"txt-confirm\" maxlength=\"99\" id=\"txt-confirm\" value=\"\">\n\
                  </div>\n\
                  <input type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"c\" data-icon=\"action\" value=\"Mettre à jour mon profil\">\n\
                  </form>\n",nom,mdp,site,code,nom);
	}
else
	{
	printf("%s<br><br>\n",reponse);
	}
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
      </div>\n\
   </div>\n\
</body>\n\
</html>",nom,mdp,site,code);
}