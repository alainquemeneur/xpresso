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
int i,start,id, succes;
char *query,*reponse,*jour,*mois,*annee,*heures,*minutes,*secondes;
char *site,*article,*pseudo,*avatar,*email,*contenu,*horodatage;
time_t tim;
struct tm *TM;

envoi=read_POST();
start=strlen(envoi);
for(i=0;i<start;i++)
	{
	if(envoi[i]<32) envoi[i]=0;
	}
query_size=atoi(getenv("CONTENT_LENGTH"));
site=(char*)malloc(query_size);
article=(char*)malloc(query_size);
pseudo=(char*)malloc(query_size);
avatar=(char*)malloc(query_size);
email=(char*)malloc(query_size);
contenu=(char*)malloc(1000+query_size);
reponse=(char*)malloc(1000);
jour=(char*)malloc(4);
mois=(char*)malloc(4);
heures=(char*)malloc(4);
minutes=(char*)malloc(4);
annee=(char*)malloc(5);
secondes=(char*)malloc(4);
horodatage=(char*)malloc(100);
query=(char*)malloc(20000+query_size);
get_chaine(envoi,6,site);
tamb(site);
get_chaine(envoi,5,article);
tamb(article);
get_chaine(envoi,4,pseudo);
tamb(pseudo);
get_chaine(envoi,3,avatar);
tamb(avatar);
get_chaine(envoi,2,email);
tamb(email);
get_chaine(envoi,1,contenu);
tamb(contenu);
succes=0;
if((handler=db_opendatabase("xpresso","localhost","xpresso",PASSWORD))==NULL)
	{
	strcpy(reponse,"Erreur : Impossible d'accéder à la base de données");
	}
else
	{
	TM=(struct tm *)malloc(sizeof(struct tm));
	time(&tim);
	TM=localtime(&tim);
	magiczero(TM->tm_mday,jour);
	magiczero(TM->tm_mon+1,mois);
	magiczero(TM->tm_hour,heures);
	magiczero(TM->tm_min,minutes);
	magiczero(TM->tm_sec,secondes);
	sprintf(annee,"%d",TM->tm_year+1900);
						//site text, article integer,pseudo text, email text, urlavatar text, horodatage text, contenu text, valide text);
	sprintf(horodatage,"%s-%s-%d à %s:%s",jour,mois,TM->tm_year+1900,heures,minutes);
	sprintf(query,"insert into commentaire values (\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'non\');",site,article,pseudo,email,avatar,horodatage,contenu);
	db_query(handler,query);
	db_clear_result(result);
	succes=1;
	sprintf(reponse,"/var/www/html/%s/commentaire_recu",site);
	system(reponse);
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
                  <form action=\"/cgi-bin/xpresso_lire_article.cgi?site=%s&article=%s\" method=\"get\" id=\"form-articles\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"d\" data-icon=\"bars\" class=\"ui-shadow\">Retour à l'article</button>\n\
                  </form>\n\
               </li>\n",site,site,article);
printf("</ul>\n\
         </div>\n\
         </div>\n\
      <div role=\"main\" class=\"ui-content\" data-theme=\"b\">\n\
      Merci pour votre commentaire. Il a bien été pris en compte. Il apparaitra une fois validé par le modérateur ...\n\
      </div>\n\
      <div data-role=\"footer\" data-position=\"fixed\" data-theme=\"b\">\n\
         <div data-role=\"navbar\">\n\
            <ul>\n\
               <li>\n\
                  <form action=\"/cgi-bin/xpresso_accueil.cgi?site=%s\" method=\"get\" id=\"form-articles\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"d\" data-icon=\"home\" class=\"ui-shadow\">Retour à l'accueil</button>\n\
                  </form>\n\
               </li>\n\
            </ul>\n\
         </div>\n\
      </div>\n\
   </div>\n\
</body>\n\
</html>",site);
	}
}
