#include "functions.h"

void initialiserFenetre(void){
    
    /* Créé et affiche la fenêtre */
    int window_width = (LARG+1+5)*COTECASE;
    int window_height = (LARG+1+5)*COTECASE;
    MLV_create_window( "Jeu de plateau", "hello world", window_width, window_height );

    /* Affiche un fond gris */
    MLV_draw_filled_rectangle(0, 0, window_width, window_height, MLV_rgba(18, 18, 18, 255));

    /* Met a jour l'affichage de la fenêtre. */
    MLV_actualise_window();

}

/* Fonction qui ne retourne rien et prend en paramètre le monde et qui met la valeur de tous ses pointeurs et les cases du plateau à NULL et le compteur de tours a zéro */
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

/* Fonction qui ne retourne rien prenant en paramètre le monde et qui affiche l’état actuel du plateau de jeu (à l'aide de la bibliothèque MLV) */
void affichePlateau(Monde *monde){
    int i, j, k;
    int spaceX, spaceY;
    char indexX[2], indexY[2];
    MLV_Color background_color;
    MLV_Image *guerrier_rouge_img, *guerrier_bleu_img, *serf_rouge_img, *serf_bleu_img;

    // Affiche Les abscisses à l'écran 
    for (k = 0; k < LARG; k++) {
        sprintf(indexX, "%d", k);
        if (k<10) {
            spaceX = k*COTECASE + ESPACE + COTECASE/3;
        } else {
            spaceX = k*COTECASE + ESPACE - 5 + COTECASE/3;
        }
        
        MLV_draw_text(
            spaceX, ESPACE/3,
            indexX,
            MLV_COLOR_GREY
        );
    }

    //Charge les images
    guerrier_rouge_img = MLV_load_image( "img/guerrier_rouge.png" );
    guerrier_bleu_img = MLV_load_image( "img/guerrier_bleu.png" );
    serf_rouge_img = MLV_load_image("img/serf_rouge.png");
    serf_bleu_img = MLV_load_image("img/serf_bleu.png");
    MLV_resize_image_with_proportions( guerrier_rouge_img, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( guerrier_bleu_img, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( serf_rouge_img, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( serf_bleu_img, COTECASE, COTECASE );

    //Affiche les cases
    for (i = 0; i < LONG; i++){

        //Affiche les ordonnées
        if (i<10) {
            sprintf(indexY, " %d", i);
        } else {
            sprintf(indexY, "%d", i);
        }
        
        spaceY = i*COTECASE + ESPACE + COTECASE/3;
        MLV_draw_text(
            ESPACE/3, spaceY,
            indexY,
            MLV_COLOR_GREY
        );
        
        for (j = 0; j < LARG; j++){

            background_color = MLV_COLOR_WHITE;
            
            MLV_draw_filled_rectangle(j*COTECASE + ESPACE, i*COTECASE + ESPACE, COTECASE, COTECASE, background_color);
            MLV_draw_rectangle(j*COTECASE + ESPACE, i*COTECASE + ESPACE, COTECASE, COTECASE, MLV_COLOR_BLACK);
            if (monde->plateau[i][j]) {
                if (monde->plateau[i][j]->genre == GUERRIER) {
                    if (monde->plateau[i][j]->couleur == BLEU) {
                        MLV_draw_image( guerrier_bleu_img, j*COTECASE + ESPACE, i*COTECASE + ESPACE );
                    } else if (monde->plateau[i][j]->couleur == ROUGE) {
                        MLV_draw_image( guerrier_rouge_img, j*COTECASE + ESPACE, i*COTECASE + ESPACE );
                    }
                } else if (monde->plateau[i][j]->genre == SERF) {
                    if (monde->plateau[i][j]->couleur == BLEU) {
                        MLV_draw_image( serf_bleu_img, j*COTECASE + ESPACE, i*COTECASE + ESPACE );
                    } else if (monde->plateau[i][j]->couleur == ROUGE) {
                        MLV_draw_image( serf_rouge_img, j*COTECASE + ESPACE, i*COTECASE + ESPACE );
                    }

                }
            }
        }
    }

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
    int posX, posY, mouseX, mouseY, x, y, i, j;
    MLV_Image *guerrier_rouge_img, *guerrier_bleu_img, *serf_rouge_img, *serf_bleu_img;
    MLV_Event event;
    char message[200];

    //Charge les images
    guerrier_rouge_img = MLV_load_image( "img/guerrier_rouge.png" );
    guerrier_bleu_img = MLV_load_image( "img/guerrier_bleu.png" );
    serf_rouge_img = MLV_load_image("img/serf_rouge.png");
    serf_bleu_img = MLV_load_image("img/serf_bleu.png");
    MLV_resize_image_with_proportions( guerrier_rouge_img, COTECASE, COTECASE);
    MLV_resize_image_with_proportions( guerrier_bleu_img, COTECASE, COTECASE);
    MLV_resize_image_with_proportions( serf_rouge_img, COTECASE, COTECASE);
    MLV_resize_image_with_proportions( serf_bleu_img, COTECASE, COTECASE);

    affichePlateau(monde);
    do {
        sprintf(message, "Positionnement de l'unité : %c%c", unite->genre, couleur);
        ecrireMessage(message);

        do {
            event = MLV_MOUSE_MOTION;
            do {
                event = MLV_get_event( 
                        NULL, NULL, NULL,
                        NULL, NULL,
                        &x, &y, NULL,
                        NULL
                );
                if( event == MLV_MOUSE_MOTION ){
                    for (i = 0; i < LONG; i++){
                        for (j = 0; j < LARG; j++){
                            if ((x>ESPACE) && (x < LARG * COTECASE + ESPACE) && (y>ESPACE) && (y < LONG * COTECASE + ESPACE))
                            {
                                if (monde->plateau[i][j] == NULL) {
                                    MLV_draw_filled_rectangle(j*COTECASE + ESPACE, i*COTECASE + ESPACE, COTECASE, COTECASE, MLV_COLOR_WHITE);
                                }
                                MLV_draw_rectangle(j*COTECASE + ESPACE, i*COTECASE + ESPACE, COTECASE, COTECASE, MLV_COLOR_BLACK);
                                MLV_draw_rectangle(j*COTECASE + ESPACE -1, i*COTECASE + ESPACE-1, COTECASE+2, COTECASE+2, MLV_COLOR_BLACK);
                                if (monde->plateau[((y-ESPACE)/COTECASE)][((x-ESPACE)/COTECASE)] == NULL) {
                                    if (couleur == BLEU) {
                                        if (unite->genre == GUERRIER)
                                        {
                                            MLV_draw_image( guerrier_bleu_img, ((x-ESPACE)/COTECASE)*COTECASE + ESPACE, ((y-ESPACE)/COTECASE)*COTECASE + ESPACE );
                                        } else {
                                            MLV_draw_image( serf_bleu_img, ((x-ESPACE)/COTECASE)*COTECASE + ESPACE, ((y-ESPACE)/COTECASE)*COTECASE + ESPACE );
                                        }
                                    } else if (couleur == ROUGE) {
                                        if (unite->genre == GUERRIER)
                                        {
                                            MLV_draw_image( guerrier_rouge_img, ((x-ESPACE)/COTECASE)*COTECASE + ESPACE, ((y-ESPACE)/COTECASE)*COTECASE + ESPACE );
                                        } else {
                                            MLV_draw_image( serf_rouge_img, ((x-ESPACE)/COTECASE)*COTECASE + ESPACE, ((y-ESPACE)/COTECASE)*COTECASE + ESPACE );
                                        }
                                    }
                                    MLV_draw_filled_rectangle(((x-ESPACE)/COTECASE)*COTECASE + ESPACE, ((y-ESPACE)/COTECASE)*COTECASE + ESPACE, COTECASE, COTECASE, MLV_rgba(255,255,255,100));
                                    MLV_draw_rectangle(((x-ESPACE)/COTECASE)*COTECASE + ESPACE, ((y-ESPACE)/COTECASE)*COTECASE + ESPACE, COTECASE, COTECASE, MLV_COLOR_BLACK);
                                } else {
                                    /* Sinon, on est sur une case occupée, donc on affiche un contour rouge autour de la case */
                                    MLV_draw_rectangle(((x-ESPACE)/COTECASE)*COTECASE + ESPACE, ((y-ESPACE)/COTECASE)*COTECASE + ESPACE, COTECASE, COTECASE, MLV_rgba(255,70,70,255));
                                    MLV_draw_rectangle(((x-ESPACE)/COTECASE)*COTECASE + ESPACE - 1, ((y-ESPACE)/COTECASE)*COTECASE + ESPACE - 1, COTECASE + 2, COTECASE + 2, MLV_rgba(255,70,70,255));
                                }
                            }
                        }
                    }
                };
                MLV_actualise_window();
            } while( event != MLV_MOUSE_BUTTON );

            mouseX = x;
            mouseY = y;

            if ((mouseX < (LARG*COTECASE + ESPACE)) && (mouseX > ESPACE) && (mouseY < (LONG*COTECASE + ESPACE)) && (mouseY > ESPACE)) {
                posX = (mouseX - ESPACE) / COTECASE;
                posY = (mouseY - ESPACE) / COTECASE;
            }
        } while ((mouseX > (LARG*COTECASE + ESPACE)) && (mouseX < ESPACE) && (mouseY > (LONG*COTECASE + ESPACE)) && (mouseY < ESPACE));


        if (posX < 0 || posX > 17 || posY < 0 || posY > 11) {
            printf("Coordonnées invalides\nRecommencez svp\n");
        } else if (monde->plateau[posY][posX]) {
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
    char message[MESSAGE_MAX_SIZE];
    if (attaquant->genre == defenseur->genre) {
        sprintf(message, "L'attaquant (%c%c) gagne (Les deux sont du même type)\n", defenseur->genre, defenseur->couleur);
        ecrireMessage(message);
        MLV_wait_seconds(1);
        enleverUnite(defenseur, monde);
        return 1;
    } else if ((attaquant->genre == SERF) & (defenseur->genre == GUERRIER)) {
        sprintf(message, "L'attaquant (%c%c) perd (le défenseur est de meilleur type)\n", attaquant->genre, attaquant->couleur);
        ecrireMessage(message);
        MLV_wait_seconds(1);
        enleverUnite(attaquant, monde);
        return 0;
    } else if ((attaquant->genre == GUERRIER) & (defenseur->genre == SERF)) {
        sprintf(message, "L'attaquant (%c%c) gagne (l'attaquant est de meilleur type)\n", defenseur->genre, defenseur->couleur);
        ecrireMessage(message);
        MLV_wait_seconds(1);
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
    int choix, x, y, i, j, mouseX, mouseY;
    int finDeTour;
    char message[MESSAGE_MAX_SIZE];
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
            sprintf(message, "Unité actuelle : %c%c, (%d, %d)\nQue souhaitez-vous faire ? (Se déplacer/attaquer, Ne rien faire)", actuel->genre, actuel->couleur, actuel->posX, actuel->posY);
            ecrireMessage(message);
            
            /* Affichage des carrés de couleur autour de l'unité actuelle : VERT pour les alliés et les cases disponibles, ROUGE pour les ennemis */
            for (i = -1; i <= 1; ++i)
            {
                for (j = -1; j <= 1; ++j)
                {
                    if ((actuel->posY + j >= 0) && (actuel->posX + i >= 0) && (actuel->posY + j < LONG) && (actuel->posX + i < LARG)) {
                        if ((i != 0) || (j != 0)) {
                            if (monde->plateau[actuel->posY + j][actuel->posX + i] == NULL) {
                                MLV_draw_filled_rectangle((actuel->posX*COTECASE) + (i*COTECASE + ESPACE), (actuel->posY*COTECASE) + (j*COTECASE + ESPACE), COTECASE, COTECASE, MLV_COLOR_PALE_GREEN);
                            } else if ((monde->plateau[actuel->posY + j][actuel->posX + i]->couleur == actuel->couleur)) {
                                MLV_draw_filled_rectangle((actuel->posX*COTECASE) + (i*COTECASE + ESPACE), (actuel->posY*COTECASE) + (j*COTECASE + ESPACE), COTECASE, COTECASE, MLV_rgba(50,255,50,50));
                            } else {
                                MLV_draw_filled_rectangle((actuel->posX*COTECASE) + (i*COTECASE + ESPACE), (actuel->posY*COTECASE) + (j*COTECASE + ESPACE), COTECASE, COTECASE, MLV_rgba(255,50,50,50));
                            }
                        MLV_draw_rectangle((actuel->posX*COTECASE) + (i*COTECASE + ESPACE), (actuel->posY*COTECASE) + (j*COTECASE + ESPACE), COTECASE, COTECASE, MLV_COLOR_BLACK);
                        } else {
                            MLV_draw_rectangle((actuel->posX*COTECASE) + (i*COTECASE + ESPACE), (actuel->posY*COTECASE) + (j*COTECASE + ESPACE), COTECASE, COTECASE, MLV_rgba(120,0,255,255));
                        }
                        
                    } 
                }
            }
            MLV_actualise_window();
            
            MLV_draw_text_box(
                ESPACE + (LARG+.5)*COTECASE, ESPACE, 
                170, COTECASE,
                "Se déplacer / Attaquer",
                10,
                MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
                MLV_TEXT_CENTER,
                MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
            );
            MLV_draw_text_box(
                ESPACE + (LARG+.5)*COTECASE, ESPACE + COTECASE + COTECASE/2, 
                170, COTECASE,
                "Ne rien faire",
                10,
                MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
                MLV_TEXT_CENTER,
                MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
            );
            MLV_actualise_window();

            choix = 0;
            while (choix == 0) {
                MLV_wait_mouse( &mouseX, &mouseY );
                if ((mouseX > ESPACE + (LARG+0.5)*COTECASE) && (mouseX < (ESPACE + (LARG+0.5)*COTECASE) + 170)) {
                    /* Bouton "Se déplacer / Attaquer" */
                    if ((mouseY > ESPACE) && (mouseY < ESPACE + COTECASE)) {
                        choix = 1;
                    }
                    /* Bouton "Ne rien faire" */
                    else if ((mouseY > ESPACE + COTECASE + COTECASE/2) && (mouseY < (ESPACE + COTECASE + COTECASE/2) + COTECASE)) {
                        choix = 2;
                    }
                }
            }

            if (choix == 1) {
                sprintf(message, "L'utilisateur souhaite se déplacer ou attaquer.\nVeuillez cliquer sur la case cible.");
                ecrireMessage(message);
                MLV_draw_filled_rectangle(ESPACE + (LARG+.5)*COTECASE, ESPACE, 300, 500, MLV_rgba(18,18,18,255));
                MLV_actualise_window();
                do {
                    MLV_wait_mouse( &mouseX, &mouseY );
                    if ((mouseX < (LARG*COTECASE + ESPACE)) && (mouseX > ESPACE) && (mouseY < (LONG*COTECASE + ESPACE)) && (mouseY > ESPACE)) {
                        x = (mouseX-ESPACE)/COTECASE;
                        y = (mouseY-ESPACE)/COTECASE;
                    }
                } while ((mouseX > (LARG*COTECASE + ESPACE)) && (mouseX < ESPACE) && (mouseY > (LONG*COTECASE + ESPACE)) && (mouseY < ESPACE));


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

        //Indiquer la fin du tour en cliquant sur le bouton "Fin du tour"
        finDeTour = 0;
        sprintf(message, "Veuillez indiquer la fin de votre tour");
        ecrireMessage(message);

        MLV_draw_filled_rectangle(ESPACE + (LARG+.5)*COTECASE, ESPACE, 300, 500, MLV_rgba(18,18,18,255));
        MLV_draw_text_box(
            ESPACE + (LARG+.5)*COTECASE, ESPACE, 
            170, COTECASE,
            "Fin du tour",
            10,
            MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
            MLV_TEXT_CENTER,
            MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
        );
        MLV_actualise_window();

        while (finDeTour == 0) {
            MLV_wait_mouse( &mouseX, &mouseY );
            if ((mouseX > ESPACE + (LARG+0.5)*COTECASE) && (mouseX < (ESPACE + (LARG+0.5)*COTECASE) + 170) 
                && (mouseY > ESPACE) && (mouseY < ESPACE + COTECASE)) {
                finDeTour = 1;
            }
        }

        sprintf(message, "Le tour du joueur %c est terminé.", joueur);
        ecrireMessage(message);
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
    int arreterPartie, mouseX, mouseY;
    arreterPartie = 0;
    char message[MESSAGE_MAX_SIZE];
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
                sprintf(message, "Voulez vous arrêter la partie sans vainqueur ?");
                ecrireMessage(message);

                MLV_draw_text_box(
                    ESPACE + (LARG+.5)*COTECASE, ESPACE, 
                    170, COTECASE,
                    "Continuer",
                    10,
                    MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
                    MLV_TEXT_CENTER,
                    MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
                );
                MLV_draw_text_box(
                    ESPACE + (LARG+.5)*COTECASE, ESPACE + COTECASE + COTECASE/2, 
                    170, COTECASE,
                    "Arrêter la partie",
                    10,
                    MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
                    MLV_TEXT_CENTER,
                    MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
                );
                MLV_actualise_window();

                do {
                    arreterPartie = -1;
                    MLV_wait_mouse( &mouseX, &mouseY );
                    if ((mouseX > ESPACE + (LARG+0.5)*COTECASE) && (mouseX < (ESPACE + (LARG+0.5)*COTECASE) + 170)) {
                        /* Bouton "Continuer" */
                        if ((mouseY > ESPACE) && (mouseY < ESPACE + COTECASE)) {
                            arreterPartie = 0;
                        }
                        /* Bouton "Arrêter la partie" */
                        else if ((mouseY > ESPACE + COTECASE + COTECASE/2) && (mouseY < (ESPACE + COTECASE + COTECASE/2) + COTECASE)) {
                            arreterPartie = 1;
                        }
                    }
                } while (arreterPartie == -1);

            } while (arreterPartie != 0 && arreterPartie != 1);
        }
    } while ((monde.rouge != NULL && monde.bleu != NULL) && arreterPartie == 0);
    
    if (monde.rouge == NULL) {
        sprintf(message, "Vainqueur : Joueur Bleu");
    } else if (monde.bleu == NULL) {
        sprintf(message, "Vainqueur : Joueur Rouge");
    } else {
        sprintf(message, "Égalité");
    }
    ecrireMessage(message);
    MLV_wait_seconds(2);
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
    MLV_draw_filled_rectangle(45, LONG*COTECASE + ESPACE + 40, 500, 100, MLV_rgba(18,18,18,255));
    MLV_draw_adapted_text_box(
        45, LONG*COTECASE + ESPACE + 40,
        message,
        10,
        MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_GREY,
        MLV_TEXT_LEFT
    );

    MLV_actualise_window();
}