#include "functions.h"

void initialiserFenetre(void){
    //
    // Créé et affiche la fenêtre
    //
    int window_width = (LARG+1+5)*COTECASE;
    int window_height = (LARG+1+5)*COTECASE;
    MLV_create_window( "Jeu de plateau", "hello world", window_width, window_height );

    //Affiche un fond gris
    MLV_draw_filled_rectangle(0, 0, window_width, window_height, MLV_rgba(18, 18, 18, 255));
    //
    // Met a jour l'affichage.
    //
    MLV_actualise_window();

    //
    // Attend 10 secondes avant la fin du programme.
    //
    // MLV_wait_seconds( 1 );

    //
    // Ferme la fenêtre
    //
    // MLV_free_window();
}

/* Fonction qui ne retourne rien et prend en paramètre le monde et qui met la valeur de tous ses pointeurs et les cases du plateau a NULL et le compteur de tours a zero */
void initialiserMonde(Monde *monde){
    int i, j;
    for (i=0; i<LONG; i++) {
        for (j=0; j<LARG; j++) {
            monde->plateau[i][j] = NULL;
        }
    }
    monde->tour = 1;
    monde->rouge = NULL;
    monde->bleu = NULL;
}

/* Fonction qui ne retourne rien prenant en paramètre le monde et qui affiche l’´etat actuel du plateau de jeu (en régime texte) */
void affichePlateau(Monde *monde){
    int i, j, k;
    printf("\n   ");
    for (k = 0; k < LARG; k++) {
        if (k < 10) {
            printf("  %d  ", k);
        } else {
            printf("  %d ", k);
        }
    }
    printf("\n");
    for (i = 0; i < LONG; i++){
        printf("   +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+\n");
        if (i < 10) {
            printf("%d  ", i);
        } else {
            printf("%d ", i);
        }
        
        for (j=0; j<LARG; j++){
            printf("|");
            if (monde->plateau[i][j]) {
                printf(" %c", monde->plateau[i][j]->genre);
                printf("%c ", monde->plateau[i][j]->couleur);
            } else {
                printf("    ");
            }
            /* Lorsqu'on arrive à a fin de la ligne, on ferme la case */
            if (j == LARG-1) {
                printf("|\n");
            }
        }
    }
    printf("   +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+\n\n");

    /* Affichage plateau avec MLV */

    // Affiche Les abscisses à l'écran 
    int spaceX, spaceY;
    char indexX[2], indexY[2];
    for (k = 0; k < LARG; k++) {
        sprintf(indexX, "%d", k);
        if (k<10) {
            spaceX = k*COTECASE + 50;
        } else {
            spaceX = k*COTECASE + 45;
        }
        
        MLV_draw_text(
            spaceX+COTECASE/3, COTECASE/3,
            indexX,
            MLV_COLOR_GREY
        );
    }
    //Affiche les cases
    MLV_Color background_color;
    for (i = 0; i < LONG; i++){

        //Affiche les ordonnées
        if (i<10) {
            sprintf(indexY, " %d", i);
        } else {
            sprintf(indexY, "%d", i);
        }
        
        spaceY = i*COTECASE + 50;
        MLV_draw_text(
            COTECASE/3, spaceY+COTECASE/3,
            indexY,
            MLV_COLOR_GREY
        );
        
        for (j=0; j<LARG; j++){
            if (monde->plateau[i][j]) {
                if (monde->plateau[i][j]->couleur == BLEU) {
                    background_color = MLV_COLOR_SKYBLUE3;
                } else if (monde->plateau[i][j]->couleur == ROUGE) {
                    background_color = MLV_rgba(240,70,70,255);
                }
            } else {
                background_color = MLV_COLOR_GREY;
            }

            MLV_draw_filled_rectangle(j*COTECASE + 40, i*COTECASE + 40, COTECASE, COTECASE, background_color);
            MLV_draw_rectangle(j*COTECASE + 40, i*COTECASE + 40, COTECASE, COTECASE, MLV_COLOR_BLACK);
        }
    }

    //void MLV_draw_rectangle (int x, int y, int width, int height, MLV_Color color);
    MLV_actualise_window();
}

/* Fonction qui retourne un entier servant à la gestion d'erreur et prend en paramètre un type et une liste d'unité et alloue une nouvelle unite de type type, et stocke son adresse dans *unite */
int creerUnite(char type, UListe * unite){
    Unite *u;
    u = malloc(sizeof(Unite));
    if (u == NULL) {
        printf("Erreur d'allocation\n");
        exit(EXIT_FAILURE);
    }
    u->genre = type;
    u->suiv = NULL;
    *unite = u;
    return 1;
}
  
