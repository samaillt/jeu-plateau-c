#include "functions.h"

int random_0_1(void){
    srand(time(NULL));
    return (rand()&1);
}

int random_0_9(void){
    srand(time(NULL));
    return (rand()%9+1);
}

void initialiserFenetre(void){
    
    /* Créé et affiche la fenêtre */
    MLV_create_window( "Jeu de plateau", "hello world", WINDOW_WIDTH, WINDOW_HEIGHT );

    /* Affiche un fond gris */
    MLV_draw_filled_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, MLV_rgba(0, 0, 0, 255));

    MLV_draw_rectangle(ESPACE/2 - 5, Y_PREMIER_BOUTON-5, BUTTON_WIDTH+10, 4*BUTTON_HEIGHT+10, MLV_rgba(50,50,50,255));

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
    int i, j, k, random_number;
    int spaceX, spaceY;
    char indexX[2], indexY[2];

    MLV_Image *guerrier_rouge_img, *guerrier_bleu_img, *serf_rouge_img, *serf_bleu_img, *reine_rouge_img, *reine_bleu_img;
    MLV_Image *texture_01, *texture_02;

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

    //Charge les images de personnages
    guerrier_rouge_img = MLV_load_image( "img/guerrier_rouge.png" );
    guerrier_bleu_img = MLV_load_image( "img/guerrier_bleu.png" );
    serf_rouge_img = MLV_load_image("img/serf_rouge.png");
    serf_bleu_img = MLV_load_image("img/serf_bleu.png");
    reine_rouge_img = MLV_load_image("img/reine_rouge.png");
    reine_bleu_img = MLV_load_image("img/reine_bleu.png");
    //Charge les images de texture
    texture_01 = MLV_load_image("img/Texture_07.jpg");
    texture_02 = MLV_load_image("img/Texture_05.jpg");

    //Redimensionne les images
    MLV_resize_image_with_proportions( guerrier_rouge_img, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( guerrier_bleu_img, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( serf_rouge_img, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( serf_bleu_img, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( reine_rouge_img, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( reine_bleu_img, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( texture_01, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( texture_02, COTECASE, COTECASE );

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

            random_number = i+j;
            switch (random_number%2){
                case 0:
                    MLV_draw_image(texture_01, j*COTECASE + ESPACE, i*COTECASE + ESPACE);
                    break;
                case 1:
                    MLV_draw_image(texture_02, j*COTECASE + ESPACE, i*COTECASE + ESPACE);
                    break;
                default:
                    MLV_draw_image(texture_02, j*COTECASE + ESPACE, i*COTECASE + ESPACE);
                    break;
            }
            MLV_draw_rectangle(j*COTECASE + ESPACE, i*COTECASE + ESPACE, COTECASE, COTECASE, MLV_COLOR_BLACK);
            MLV_draw_rectangle(j*COTECASE + ESPACE -1, i*COTECASE + ESPACE-1, COTECASE+2, COTECASE+2, MLV_COLOR_BLACK);
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
                } else if (monde->plateau[i][j]->genre == REINE) {
                    if (monde->plateau[i][j]->couleur == BLEU) {
                        MLV_draw_image( reine_bleu_img, j*COTECASE + ESPACE, i*COTECASE + ESPACE );
                    } else if (monde->plateau[i][j]->couleur == ROUGE) {
                        MLV_draw_image( reine_rouge_img, j*COTECASE + ESPACE, i*COTECASE + ESPACE );
                    }
                }
            }
        }
    }
    afficherUnites(*monde);
    MLV_actualise_window();

    MLV_free_image( guerrier_rouge_img );
    MLV_free_image( serf_rouge_img );
    MLV_free_image( reine_rouge_img );
    MLV_free_image( guerrier_bleu_img );
    MLV_free_image( serf_bleu_img );
    MLV_free_image( reine_bleu_img );
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
    if (type == GUERRIER){
        u->ptAttaque = 95;
        u->ptVie = 150;
        u->ptVieMax = 150;
        u->ptMouvement=4;
    }
    else if (type == SERF){
        u->ptAttaque = 75;
        u->ptVie = 100;
        u->ptVieMax = 100;
        u->ptMouvement=3;
    }
    else if (type == REINE) {
        u->ptAttaque = 145;
        u->ptVie = 300;
        u->ptVieMax = 500;
        u->ptMouvement=0;
    }
    u->cptTour=-1;
    u->action = 0;
    u->suiv = NULL;
    u->uniteEnProduction = 0;
    *unite = u;
    return 1;
}
  
/* Fonction qui ne retourne rien et prend en parametre une unite, sa couleur et le monde et qui permet à l'utilisateur d'entrer ses coordonnées en début de partie */
void positionnerUnite(Unite *unite, Monde *monde, char couleur){
    int posX, posY, mouseX, mouseY, x, y, i, j, random_number;
    MLV_Image *guerrier_rouge_img, *guerrier_bleu_img, *serf_rouge_img, *serf_bleu_img, *reine_rouge_img, *reine_bleu_img;
    MLV_Image *texture_01, *texture_02;
    MLV_Event event;
    char message[MESSAGE_MAX_SIZE];
    char nom_unite[MESSAGE_MAX_SIZE];
    char *genre_unite;
    char *couleur_unite;

    if (unite->genre == REINE) {
        genre_unite = "Reine";
    } else if (unite->genre == GUERRIER) {
        genre_unite = "Guerrier";
    } else if (unite->genre == SERF) {
        genre_unite = "Serf";
    }
    if (couleur == BLEU)
    {
        couleur_unite = "Bleu";
    } else {
        couleur_unite = "Rouge";
    }
    sprintf(nom_unite, "%s %s", genre_unite, couleur_unite);

    //Charge les images
    guerrier_rouge_img = MLV_load_image( "img/guerrier_rouge.png" );
    guerrier_bleu_img = MLV_load_image( "img/guerrier_bleu.png" );
    serf_rouge_img = MLV_load_image("img/serf_rouge.png");
    serf_bleu_img = MLV_load_image("img/serf_bleu.png");
    reine_rouge_img = MLV_load_image("img/reine_rouge.png");
    reine_bleu_img = MLV_load_image("img/reine_bleu.png");
    //Charge les images de texture
    texture_01 = MLV_load_image("img/Texture_07.jpg");
    texture_02 = MLV_load_image("img/Texture_05.jpg");
    //Redimension des images
    MLV_resize_image_with_proportions( guerrier_rouge_img, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( guerrier_bleu_img, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( serf_rouge_img, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( serf_bleu_img, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( reine_rouge_img, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( reine_bleu_img, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( texture_01, COTECASE, COTECASE );
    MLV_resize_image_with_proportions( texture_02, COTECASE, COTECASE );

    affichePlateau(monde);
    do {
        sprintf(message, "Positionnement de l'unité : %s", nom_unite);
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
                                    random_number = i+j;
                                    switch (random_number%2){
                                        case 0:
                                            MLV_draw_image(texture_01, j*COTECASE + ESPACE, i*COTECASE + ESPACE);
                                            break;
                                        case 1:
                                            MLV_draw_image(texture_02, j*COTECASE + ESPACE, i*COTECASE + ESPACE);
                                            break;
                                        default:
                                            MLV_draw_image(texture_02, j*COTECASE + ESPACE, i*COTECASE + ESPACE);
                                            break;
                                    }
                                }
                                MLV_draw_rectangle(j*COTECASE + ESPACE, i*COTECASE + ESPACE, COTECASE, COTECASE, MLV_COLOR_BLACK);
                                MLV_draw_rectangle(j*COTECASE + ESPACE -1, i*COTECASE + ESPACE-1, COTECASE+2, COTECASE+2, MLV_COLOR_BLACK);
                                if (monde->plateau[((y-ESPACE)/COTECASE)][((x-ESPACE)/COTECASE)] == NULL) {
                                    if (couleur == BLEU) {
                                        if (unite->genre == GUERRIER) {
                                            MLV_draw_image( guerrier_bleu_img, ((x-ESPACE)/COTECASE)*COTECASE + ESPACE, ((y-ESPACE)/COTECASE)*COTECASE + ESPACE );
                                        } else if (unite->genre == SERF) {
                                            MLV_draw_image( serf_bleu_img, ((x-ESPACE)/COTECASE)*COTECASE + ESPACE, ((y-ESPACE)/COTECASE)*COTECASE + ESPACE );
                                        } else if (unite->genre == REINE) {
                                            MLV_draw_image( reine_bleu_img, ((x-ESPACE)/COTECASE)*COTECASE + ESPACE, ((y-ESPACE)/COTECASE)*COTECASE + ESPACE );
                                        }
                                    } else if (couleur == ROUGE) {
                                        if (unite->genre == GUERRIER)
                                        {
                                            MLV_draw_image( guerrier_rouge_img, ((x-ESPACE)/COTECASE)*COTECASE + ESPACE, ((y-ESPACE)/COTECASE)*COTECASE + ESPACE );
                                        } else if (unite->genre == SERF) {
                                            MLV_draw_image( serf_rouge_img, ((x-ESPACE)/COTECASE)*COTECASE + ESPACE, ((y-ESPACE)/COTECASE)*COTECASE + ESPACE );
                                        } else if (unite->genre == REINE) {
                                            MLV_draw_image( reine_rouge_img, ((x-ESPACE)/COTECASE)*COTECASE + ESPACE, ((y-ESPACE)/COTECASE)*COTECASE + ESPACE );
                                        }
                                    }
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

    } while ((posX < 0 || posX > 17 || posY < 0 || posY > 11) || (monde->plateau[posY][posX]));
    placerAuMonde(unite, monde, posX, posY, couleur);

    MLV_free_image( guerrier_rouge_img );
    MLV_free_image( serf_rouge_img );
    MLV_free_image( reine_rouge_img );
    MLV_free_image( guerrier_bleu_img );
    MLV_free_image( serf_bleu_img );
    MLV_free_image( reine_bleu_img );
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
        return 0;
    } else {
        monde->plateau[posY][posX] = tmp;
        return 1;
    }
}

// void produireUnite(){

// }

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
}

/* Fonction qui retourne un paramètre indiquant le résultat du combat et qui prend en paramètre une unité, les coordonnées da l'attaque et qui qui gère le combat selon les règles du jeu (.cf sujet) */
int attaquer(Unite *unite, Monde *monde, int posX, int posY) {
    Unite *attaquant, *defenseur;
    int degats;
    attaquant = unite;
    defenseur = monde->plateau[posY][posX];
    degats = attaquant->ptAttaque;
    char message[MESSAGE_MAX_SIZE];
    char nom_defenseur[MESSAGE_MAX_SIZE];
    char *genre;
    char *couleur;

    if (defenseur->genre == REINE) {
        genre = "Reine";
    } else if (defenseur->genre == GUERRIER) {
        genre = "Guerrier";
    } else if (defenseur->genre == SERF) {
        genre = "Serf";
    }
    if (defenseur->couleur == BLEU)
    {
        couleur = "Bleu";
    } else {
        couleur = "Rouge";
    }
    sprintf(nom_defenseur, "%s %s", genre, couleur);

    sprintf(message, "Points de vie du défenseur = %d", defenseur->ptVie);
    ecrireMessage(message);
    MLV_wait_milliseconds(TIME_DELAY);

    if (random_0_1() == 0){
        degats += random_0_9();
    }
    else {
        degats -= random_0_9();
    }
    if (defenseur->ptVie <= degats){
        sprintf(message, "Le défenseur (%s) meurt", nom_defenseur);
        afficherUnites(*monde);
        ecrireMessage(message);
        MLV_wait_milliseconds(TIME_DELAY);
        enleverUnite(defenseur, monde);
        return 1;
    } else {
        sprintf(message, "Le défenseur (%s) perd %d points de vie", nom_defenseur, degats);
        afficherUnites(*monde);
        ecrireMessage(message);
        MLV_wait_milliseconds(TIME_DELAY);
        defenseur->ptVie -= degats;
        sprintf(message, "Points de vie restant du défenseur = %d", defenseur->ptVie );
        ecrireMessage(message);
        MLV_wait_milliseconds(TIME_DELAY);
        return 0;
    }
    return 0;
}

/* Fonction qui remplace deplacerOuAttaquer et retourne un entier en paramètre pour la gestion d'erreur et au resultat et qui prend en paramètre une unité, les coordonnées de l'action et le monde et qui qui gère le déplacements et le combat */
int actionUnite(Unite *unite, Monde *monde, int destX, int destY) {
    char message[MESSAGE_MAX_SIZE];
    int choix, mouseX, mouseY;
    if (unite->genre == REINE){
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
            if (monde->plateau[destY][destX]->couleur == unite->couleur && monde->plateau[destY][destX] != unite) {
                return -3;
            }
        }
        if (monde->plateau[destY][destX] == unite){

            sprintf(message, "Selectionnez l'unité à produire");
            ecrireMessage(message);

            MLV_draw_text_box(
                ESPACE/2, Y_PREMIER_BOUTON,
                BUTTON_WIDTH, BUTTON_HEIGHT,
                "Guerrier (4 tours)",
                10,
                MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
                MLV_TEXT_CENTER,
                MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
            );
            MLV_draw_text_box(
                ESPACE/2, Y_PREMIER_BOUTON + BUTTON_HEIGHT + ESPACE_ENTRE_BOUTONS, 
                BUTTON_WIDTH, BUTTON_HEIGHT,
                "Serf (2 tours)",
                10,
                MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
                MLV_TEXT_CENTER,
                MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
            );

            MLV_actualise_window();

            choix = 0;
            while (choix == 0) {
                MLV_wait_mouse( &mouseX, &mouseY );
                if ((mouseX > ESPACE/2) && (mouseX < ESPACE/2 + BUTTON_WIDTH)) {
                    /* Bouton "Guerrier (4 tours)" */
                    if ((mouseY > Y_PREMIER_BOUTON) && (mouseY < Y_PREMIER_BOUTON + BUTTON_HEIGHT)) {
                        choix = 1;
                    }
                    /* Bouton "Serf (2 tours)" */
                    else if ((mouseY > Y_PREMIER_BOUTON + BUTTON_HEIGHT + ESPACE_ENTRE_BOUTONS) && (mouseY < Y_PREMIER_BOUTON + 2*BUTTON_HEIGHT + ESPACE_ENTRE_BOUTONS)) {
                        choix = 2;
                    }
                }
            }

            if (choix == 1){
                unite->cptTour = 4;
                unite->uniteEnProduction = GUERRIER;
                sprintf(message, "Vous avez lancé la production d'un guerrier");
            } else {
                unite->cptTour = 2;
                unite->uniteEnProduction = SERF;
                sprintf(message, "Vous avez lancé la production d'un serf");
            }
            ecrireMessage(message);
            MLV_wait_milliseconds(TIME_DELAY);
            return 1;
        }
        /*  Si la case destination est vide et adjacente, erreur car la reine ne peut pas se déplacer donc erreur d'invalidité.
            Si la case de destination est valide, adjacente, et occupée par un ennemi, un combat prend lieu. 
            La fonction retourne 2 si l'attaquant a gagné ou 3 s'il a seulement infligé des dégats */
        if (monde->plateau[destY][destX] == NULL) {
            // sprintf(message, "La reine ne peut pas se déplacer");
            // ecrireMessage(message);
            // MLV_wait_milliseconds(TIME_DELAY);
            return -1;
        } else {
            /*  Un ennemi a été rencontré */
            if (attaquer(unite, monde, destX, destY) == 1) {
                // sprintf(message, "La reine a éliminé le défenseur");
                // ecrireMessage(message);
                // MLV_wait_milliseconds(TIME_DELAY);
                return 2;
            } else {
                // sprintf(message, "La reine a infligé des dégats au défenseur");
                // ecrireMessage(message);
                // MLV_wait_milliseconds(TIME_DELAY);
                return 3;
            }
        }
    } else {
        /* Si les coordonnées sont invalides, la fonction retourne -1 */
        if (destX < 0 || destX > 17 || destY < 0 || destY > 11) {
            return -1;
        }
        /* Si les coordonnées de sont pas adjacentes, la fonction retourne -2 */
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
            La fonction retourne 2 si l'attaquant a gagné ou 3 s'il a seulement infligé des dégats */
        if (monde->plateau[destY][destX] == NULL) {
            if (unite->ptMouvement > 0){
                deplacerUnite(unite, monde, destX, destY);
                unite->ptMouvement -= 1;
                return 1;
            } else {
                return -4;
            }
        } else {
            /*  Un ennemi a été rencontré */
            if (attaquer(unite, monde, destX, destY) == 1) {
                unite->ptMouvement = (-1);
                return 2;
            } else {
                unite->ptMouvement = (-1);
                return 3;
            }
        }
    }
}

/* Fonction qui ne retourne rien et prend en paramètre le joueur et le monde et qui gère toutes les actions d’un joueur pendant son tour */
void gererDemiTour(char joueur, Monde *monde) {
    /* Parcourir les unités du joueur */
    int choix, x, y, uniteEnAttente, mouseX, mouseY, compteur_tour;
    char finDeTour;
    char message[MESSAGE_MAX_SIZE];
    UListe liste;
    char nom_unite[MESSAGE_MAX_SIZE];
    char *genre;
    char *couleur;
    char *couleur_joueur;

    uniteEnAttente = 1;

    if (joueur == 'B') {
        liste = monde->bleu;
        couleur_joueur = "Bleu";
    } else if (joueur == 'R') {
        liste = monde->rouge;
        couleur_joueur = "Rouge";
    }
    if(liste != NULL){
        afficherTourJoueur(monde->tour, couleur_joueur);
        affichePlateau(monde);
        Unite *actuel, *tmp;
        actuel = liste;
        while(actuel != NULL && uniteEnAttente == 1) {

            if (actuel->genre == REINE) {
                genre = "Reine";
            } else if (actuel->genre == GUERRIER) {
                genre = "Guerrier";
            } else if (actuel->genre == SERF) {
                genre = "Serf";
            }
            if (actuel->couleur == BLEU)
            {
                couleur = "Bleu";
            } else {
                couleur = "Rouge";
            }
            sprintf(nom_unite, "%s %s", genre, couleur);

            if (actuel->action == 0){
                sprintf(message, "Unité actuelle : %s (%d, %d)\nQue souhaitez-vous faire ?\n - Effectuer une (ou plusieurs) action(s) avec l'unité\n - Mettre l'unité en attente\n - Ne rien faire", nom_unite, actuel->posX, actuel->posY);
                ecrireMessage(message);
                colorerCaseCourante(*monde, *actuel);

                if ((actuel->genre == REINE)) {
                    if (actuel->cptTour > 0) {
                        sprintf(message, "Continuer la production");
                    } else if (actuel->cptTour == 0) {
                        sprintf(message, "Placer l'unité");
                    } else {
                        sprintf(message, "Effectuer une action");
                    }
                } else {
                    sprintf(message, "Effectuer une action");
                }

                MLV_draw_text_box(
                    ESPACE/2, Y_PREMIER_BOUTON,
                    BUTTON_WIDTH, BUTTON_HEIGHT,
                    message,
                    10,
                    MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
                    MLV_TEXT_CENTER,
                    MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
                );
                MLV_draw_text_box(
                    ESPACE/2, Y_PREMIER_BOUTON + BUTTON_HEIGHT + ESPACE_ENTRE_BOUTONS, 
                    BUTTON_WIDTH, BUTTON_HEIGHT,
                    "Mettre en attente",
                    10,
                    MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
                    MLV_TEXT_CENTER,
                    MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
                );
                MLV_draw_text_box(
                    ESPACE/2, Y_PREMIER_BOUTON + 2*(BUTTON_HEIGHT + ESPACE_ENTRE_BOUTONS), 
                    BUTTON_WIDTH, BUTTON_HEIGHT,
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
                    if ((mouseX > ESPACE/2) && (mouseX < ESPACE/2 + BUTTON_WIDTH)) {
                        /* Bouton "Effectuer une action" */
                        if ((mouseY > Y_PREMIER_BOUTON) && (mouseY < Y_PREMIER_BOUTON + BUTTON_HEIGHT)) {
                            choix = 1;
                        }
                        /* Bouton "Mettre en attente" */
                        else if ((mouseY > Y_PREMIER_BOUTON + BUTTON_HEIGHT + ESPACE_ENTRE_BOUTONS) && (mouseY < Y_PREMIER_BOUTON + 2*BUTTON_HEIGHT + ESPACE_ENTRE_BOUTONS)) {
                            choix = 2;
                        }
                        /* Bouton "Ne rien faire" */
                        else if ((mouseY > Y_PREMIER_BOUTON + 2*(BUTTON_HEIGHT + ESPACE_ENTRE_BOUTONS)) && (mouseY < Y_PREMIER_BOUTON + 2*(BUTTON_HEIGHT + ESPACE_ENTRE_BOUTONS) + BUTTON_HEIGHT)) {
                            choix = 3;
                        }
                    }
                }

                if (choix == 1) {
                    if (actuel->genre == REINE){
                        sprintf(message, "L'utilisateur souhaite effectuer une (ou plusieurs) action(s) avec la Reine.\nL'unité actuelle étant une reine, veuillez cliquer sur elle pour lancer la production d'unité\nou cliquez sur une unité à attaquer (Portée : 1) (ATTENTION, la reine ne peut pas se déplacer !)");
                    } else {
                        sprintf(message, "L'utilisateur souhaite effectuer une (ou plusieurs) action(s) avec l'Unité.\nVeuillez cliquer sur la case cible.");
                    }
                    ecrireMessage(message);
                    effacerBoutons();
                    MLV_actualise_window();

                    if (actuel->genre == REINE){
                        compteur_tour = 0;
                        if (actuel->cptTour < 0 && actuel->uniteEnProduction == 0){
                            do {
                                if (compteur_tour == 0) {
                                    MLV_draw_filled_rectangle(actuel->posX*COTECASE + ESPACE, actuel->posY*COTECASE + ESPACE, COTECASE, COTECASE, MLV_rgba(120,50,255,50));
                                    colorerCasesEnnemies(*monde, *actuel);
                                }
                                do {
                                    MLV_wait_mouse( &mouseX, &mouseY );
                                    if ((mouseX < (LARG*COTECASE + ESPACE)) && (mouseX > ESPACE) && (mouseY < (LONG*COTECASE + ESPACE)) && (mouseY > ESPACE)) {
                                        x = (mouseX-ESPACE)/COTECASE;
                                        y = (mouseY-ESPACE)/COTECASE;
                                    }
                                } while ((mouseX > (LARG*COTECASE + ESPACE)) && (mouseX < ESPACE) && (mouseY > (LONG*COTECASE + ESPACE)) && (mouseY < ESPACE));
                                    compteur_tour++;
                            } while (actionUnite(actuel, monde, x, y) < 0);
                        } else if (actuel->cptTour == 0){
                            Unite *u;
                            creerUnite(actuel->uniteEnProduction,&u);
                            positionnerUnite(u, monde, actuel->couleur);
                            actuel->cptTour = -1;
                            actuel->uniteEnProduction = 0;
                        } else if (actuel->cptTour > 0){
                            actuel->cptTour -= 1;
                            if (actuel->cptTour == 0) {
                                sprintf(message, "La production est terminée, vous pourrez placer une unité au prochain tour.");
                            } else {
                                sprintf(message, "Il reste %d tour(s) de production", actuel->cptTour);
                            }
                            ecrireMessage(message);
                            MLV_wait_milliseconds(TIME_DELAY);
                        }
                    } else {
                        while (actuel->ptMouvement+1 > 0){
                            if (actuel->ptMouvement+1 > 1) {
                                colorerCasesAdj(*monde, *actuel);
                            } else {
                                if (attaquePossible(*monde, *actuel) == 1){
                                    colorerCasesEnnemies(*monde, *actuel); //On colore les cases en rouge
                                } else {
                                    break;
                                }
                            }
                            do {
                                MLV_wait_mouse( &mouseX, &mouseY );
                                if ((mouseX < (LARG*COTECASE + ESPACE)) && (mouseX > ESPACE) && (mouseY < (LONG*COTECASE + ESPACE)) && (mouseY > ESPACE)) {
                                    x = (mouseX-ESPACE)/COTECASE;
                                    y = (mouseY-ESPACE)/COTECASE;
                                }
                            } while ((mouseX > (LARG*COTECASE + ESPACE)) && (mouseX < ESPACE) && (mouseY > (LONG*COTECASE + ESPACE)) && (mouseY < ESPACE));
                            actionUnite(actuel, monde, x, y);
                            affichePlateau(monde);
                        }
                    }
                    actuel->action=1;
                    actuel = actuel->suiv;
                } else if (choix == 2) {
                    printf("L'utilisateur souhaite mettre l'unité en attente, on passe à l'unité suivante.\n");
                    actuel = actuel->suiv;
                } else if (choix == 3) {
                    printf("L'utilisateur souhaite ne rien faire avec cette unité, on passe à l'unité suivante.\n");
                    actuel->action = 1;
                    actuel = actuel->suiv;
                }
                affichePlateau(monde);
            } else {
                actuel = actuel->suiv;
            }
            tmp = liste;
            uniteEnAttente = 0;
            while (tmp != NULL){
                if (tmp->action == 0){
                    uniteEnAttente = 1;
                } 
                tmp = tmp->suiv;
            }
            if (actuel == NULL && uniteEnAttente == 1){
                actuel = liste;
            }
        }


        effacerBoutons();

        //Indiquer la fin du tour en cliquant sur le bouton "Fin du tour"
        finDeTour = 0;
        sprintf(message, "Veuillez indiquer la fin de votre tour");
        ecrireMessage(message);


        MLV_draw_text_box(
            ESPACE/2, Y_PREMIER_BOUTON,
            BUTTON_WIDTH, BUTTON_HEIGHT,
            "Fin du tour",
            10,
            MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
            MLV_TEXT_CENTER,
            MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
        );
        MLV_actualise_window();

        while (finDeTour == 0) {
            MLV_wait_mouse( &mouseX, &mouseY );
            if ((mouseX > ESPACE/2) && (mouseX < ESPACE/2 + BUTTON_WIDTH)
                && (mouseY > Y_PREMIER_BOUTON) && (mouseY < Y_PREMIER_BOUTON + BUTTON_HEIGHT)) {
                finDeTour = 1;
            }
        }

        effacerBoutons();

        /* remet le compteur d'actions effectuées à 0 */
        tmp = liste;
        while (tmp != NULL){
            tmp->action = 0;
            if (tmp->genre == GUERRIER){
                tmp->ptMouvement=2;
            }
            else if (tmp->genre == SERF){
                tmp->ptMouvement=1;
            }
            else {
                tmp->ptMouvement=0;
            }
            tmp = tmp->suiv;
        }
    }
}

/* Fonction qui ne retourne rien et prend en paramètre le monde et qui gère un tour de jeu complet */
void gererTour(Monde *monde){
    char joueurBleu = BLEU; /* Déclaration et initialisation du joueur bleu */
    char joueurRouge = ROUGE; /* Déclaration et initialisation du joueur rouge */
    int nbAlea = random_0_1();
    if (nbAlea == 0){
        printf("C'est au joueur Bleu de commencer\n");
        gererDemiTour(joueurBleu, monde); /* Tour du joueur 1 */
        gererDemiTour(joueurRouge, monde); /* Tour du joueur 2 */
    }
    else{
        printf("C'est au joueur Rouge de commencer\n");
        gererDemiTour(joueurRouge, monde); /* Tour du joueur 1 */
        gererDemiTour(joueurBleu, monde); /* Tour du joueur 2 */
    }
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
    Unite *u1, *u2, *u3, *u4, *u5, *u6, *u7, *u8; /* Déclaration des unités */
    char message[MESSAGE_MAX_SIZE];

    /* Initialisaton du monde */
    initialiserMonde(&monde);
    
    /* Création et placement des unités bleues */
    creerUnite(GUERRIER, &u1);
    creerUnite(SERF, &u2);
    creerUnite(SERF, &u3);
    creerUnite(REINE, &u4);
    positionnerUnite(u1, &monde, BLEU);
    positionnerUnite(u2, &monde, BLEU);
    positionnerUnite(u3, &monde, BLEU);
    positionnerUnite(u4, &monde, BLEU);
    
    /* Création et placement des unités rouges */
    creerUnite(GUERRIER, &u5);
    creerUnite(SERF, &u6);
    creerUnite(SERF, &u7);
    creerUnite(REINE, &u8);
    positionnerUnite(u5, &monde, ROUGE);
    positionnerUnite(u6, &monde, ROUGE);
    positionnerUnite(u7, &monde, ROUGE);
    positionnerUnite(u8, &monde, ROUGE);
    do {
        gererTour(&monde);
        if (monde.rouge == NULL || monde.bleu == NULL) {
            arreterPartie = 1;
        } else {
            do {
                sprintf(message, "Voulez-vous arrêter la partie sans vainqueur ?");
                ecrireMessage(message);

                MLV_draw_text_box(
                    ESPACE/2, Y_PREMIER_BOUTON,
                    BUTTON_WIDTH, BUTTON_HEIGHT,
                    "Continuer",
                    10,
                    MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
                    MLV_TEXT_CENTER,
                    MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
                );
                MLV_draw_text_box(
                    ESPACE/2, Y_PREMIER_BOUTON + BUTTON_HEIGHT + ESPACE_ENTRE_BOUTONS, 
                    BUTTON_WIDTH, BUTTON_HEIGHT,
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
                    if ((mouseX > ESPACE/2) && (mouseX < ESPACE/2 + BUTTON_WIDTH)) {
                        /* Bouton "Continuer" */
                        if ((mouseY > Y_PREMIER_BOUTON) && (mouseY < Y_PREMIER_BOUTON + BUTTON_HEIGHT)) {
                            arreterPartie = 0;
                            effacerBoutons();
                        }
                        /* Bouton "Arrêter la partie" */
                        else if ((mouseY > Y_PREMIER_BOUTON + BUTTON_HEIGHT + ESPACE_ENTRE_BOUTONS) && (mouseY < Y_PREMIER_BOUTON + 2*BUTTON_HEIGHT + ESPACE_ENTRE_BOUTONS)) {
                            arreterPartie = 1;
                            effacerBoutons();
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
    //Efface l'espace
    MLV_draw_filled_rectangle(BUTTON_WIDTH + ESPACE - 5, Y_PREMIER_BOUTON-5, LARG*COTECASE+10, WINDOW_HEIGHT+10, MLV_rgba(0,0,0,255));
    //Affiche le nouveau message
    MLV_draw_adapted_text_box(
        BUTTON_WIDTH + ESPACE -5, Y_PREMIER_BOUTON-5,
        message,
        10,
        MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_GREY,
        MLV_TEXT_LEFT
    );

    MLV_actualise_window();
}

void effacerBoutons(){
    MLV_draw_filled_rectangle(ESPACE/2, Y_PREMIER_BOUTON, BUTTON_WIDTH, 4*BUTTON_HEIGHT, MLV_rgba(0,0,0,255));
    MLV_draw_rectangle(ESPACE/2 - 5, Y_PREMIER_BOUTON-5, BUTTON_WIDTH+10, 4*BUTTON_HEIGHT+10, MLV_rgba(50,50,50,255));
    MLV_actualise_window();
}


/* Fontion qui ne retourne rien et prend en paramètre le monde pour afficher le contenu des listes des deux joueurs dans l'interface graphique */
void afficherUnites(Monde monde){
    int compteur, x, y;
    char message[MESSAGE_MAX_SIZE];
    MLV_Image *guerrier_rouge_img, *guerrier_bleu_img, *serf_rouge_img, *serf_bleu_img, *reine_rouge_img, *reine_bleu_img;
    compteur = 0;

    //Charge les images
    guerrier_rouge_img = MLV_load_image( "img/guerrier_rouge.png" );
    guerrier_bleu_img = MLV_load_image( "img/guerrier_bleu.png" );
    serf_rouge_img = MLV_load_image("img/serf_rouge.png");
    serf_bleu_img = MLV_load_image("img/serf_bleu.png");
    reine_rouge_img = MLV_load_image("img/reine_rouge.png");
    reine_bleu_img = MLV_load_image("img/reine_bleu.png");
    MLV_resize_image_with_proportions( guerrier_rouge_img, COTECASE-10, COTECASE-10 );
    MLV_resize_image_with_proportions( guerrier_bleu_img, COTECASE-10, COTECASE-10 );
    MLV_resize_image_with_proportions( serf_rouge_img, COTECASE-10, COTECASE-10 );
    MLV_resize_image_with_proportions( serf_bleu_img, COTECASE-10, COTECASE-10 );
    MLV_resize_image_with_proportions( reine_rouge_img, COTECASE-10, COTECASE-10 );
    MLV_resize_image_with_proportions( reine_bleu_img, COTECASE-10, COTECASE-10 );

    //Efface l'affichage précédent des unités
    MLV_draw_filled_rectangle(ESPACE + (LARG+0.5)*COTECASE, ESPACE, 300, WINDOW_HEIGHT, MLV_rgba(0,0,0,255));

    if(monde.bleu != NULL){
        Unite *actuel = monde.bleu;
        while(actuel != NULL) {
            x = ESPACE + (LARG+0.5)*COTECASE;
            y = ESPACE + compteur*50;

            //Affiches les infos sous forme de texte
            sprintf(message, "        (%d, %d), PV : %d/%d", actuel->posX, actuel->posY, actuel->ptVie, actuel->ptVieMax);
            MLV_draw_adapted_text_box(
                x, y,
                message,
                10,
                MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
                MLV_TEXT_LEFT
            );

            //Affiche les images
            if (actuel->genre == GUERRIER) {
                MLV_draw_image(guerrier_bleu_img, x, y);
            } else if (actuel->genre == SERF) {
                MLV_draw_image(serf_bleu_img, x, y);
            } else if (actuel->genre == REINE) {
                MLV_draw_image(reine_bleu_img, x, y);
            }
            
            actuel = actuel->suiv;
            compteur++;
        }
    }

    if(monde.rouge != NULL){
        Unite *actuel = monde.rouge;
        while(actuel != NULL) {
            x = ESPACE + (LARG+0.5)*COTECASE;
            y = ESPACE + compteur*50;

            //Affiches les infos sous forme de texte
            sprintf(message, "      (%d, %d), PV : %d/%d", actuel->posX, actuel->posY, actuel->ptVie, actuel->ptVieMax);
            MLV_draw_adapted_text_box(
                x, y,
                message,
                10,
                MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
                MLV_TEXT_LEFT
            );

            //Affiche les images
            if (actuel->genre == GUERRIER)
            {
                MLV_draw_image(guerrier_rouge_img, x, y);
            } else if (actuel->genre == SERF) {
                MLV_draw_image(serf_rouge_img, x, y);
            } else if (actuel->genre == REINE) {
                MLV_draw_image(reine_rouge_img, x, y);
            }
            
            actuel = actuel->suiv;
            compteur++;
        }
    }
    MLV_actualise_window();

    MLV_free_image( guerrier_rouge_img );
    MLV_free_image( serf_rouge_img );
    MLV_free_image( reine_rouge_img );
    MLV_free_image( guerrier_bleu_img );
    MLV_free_image( serf_bleu_img );
    MLV_free_image( reine_bleu_img );
}

/* Colore les case adjacentes à l'unité courante en vert si la case est vide, vert transparent si un allié est sur la case et rouge tranparent si ennemi */
void colorerCasesAdj(Monde monde, Unite unite){
    int i, j, portee;
    MLV_Color couleur_case;
    portee = 1;
    for (i = -portee; i <= portee; ++i)
    {
        for (j = -portee; j <= portee; ++j)
        {
            if ((unite.posY + j >= 0) && (unite.posX + i >= 0) && (unite.posY + j < LONG) && (unite.posX + i < LARG)) {
                if ((i != 0) || (j != 0)) {
                    if (monde.plateau[unite.posY + j][unite.posX + i] == NULL) {
                        // couleur_case = MLV_COLOR_PALE_GREEN; //Couleur vert pâle
                        couleur_case = MLV_rgba(50,255,50,50); 
                    } else if ((monde.plateau[unite.posY + j][unite.posX + i]->couleur == unite.couleur)) {
                        couleur_case = MLV_rgba(50,255,50,50); //Couleur vert transparent
                    } else {
                        couleur_case = MLV_rgba(255,50,50,50); //Couleur rouge transparent
                    }
                    MLV_draw_filled_rectangle((unite.posX*COTECASE) + (i*COTECASE + ESPACE), (unite.posY*COTECASE) + (j*COTECASE + ESPACE), COTECASE, COTECASE, couleur_case);
                    MLV_draw_rectangle((unite.posX*COTECASE) + (i*COTECASE + ESPACE), (unite.posY*COTECASE) + (j*COTECASE + ESPACE), COTECASE, COTECASE, MLV_COLOR_BLACK);
                } else {
                    MLV_draw_rectangle((unite.posX*COTECASE) + (i*COTECASE + ESPACE), (unite.posY*COTECASE) + (j*COTECASE + ESPACE), COTECASE, COTECASE, MLV_rgba(120,0,255,150));
                }
            } 
        }
    }
    MLV_actualise_window();
}

/* Fonction qui colore le contour de la case de l'unite courante en violet */
void colorerCaseCourante(Monde monde, Unite unite){
    MLV_Color couleur_case;
    // couleur_case = MLV_COLOR_PURPLE;
    couleur_case = MLV_rgba(210,90,210,255);
    MLV_draw_rectangle(unite.posX*COTECASE + ESPACE - 1, unite.posY*COTECASE + ESPACE - 1, COTECASE + 2, COTECASE + 2, couleur_case);
    MLV_draw_rectangle(unite.posX*COTECASE + ESPACE, unite.posY*COTECASE + ESPACE, COTECASE, COTECASE, couleur_case);
    MLV_actualise_window();
}

/* Fonction qui affiche le numéro du tour et quel joueur est en train de jouer */
void afficherTourJoueur(int num_tour, char couleur[]){
    char message[MESSAGE_MAX_SIZE];
    MLV_Color couleur_texte;
    sprintf(message, "Tour N°%d - Joueur %s.", num_tour, couleur);

    if (strcmp(couleur, "Bleu"))
    {
        // couleur_texte = MLV_rgba(255,50,50,255);
        couleur_texte = MLV_COLOR_INDIANRED3;
    } else {
        couleur_texte = MLV_COLOR_SKYBLUE3;
    }
    MLV_draw_filled_rectangle(ESPACE + (LARG+0.5)*COTECASE, 0, 2*BUTTON_WIDTH, ESPACE, MLV_rgba(0,0,0,255));
    MLV_draw_adapted_text_box(
        ESPACE + (LARG+0.5)*COTECASE, 0,
        message,
        10,
        MLV_rgba(0,0,0,255), couleur_texte, MLV_rgba(0,0,0,255),
        MLV_TEXT_LEFT
    );
    MLV_actualise_window();
}

/* Colore les case adjacentes occupées par un ennemi */
void colorerCasesEnnemies(Monde monde, Unite unite){
    int i, j, portee;
    MLV_Color couleur_case;
    portee = 1;
    for (i = -portee; i <= portee; ++i)
    {
        for (j = -portee; j <= portee; ++j)
        {
            if ((unite.posY + j >= 0) && (unite.posX + i >= 0) && (unite.posY + j < LONG) && (unite.posX + i < LARG)) {
                if ((i != 0) || (j != 0)) {
                    if (monde.plateau[unite.posY + j][unite.posX + i] != NULL) {
                        if (monde.plateau[unite.posY + j][unite.posX + i]->couleur != unite.couleur) {
                            couleur_case = MLV_rgba(255,50,50,60);
                            MLV_draw_filled_rectangle((unite.posX*COTECASE) + (i*COTECASE + ESPACE), (unite.posY*COTECASE) + (j*COTECASE + ESPACE), COTECASE, COTECASE, couleur_case);
                            MLV_draw_rectangle((unite.posX*COTECASE) + (i*COTECASE + ESPACE), (unite.posY*COTECASE) + (j*COTECASE + ESPACE), COTECASE, COTECASE, MLV_COLOR_BLACK);
                        }
                    }
                } else {
                    MLV_draw_rectangle((unite.posX*COTECASE) + (i*COTECASE + ESPACE), (unite.posY*COTECASE) + (j*COTECASE + ESPACE), COTECASE, COTECASE, MLV_rgba(120,0,255,255));
                }
                
            } 
        }
    }
    MLV_actualise_window();
}

/* Vérifie si un ennemi se trouve à la portée de l'unite passée en paramètre */
int attaquePossible(Monde monde, Unite unite){
    int i, j, portee;
    portee = 1;
    for (i = -portee; i <= portee; ++i)
    {
        for (j = -portee; j <= portee; ++j)
        {
            if ((unite.posY + j >= 0) && (unite.posX + i >= 0) && (unite.posY + j < LONG) && (unite.posX + i < LARG)) {
                if ((i != 0) || (j != 0)) {
                    if (monde.plateau[unite.posY + j][unite.posX + i] != NULL) {
                        if (monde.plateau[unite.posY + j][unite.posX + i]->couleur != unite.couleur) {
                            return 1;
                        }
                    }
                }
            } 
        }
    }
    return 0;
}

void playMusic(MLV_Music* music){
    MLV_play_music( music, 1.0, -1 );
}

void stopMusic(MLV_Music* music){
    MLV_stop_music();
    MLV_free_music(music);
    MLV_free_audio();
}