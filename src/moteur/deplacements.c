#include "moteur/deplacements.h"
#include "moteur/main.h"
#include "moteur/colision.h"
#include <GL/gl.h>
#include <GL/glu.h>
/************************************/
/*   Gestion des déplacements       */
/************************************/

void deplacementJoueur(Personnage *perso, int** level, Camera *camera){

	camera->formerX = perso->centerX;
	camera->formerY = perso->centerY;

	//glTranslatef(-perso->vitesse * perso->sens,0,0);

    perso->centerX += perso->vitesse * perso->sens;
    collisionLateral(perso, level);
    camera->currentX = perso->centerX;
   
 	perso->centerY += perso->gravite++;
 	camera->currentY = perso->centerY;
    if(CollisionRoof(perso, level) == 1){
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
