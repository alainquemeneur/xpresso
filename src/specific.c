#define SITE "https://votre_site"

struct Site
{
char *titrecomplet, *titrecourt, *urlaccueil, *urlfavicon, *urlapropos, *urlrss, *urlpubaccueil, *linkpubaccueil, *urlpubarticle, *linkpubarticle, *nombrecommaccueil, *nombreartaccueil, *copyright, *chemintheme;
};

struct Article
{
char *site, *titre, *jour, *mois, *annee, *heure, *minute, *urlmiseenavant, *contenu, *auteur, *id;
};

struct Commentaire
{
char *site, *article, *pseudo, *email, *urlavatar, *horodatage, *contenu, *valide;
};

struct Vue
{
int lectures, lecteurs;
};