/* Fonction qui ne retourne rien et prend en parametre une unite, sa couleur et le monde et qui permet à l'utilisateur d'entrer ses coordonnées en début de partie */
void positionnerUnite(Unite *unite, Monde *monde, char couleur){
    int posX, posY;
    char message[200];
    affichePlateau(monde);
    do {
        sprintf(message, "Positionnement de l'unité : %c%c", unite->genre, couleur);
        ecrireMessage(message);
        printf("Positionnement de l'unité : %c%c\n", unite->genre, couleur);
        printf("Entrez la position X suivie de la position Y : \n");
        scanf(" %d %d", &posX, &posY);
        /* Si les coordonnées sont invalides, la fonction retourne -1 */
        if (posX < 0 || posX > 17 || posY < 0 || posY > 11) {
            printf("Coordonnées invalides\nRecommencez svp\n");
        } else if (monde->plateau[posY][posX]) { /* Si la case marquée par les coordonnées est déjà occupée par une unité, la fonction retourne -2 */
            printf("Case déjà occupée\nRecommencez svp\n");
        }
    } while ((posX < 0 || posX > 17 || posY < 0 || posY > 11) || (monde->plateau[posY][posX]));
    placerAuMonde(unite, monde, posX, posY, couleur);
    printf("L'unité %c%c à été placée en (%d, %d)\n", unite->genre, couleur, posX, posY);
}

/* Fonction qui retourne un entier permettant la gestion d'erreur et prend en paramètre une unité, les coordonnées auxquelles la placer, sa couleur et le monde. Elle place une unité qui vient d’être créée à la position souhaitée dans le monde sous le contrôle de son nouveau maître */
int placerAuMonde(Unite *unite, Monde *monde, int posX, int posY, char couleur){
    Unite *tmp = malloc(sizeof(Unite));
    if (tmp == NULL) {
        printf("Erreur d'allocation");
        exit(EXIT_FAILURE);
    }
    unite->posX = posX;
    unite->posY = posY;
    unite->couleur = couleur;
    tmp = unite;
    if (tmp->couleur == ROUGE) {
        if (monde->rouge != NULL) {
            tmp->suiv = monde->rouge;
        }
        monde->rouge = tmp;
    }
    else {
        if (monde->bleu != NULL) {
            tmp->suiv = monde->bleu;
        }
        monde->bleu = tmp;
    }
    if (monde->plateau[posY][posX] != NULL){
        printf("Case déjà occupée\n");
        return 0;
    } else {
        monde->plateau[posY][posX] = tmp;
        return 1;
    }
}

/* Fonction qui ne retourne rien et prend en paramètre une unité, les coordonnées du déplacement et le monde et qui déplace une unité vers une case spécifiée par les coordonnées */
void deplacerUnite(Unite *unite, Monde *monde, int destX, int destY) {
    monde->plateau[unite->posY][unite->posX] = NULL;
    unite->posX = destX;
    unite->posY = destY;
    monde->plateau[unite->posY][unite->posX] = unite;
}

/* Fonction qui ne retourne rien et prend en paramètre une unité et le monde et qui enlève l’unité du jeu (l'enlève donc du plateau et de la liste des unités et libère la mémoire) */
void enleverUnite(Unite *unite, Monde *monde) {
    monde->plateau[unite->posY][unite->posX] = NULL;
    if (unite->couleur == ROUGE){
        if (unite == monde->rouge){
            Unite *tmp = monde->rouge;
            monde->rouge = monde->rouge->suiv;
            free(tmp);
        }
        else{
            Unite *tmp = monde->rouge->suiv;
            Unite *prev = monde->rouge;
            while (unite != tmp){
                prev = tmp;
                tmp = tmp->suiv;
            }
            prev->suiv = tmp->suiv;
            free(tmp);
        }
    }
    if (unite->couleur == BLEU){
        if (unite == monde->bleu){
            Unite *tmp = monde->bleu;
            monde->bleu = monde->bleu->suiv;
            free(tmp);
        }
        else{
            Unite *tmp = monde->bleu->suiv;
            Unite *prev = monde->bleu;
            while (unite != tmp){
                prev = tmp;
                tmp = tmp->suiv;
            }
            prev->suiv = tmp->suiv;
            free(tmp);
        }
    }
    afficherListes(*monde);
}

