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
char *site;
struct Site *st;
struct Article **art;
time_t tim;
struct tm *TM;
char *jour,*Mois,*Annee,*heures,*minutes,*url;

query=(char *)malloc(strlen(getenv("QUERY_STRING"))+1000);
site=(char *)malloc(strlen(getenv("QUERY_STRING"))+10);
reponse=(char *)malloc(20000);
reponse2=(char *)malloc(100);
reponse3=(char *)malloc(100);
jour=(char*)malloc(4);
Mois=(char*)malloc(4);
heures=(char*)malloc(4);
minutes=(char*)malloc(4);
Annee=(char*)malloc(5);
url=(char*)malloc(500);
st=(struct Site *)malloc(sizeof(struct Site));
strcpy(query,getenv("QUERY_STRING"));
strcpy(site,"");
strcpy(Mois,"");
strcpy(Annee,"");
start=0;
for(i=strlen(query)-1;i>=0;i--)
	{
	if(query[i]=='=') start++;
	}
for(i=0;i<start;i++)
	{
	get_chaine2(query,i+1,reponse);
	if(strcmp(reponse,"site")==0) get_chaine(query,i+1,site);
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
	printf("Content-Type: text/xml\n\n\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<rss version=\"2.0\">\n\
<channel>\n\
<title>%s le podcast</title>\n\
<description>%s le podcast</description>\n\
<language>fr</language>\n\
<link>%s/cgi-bin/xpresso_rss.cgi?site=%s</link>\n\
<image>\n\
<url>%s/%s/rss.png</url>\n\
<title>%s le podcast</title>\n\
<link>%s/cgi-bin/xpresso_rss.cgi?site=%s</link>\n\
<width>32</width>\n\
<height>32</height>\n\
</image>\n",st->titrecomplet,st->titrecomplet,SITE,st->titrecourt,SITE,st->titrecourt,st->titrecomplet, SITE,st->titrecourt);
	sprintf(query,"select * from article where site=\'%s\';",site);
	db_query(handler,query);
	nbarticleaafficher=db_ntuples(result);
	art=(struct Article **)malloc(nbarticleaafficher*sizeof(struct Article *));
	for(i=nbarticleaafficher-1;i>=0;i--)
		{
		art[i]=(struct Article *)malloc(sizeof(struct Article));
		db_getvalue(result,i,1,reponse,1000);
		art[i]->titre=(char *)malloc(strlen(reponse)+2);
		strcpy(art[i]->titre,reponse);
		db_getvalue(result,i,2,reponse,1000);
		art[i]->jour=(char *)malloc(strlen(reponse)+2);
		strcpy(art[i]->jour,reponse);
		db_getvalue(result,i,3,reponse,1000);
		art[i]->mois=(char *)malloc(strlen(reponse)+2);
		strcpy(art[i]->mois,reponse);
		db_getvalue(result,i,4,reponse,1000);
		art[i]->annee=(char *)malloc(strlen(reponse)+2);
		strcpy(art[i]->annee,reponse);
		db_getvalue(result,i,5,reponse,1000);
		art[i]->heure=(char *)malloc(strlen(reponse)+2);
		strcpy(art[i]->heure,reponse);
		db_getvalue(result,i,6,reponse,1000);
		art[i]->minute=(char *)malloc(strlen(reponse)+2);
		strcpy(art[i]->minute,reponse);
		db_getvalue(result,i,10,reponse,1000);
		art[i]->id=(char *)malloc(strlen(reponse)+2);
		strcpy(art[i]->id,reponse);
		if(strcmp(art[i]->mois,"1")==0) strcpy(Mois,"Jan");
		if(strcmp(art[i]->mois,"2")==0) strcpy(Mois,"Feb");
		if(strcmp(art[i]->mois,"3")==0) strcpy(Mois,"Mar");
		if(strcmp(art[i]->mois,"4")==0) strcpy(Mois,"Apr");
		if(strcmp(art[i]->mois,"5")==0) strcpy(Mois,"May");
		if(strcmp(art[i]->mois,"6")==0) strcpy(Mois,"Jun");
		if(strcmp(art[i]->mois,"7")==0) strcpy(Mois,"Jul");
		if(strcmp(art[i]->mois,"8")==0) strcpy(Mois,"Aug");
		if(strcmp(art[i]->mois,"9")==0) strcpy(Mois,"Sep");
		if(strcmp(art[i]->mois,"10")==0) strcpy(Mois,"Oct");
		if(strcmp(art[i]->mois,"11")==0) strcpy(Mois,"Nov");
		if(strcmp(art[i]->mois,"12")==0) strcpy(Mois,"Dec");
		sprintf(reponse,"%s/%s/%s",art[i]->annee,art[i]->mois,art[i]->jour);
		sprintf(url,"%s/cgi-bin/xpresso_lire_article.cgi?site=%s&amp;article=%s",SITE,st->titrecourt,art[i]->id);
		switch(get_weekday(reponse))
         {
         case 0:
         strcpy(jour,"Sun");
         break;
         case 1:
         strcpy(jour,"Mon");
         break;
         case 2:
         strcpy(jour,"Tue");
         break;
         case 3:
         strcpy(jour,"Wed");
         break;
         case 4:
         strcpy(jour,"Thi");
         break;
         case 5:
         strcpy(jour,"Fri");
         break;
         case 6:
         strcpy(jour, "Sat");
         break;
         default:
         strcpy(jour,"");
         break;
         }
		printf("<item>\n\
<title>%s</title>\n\
<link>%s</link>\n\
<description>%s</description>\n\
<pubDate>Tue, %s %s %s %s:%s:00 GMT</pubDate>\n\
</item>\n",art[i]->titre,url,art[i]->titre,art[i]->jour,Mois,art[i]->annee,art[i]->heure,art[i]->minute);
		}
	printf("</channel>\n</rss>\n");
	}
}