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
int i,j,start,success,nbarticles,nbarticleaafficher,artdebut;
int nbcommentaires,nbcommentairesaafficher,commdebut;
char *query,*reponse, *reponse2, *reponse3;
char *site,*page,*categorie,*mois,*annee,*recherche;
struct Site *st;
struct Article **art;
struct Commentaire **comm;
time_t tim;
struct tm *TM;
char *jour,*Mois,*Annee,*heures,*minutes,*secondes;

query=(char *)malloc(strlen(getenv("QUERY_STRING"))+1000);
site=(char *)malloc(strlen(getenv("QUERY_STRING"))+10);
page=(char *)malloc(strlen(getenv("QUERY_STRING"))+10);
categorie=(char *)malloc(strlen(getenv("QUERY_STRING"))+10);
mois=(char *)malloc(strlen(getenv("QUERY_STRING"))+10);
annee=(char *)malloc(strlen(getenv("QUERY_STRING"))+10);
recherche=(char *)malloc(strlen(getenv("QUERY_STRING"))+10);
reponse=(char *)malloc(20000);
reponse2=(char *)malloc(100);
reponse3=(char *)malloc(100);
jour=(char*)malloc(4);
Mois=(char*)malloc(4);
heures=(char*)malloc(4);
minutes=(char*)malloc(4);
Annee=(char*)malloc(5);
secondes=(char*)malloc(4);
st=(struct Site *)malloc(sizeof(struct Site));
strcpy(query,getenv("QUERY_STRING"));
strcpy(site,"");
strcpy(page,"1");
strcpy(categorie,"");
strcpy(mois,"");
strcpy(annee,"");
start=0;
for(i=strlen(query)-1;i>=0;i--)
	{
	if(query[i]=='=') start++;
	}