/* Fonction qui retourne un paramètre indiquant le résultat du combat et qui prend en paramètre une unité, les coordonnées da l'attaque et qui qui gère le combat selon les règles du jeu (.cf sujet) */
int attaquer(Unite *unite, Monde *monde, int posX, int posY) {
    Unite *attaquant = unite;
    Unite *defenseur = monde->plateau[posY][posX];
    if (attaquant->genre == defenseur->genre) {
        printf("Le défenseur (%c%c) perd (Les deux sont du même type)\n", defenseur->genre, defenseur->couleur);
        enleverUnite(defenseur, monde);
        return 1;
    } else if ((attaquant->genre == SERF) & (defenseur->genre == GUERRIER)) {
        printf("L'attaquant (%c%c) perd (le défenseur est de meilleur type)\n", attaquant->genre, attaquant->couleur);
        enleverUnite(attaquant, monde);
        return 0;
    } else if ((attaquant->genre == GUERRIER) & (defenseur->genre == SERF)) {
        printf("Le défenseur (%c%c) perd (l'attaquant est de meilleur type)\n", defenseur->genre, defenseur->couleur);
        enleverUnite(defenseur, monde);
        return 1;
    }
    return 0;
}

/* Fonction qui retourne un entier en paramètre pour la gestion d'erreur et au resultat et qui prend en paramètre une unité, les coordonnées de l'action et le monde et qui qui gère le déplacements et le combat */
int deplacerOuAttaquer(Unite *unite, Monde *monde, int destX, int destY) {
    /* Si les coordonnées sont invalides, la fonction retourne -1 */
    if (destX < 0 || destX > 17 || destY < 0 || destY > 11) {
        return -1;
    }
    /* Si la case marquée par les coordonnées n'est pas voisine à celle où l’unité en question se trouve, la fonction retourne -2 */
    if (destX > unite->posX + 1 || destX < unite->posX - 1 || destY > unite->posY + 1 || destY < unite->posY - 1 ) {
        return -2;
    }
    /* Si la case marquée par les coordonnées est déjà occupée par une unité alliée, la fonction retourne -3 */
    if (monde->plateau[destY][destX]) {
        if (monde->plateau[destY][destX]->couleur == unite->couleur) {
            return -3;
        }
    }
    /*  Si la case destination est vide, valide et adjacente, l’unité se déplace.
        Si la case de destination est valide, adjacente, et occupée par un ennemi, un combat prend lieu. 
        La fonction retourne 2 si l'attaquant a gagné ou 3 s'il a perdu */
    if (monde->plateau[destY][destX] == NULL) {
        deplacerUnite(unite, monde, destX, destY);
        printf("L'unité s'est deplacée\n");
        return 1;
    } else {
        /*  Un ennemi a été rencontré */
        if (attaquer(unite, monde, destX, destY) == 1) {
            printf("Victoire de l'attaquant\n");
            return 2;
        } else {
            printf("Défaite de l'attaquant\n");
            return 3;
        }
    }
}

/* Fonction qui ne retourne rien et prend en paramètre le joueur et le monde et qui gère toutes les actions d’un joueur pendant son tour */
void gererDemiTour(char joueur, Monde *monde) {
    /* Parcourir les unités du joueur */
    int choix, x, y, i, j;
    char finDeTour;
    UListe liste;
    
    if (joueur == 'B') {
        liste = monde->bleu;
    } else if (joueur == 'R') {
        liste = monde->rouge;
    }
    if(liste != NULL){
        printf("C'est le tour N°%d du joueur %c.\n", monde->tour, joueur);
        affichePlateau(monde);
        Unite *actuel = liste;
        while(actuel != NULL) {
            printf("Unité actuelle : %c%c, (%d, %d)\n", actuel->genre, actuel->couleur, actuel->posX, actuel->posY);
            printf("Que souhaitez-vous faire ? (1 : Déplacer/Attaquer, 2 : Ne rien faire)\n");
            for (i = -1; i <= 1; ++i)
            {
                for (j = -1; j <= 1; ++j)
                {
                    if (monde->plateau[actuel->posY + j][actuel->posX + i] == NULL)
                    {
                        MLV_draw_filled_rectangle((actuel->posX*COTECASE) + (i*COTECASE + 40), (actuel->posY*COTECASE) + (j*COTECASE + 40), COTECASE, COTECASE, MLV_COLOR_LIGHT_SEA_GREEN);
                        MLV_draw_rectangle((actuel->posX*COTECASE) + (i*COTECASE + 40), (actuel->posY*COTECASE) + (j*COTECASE + 40), COTECASE, COTECASE, MLV_COLOR_BLACK);
                    }
                }
            }
            MLV_actualise_window();
            scanf(" %d", &choix);
            if (choix == 1) {
                printf("L'utilisateur souhaite se déplacer ou attaquer.\n");
                printf("Veuillez entrer les coordonnées x et y:\n");
                scanf(" %d %d", &x, &y);
                if (deplacerOuAttaquer(actuel, monde, x, y) < 0){
                    printf("Ordre non valide, on passe à l'unité suivante\n");
                }
                actuel = actuel->suiv;
            } else if (choix == 2) {
                printf("L'utilisateur ne veux rien faire, on passe à l'unité suivante.\n");
                actuel = actuel->suiv;
            }
            affichePlateau(monde);
        }
        do {
            printf("Veuillez indiquer la fin du tour (f)\n");
            scanf(" %c", &finDeTour);
        } while (finDeTour != 'f');
        printf("Le tour du joueur %c est terminé.\n", joueur);
    }
}

