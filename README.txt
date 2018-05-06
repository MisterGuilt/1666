pour lire le projet, il faut installer la sdl 1.2 version 64bits
ainsi que la sdl_ttf permettant de lire le texte 

Cette version affiche le plateau de jeu avec les cartes des joueurs.
On initialise une image par carte
Jai commencé a traiter les touche claviers avec la fonction : EventProcessing()

Je pense que ca suffirat pr le premier rendu, dimanche, j'ai pas eu le temps de faire une interface graphique de demarrage avec un bouton play 
et il faudra traiter par la suite le deplacement des cartes en fonction du tour de chaque joueur et des regles du jeu.

**********************************************************************************************************************************************

1) le jeu affiche le plateau et genere une serie de carte aléatoire 
2) en cliquant sur la 4eme carte du jeu, le joueur choisit de piocher une nouvelle carte 
 => la 4eme carte va dans la defausse et elle est remplacé par une des cartes de la pioche 