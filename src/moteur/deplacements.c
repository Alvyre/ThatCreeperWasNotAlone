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
        collisionsJoueur(&persoHandler[0], &persoHandler[1]);
        collisionsJoueur(&persoHandler[0], &persoHandler[2]);
        camera->currentX = perso->centerX;
    } 
    else if(persoHandler[1].active){
        perso = &(persoHandler[1]);
        camera->formerX = perso->centerX;
        camera->formerY = perso->centerY;
        collisionsJoueur(&persoHandler[1], &persoHandler[0]);
        collisionsJoueur(&persoHandler[1], &persoHandler[2]);
        camera->currentX = perso->centerX;
    } 
    else if(persoHandler[2].active){
        perso = &(persoHandler[2]);
        camera->formerX = perso->centerX;
        camera->formerY = perso->centerY;
        collisionsJoueur(&persoHandler[2], &persoHandler[0]);
        collisionsJoueur(&persoHandler[2], &persoHandler[1]);
        camera->currentX = perso->centerX;
    } 
    perso->centerX += perso->vitesse * perso->sens;
    collisionLateral(perso, level);
    camera->currentX = perso->centerX;
   
 	perso->centerY += perso->gravite++;
 	camera->currentY = perso->centerY;

    if(collisionRoof(perso, level) == 1){
         perso->saute = false;
         perso->gravite = 10;
        perso->centerY += perso->gravite++;
        camera->currentY = perso->centerY;
    }
    if(collisionGround(perso, level)){
    	camera->currentY = perso->centerY;
    } 

    //scrolling(camera);
}
