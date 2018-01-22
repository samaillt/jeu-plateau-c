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

/* dimension du côté d'une case pour l'affichage graphique */
#define COTECASE 40
/* l'origine est en haut a gauche */

#define ROUGE 'R' /*identifiant du premier joueur */
#define BLEU 'B' /* identifiant du deuxième joueur */

/* les genres d'unites */
#define SERF 's'
#define GUERRIER 'g'

/*STRUCTURES */
typedef struct unite{
    int posX, posY; /* Pour stocker les coordonnées de l'unité */
    char couleur; /* ROUGE ou BLEU */
    char genre; /* GUERRIER ou SERF */
    int ptVie; /* Nombre de vie de l'unité */
    int ptAttaque; /* Points d'attaque de l'unité */
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
int deplacerOuAttaquer(Unite *unite, Monde *monde, int destX, int destY);
void gererDemiTour(char joueur, Monde *monde);
void gererTour(Monde *monde);
void viderMonde(Monde *monde);
void gererPartie(void);
void afficherListes(Monde monde);

/* MLV Functions */
void ecrireMessage(char message[]);

#endif