#include "functions.h"

/* Fonction principale qui lance une partie */
int main() {
    MLV_init_audio( );
	MLV_Music* music = MLV_load_music("music/zelda_epique_cc.mp3");
	playMusic(music);
	initialiserFenetre();
	gererPartie();
	stopMusic(music);
    return 0;
}