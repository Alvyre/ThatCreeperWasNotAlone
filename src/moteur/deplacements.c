#include "moteur/deplacements.h"
#include "moteur/main.h"
#include "moteur/colision.h"
#include <GL/gl.h>
#include <GL/glu.h>
/************************************/
/*   Gestion des déplacements       */
/************************************/

void deplacementJoueur(Personnage *persoHandler, int nbrPerso, Level *level, Camera *camera){

    Personnage *perso;
    int i;
    for(i = 0; i<nbrPerso;++i){
        if(persoHandler[i].active)
        	perso = &persoHandler[i];
    }

    camera->formerX = perso->box.pos.x + perso->box.size.x/2;
    camera->formerY = perso->box.pos.y + perso->box.size.y/2;

    // Si perso bouge, il n'est plus sur sa case de fin
    perso->end = false;

    collisions(persoHandler, nbrPerso, level);
    camera->currentX = perso->box.pos.x + perso->box.size.x/2;


}
