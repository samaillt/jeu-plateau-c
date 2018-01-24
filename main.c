#include "functions.h"

/* Fonction principale qui lance une partie */
int main() {
    MLV_init_audio( );
	MLV_Music* music = MLV_load_music("music/zelda_epique_cc.mp3");
	MLV_play_music( music, 1.0, -1 );
	initialiserFenetre();
	gererPartie();
	stopMusic(music);
    return 0;
}