/* Fonction qui ne retourne rien et prend en paramètre le monde et qui gère un tour de jeu complet */
void gererTour(Monde *monde){
    char joueur1 = BLEU; /* Déclaration et initialisation du joueur bleu */
    char joueur2 = ROUGE; /* Déclaration et initialisation du joueur rouge */
    gererDemiTour(joueur1, monde); /* Tour du joueur 1 */
    gererDemiTour(joueur2, monde); /* Tour du joueur 2 */
    monde->tour+=1; /* Incrémentation du compteur de tours */
}

/* Fonction qui ne retourne rien et prend en paramètre le monde et qui le réinitialise et vide proprement la mémoire utilisée par les unités notamment */
void viderMonde(Monde *monde){
    /* Vide la mémoire de toutes les unités de la liste rouge du monde */
    while (monde->rouge != NULL){
        Unite *tmp = monde->rouge;
        monde->rouge = monde->rouge->suiv;
        free(tmp);
    }
    /* Vide la mémoire de toutes les unités de la liste bleue du monde */
    while (monde->bleu != NULL){
        Unite *tmp = monde->bleu;
        monde->bleu = monde->bleu->suiv;
        free(tmp);
    }
    /* réinitialise le monde */
    initialiserMonde(monde);
}

/* Fonction qui ne retourne rien et ne prend pas de paramètre et qui gère une partie de jeu */
void gererPartie(void){
    Monde monde; /* Déclaration du monde */
    int arreterPartie;
    arreterPartie = 0;
    Unite *u1, *u2, *u3, *u4, *u5, *u6; /* Déclaration des unités */
    //Unite *u1, *u4; /* Déclaration des unités */
    initialiserMonde(&monde); /* Initialisaton du monde */
    
    /* Création et placement des unités bleues */
    creerUnite(GUERRIER, &u1);
    creerUnite(SERF, &u2);
    creerUnite(SERF, &u3);
    positionnerUnite(u1, &monde, BLEU);
    positionnerUnite(u2, &monde, BLEU);
    positionnerUnite(u3, &monde, BLEU);
    
    /* Création et placement des unités rouges */
    creerUnite(GUERRIER, &u4);
    creerUnite(SERF, &u5);
    creerUnite(SERF, &u6);
    positionnerUnite(u4, &monde, ROUGE);
    positionnerUnite(u5, &monde, ROUGE);
    positionnerUnite(u6, &monde, ROUGE);
    do {
        gererTour(&monde);
        if (monde.rouge == NULL || monde.bleu == NULL) {
            arreterPartie = 1;
        } else {
            do {
                printf("Voulez vous arrêter la partie sans vainqueur ? (0: Non / 1: Oui)\n");
                scanf(" %d", &arreterPartie);
            } while (arreterPartie != 0 && arreterPartie != 1);
        }
    } while ((monde.rouge != NULL && monde.bleu != NULL) && arreterPartie == 0);
    
    if (monde.rouge == NULL) {
        printf("Vainqueur : Joueur Bleu\n");
    } else if (monde.bleu == NULL) {
        printf("Vainqueur : Joueur Rouge\n");
    } else {
        printf("Égalité\n");
    }
    viderMonde(&monde);
}

/* Fontion qui ne retourne rien et prend en paramètre le monde et affiche le contenu des listes des deux joueurs (Très utile pour le débugage des fonctions liées aux listes) */
void afficherListes(Monde monde){
    printf("Liste bleu : \n");
    if(monde.bleu != NULL){
        Unite *actuel = monde.bleu;
        while(actuel != NULL) {
            printf("%c %c\n", actuel->genre, actuel->couleur);
            actuel = actuel->suiv;
        }
    }
    printf("Liste rouge : \n");
    if(monde.rouge != NULL){
        Unite *actuel = monde.rouge;
        while(actuel != NULL) {
            printf("%c %c\n", actuel->genre, actuel->couleur);
            actuel = actuel->suiv;
        }
    }
}

void ecrireMessage(char message[]){
    MLV_draw_filled_rectangle(45, 550, 500, 100, MLV_COLOR_GREY);
    MLV_draw_rectangle(45, 550, 500, 100, MLV_COLOR_WHITE);
    MLV_draw_text(55, 560, message, MLV_COLOR_BLACK);
    MLV_actualise_window();
}