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
int i,j,start,success;
int nbcommentaires,nbcommentairesaafficher,nbarticles;
char *query,*reponse;
char *site,*article;
struct Site *st;
struct Article **art;
struct Commentaire **comm;
time_t tim;
struct tm *TM;
char *jour,*Mois,*Annee,*heures,*minutes,*secondes;

query=(char *)malloc(strlen(getenv("QUERY_STRING"))+1000);
site=(char *)malloc(strlen(getenv("QUERY_STRING"))+10);
article=(char *)malloc(strlen(getenv("QUERY_STRING"))+10);
reponse=(char *)malloc(20000);
jour=(char*)malloc(4);
Mois=(char*)malloc(4);
heures=(char*)malloc(4);
minutes=(char*)malloc(4);
Annee=(char*)malloc(5);
secondes=(char*)malloc(4);
st=(struct Site *)malloc(sizeof(struct Site));
strcpy(query,getenv("QUERY_STRING"));
start=0;
i=strlen(query)-1;
while(query[i]!='=') i--;
i++;
while(i<=strlen(query))
	{
	article[start]=query[i];
	i++;
	start++;
	}
start=0;
i=strlen(query)-1;
while(query[i]!='=') i--;
i--;
while(query[i]!='=') i--;
i++;
while(query[i]!='&')
	{
	site[start]=query[i];
	i++;
	start++;
	}
site[start]=0;
if((handler=db_opendatabase("xpresso","localhost","xpresso",PASSWORD))==NULL)
	{
	strcpy(reponse,"Erreur : Impossible d'accéder à la base de données");
	success=0;
	}
