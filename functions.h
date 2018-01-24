#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <MLV/MLV_all.h>

/* CONSTANTES */

/* dimension du monde en nombre de cases */
/* l'origine est en haut a gauche */
#define LONG 12
#define LARG 18

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

/* Fontion qui ne prend rien en paramètre et retourne un entier aléatoire entre 0 et 1, utilisée notamment pour la gestion d'élément éléatoire à deux possibilité */
int random_0_1(void);

/* Fontion qui ne prend rien en paramètre et retourne un entier aléatoire entre 1 et 9, utilisée notamment pour l'ajout ou la soustraction d'un nombre aléatoire de points d'attaque lors des combats */
int random_0_9(void);

/* Fonction qui ne prend pas de paramètre et ne retourne rien et initialise la fenêtre d'affichage graphique du jeu */
void initialiserFenetre(void);

/* Fonction qui ne retourne rien et prend en paramètre le monde et qui met la valeur de tous ses pointeurs et les cases du plateau à NULL et le compteur de tours a zéro */
void initialiserMonde(Monde *monde);

/* Fonction qui ne retourne rien prenant en paramètre le monde et qui affiche l’état actuel du plateau de jeu (à l'aide de la bibliothèque MLV) */
void affichePlateau(Monde *monde);

/* Fonction qui retourne un entier servant à la gestion d'erreur et prend en paramètre un type et une liste d'unité et alloue une nouvelle unite de type type, et stocke son adresse dans *unite */
int creerUnite(char type, UListe * unite);

/* Fonction qui ne retourne rien et prend en parametre une unite, sa couleur et le monde et qui permet à l'utilisateur d'entrer ses coordonnées en début de partie */
void positionnerUnite(Unite *unite, Monde *monde, char couleur);

/* Fonction qui retourne un entier permettant la gestion d'erreur et prend en paramètre une unité, les coordonnées auxquelles la placer, sa couleur et le monde. Elle place une unité qui vient d’être créée à la position souhaitée dans le monde sous le contrôle de son nouveau maître */
int placerAuMonde(Unite *unite, Monde *monde, int posX, int posY, char couleur);

/* Fonction qui ne retourne rien et prend en paramètre une unité, les coordonnées du déplacement et le monde et qui déplace une unité vers une case spécifiée par les coordonnées */
void deplacerUnite(Unite *unite, Monde *monde, int destX, int destY);

/* Fonction qui ne retourne rien et prend en paramètre une unité et le monde et qui enlève l’unité du jeu (l'enlève donc du plateau et de la liste des unités et libère la mémoire) */
void enleverUnite(Unite *unite, Monde *monde);

/* Fonction qui retourne un paramètre indiquant le résultat du combat et qui prend en paramètre une unité, les coordonnées da l'attaque et qui qui gère le combat selon les règles du jeu (.cf sujet) */
int attaquer(Unite *unite, Monde *monde, int posX, int posY);

/* Fonction qui remplace deplacerOuAttaquer et retourne un entier en paramètre pour la gestion d'erreur et au resultat et qui prend en paramètre une unité, les coordonnées de l'action et le monde et qui qui gère le déplacements et le combat */
int actionUnite(Unite *unite, Monde *monde, int destX, int destY);

/* Fonction qui ne retourne rien et prend en paramètre le joueur et le monde et qui gère toutes les actions d’un joueur pendant son tour */
void gererDemiTour(char joueur, Monde *monde);

/* Fonction qui ne retourne rien et prend en paramètre le monde et qui gère un tour de jeu complet */
void gererTour(Monde *monde);

/* Fonction qui ne retourne rien et prend en paramètre le monde et qui le réinitialise et vide proprement la mémoire utilisée par les unités notamment */
void viderMonde(Monde *monde);

/* Fonction qui ne retourne rien et ne prend pas de paramètre et qui gère une partie de jeu */
void gererPartie(void);

/* Fontion qui ne retourne rien et prend en paramètre le monde et affiche le contenu des listes des deux joueurs (Très utile pour le débugage des fonctions liées aux listes) */
void afficherListes(Monde monde);


/* MLV Functions */

/* Fonction qui écrit un message en dessous du plateau de jeu */
void ecrireMessage(char message[]);

/* Fonction qui efface les boutons d'action */
void effacerBoutons(void);

/* Fontion qui ne retourne rien et prend en paramètre le monde pour afficher le contenu des listes des deux joueurs dans l'interface graphique */
void afficherUnites(Monde monde);

/* Colore les case adjacentes à l'unité courante en vert si la case est vide, vert transparent si un allié est sur la case et rouge tranparent si ennemi */
void colorerCasesAdj(Monde monde, Unite unite);

/* Fonction qui colore le contour de la case de l'unite courante en violet */
void colorerCaseCourante(Monde monde, Unite unite);

/* Fonction qui affiche le numéro du tour et quel joueur est en train de jouer */
void afficherTourJoueur(int num_tour, char couleur[]);

/* Colore les case adjacentes occupées par un ennemi en rouge transparent */
void colorerCasesEnnemies(Monde monde, Unite unite);

/* Vérifie si un ennemi se trouve à la portée de l'unite passée en paramètre. Retourne 1 si un ennemi est à sa portée, 0 sinon */
int attaquePossible(Monde monde, Unite unite);

/* Arrête la musique */
void stopMusic(MLV_Music* music);

#endif