#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <MLV/MLV_all.h>
/* CONSTANTES */
/* dimension du monde en nombre de cases */
#define LONG 12
#define LARG 18
/* l'origine est en haut a gauche */

#define ROUGE 'R' /*identifiant du premier joueur */
#define BLEU 'B' /* identifiant du deuxième joueur */

/* les genres d'unites */
#define SERF 's'
#define GUERRIER 'g'
#define REINE 'r'

/* Dimension du côté d'une case pour l'affichage graphique */
#define COTECASE 45
/* Cette constante correspond à l'espace en haut et à gauche du plateau */
#define ESPACE 40

/* Défini les dimensions de la fenêtre en fonction d'autre variables */
#define WINDOW_WIDTH (LARG+1+6)*COTECASE
#define WINDOW_HEIGHT (LONG+1+5)*COTECASE

/* Défini les dimensions des boutons */
#define BUTTON_WIDTH 170
#define BUTTON_HEIGHT COTECASE-10
#define ESPACE_ENTRE_BOUTONS COTECASE/4
#define Y_PREMIER_BOUTON ESPACE + (LONG+.5)*COTECASE

/* Durée d'attente entre les différents messages (en millisecondes). */
#define TIME_DELAY 1500

/* Constante pour définir le nombre de caractères maximum du message */
#define MESSAGE_MAX_SIZE 1000

/*STRUCTURES */
typedef struct unite{
    int posX, posY; /* Pour stocker les coordonnées de l'unité */
    char couleur; /* ROUGE ou BLEU */
    char genre; /* GUERRIER ou SERF ou REINE */
    int ptVie; /* Points de vie de l'unité */
    int ptVieMax; /* Points de vie maximum de l'unité */
    int ptAttaque; /* Points d'attaque de l'unité */
    int ptMouvement; /* Points de mouvement de l'unité */
    int action; /* Entier qui vaudra 1 si l'unité peut effectuer une action ou 0 sinon */
    int cptTour; /* Compteur utilisable pour la reine qui produit des unités */
    char uniteEnProduction; /* GUERRIER ou SERF ou 0 lorsqu'il n'y en a pas */
    struct unite *suiv; /* liste des unités suivantes */
} Unite;

typedef Unite* UListe;

typedef struct monde{
    Unite *plateau[LONG][LARG];
    int tour; /* Numero du tour */
    UListe rouge, bleu; /*Listes des deux joueurs*/
} Monde;


/* PROTOTYPES DES FONCTIONS */
int random_0_1(void);
int random_0_9(void);
void initialiserFenetre(void);
void initialiserMonde(Monde *monde);
void affichePlateau(Monde *monde);
int creerUnite(char type, UListe * unite);
void positionnerUnite(Unite *unite, Monde *monde, char couleur);
int placerAuMonde(Unite *unite, Monde *monde, int posX, int posY, char couleur);
void deplacerUnite(Unite *unite, Monde *monde, int destX, int destY);
void enleverUnite(Unite *unite, Monde *monde);
int attaquer(Unite *unite, Monde *monde, int posX, int posY);
int actionUnite(Unite *unite, Monde *monde, int destX, int destY);
void gererDemiTour(char joueur, Monde *monde);
void gererTour(Monde *monde);
void viderMonde(Monde *monde);
void gererPartie(void);
void afficherListes(Monde monde);

/* MLV Functions */
void ecrireMessage(char message[]);
void effacerBoutons(void);
void afficherUnites(Monde monde);
void colorerCasesAdj(Monde monde, Unite unite);
void colorerCaseCourante(Monde monde, Unite unite);

#endif