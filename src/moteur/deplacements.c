#include "moteur/deplacements.h"
#include "moteur/main.h"
#include "moteur/colision.h"
#include <GL/gl.h>
#include <GL/glu.h>
/************************************/
/*   Gestion des déplacements       */
/************************************/

void deplacementJoueur(Personnage *persoHandler, int nbrPerso, int** level, Camera *camera){

    Personnage *perso;
    int i;
    for(i = 0; i<nbrPerso;++i){
        if(persoHandler[i].active) perso = &persoHandler[i];
    }

    camera->formerX = perso->box.pos.x + perso->box.size.x/2;
    camera->formerY = perso->box.pos.y + perso->box.size.y/2;


    // Si perso bouge, il n'est plus sur sa case de fin
    perso->end = false;
    perso->box.pos.y += perso->gravite++;

    perso->box.pos.x += perso->vitesse * perso->sens;
     collisionLateral(perso, level);
    camera->currentX = perso->box.pos.x + perso->box.size.x/2;

    // if(collisionRoof(perso, level) == 1){
    //      perso->saute = false;
    //      perso->gravite = 10;
    //     
    //     camera->currentY = perso->centerY;
    // }

    collisionGround(&persoHandler[0], level);
    collisionGround(&persoHandler[1], level);
    collisionGround(&persoHandler[2], level);
    // camera->currentY = perso->centerY;

    //collisionsJoueurs(persoHandler, nbrPerso);

    camera->currentX = perso->box.pos.x + perso->box.size.x/2;
}