for(i=0;i<start;i++)
	{
	get_chaine2(query,i+1,reponse);
	if(strcmp(reponse,"site")==0) get_chaine(query,i+1,site);
	if(strcmp(reponse,"page")==0) get_chaine(query,i+1,page);
	if(strcmp(reponse,"categorie")==0) get_chaine(query,i+1,categorie);
	if(strcmp(reponse,"mois")==0) get_chaine(query,i+1,mois);
	if(strcmp(reponse,"annee")==0) get_chaine(query,i+1,annee);
	if(strcmp(reponse,"recherche")==0) 
		{
		get_chaine(query,i+1,recherche);
		tamb(recherche);
		}
	}
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
	printf("Content-Type: text/html\n\n\
<!DOCTYPE html>\n\
<html>\n\
<head>\n\
<title>%s</title>\n\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\
<meta charset=\"utf-8\">\n\
<link rel=\"manifest\" href=\"/%s/manifest.json\" />\n\
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
</head>\n",st->titrecomplet,st->titrecourt,st->urlfavicon,st->chemintheme,st->chemintheme);
	printf("<body>\n\
   <div data-role=\"page\" data-theme=\"b\">\n\
      <div data-role=\"header\" data-position=\"fixed\" data-theme=\"b\">\n\
         <div data-role=\"navbar\">\n\
            <ul>\n\
               <li>\n\
                  <form action=\"%s\" method=\"get\" id=\"form-home\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <button type=\"submit\" data-mini=\"false\" data-inline=\"false\" data-theme=\"d\" data-icon=\"recycle\" class=\"ui-shadow\">Accueil</button>\n\
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
	if(strcmp(categorie,"")!=0) 
		{
		sprintf(query,"select nomlong from categorie where site=\'%s\' and nomcourt=\'%s\';",site,categorie);
		db_query(handler,query);
		db_getvalue(result,0,0,reponse,1000);
		db_clear_result(result);
		printf("<p align=\"center\">Catégorie : %s</p>\n",reponse);
		}
	if(strcmp(mois,"")!=0) 
		{
		if(strcmp(mois,"1")==0) strcpy(reponse3,"Janvier");
   	if(strcmp(mois,"2")==0) strcpy(reponse3,"Février");
   	if(strcmp(mois,"3")==0) strcpy(reponse3,"Mars");
   	if(strcmp(mois,"4")==0) strcpy(reponse3,"Avril");
   	if(strcmp(mois,"5")==0) strcpy(reponse3,"Mai");
   	if(strcmp(mois,"6")==0) strcpy(reponse3,"Juin");
   	if(strcmp(mois,"7")==0) strcpy(reponse3,"Juillet");
   	if(strcmp(mois,"8")==0) strcpy(reponse3,"Août");
   	if(strcmp(mois,"9")==0) strcpy(reponse3,"Septembre");
   	if(strcmp(mois,"10")==0) strcpy(reponse3,"Octobre");
   	if(strcmp(mois,"11")==0) strcpy(reponse3,"Novembre");
   	if(strcmp(mois,"12")==0) strcpy(reponse3,"Décembre");
		printf("<p align=\"center\">%s %s</p>\n",reponse3,annee);
		}
	if(strcmp(categorie,"")==0)
		{
		sprintf(query,"select * from article where site=\'%s\'",site);
		if(strcmp(mois,"")!=0)
			{
			sprintf(reponse," and mois=\'%s\'",mois);
			strcat(query,reponse);
			}
		if(strcmp(annee,"")!=0)
			{
			sprintf(reponse," and annee=\'%s\'",annee);
			strcat(query,reponse);
			}
		if(strcmp(recherche,"")!=0)
			{
			sprintf(reponse," and article.contenu like \'%%%s%%\'",recherche);
			strcat(query,reponse);
			}
		strcat(query," order by id desc;");
		}
	else
		{
		sprintf(query,"select article.* from article,categorieallouee where article.site=\'%s\' and categorieallouee.categorie=\'%s\' and categorieallouee.article=article.id",site,categorie);
		if(strcmp(mois,"")!=0)
			{
			sprintf(reponse," and article.mois=\'%s\'",mois);
			strcat(query,reponse);
			}
		if(strcmp(annee,"")!=0)
			{
			sprintf(reponse," and article.annee=\'%s\'",annee);
			strcat(query,reponse);
			}
		strcat(query," order by article.id desc;");
		}
	db_query(handler,query);
	nbarticles=db_ntuples(result);
	if(nbarticles==0 || (atoi(page)-1)*atoi(st->nombreartaccueil)+1>nbarticles)
		{
		printf("Aucun article à afficher<br>\n");
		}
	else
		{
		 printf("<form autocomplete=\"off\" action=\"/cgi-bin/xpresso_accueil.cgi\" method=\"get\" id=\"form-recherche\" data-transition=\"none\" data-rel=\"dialog\">\n\
            <div data-role=\"fieldcontain\">\n\
            	<input type=\"hidden\" name=\"site\" id=\"site\" value=\"%s\">\n\
               <input type=\"text\" name=\"recherche\" id=\"recherche\" value=\"\">\n\
               <input type=\"submit\" data-theme=\"c\" data-mini=\"true\" data-inline=\"true\"  data-icon=\"search\" value=\"Recherche\">\n\
            </div>\n\
      </form>\n\
      <hr>\n",st->titrecourt);
		if(nbarticles-((atoi(page)-1)*atoi(st->nombreartaccueil))>atoi(st->nombreartaccueil)) nbarticleaafficher=atoi(st->nombreartaccueil);
		else nbarticleaafficher=nbarticles-((atoi(page)-1)*atoi(st->nombreartaccueil));
		art=(struct Article **)malloc(nbarticleaafficher*sizeof(struct Article *));
		for(i=0;i<nbarticleaafficher;i++)
			{
			art[i]=(struct Article *)malloc(sizeof(struct Article));
			}
		artdebut=((atoi(page)-1)*atoi(st->nombreartaccueil));
		for(i=0;i<nbarticleaafficher;i++)
			{
			db_getvalue(result,artdebut,0,reponse,1000);
			art[i]->site=(char *)malloc(strlen(reponse)+2);
			strcpy(art[i]->site,reponse);
			db_getvalue(result,artdebut,1,reponse,1000);
			art[i]->titre=(char *)malloc(strlen(reponse)+2);
			strcpy(art[i]->titre,reponse);
			db_getvalue(result,artdebut,2,reponse,1000);
			art[i]->jour=(char *)malloc(strlen(reponse)+2);
			strcpy(art[i]->jour,reponse);
			db_getvalue(result,artdebut,3,reponse,1000);
			art[i]->mois=(char *)malloc(strlen(reponse)+2);
			strcpy(art[i]->mois,reponse);
			db_getvalue(result,artdebut,4,reponse,1000);
			art[i]->annee=(char *)malloc(strlen(reponse)+2);
			strcpy(art[i]->annee,reponse);
			db_getvalue(result,artdebut,5,reponse,1000);
			art[i]->heure=(char *)malloc(strlen(reponse)+2);
			strcpy(art[i]->heure,reponse);
			db_getvalue(result,artdebut,6,reponse,1000);
			art[i]->minute=(char *)malloc(strlen(reponse)+2);
			strcpy(art[i]->minute,reponse);
			db_getvalue(result,artdebut,7,reponse,1000);
			art[i]->urlmiseenavant=(char *)malloc(strlen(reponse)+2);
			strcpy(art[i]->urlmiseenavant,reponse);
			db_getvalue(result,artdebut,8,reponse,20000);
			art[i]->contenu=(char *)malloc(strlen(reponse)+2);
			strcpy(art[i]->contenu,reponse);
			for(j=0;j<strlen(reponse);j++)
				{
				if(art[i]->contenu[j]=='<' && art[i]->contenu[j+1]=='!' && art[i]->contenu[j+2]=='>') art[i]->contenu[j]=0;
				}
			db_getvalue(result,artdebut,9,reponse,1000);
			art[i]->auteur=(char *)malloc(strlen(reponse)+2);
			strcpy(art[i]->auteur,reponse);
			db_getvalue(result,artdebut,10,reponse,1000);
			art[i]->id=(char *)malloc(strlen(reponse)+2);
			strcpy(art[i]->id,reponse);
			artdebut++;
			}
		db_clear_result(result);
		for(i=0;i<nbarticleaafficher;i++)
			{
			printf("<h2>%s</h2>\n",art[i]->titre);
			start=atoi(art[i]->jour);
			magiczero(start,art[i]->jour);
			start=atoi(art[i]->mois);
			magiczero(start,art[i]->mois);
			start=atoi(art[i]->heure);
			magiczero(start,art[i]->heure);
			start=atoi(art[i]->minute);
			magiczero(start,art[i]->minute);
			printf("<h4>Le %s/%s/%s, à %sh%s, par %s</h4>\n",art[i]->jour,art[i]->mois,art[i]->annee,art[i]->heure,art[i]->minute,art[i]->auteur);
			if(strcmp(art[i]->urlmiseenavant,"")!=0) printf("<p><img src=\"%s\" align=\"middle\" style=\"max-width:100%%;\"></p>\n",art[i]->urlmiseenavant);
			printf("%s<br>...<br>",art[i]->contenu);
			sprintf(query,"select site from commentaire where site=\'%s\' and article=\'%s\' and valide='oui';",site,art[i]->id);
			db_query(handler,query);
			if(db_ntuples(result)==0) printf("<p><i>Soyez le premier à commenter cet article</i></p>\n");
			if(db_ntuples(result)==1) printf("<p><i>1 commentaire</i></p>\n");
			if(db_ntuples(result)>1) printf("<p><i>%d commentaires</i></p>\n",db_ntuples(result));
			db_clear_result(result);
         printf("<form action=\"/cgi-bin/xpresso_lire_article.cgi?site=%s&article=%s\" method=\"get\" id=\"form-suite\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <button type=\"submit\" data-theme=\"c\" data-mini=\"true\" data-inline=\"true\" data-icon=\"forward\">Lire l'article</button>\n\
               </form>\n",site,art[i]->id);
         sprintf(query,"select distinct categorie.nomcourt,categorie.nomlong from categorie,categorieallouee where categorieallouee.site=\'%s\' and categorieallouee.article=\'%s\' and categorieallouee.categorie = categorie.nomcourt;",site,art[i]->id);
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
         printf("<hr>\n");
         }
		}
   if(strcmp(st->urlpubaccueil,"")!=0) printf("<p><a href=\"%s\"><img src=\"%s\" align=\"middle\" style=\"max-width:100%%;\"></a></p>\n",st->linkpubaccueil,st->urlpubaccueil);
   strcpy(reponse,"");
   if(strcmp(categorie,"")!=0)
   	{
   	sprintf(reponse3,"&categorie=%s",categorie);
   	strcat(reponse,reponse3);
   	}
   if(strcmp(mois,"")!=0)
   	{
   	sprintf(reponse3,"&mois=%s&annee=%s",mois,annee);
   	strcat(reponse,reponse3);
   	}
   if(strcmp(recherche,"")!=0)
   	{
   	sprintf(reponse3,"&recherche=%s",recherche);
   	strcat(reponse,reponse3);
   	}
   if(atoi(page)>1 && nbarticles>(atoi(page)*atoi(st->nombreartaccueil)))
   	{
   	printf("<form action=\"/cgi-bin/xpresso_accueil.cgi?site=%s%s\" method=\"get\" id=\"form-anciens\" data-transition=\"none\" data-rel=\"dialog\">\n\
            <fieldset data-role=\"controlgroup\" data-type=\"horizontal\">\n\
                <legend>Pages suivante et précédente:</legend>\n\
                <input type=\"submit\" name=\"page\" value=\"%d\" data-theme=\"c\">\n\
                <input type=\"submit\" name=\"page\" value=\"%d\" data-theme=\"c\">\n\
                </fieldset>\n\
            </form>\n",site,reponse,atoi(page)-1,atoi(page)+1);
   	}
   if(atoi(page)>1 && nbarticles<=(atoi(page)*atoi(st->nombreartaccueil)))
   	{
   		printf("<form action=\"/cgi-bin/xpresso_accueil.cgi?site=%s%s\" method=\"get\" id=\"form-anciens\" data-transition=\"none\" data-rel=\"dialog\">\n\
            <fieldset data-role=\"controlgroup\" data-type=\"horizontal\">\n\
                <legend>Page précédente:</legend>\n\
                <input type=\"submit\" name=\"page\" value=\"%d\" data-theme=\"c\">\n\
                </fieldset>\n\
            </form>\n",site,reponse,atoi(page)-1);
   	}
   if(atoi(page)==1 && nbarticles>(atoi(page)*atoi(st->nombreartaccueil)))
   	{
   		printf("<form action=\"/cgi-bin/xpresso_accueil.cgi?site=%s%s\" method=\"get\" id=\"form-anciens\" data-transition=\"none\" data-rel=\"dialog\">\n\
            <fieldset data-role=\"controlgroup\" data-type=\"horizontal\">\n\
                <legend>Page suivante:</legend>\n\
                <input type=\"submit\" name=\"page\" value=\"%d\" data-theme=\"c\">\n\
                </fieldset>\n\
            </form>\n",site,reponse,atoi(page)+1);
   	}
      printf("<br>\n");
      printf("<div class=\"ui-corner-all custom-corners\">\n\
      <div class=\"ui-bar ui-bar-b\">\n\
          <h3>Derniers commentaires :</h3>\n\
      </div>\n\
      <div class=\"ui-body ui-body-b\">\n\
      <p><ul>\n");
      sprintf(query,"select * from commentaire where site=\'%s\' and valide=\'oui\';",site);
      db_query(handler,query);
      nbcommentaires=db_ntuples(result);
      if(nbcommentaires<atoi(st->nombrecommaccueil)) nbcommentairesaafficher=nbcommentaires;
      else nbcommentairesaafficher=atoi(st->nombrecommaccueil);
      comm=(struct Commentaire **)malloc(nbcommentairesaafficher*sizeof(struct Commentaire *));
      for(i=0;i<nbcommentairesaafficher;i++)
      	{
      	comm[i]=(struct Commentaire *)malloc(sizeof(struct Commentaire));
      	}
      for(i=0;i<nbcommentairesaafficher;i++)
      	{
      	j=nbcommentaires-nbcommentairesaafficher+i;
      	//j=i;
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
      	}
      db_clear_result(result);
      for(i=nbcommentairesaafficher-1;i>=0;i--)
      	{
      	sprintf(query,"select titre from article where site=\'%s\' and id=\'%s\';",site,comm[i]->article);
      	db_query(handler,query);
      	db_getvalue(result,0,0,reponse,1000);
      	printf("<li>\n\
            <form action=\"/cgi-bin/xpresso_lire_article.cgi?site=%s&article=%s\" method=\"get\" id=\"form-article\" data-transition=\"none\" data-rel=\"dialog\"> %s sur \
                  <input type=\"submit\" data-theme=\"c\" data-mini=\"true\" data-inline=\"true\" value=\"%s\">\n\
            </form>\n\
         </li>\n",site,comm[i]->article,comm[i]->pseudo,reponse);
         db_clear_result(result);
      	}
      printf("</ul></p>\n\
      </div>\n\
      </div>\n\
      <br><hr>\n");
      if(strcmp(st->urlrss,"")!=0) printf("<form action=\"%s\" method=\"get\" id=\"form-podcast\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"submit\" data-theme=\"d\" data-mini=\"true\" data-inline=\"true\" value=\"Abonne toi au podcast\">\n\
            </form>\n\
      <img src=\"/xpresso/rss.png\"></a>\n<hr>\n",st->urlrss);
	printf("Catégories\n\
      <ul>\n");
	sprintf(query,"select nomlong,nomcourt from categorie where site=\'%s\';",site);
	db_query(handler,query);
	for(i=0;i<db_ntuples(result);i++)
   	{
   	db_getvalue(result,i,0,reponse,1000);
   	db_getvalue(result,i,1,reponse2,100);
   	printf("<li>\n\
            <form action=\"/cgi-bin/xpresso_accueil.cgi?site=%s&categorie=%s\" method=\"post\" id=\"form-categories\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"submit\" data-theme=\"d\" data-mini=\"true\" data-inline=\"true\" value=\"%s\">\n\
            </form>\n\
         </li>\n",site,reponse2,reponse);
   	}
   db_clear_result(result);
   printf("</ul><hr>\n");
   printf("Archives\n\
      <ul>\n");
   sprintf(query,"select distinct mois,annee from article where site=\'%s\' order by annee desc,mois desc;",site);
   db_query(handler,query);
   for(i=0;i<db_ntuples(result);i++)
   	{
   	db_getvalue(result,i,0,reponse,1000);
   	db_getvalue(result,i,1,reponse2,100);
   	if(strcmp(reponse,"1")==0) strcpy(reponse3,"Janvier");
   	if(strcmp(reponse,"2")==0) strcpy(reponse3,"Février");
   	if(strcmp(reponse,"3")==0) strcpy(reponse3,"Mars");
   	if(strcmp(reponse,"4")==0) strcpy(reponse3,"Avril");
   	if(strcmp(reponse,"5")==0) strcpy(reponse3,"Mai");
   	if(strcmp(reponse,"6")==0) strcpy(reponse3,"Juin");
   	if(strcmp(reponse,"7")==0) strcpy(reponse3,"Juillet");
   	if(strcmp(reponse,"8")==0) strcpy(reponse3,"Août");
   	if(strcmp(reponse,"9")==0) strcpy(reponse3,"Septembre");
   	if(strcmp(reponse,"10")==0) strcpy(reponse3,"Octobre");
   	if(strcmp(reponse,"11")==0) strcpy(reponse3,"Novembre");
   	if(strcmp(reponse,"12")==0) strcpy(reponse3,"Décembre");
   	printf("<li>\n\
            <form action=\"/cgi-bin/xpresso_accueil.cgi?site=%s&mois=%s&annee=%s\" method=\"post\" id=\"form-archives\" data-transition=\"none\" data-rel=\"dialog\">\n\
                  <input type=\"submit\" data-theme=\"d\" data-mini=\"true\" data-inline=\"true\" value=\"%s %s\">\n\
            </form>\n\
         </li>\n",site,reponse,reponse2,reponse3,reponse2);
   	}
   db_clear_result(result);
   printf("</ul>\n");
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
	sprintf(query,"insert into vue values (\'%s\',\'0\',\'%s\',\'%s\',\'%s\',\'%s\');",site,jour,Mois,Annee,getenv("REMOTE_ADDR"));
	db_query(handler,query);
	db_clear_result(result);
	}
}