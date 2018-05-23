# 1666

Un jeu de cartes basé sur des dates historiques avec pour but d'implémenter une IA pouvant choisir entre différentes stratégies.

Interface console:

Cette interface basique permet de jouer au jeu contre une IA.

Règles:
- Il y a 14 figures avec une date associée. L'objectif est de reconstituer la date de la figure pour gagner des points
- Chaque tour, le joueur peut piocher (et défausser une carte), prendre la derniére carte défaussée, valider une main, etc
- Les jokers peuvent correspondre a toutes les dates
- Il existe des dates maudites (les dates de 1315 à 1915 se finissant en 15) faisant perdre des points a l'adversaire. Le joker amplifie leur effet
- Obtenir 1666 avec le joker permet de gagner la partie. Sinon, il faut que toutes les figures soient épuisées
- On peut changer de figure 2 fois au début. On gagne un changement lorsque l'on valide une main
- Il y a trois attaques spéciales:
	*Perturbation: Change de place deux cartes dans le jeu adverse. Necessite 3 couleurs identiques
	*Echange: Echange une carte de son jeu avec l'ennemi. Necessite un valet et deux cartes de couleur correspondante
	*Assassinat: Defausse une carte chiffre de l'adversaire. Necessite deux paires de couleurs
-Les attaques speciales ont un cooldown partagé de 2 tours

Pour activer le mode diagnostic qui montre plus en détail les choix de l'IA, il faut changer la valeur booléene dans le constructeur.
Pour créer un scénario prédéfini pour tester l'IA, il faut modifier le bloc en commentaire dans le fichier principal.

Pour la compilation, il se peut qu'il faut mettre tous les fichiers dans un projet d'IDE tel que CodeBlocks.

Interface graphique:

Cette interface n'est pas encore reliée au jeu.
Elle permet de tester la défausse (cliquer sur la 4éme carte) et l'échange des cartes cachées (cliquer sur les cartes 3 et 4)

Pour compiler l'interface graphique, il faut avoir installé la SDL 1.2 (64 bits) et les plugins SDL_ttf et SDL_mixer

Compilateur utilisé: minGW/GNU GCC avec comme options:

Flags:
-std=c++11

Linker settings:
-lmingw32
-lSDLmain
-lSDL
-lSDL_ttf
-lSDL_mixer

Si problème avec to_string lors de la compilation, il existe un patch: http://tehsausage.com/mingw-to-string