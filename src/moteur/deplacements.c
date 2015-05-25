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
        // collisionsJoueur(&persoHandler[0], &persoHandler[1]);
        // collisionsJoueur(&persoHandler[0], &persoHandler[2]);
        //camera->currentX = perso->centerX;
    } 
    else if(persoHandler[1].active){
        perso = &(persoHandler[1]);
        camera->formerX = perso->centerX;
        camera->formerY = perso->centerY;
        // collisionsJoueur(&persoHandler[1], &persoHandler[0]);
        // collisionsJoueur(&persoHandler[1], &persoHandler[2]);
        //camera->currentX = perso->centerX;
    } 
    else if(persoHandler[2].active){
        perso = &(persoHandler[2]);
        camera->formerX = perso->centerX;
        camera->formerY = perso->centerY;
        // collisionsJoueur(&persoHandler[2], &persoHandler[0]);
        // collisionsJoueur(&persoHandler[2], &persoHandler[1]);
        //camera->currentX = perso->centerX;
    } 

    // Si perso bouge, il n'est plus sur sa case de fin
    perso->end = false;
    perso->centerX += perso->vitesse * perso->sens;
    collisionLateral(perso, level);
    camera->currentX = perso->centerX;
   
 	if(persoHandler[0].freeze == false) persoHandler[0].centerY += persoHandler[0].gravite++;
    if(persoHandler[1].freeze == false) persoHandler[1].centerY += persoHandler[1].gravite++;
    if(persoHandler[2].freeze == false) persoHandler[2].centerY += persoHandler[2].gravite++;


 	camera->currentY = perso->centerY;

    if(collisionRoof(perso, level) == 1){
         perso->saute = false;
         perso->gravite = perso->defaultGravite;
        perso->centerY += perso->gravite++;
        camera->currentY = perso->centerY;
    }

    collisionGround(&persoHandler[0], level);
    collisionGround(&persoHandler[1], level);
    collisionGround(&persoHandler[2], level);
    camera->currentY = perso->centerY;

    collisionsJoueur(&persoHandler[0], &persoHandler[1]);
    collisionsJoueur(&persoHandler[0], &persoHandler[2]);

    collisionsJoueur(&persoHandler[1], &persoHandler[0]);
    collisionsJoueur(&persoHandler[1], &persoHandler[2]);

    collisionsJoueur(&persoHandler[2], &persoHandler[0]);
    collisionsJoueur(&persoHandler[2], &persoHandler[1]);
    camera->currentX = perso->centerX;
}