else
	{
	sprintf(query,"select * from site where titrecourt=\'%s\';",site);
	db_query(handler,query);
	if(db_ntuples(result)==0)
		{
		sprintf(reponse,"Erreur : Le site %s n'est pas hébergé sur ce serveur ...",site);
		db_clear_result(result);
		db_close(handler);
		success=0;
		}
	else
		{
		success=1;
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
	sprintf(query,"select titre from article where site=\'%s\' and id=\'%s\';",site,article);
	db_query(handler,query);
	nbarticles=db_ntuples(result);
	if(nbarticles==0) strcpy(reponse, "");
	else db_getvalue(result,0,0,reponse,1000);
	db_clear_result(result);
	printf("Content-Type: text/html\n\n\
<!DOCTYPE html>\n\
<html>\n\
<head>\n\
<title>%s - %s</title>\n\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\
<meta charset=\"utf-8\">\n\
  <meta http-equiv=\"cache-control\" content=\"no-cache, must-revalidate, post-check=0, pre-check=0\" />\n\
  <meta http-equiv=\"cache-control\" content=\"max-age=0\" />\n\
  <meta http-equiv=\"expires\" content=\"0\" />\n\
  <meta http-equiv=\"expires\" content=\"Tue, 01 Jan 1980 1:00:00 GMT\" />\n\
  <meta http-equiv=\"pragma\" content=\"no-cache\" />\n\
<link rel=\"icon\" type=\"image/x-icon\" href=\"%s\">\n\
<link rel=\"stylesheet\" href=\"%s/press.min.css\" />\n\
<link rel=\"stylesheet\" href=\"%s/jquery.mobile.icons.min.css\" />\n\
<link rel=\"stylesheet\" href=\"/jq/jquery.mobile.structure-1.4.5.min.css\" />\n\
<script src=\"/jq/demos/js/jquery.min.js\"></script>\n\
<script src=\"/jq/jquery.mobile-1.4.5.min.js\"></script>\n\
</head>\n",reponse,st->titrecomplet,st->urlfavicon,st->chemintheme,st->chemintheme);
	printf("<body>\n\
   <div data-role=\"page\" data-theme=\"b\">\n\
      <div data-role=\"header\" data-position=\"fixed\" data-theme=\"b\">\n\
         <div data-role=\"navbar\">\n\
            <ul>\n\
               <li>\n\
                  <form action=\"%s\" method=\"get\" id=\"form-home\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"d\" data-icon=\"home\" class=\"ui-shadow\">Accueil</button>\n\
                  </form>\n\
               </li>\n\
               <li>\n\
                  <form action=\"%s\" method=\"get\" id=\"form-about\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"d\" data-icon=\"info\" class=\"ui-shadow\">A propos</button>\n\
                  </form>\n\
               </li>\n\
            </ul>\n\
         </div>\n\
         <h4>%s</h4>\n\
      </div>\n",st->urlaccueil,st->urlapropos,st->titrecomplet);
	printf("<div role=\"main\" class=\"ui-content\" data-theme=\"b\">\n");
	sprintf(query,"select * from article where site=\'%s\' and id=\'%s\';",site,article);
	db_query(handler,query);
	nbarticles=db_ntuples(result);
	if(nbarticles==0)
		{
		printf("Aucun article à afficher<br>\n");
		}
	else
		{
		art=(struct Article **)malloc(sizeof(struct Article *));
		art[0]=(struct Article *)malloc(sizeof(struct Article));
		db_getvalue(result,0,0,reponse,1000);
		art[0]->site=(char *)malloc(strlen(reponse)+2);
		strcpy(art[0]->site,reponse);
		db_getvalue(result,0,1,reponse,1000);
		art[0]->titre=(char *)malloc(strlen(reponse)+2);
		strcpy(art[0]->titre,reponse);
		db_getvalue(result,0,2,reponse,1000);
		art[0]->jour=(char *)malloc(strlen(reponse)+2);
		strcpy(art[0]->jour,reponse);
		db_getvalue(result,0,3,reponse,1000);
		art[0]->mois=(char *)malloc(strlen(reponse)+2);
		strcpy(art[0]->mois,reponse);
		db_getvalue(result,0,4,reponse,1000);
		art[0]->annee=(char *)malloc(strlen(reponse)+2);
		strcpy(art[0]->annee,reponse);
		db_getvalue(result,0,5,reponse,1000);
		art[0]->heure=(char *)malloc(strlen(reponse)+2);
		strcpy(art[0]->heure,reponse);
		db_getvalue(result,0,6,reponse,1000);
		art[0]->minute=(char *)malloc(strlen(reponse)+2);
		strcpy(art[0]->minute,reponse);
		db_getvalue(result,0,7,reponse,1000);
		art[0]->urlmiseenavant=(char *)malloc(strlen(reponse)+2);
		strcpy(art[0]->urlmiseenavant,reponse);
		db_getvalue(result,0,8,reponse,20000);
		art[0]->contenu=(char *)malloc(strlen(reponse)+2);
		strcpy(art[0]->contenu,reponse);
		db_getvalue(result,0,9,reponse,1000);
		art[0]->auteur=(char *)malloc(strlen(reponse)+2);
		strcpy(art[0]->auteur,reponse);
		db_getvalue(result,0,10,reponse,1000);
		art[0]->id=(char *)malloc(strlen(reponse)+2);
		strcpy(art[0]->id,reponse);
		db_clear_result(result);
		printf("<h2>%s</h2>\n",art[0]->titre);
		start=atoi(art[0]->jour);
		magiczero(start,art[0]->jour);
		start=atoi(art[0]->mois);
		magiczero(start,art[0]->mois);
		start=atoi(art[0]->heure);
		magiczero(start,art[0]->heure);
		start=atoi(art[0]->minute);
		magiczero(start,art[0]->minute);
		printf("<h4>Le %s/%s/%s, à %sh%s, par %s</h4>\n",art[0]->jour,art[0]->mois,art[0]->annee,art[0]->heure,art[0]->minute,art[0]->auteur);
		if(strcmp(art[0]->urlmiseenavant,"")!=0) printf("<p><img src=\"%s\" align=\"middle\" style=\"max-width:100%%;\"></p>\n",art[0]->urlmiseenavant);
		printf("%s<br>",art[0]->contenu);
		sprintf(query,"select distinct categorie.nomcourt,categorie.nomlong from categorie,categorieallouee where categorieallouee.site=\'%s\' and categorieallouee.article=\'%s\' and categorieallouee.categorie = categorie.nomcourt;",site,art[0]->id);
      db_query(handler,query);
      if(db_ntuples(result)>0) printf("<p>\n");
      for(j=0;j<db_ntuples(result);j++)
       	{
        	db_getvalue(result,j,0,reponse,1000);
        	printf("<form action=\"/cgi-bin/xpresso_accueil.cgi?site=%s&categorie=%s\" method=\"get\" id=\"form-categorie\" data-transition=\"none\" data-rel=\"dialog\">\n",site,reponse);
			db_getvalue(result,j,1,reponse,1000);     
         printf("<button type=\"submit\" data-theme=\"d\" data-mini=\"true\" data-inline=\"true\">%s</button>\n\
              </form>\n",reponse);
         }
      if(db_ntuples(result)>0) printf("</p>\n");
      db_clear_result(result);
		if(strcmp(st->urlpubarticle,"")!=0) printf("<a href=\"%s\"><img src=\"%s\" align=\"middle\" style=\"max-width:100%%;\"></a><br>\n",st->linkpubarticle,st->urlpubarticle);
		sprintf(query,"select site from commentaire where site=\'%s\' and article=\'%s\' and valide='oui';",site,art[0]->id);
		db_query(handler,query);
		if(db_ntuples(result)==0) printf("<p><i>Soyez le premier à commenter cet article</i></p>\n");
		if(db_ntuples(result)==1) printf("<p><i>1 commentaire</i></p>\n");
		if(db_ntuples(result)>1) printf("<p><i>%d commentaires</i></p>\n",db_ntuples(result));
		db_clear_result(result);
   	printf("<hr>\n");
      printf("<h3>Commentaires :</h3>\n<p><ul>\n");
      sprintf(query,"select * from commentaire where site=\'%s\' and article=\'%s\' and valide=\'oui\' order by horodatage desc;",site,article);
      db_query(handler,query);
      nbcommentaires=db_ntuples(result);
      nbcommentairesaafficher=nbcommentaires;
      comm=(struct Commentaire **)malloc(nbcommentairesaafficher*sizeof(struct Commentaire *));
      for(i=0;i<nbcommentairesaafficher;i++)
      	{
      	comm[i]=(struct Commentaire *)malloc(sizeof(struct Commentaire));
      	}
      for(i=0;i<nbcommentairesaafficher;i++)
      	{
      	j=nbcommentaires-nbcommentairesaafficher+i;
      	comm[i]->site=(char *)malloc(strlen(site)+2);
      	strcpy(comm[i]->site,site);
      	db_getvalue(result,j,1,reponse,1000);
      	comm[i]->article=(char *)malloc(strlen(reponse)+2);
      	strcpy(comm[i]->article,reponse);
      	db_getvalue(result,j,2,reponse,1000);
      	comm[i]->pseudo=(char *)malloc(strlen(reponse)+2);
      	strcpy(comm[i]->pseudo,reponse);
      	db_getvalue(result,j,3,reponse,1000);
      	comm[i]->email=(char *)malloc(strlen(reponse)+2);
      	strcpy(comm[i]->email,reponse);
      	db_getvalue(result,j,4,reponse,1000);
      	comm[i]->urlavatar=(char *)malloc(strlen(reponse)+2);
      	strcpy(comm[i]->urlavatar,reponse);
      	db_getvalue(result,j,5,reponse,1000);
      	comm[i]->horodatage=(char *)malloc(strlen(reponse)+2);
      	strcpy(comm[i]->horodatage,reponse);
      	db_getvalue(result,j,6,reponse,1000);
      	comm[i]->contenu=(char *)malloc(strlen(reponse)+2);
      	strcpy(comm[i]->contenu,reponse);
      	db_getvalue(result,j,7,reponse,1000);
      	comm[i]->valide=(char *)malloc(strlen(reponse)+2);
      	strcpy(comm[i]->valide,reponse);
      	printf("<li>\n<h4>Le %s par %s</h4>\n",comm[i]->horodatage,comm[i]->pseudo);
         if(strcmp(comm[i]->urlavatar,"")!=0) printf("<img src=\"%s\">\n",comm[i]->urlavatar);
         printf("%s</li>\n",comm[i]->contenu);
      	}
      printf("</ul></p><hr>\n");
      db_clear_result(result);
      printf("<p>Commentez cet article :<br>\n\
               <form autocomplete=\"off\" action=\"/cgi-bin/xpresso_commenter.cgi\" method=\"post\" id=\"form-commenter\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"hidden\" name=\"txt-site\" id=\"txt-site\" value=\"%s\">\n\
                  <input type=\"hidden\" name=\"txt-article\" id=\"txt-article\" value=\"%s\">\n\
                  <div data-role=\"fieldcontain\">\n\
                     <label for=\"txt-pseudo\">Pseudo :</label>\n\
                     <input type=\"text\" name=\"txt-pseudo\" maxlength=\"100\" id=\"txt-pseudo\" value=\"\" required>\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                     <label for=\"txt-pseudo\">URL de l'avatar (optionnel) :</label>\n\
                     <input type=\"text\" name=\"txt-avatar\" maxlength=\"100\" id=\"txt-avatar\" value=\"\">\n\
                  </div>\n\
                  <div data-role=\"fieldcontain\">\n\
                     <label for=\"txt-email\">Email (optionnel) :</label>\n\
                     <input type=\"text\" name=\"txt-email\" maxlength=\"100\" id=\"txt-email\" value=\"\">\n\
                  </div>\n\
            <div data-role=\"fieldcontain\">\n\
                  <label for=\"textarea\">Commentaire (1000 caractères max) :</label>\n\
                  <textarea name=\"textarea\" maxlength=\"1000\"  required></textarea>\n\
                  </div>\n\
            <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"c\" data-icon=\"comment\">Commenter</button>\n\
         </form></p>\n",site,article);
   printf("</div>\n");
   printf("<div data-role=\"footer\" data-position=\"fixed\" data-theme=\"b\">\n\
         <h4>%s</h4>\n\
      </div>\n\
   </div>\n\
</body>\n\
</html>",st->copyright);
   TM=(struct tm *)malloc(sizeof(struct tm));
	time(&tim);
	TM=localtime(&tim);
	magiczero(TM->tm_mday,jour);
	magiczero(TM->tm_mon+1,Mois);
	magiczero(TM->tm_hour,heures);
	magiczero(TM->tm_min,minutes);
	magiczero(TM->tm_sec,secondes);
	sprintf(Annee,"%d",TM->tm_year+1900);
	sprintf(query,"insert into vue values (\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\');",site,article,jour,Mois,Annee,getenv("REMOTE_ADDR"));
	db_query(handler,query);
	db_clear_result(result);
   	}
	}
}