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
char *query,*reponse,*reponse2,*site,*totpsecret,*totpcode;
char *nom,*mdp,*code,*article;
struct Article *art;

envoi=read_POST();
start=strlen(envoi);
for(i=0;i<start;i++)
	{
	if(envoi[i]<32) envoi[i]=0;
	}
query_size=atoi(getenv("CONTENT_LENGTH"));
nom=(char*)malloc(query_size);
mdp=(char*)malloc(query_size);
code=(char*)malloc(query_size);
site=(char*)malloc(query_size);
article=(char*)malloc(query_size);
reponse=(char*)malloc(20000);
reponse2=(char*)malloc(1000);
totpsecret=(char*)malloc(40);
totpcode=(char*)malloc(40);
query=(char*)malloc(20000+query_size);
art=(struct Article *)malloc(sizeof(struct Article));
get_chaine(envoi,5,nom);
tamb(nom);
get_chaine(envoi,4,mdp);
tamb(mdp);
get_chaine(envoi,3,site);
tamb(site);
get_chaine(envoi,2,code);
tamb(code);
get_chaine(envoi,1,article);
tamb(article);
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
         		sprintf(query,"select * from article where site=\'%s\' and id=\'%s\';",site,article);
					db_query(handler,query);
					if(db_ntuples(result)==0) 
						{
						strcpy(reponse,"Aucun article n'a été selectionné ...");
						succes=0;
						db_clear_result(result);
						}
					else 
						{
						db_clear_result(result);
						sprintf(query,"select * from article where site=\'%s\' and id=\'%s\';",site,article);
						db_query(handler,query);
						db_getvalue(result,0,1,reponse,20000);
						art->titre=(char *)malloc(strlen(reponse)+2);
						strcpy(art->titre,reponse);
						db_getvalue(result,0,7,reponse,20000);
						art->urlmiseenavant=(char *)malloc(strlen(reponse)+2);
						strcpy(art->urlmiseenavant,reponse);
						db_getvalue(result,0,8,reponse,20000);
						art->contenu=(char *)malloc(strlen(reponse)+2);
						strcpy(art->contenu,reponse);
						db_clear_result(result);
						}
					}
				//db_close(handler);
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
            </ul>\n\
         </div>\n\
      </div>\n\
