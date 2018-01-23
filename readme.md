#Jeu de plateau en c

### Améliorations intéressantes à faire :

- [x] A chaque tour, choisir à l’aléatoire le joueur qui joue en premier.
- [x] Ajouter un système de points d'attaque / défense / vie (avec à chaque attaque ou défense une valeur fixe +- une petite valeur aléatoire)
- [x] Ajouter la possibilité de gérer les points de mouvement. Les serviteurs et les guerriers pourront désormais se déplacer de jusqu’à deux cases
- [x] Rajouter une unité Reine qui peut produire des unités (avec limite max d'unité et donc une valeur pour chaque unité ex serf : 1 et guerrier : 2)
- [x] Permettre de se déplacer puis d'attaquer
- [x] Permettre aux joueurs de faire attendre les unités et de reprendre leur action plus tard (passer le tour de l'unité et revenir ensuite)
- [ ] Sauvegarder la partie en cours dans un fichier pour pouvoir la reprendre plus tard (cf. sujet)

### Implémenter une interface graphique avec MLV :
- [x] Ajouter des images pour les différentes unités
- [x] Penser à libérer les images `MLV_free_image( image );` à la suppression du perso ?
- [x] Cliquer sur les cases pour se positionner.
- [x] Cliquer sur les cases pour se déplacer et attaquer.
- [x] Fin du tour : Bouton Continuer / Arrêter.
- [x] Changer la couleur des cases lorsqu'on passe la souris dessus.
- [x] Afficher tous les textes dans le carré d'affichage
- [x] Guerrier : 2 cases de portées autour
- [x] Afficher le compteur de tours
- [x] Afficher les images dans la liste des unités


A FAIRE AMELIO : 
- FINIIIIIR LEEEE RAPPOOOOOORRTT !!!!!!!!!
- (Savoir si on chosit la case dans tout le plateau ou nom pour la prod d'unité)
- Faire apparaître à chaque action les "cases contours" possibles
afficher la vie et les dégâts
- A chaque action possibilité de passer l'action
- Afficher les compteurs de tour pour la production d'unité
- Fin de la partie : QUand plus de reine dans une des deux listes

- Recheck l'expérience de jeu et rajouter pleins d'infos pour aider le joueur à savoir quoi faire

- Vérifier le code (commentaire, virer les printf etc...)

- Commenter les fonctions dans les fichiers en-tête