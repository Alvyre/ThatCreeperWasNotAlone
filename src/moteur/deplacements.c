#include "moteur/deplacements.h"
#include "moteur/main.h"
#include "moteur/colision.h"
#include <GL/gl.h>
#include <GL/glu.h>
/************************************/
/*   Gestion des déplacements       */
/************************************/

void deplacementJoueur(Personnage *persoHandler, int nbrPerso, Level *level){

    Personnage *perso;
    int i;
    for(i = 0; i<nbrPerso;++i){
        if(persoHandler[i].active)
        	perso = &persoHandler[i];
    }

    // Si perso bouge, il n'est plus sur sa case de fin
    perso->end = false;

    // Si le perso tombe on le remet à sa place de départ
    if (perso->box.pos.y > level->height*TAILLE_CASE + WINDOW_HEIGHT/2)
    {
    	perso->box.pos.y = perso->initialPosY * TAILLE_CASE;
    	perso->box.pos.x = perso->initialPosX * TAILLE_CASE;
    }

    collisions(persoHandler, nbrPerso, level);
}
