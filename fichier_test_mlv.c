#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <MLV/MLV_all.h>
/* CONSTANTES */
/* dimension du monde en nombre de cases */
#define LONG 12
#define LARG 18
#define COTECASE 60
/* l'origine est en haut a gauche */

#define ROUGE 'R' /*identifiant du premier joueur */
#define BLEU 'B' /* identifiant du deuxième joueur */

/* les genres d'unites */
#define SERF 's'
#define GUERRIER 'g'

/*Fonction principale qui lance une partie*/
int main() {
	srand(time(NULL));
    int nbgen=rand()%9+1;    //entre 1-9
    printf("%d\n",nbgen);    teste affichage
    return 0;
}