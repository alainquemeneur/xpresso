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
struct Site *st;

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
         		sprintf(query,"select * from site where titrecourt=\'%s\';",site);
					db_query(handler,query);
					if(db_ntuples(result)==0)
						{
						sprintf(reponse,"Erreur : Le site %s n'est pas hébergé sur ce serveur ...",site);
						db_clear_result(result);
						db_close(handler);
						succes=0;
						}
					else
						{
						st=(struct Site *)malloc(sizeof(struct Site));
						st->titrecourt=(char *)malloc(strlen(site)+2);
						strcpy(st->titrecourt,site);
						db_getvalue(result,0,0,reponse,1000);
						st->titrecomplet=(char *)malloc(strlen(reponse)+2);
						strcpy(st->titrecomplet,reponse);
						db_getvalue(result,0,2,reponse,1000);
						st->urlaccueil=(char *)malloc(strlen(reponse)+2);
						strcpy(st->urlaccueil,reponse);
						db_getvalue(result,0,3,reponse,1000);
						st->urlfavicon=(char *)malloc(strlen(reponse)+2);
						strcpy(st->urlfavicon,reponse);
						db_getvalue(result,0,4,reponse,1000);
						st->urlapropos=(char *)malloc(strlen(reponse)+2);
						strcpy(st->urlapropos,reponse);
						db_getvalue(result,0,5,reponse,1000);
						st->urlrss=(char *)malloc(strlen(reponse)+2);
						strcpy(st->urlrss,reponse);
						db_getvalue(result,0,6,reponse,1000);
						st->urlpubaccueil=(char *)malloc(strlen(reponse)+2);
						strcpy(st->urlpubaccueil,reponse);
						db_getvalue(result,0,7,reponse,1000);
						st->linkpubaccueil=(char *)malloc(strlen(reponse)+2);
						strcpy(st->linkpubaccueil,reponse);
						db_getvalue(result,0,8,reponse,1000);
						st->urlpubarticle=(char *)malloc(strlen(reponse)+2);
						strcpy(st->urlpubarticle,reponse);
						db_getvalue(result,0,9,reponse,1000);
						st->linkpubarticle=(char *)malloc(strlen(reponse)+2);
						strcpy(st->linkpubarticle,reponse);
						db_getvalue(result,0,10,reponse,1000);
						st->nombrecommaccueil=(char *)malloc(strlen(reponse)+2);
						strcpy(st->nombrecommaccueil,reponse);
						db_getvalue(result,0,11,reponse,1000);
						st->nombreartaccueil=(char *)malloc(strlen(reponse)+2);
						strcpy(st->nombreartaccueil,reponse);
						db_getvalue(result,0,12,reponse,1000);
						st->copyright=(char *)malloc(strlen(reponse)+2);
						strcpy(st->copyright,reponse);
						db_getvalue(result,0,13,reponse,1000);
						st->chemintheme=(char *)malloc(strlen(reponse)+2);
						strcpy(st->chemintheme,reponse);
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
	printf("<p style=\"text-align:center\"><strong>Paramètres du site</strong></p>\n\
               <form autocomplete=\"off\" action=\"/cgi-bin/xpresso_updateparam.cgi\" method=\"post\" id=\"form-update\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-password\" id=\"txt-password\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"%s\">\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-titrecourt\">Titre court *</label>\n\
                  <input type=\"text\" name=\"txt-court\" id=\"txt-titrecourt\" maxlength=\"99\" value=\"%s\" disabled>\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-titrecomplet\">Titre complet</label>\n\
                  <input type=\"text\" name=\"txt-titrecomplet\" maxlength=\"99\" id=\"txt-titrecomplet\" value=\"%s\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-urlaccueil\">URL accueil</label>\n\
                  <input type=\"text\" name=\"txt-urlaccueil\" maxlength=\"199\" id=\"txt-urlaccueil\" value=\"%s\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-urlfavicon\">URL favicon</label>\n\
                  <input type=\"text\" name=\"txt-urlfavicon\" maxlength=\"199\" id=\"txt-urlfavicon\" value=\"%s\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-urlapropos\">URL page \"A propos\"</label>\n\
                  <input type=\"text\" name=\"txt-urlapropos\" maxlength=\"199\" id=\"txt-urlapropos\" value=\"%s\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-urlrss\">URL fichier RSS</label>\n\
                  <input type=\"text\" name=\"txt-urlrss\" maxlength=\"199\" id=\"txt-urlrss\" value=\"%s\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-urlpubaccueil\">URL pub accueil</label>\n\
                  <input type=\"text\" name=\"txt-urlpubaccueil\" maxlength=\"199\" id=\"txt-urlpubaccueil\" value=\"%s\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-linkpubaccueil\">URL lien pub accueil</label>\n\
                  <input type=\"text\" name=\"txt-linkpubaccueil\" maxlength=\"199\" id=\"txt-linkpubaccueil\" value=\"%s\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-urlpubarticle\">URL pub article</label>\n\
                  <input type=\"text\" name=\"txt-urlpubarticle\" maxlength=\"199\" id=\"txt-urlpubarticle\" value=\"%s\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-linkpubarticle\">URL lien pub article</label>\n\
                  <input type=\"text\" name=\"txt-linkpubarticle\" maxlength=\"199\" id=\"txt-linkpubarticle\" value=\"%s\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-nombrecommaccueil\">Nombre de commentaires sur la page d'accueil</label>\n\
                  <input type=\"number\" name=\"txt-nombrecommaccueil\" maxlength=\"3\" id=\"txt-nombrecommaccueil\" value=\"%s\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-nombreartaccueil\">Nombre d'articles sur la page d'accueil</label>\n\
                  <input type=\"number\" name=\"txt-nombreartaccueil\" maxlength=\"3\" id=\"txt-nombreartaccueil\" value=\"%s\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-copyright\">Texte de copyright</label>\n\
                  <input type=\"text\" name=\"txt-copyright\" maxlength=\"199\" id=\"txt-copyright\" value=\"%s\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-chemintheme\">Chemin du thème</label>\n\
                  <input type=\"text\" name=\"txt-chemintheme\" maxlength=\"199\" id=\"txt-chemintheme\" value=\"%s\">\n\
                  </div>\n\
                  <input type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"c\" data-icon=\"action\" value=\"Mettre à jour\">\n\
                  </form>\n",nom,mdp,site,code,st->titrecourt,st->titrecomplet,st->urlaccueil,st->urlfavicon,st->urlapropos,st->urlrss,st->urlpubaccueil,st->linkpubaccueil,st->urlpubarticle,st->linkpubarticle,st->nombrecommaccueil,st->nombreartaccueil,st->copyright,st->chemintheme);
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
}