%s\n\
</div>\n\
</body>\n\
</html>\n",nom,mdp,site,code,reponse);
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
   <div role=\"main\" class=\"ui-content\" data-theme=\"b\">\n\
	<p style=\"text-align:center\"><strong>%s : Modifier un article</strong></p>\n",site,site);
	printf("<p style=\"text-align:center\"><strong>Article à modifier</strong></p>\n\
               <form autocomplete=\"off\" action=\"/cgi-bin/xpresso_savearticle.cgi\" method=\"post\" id=\"form-salons\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-password\" id=\"txt-password\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-article\" id=\"txt-article\" value=\"%s\">\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-titre\">Titre</label>\n\
                  <input type=\"text\" name=\"txt-titre\" maxlength=\"100\" id=\"txt-titre\" value=\"%s\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"textarea\">Contenu de l'article</label>\n\
                  <textarea name=\"textarea\" maxlength=\"20000\">%s</textarea>\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                  <label for=\"txt-image\">URL image mise en avant</label>\n\
                  <input type=\"url\" name=\"txt-image\" maxlength=\"2560\" id=\"txt-image\" value=\"%s\">\n\
                  </div>\n",nom,mdp,site,code,article,art->titre,art->contenu,art->urlmiseenavant);
	sprintf(query,"select nomlong,nomcourt from categorie where site=\'%s\';",site);
	db_query(handler,query);
	printf("Catégories :<br>\n");
	for(i=0;i<db_ntuples(result);i++)
		{
      db_getvalue(result,i,0,reponse,1000);
      db_getvalue(result,i,1,reponse2,1000);
      printf("<input type=\"checkbox\" id=\"%s\" name=\"%s\" data-theme=\"d\">\n\
                  <label for=\"%s\">%s</label>\n",reponse2,reponse2,reponse2,reponse);
   	}
   db_clear_result(result);
   printf("<input type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"c\" data-icon=\"forward\" value=\"Publier\">\n\
                  </form>\n\
                  <form action=\"/cgi-bin/xpresso_articles.cgi\" method=\"post\" id=\"form-posts\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"hidden\" name=\"txt-nom\" id=\"txt-nom\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-password\" id=\"txt-password\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-code\" id=\"txt-code\" value=\"%s\">\n\
                  <input type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"d\" data-icon=\"back\" value=\"Annuler\">\n\
                  </form>\n",nom,mdp,site,code);
	printf("<hr>Emojis supportés (cliquer pour copier l'emoji dans le presse papier):<br>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😀\');\" data-inline=\"true\" data-theme=\"d\">😀</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😃\');\" data-inline=\"true\" data-theme=\"d\">😃</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😄\');\" data-inline=\"true\" data-theme=\"d\">😄</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😁\');\" data-inline=\"true\" data-theme=\"d\">😁</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😆\');\" data-inline=\"true\" data-theme=\"d\">😆</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😅\');\" data-inline=\"true\" data-theme=\"d\">😅</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤣\');\" data-inline=\"true\" data-theme=\"d\">🤣</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😂\');\" data-inline=\"true\" data-theme=\"d\">😂</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🙂\');\" data-inline=\"true\" data-theme=\"d\">🙂</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🙃\');\" data-inline=\"true\" data-theme=\"d\">🙃</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😉\');\" data-inline=\"true\" data-theme=\"d\">😉</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😊\');\" data-inline=\"true\" data-theme=\"d\">😊</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😇\');\" data-inline=\"true\" data-theme=\"d\">😇</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥰\');\" data-inline=\"true\" data-theme=\"d\">🥰</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😍\');\" data-inline=\"true\" data-theme=\"d\">😍</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤩\');\" data-inline=\"true\" data-theme=\"d\">🤩</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😘\');\" data-inline=\"true\" data-theme=\"d\">😘</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😗\');\" data-inline=\"true\" data-theme=\"d\">😗</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😋\');\" data-inline=\"true\" data-theme=\"d\">😋</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😛\');\" data-inline=\"true\" data-theme=\"d\">😛</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤪\');\" data-inline=\"true\" data-theme=\"d\">🤪</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😝\');\" data-inline=\"true\" data-theme=\"d\">😝</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤗\');\" data-inline=\"true\" data-theme=\"d\">🤗</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤭\');\" data-inline=\"true\" data-theme=\"d\">🤭</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤫\');\" data-inline=\"true\" data-theme=\"d\">🤫</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤔\');\" data-inline=\"true\" data-theme=\"d\">🤔</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤐\');\" data-inline=\"true\" data-theme=\"d\">🤐</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤨\');\" data-inline=\"true\" data-theme=\"d\">🤨</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😏\');\" data-inline=\"true\" data-theme=\"d\">😏</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😒\');\" data-inline=\"true\" data-theme=\"d\">😒</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🙄\');\" data-inline=\"true\" data-theme=\"d\">🙄</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😬\');\" data-inline=\"true\" data-theme=\"d\">😬</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😔\');\" data-inline=\"true\" data-theme=\"d\">😔</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😴\');\" data-inline=\"true\" data-theme=\"d\">😴</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😷\');\" data-inline=\"true\" data-theme=\"d\">😷</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤒\');\" data-inline=\"true\" data-theme=\"d\">🤒</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤕\');\" data-inline=\"true\" data-theme=\"d\">🤕</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤢\');\" data-inline=\"true\" data-theme=\"d\">🤢</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤮\');\" data-inline=\"true\" data-theme=\"d\">🤮</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥵\');\" data-inline=\"true\" data-theme=\"d\">🥵</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥶\');\" data-inline=\"true\" data-theme=\"d\">🥶</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥴\');\" data-inline=\"true\" data-theme=\"d\">🥴</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😎\');\" data-inline=\"true\" data-theme=\"d\">😎</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤓\');\" data-inline=\"true\" data-theme=\"d\">🤓</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🧐\');\" data-inline=\"true\" data-theme=\"d\">🧐</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😕\');\" data-inline=\"true\" data-theme=\"d\">😕</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😟\');\" data-inline=\"true\" data-theme=\"d\">😟</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'☹️\');\" data-inline=\"true\" data-theme=\"d\">☹️</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😮\');\" data-inline=\"true\" data-theme=\"d\">😮</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😲\');\" data-inline=\"true\" data-theme=\"d\">😲</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😥\');\" data-inline=\"true\" data-theme=\"d\">😥</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😢\');\" data-inline=\"true\" data-theme=\"d\">😢</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😭\');\" data-inline=\"true\" data-theme=\"d\">😭</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😤\');\" data-inline=\"true\" data-theme=\"d\">😤</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥳\');\" data-inline=\"true\" data-theme=\"d\">🥳</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'😡\');\" data-inline=\"true\" data-theme=\"d\">😡</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'💀\');\" data-inline=\"true\" data-theme=\"d\">💀</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'☠️\');\" data-inline=\"true\" data-theme=\"d\">☠️</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'💩\');\" data-inline=\"true\" data-theme=\"d\">💩</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤡\');\" data-inline=\"true\" data-theme=\"d\">🤡</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'👻\');\" data-inline=\"true\" data-theme=\"d\">👻</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'👽\');\" data-inline=\"true\" data-theme=\"d\">👽</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤖\');\" data-inline=\"true\" data-theme=\"d\">🤖</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'💋\');\" data-inline=\"true\" data-theme=\"d\">💋</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🖐️\');\" data-inline=\"true\" data-theme=\"d\">🖐️</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🖖\');\" data-inline=\"true\" data-theme=\"d\">🖖</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'👌\');\" data-inline=\"true\" data-theme=\"d\">👌</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'✌️\');\" data-inline=\"true\" data-theme=\"d\">✌️</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤞\');\" data-inline=\"true\" data-theme=\"d\">🤞</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🖕\');\" data-inline=\"true\" data-theme=\"d\">🖕</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'👍\');\" data-inline=\"true\" data-theme=\"d\">👍</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'👎\');\" data-inline=\"true\" data-theme=\"d\">👎</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'👊\');\" data-inline=\"true\" data-theme=\"d\">👊</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🤝\');\" data-inline=\"true\" data-theme=\"d\">🤝</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🙏\');\" data-inline=\"true\" data-theme=\"d\">🙏</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'💪\');\" data-inline=\"true\" data-theme=\"d\">💪</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'👀\');\" data-inline=\"true\" data-theme=\"d\">👀</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🎅\');\" data-inline=\"true\" data-theme=\"d\">🎅</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'☂️\');\" data-inline=\"true\" data-theme=\"d\">☂️</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🎃\');\" data-inline=\"true\" data-theme=\"d\">🎃</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🌹\');\" data-inline=\"true\" data-theme=\"d\">🌹</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🌻\');\" data-inline=\"true\" data-theme=\"d\">🌻</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🌲\');\" data-inline=\"true\" data-theme=\"d\">🌲</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🌴\');\" data-inline=\"true\" data-theme=\"d\">🌴</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🌵\');\" data-inline=\"true\" data-theme=\"d\">🌵</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🌾\');\" data-inline=\"true\" data-theme=\"d\">🌾</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍀\');\" data-inline=\"true\" data-theme=\"d\">🍀</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍁\');\" data-inline=\"true\" data-theme=\"d\">🍁</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍄\');\" data-inline=\"true\" data-theme=\"d\">🍄</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🌙\');\" data-inline=\"true\" data-theme=\"d\">🌙</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'☀️\');\" data-inline=\"true\" data-theme=\"d\">☀️</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'⭐\');\" data-inline=\"true\" data-theme=\"d\">⭐</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'☁️\');\" data-inline=\"true\" data-theme=\"d\">☁️</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'⛅\');\" data-inline=\"true\" data-theme=\"d\">⛅</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🌧️\');\" data-inline=\"true\" data-theme=\"d\">🌧️</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🌨️\');\" data-inline=\"true\" data-theme=\"d\">🌨️</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🌈\');\" data-inline=\"true\" data-theme=\"d\">🌈</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'⚡\');\" data-inline=\"true\" data-theme=\"d\">⚡</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'⛄\');\" data-inline=\"true\" data-theme=\"d\">⛄</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🔥\');\" data-inline=\"true\" data-theme=\"d\">🔥</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🎄\');\" data-inline=\"true\" data-theme=\"d\">🎄</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'✨\');\" data-inline=\"true\" data-theme=\"d\">✨</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'💥\');\" data-inline=\"true\" data-theme=\"d\">💥</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍇\');\" data-inline=\"true\" data-theme=\"d\">🍇</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍉\');\" data-inline=\"true\" data-theme=\"d\">🍉</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍊\');\" data-inline=\"true\" data-theme=\"d\">🍊</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍋\');\" data-inline=\"true\" data-theme=\"d\">🍋</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍌\');\" data-inline=\"true\" data-theme=\"d\">🍌</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍍\');\" data-inline=\"true\" data-theme=\"d\">🍍</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥭\');\" data-inline=\"true\" data-theme=\"d\">🥭</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍏\');\" data-inline=\"true\" data-theme=\"d\">🍏</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍐\');\" data-inline=\"true\" data-theme=\"d\">🍐</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍑\');\" data-inline=\"true\" data-theme=\"d\">🍑</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍒\');\" data-inline=\"true\" data-theme=\"d\">🍒</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍓\');\" data-inline=\"true\" data-theme=\"d\">🍓</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥝\');\" data-inline=\"true\" data-theme=\"d\">🥝</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍅\');\" data-inline=\"true\" data-theme=\"d\">🍅</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥥\');\" data-inline=\"true\" data-theme=\"d\">🥥</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥑\');\" data-inline=\"true\" data-theme=\"d\">🥑</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍆\');\" data-inline=\"true\" data-theme=\"d\">🍆</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥔\');\" data-inline=\"true\" data-theme=\"d\">🥔</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥕\');\" data-inline=\"true\" data-theme=\"d\">🥕</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🌽\');\" data-inline=\"true\" data-theme=\"d\">🌽</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🌶️\');\" data-inline=\"true\" data-theme=\"d\">🌶️</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥜\');\" data-inline=\"true\" data-theme=\"d\">🥜</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🌰\');\" data-inline=\"true\" data-theme=\"d\">🌰</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍞\');\" data-inline=\"true\" data-theme=\"d\">🍞</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥐\');\" data-inline=\"true\" data-theme=\"d\">🥐</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🧀\');\" data-inline=\"true\" data-theme=\"d\">🧀</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥩\');\" data-inline=\"true\" data-theme=\"d\">🥩</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍔\');\" data-inline=\"true\" data-theme=\"d\">🍔</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍟\');\" data-inline=\"true\" data-theme=\"d\">🍟</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍕\');\" data-inline=\"true\" data-theme=\"d\">🍕</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🌭\');\" data-inline=\"true\" data-theme=\"d\">🌭</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥚\');\" data-inline=\"true\" data-theme=\"d\">🥚</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍿\');\" data-inline=\"true\" data-theme=\"d\">🍿</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍦\');\" data-inline=\"true\" data-theme=\"d\">🍦</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍩\');\" data-inline=\"true\" data-theme=\"d\">🍩</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍪\');\" data-inline=\"true\" data-theme=\"d\">🍪</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🎂\');\" data-inline=\"true\" data-theme=\"d\">🎂</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'☕\');\" data-inline=\"true\" data-theme=\"d\">☕</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍷\');\" data-inline=\"true\" data-theme=\"d\">🍷</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍹\');\" data-inline=\"true\" data-theme=\"d\">🍹</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🍺\');\" data-inline=\"true\" data-theme=\"d\">🍺</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🥂\');\" data-inline=\"true\" data-theme=\"d\">🥂</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'💣\');\" data-inline=\"true\" data-theme=\"d\">💣</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🎉\');\" data-inline=\"true\" data-theme=\"d\">🎉</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🎁\');\" data-inline=\"true\" data-theme=\"d\">🎁</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'📷\');\" data-inline=\"true\" data-theme=\"d\">📷</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'💡\');\" data-inline=\"true\" data-theme=\"d\">💡</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'💰\');\" data-inline=\"true\" data-theme=\"d\">💰</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'💉\');\" data-inline=\"true\" data-theme=\"d\">💉</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'💊\');\" data-inline=\"true\" data-theme=\"d\">💊</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'💝\');\" data-inline=\"true\" data-theme=\"d\">💝</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'💖\');\" data-inline=\"true\" data-theme=\"d\">💖</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'💕\');\" data-inline=\"true\" data-theme=\"d\">💕</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'💔\');\" data-inline=\"true\" data-theme=\"d\">💔</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🎵\');\" data-inline=\"true\" data-theme=\"d\">🎵</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'⚠️\');\" data-inline=\"true\" data-theme=\"d\">⚠️</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'⛔\');\" data-inline=\"true\" data-theme=\"d\">⛔</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🎓\');\" data-inline=\"true\" data-theme=\"d\">🎓</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇧🇪\');\" data-inline=\"true\" data-theme=\"d\">🇧🇪</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇧🇷\');\" data-inline=\"true\" data-theme=\"d\">🇧🇷</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇨🇦\');\" data-inline=\"true\" data-theme=\"d\">🇨🇦</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇨🇭\');\" data-inline=\"true\" data-theme=\"d\">🇨🇭</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇨🇳\');\" data-inline=\"true\" data-theme=\"d\">🇨🇳</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇩🇪\');\" data-inline=\"true\" data-theme=\"d\">🇩🇪</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇩🇰\');\" data-inline=\"true\" data-theme=\"d\">🇩🇰</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇩🇿\');\" data-inline=\"true\" data-theme=\"d\">🇩🇿</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇪🇸\');\" data-inline=\"true\" data-theme=\"d\">🇪🇸</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇪🇺\');\" data-inline=\"true\" data-theme=\"d\">🇪🇺</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇫🇮\');\" data-inline=\"true\" data-theme=\"d\">🇫🇮</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇫🇷\');\" data-inline=\"true\" data-theme=\"d\">🇫🇷</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇬🇧\');\" data-inline=\"true\" data-theme=\"d\">🇬🇧</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇬🇷\');\" data-inline=\"true\" data-theme=\"d\">🇬🇷</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇮🇪\');\" data-inline=\"true\" data-theme=\"d\">🇮🇪</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇮🇱\');\" data-inline=\"true\" data-theme=\"d\">🇮🇱</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇮🇹\');\" data-inline=\"true\" data-theme=\"d\">🇮🇹</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇯🇵\');\" data-inline=\"true\" data-theme=\"d\">🇯🇵</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇰🇷\');\" data-inline=\"true\" data-theme=\"d\">🇰🇷</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇳🇴\');\" data-inline=\"true\" data-theme=\"d\">🇳🇴</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇵🇹\');\" data-inline=\"true\" data-theme=\"d\">🇵🇹</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇷🇺\');\" data-inline=\"true\" data-theme=\"d\">🇷🇺</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇸🇪\');\" data-inline=\"true\" data-theme=\"d\">🇸🇪</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇸🇳\');\" data-inline=\"true\" data-theme=\"d\">🇸🇳</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇹🇷\');\" data-inline=\"true\" data-theme=\"d\">🇹🇷</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇺🇳\');\" data-inline=\"true\" data-theme=\"d\">🇺🇳</button>\n\
		<button onclick=\"navigator.clipboard.writeText(\'🇺🇸\');\" data-inline=\"true\" data-theme=\"d\">🇺🇸</button>\n\
		<hr>\n");
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
