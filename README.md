# xpresso
CMS multi-sites auto-hébergé

XPresso est un CMS (Content Management System), c'est à dire un équivalent simple de Wordpress, permettant d'auto-héberger plusieurs sites web sur un même serveur NginX, et prévu pour afficher les sites principalement sur smartphones.

J'ai programmé ce logiciel pour répondre à mes besoins.

Techniquement, il s'agit d'une webapp installable n'importe quel OS (Windows, Linux, Mac, iOS, Android), mais prévue pour fonctionner surtout sous iOS ou Android. Le front end est programmé en HTML 5 + toolkit javascript JQuery Mobile. Le back end est constitué de scripts CGI écrits en langage C, traitant les données en interface avec une base de données MySQL ou MariaDB.

La webapp est constituée de 2 parties distinctes : le moteur de gestion des sites, et les sites auto-hébergés eux-mêmes qu'on rajoute ensuite par dessus.

<strong><u>Installation</u></strong>

Sur un serveur Linux, installer NginX, activer le https sur votre domaine, et <a href="https://techexpert.tips/nginx/nginx-shell-script-cgi/">activez les scripts CGI</a> sur votre serveur NginX

Installez xpresso dans /home/votre_repertoire/xpresso

Intégrez votre xpresso dans votre serveur web :
sudo ln -s /home/votre_repertoire/xpresso /var/www/html/xpresso

Installez JQuery Mobile dans /var/www/html/jq :
sudo cp jq.tgz /var/www/html
cd /var/www/html
sudo tar -zxvf ./jq.tgz

Désormais votre webapp est accessible à l'URL : https://votre_serveur/xpresso

Installez qrencode pour être en mesure de générer les QR codes nécessaires pour le 2FA Google Authenticator:
sudo apt-get install qrencode

Il faut maintenant préparer la base de données MySQL :
cd /home/votre_repertoire/xpresso/build
mysql -u root -p mysql
create database xpresso;
create user 'xpresso'@'localhost' identified by 'votre_mot_de_passe';
grant all privileges on xpresso.* to 'xpresso'@'localhost';
quit

mysql -u xpresso -p xpresso
source ./install_mysql_tables.sql;
quit

Avant de compiler les scripts CGI, il faut leur indiquer le mot de passe choisi pour l'utilisateur xpresso dans MySQL ainsi que l'URL du serveur sur Internet:
cd /home/votre_repertoire/xpresso/src
Renseigner le mot de passe MySQL que vous avez choisi dans password.h
Renseigner l'URL de votre serveur sur Internet dans specific.c

Il faut maintenant compiler les scripts CGI :
sudo apt install libmysqlclient-dev
cd /home/votre_repertoire/xpresso/src
sudo mkdir /usr/lib/cg-bin
chmod a+x compile*
sudo ./compile.mysql

Si vous utilisez MariaDB plutôt que MySQL compilez à la place par :
sudo ./compile.mariadb

Une fois que les scripts sont compilés et apparus dans /usr/lib/cgi-bin, il faut effacer par sécurité tous les fichiers présents dans /home/votre_repertoire/xpresso/src :
cd /home/votre_repertoire/xpresso/src
rm * (vérifiez bien d'être dans le bon répertoire avant de taper cela !!!)

Voilà, le produit est installé et paramétré. Reste à y déclarer des sites webs

Mais avant tout, connectez vous avec le login Admin et le mot de passe admin, puis changez le mot de passe admin depuis l'interface web

<strong><u>Créer un site web (blog)</u></strong>

Pour créer un site (on peut en créer autant qu'on en veut sur le même serveur), par exemple "monblog" il faut d'abord lui créer un répertoire d'accueil :
cd /home/votre_repertoire/xpresso
cp -R votre_site monblog
sudo ln -s /home/votre_repertoire/xpresso/monblog /var/www/html/monblog

Votre blog sera désormais accessible à l'URL : https://votre_serveur/monblog

Le fichier /home/votre_repertoire/xpresso/monblog/index.html contient une redirection qu'il faut paramétrer comme suit pour "monblog":
<meta http-equiv=Refresh Content="0; Url=/cgi-bin/xpresso_accueil.cgi?site=monblog">

Il faut ensuite déclarer le site dans la base MySQL, ainsi qu'au moins 1 auteur sur ce site (chaque site aura ses propres auteurs) :
mysql -u xpresso -p xpresso
insert into site values ('Mon site','monsite','/cgi-bin/xpresso_accueil.cgi?site=monblog','/xpresso/monblog/monblog.png','/xpresso/monblog/apropos.html','/cgi-bin/xpresso_rss.cgi?site=monblog','','','','',5,7,'(C) Mon blog 2024','/xpresso/monblog/themes');
insert into auteur values ('Mon pseudo','mon_mot_de_passe','monblog','oui','','');
quit

Ceci n'est à faire qu'une seule fois pour chaque site créé

Ne pas oublier de mettre une favicon pour votre blog dans /home/votre_repertoire/xpresso/monblog/monblog.png

Tout le reste du paramétrage de votre blog se fait sur l'URL https://votre_serveur/xpresso/xpresso_login.html. Vous pouvez y créer des catégories, d'autres auteurs, poster ou modifier des articles, etc.

Le theme par défaut de votre site peut être modifié dans Theme Roller (<a href="https://themeroller.jquerymobile.com/">https://themeroller.jquerymobile.com/</a>) : mettre le theme de votre cru dans /home/votre_repertoire/xpresso/monblog/themes

Vous pouvez aussi conserver le theme que je fournis par défaut.

Vous pouvez être prévenu par une notification sur votre téléphone Android dès qu'un lecteur commente un des articles de votre blog. Pour cela créez un compte gratuit sur Ntfy (<a href="https://ntfy.sh/">https://ntfy.sh/</a>) et abonnez vous à un salon dont vous créez le nom dans l'application Android Ntfy disponible (<a href="https://play.google.com/store/apps/details?id=io.heckel.ntfy">Sur Google Play</a>). Choisissez un nom de salon compliqué que vous serez le seul à connaitre. Ensuite modifiez le fichier /home/votre_repertoire/xpresso/monblog/commentaire_recu en y mettant le nom de votre salon dans l'URL :
/usr/bin/curl -d "Commentaire reçu sur votre site monblog" https://ntfy.sh/votre_adresse_ntfy

Mettez ce que vous voulez dans /home/votre_repertoire/xpresso/monblog/apropos.html pour vous présenter

alain.quemeneur@gmail.com