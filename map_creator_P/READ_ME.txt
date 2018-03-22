Pour ajouter un terrain:
	ajoute ton design dans le dossier TerrainsDefinitifs (attention ! tous les fichiers de ce dossier doivent avoir la m�me taille carr�e!) le format .bmp n'est pas obligatoire
	Dans le dossier Terrains ajoute ton design r�duit � la taille 25*25 en .bmp
	Dans le fichier constantes.h, modifie la ligne 13 "#define NB_TERRAINS 3" pour qu'il corresponde � ton nombre de terrains
	Modifie aussi la ligne 17 (enum territoires{T_INCONNU};) o� tu ajoutes en fin de ligne le type de terrain nomm� T_... remplace ... par le nom du terrain
	Dans le fichier main.c, ajoute apr�s la ligne 40 une ligne de format:
		terrains[MON_TYPE_TERRAIN] = SDL_LoadBMP("Terrains/monImage.bmp");

Pour creer une carte:
	lance le programme.
	clique sur cr�er une nouvelle carte
	Une grille s'affiche:
		les + permettent d'ajouter lignes et colonnes
		les X permettent de supprimer lignes et colonnes jusqu'� la taille minimale
		les fl�ches permettent de faire glisser l'affichage de la carte
		clique gauche/droit permet de changer le terrain de la case
		clique de roulette sur deux cases permet de s�lectionner la zone entre dans un cadre jaune pour appliquer les cliques droits et gauches sur la zone enti�re, cliquer hors de la zone pour la d�selectionner
		cliquer sur save pour enregistrer et quitter le programme, la carte est nomm�e test.txt
	si la carte ne sera plus modifi�e, renommer le fichier test.txt et le transf�rer dans le dossier Cartes
	sinon relancer le programme et cliquer sur modifier le fichier test.txt