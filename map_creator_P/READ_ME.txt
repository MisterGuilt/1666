Pour ajouter un terrain:
	ajoute ton design dans le dossier TerrainsDefinitifs (attention ! tous les fichiers de ce dossier doivent avoir la même taille carrée!) le format .bmp n'est pas obligatoire
	Dans le dossier Terrains ajoute ton design réduit à la taille 25*25 en .bmp
	Dans le fichier constantes.h, modifie la ligne 13 "#define NB_TERRAINS 3" pour qu'il corresponde à ton nombre de terrains
	Modifie aussi la ligne 17 (enum territoires{T_INCONNU};) où tu ajoutes en fin de ligne le type de terrain nommé T_... remplace ... par le nom du terrain
	Dans le fichier main.c, ajoute après la ligne 40 une ligne de format:
		terrains[MON_TYPE_TERRAIN] = SDL_LoadBMP("Terrains/monImage.bmp");

Pour creer une carte:
	lance le programme.
	clique sur créer une nouvelle carte
	Une grille s'affiche:
		les + permettent d'ajouter lignes et colonnes
		les X permettent de supprimer lignes et colonnes jusqu'à la taille minimale
		les flèches permettent de faire glisser l'affichage de la carte
		clique gauche/droit permet de changer le terrain de la case
		clique de roulette sur deux cases permet de sélectionner la zone entre dans un cadre jaune pour appliquer les cliques droits et gauches sur la zone entière, cliquer hors de la zone pour la déselectionner
		cliquer sur save pour enregistrer et quitter le programme, la carte est nommée test.txt
	si la carte ne sera plus modifiée, renommer le fichier test.txt et le transférer dans le dossier Cartes
	sinon relancer le programme et cliquer sur modifier le fichier test.txt