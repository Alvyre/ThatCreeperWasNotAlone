#include "moteur/deplacements.h"
#include "moteur/main.h"
#include "moteur/colision.h"
#include <GL/gl.h>
#include <GL/glu.h>
/************************************/
/*   Gestion des déplacements       */
/************************************/

void deplacementJoueur(Personnage *persoHandler, int** level, Camera *camera){

    Personnage *perso;
    if(persoHandler[0].active){
        perso = &(persoHandler[0]);
        camera->formerX = perso->centerX;
        camera->formerY = perso->centerY;

    } 
    else if(persoHandler[1].active){
        perso = &(persoHandler[1]);
        camera->formerX = perso->centerX;
        camera->formerY = perso->centerY;

    } 
    else if(persoHandler[2].active){
        perso = &(persoHandler[2]);
        camera->formerX = perso->centerX;
        camera->formerY = perso->centerY;

    } 

    // Si perso bouge, il n'est plus sur sa case de fin
    perso->end = false;
    perso->centerX += perso->vitesse * perso->sens;
    collisionLateral(perso, level);
    camera->currentX = perso->centerX;

    if(collisionRoof(perso, level) == 1){
         perso->saute = false;
         perso->gravite = 10;
        perso->centerY += perso->gravite++;
        camera->currentY = perso->centerY;
    }

    collisionGround(&persoHandler[0], level);
    collisionGround(&persoHandler[1], level);
    collisionGround(&persoHandler[2], level);
    camera->currentY = perso->centerY;

    //collisionsJoueur(&persoHandler, NBR_PERSO);

    camera->currentX = perso->centerX;
}
