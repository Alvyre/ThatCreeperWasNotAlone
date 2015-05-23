#include "moteur/deplacements.h"
#include "moteur/main.h"
#include "moteur/colision.h"
#include <GL/gl.h>
#include <GL/glu.h>
/************************************/
/*   Gestion des déplacements       */
/************************************/

void deplacementJoueur(Personnage *perso, int** level){
    glTranslatef(-perso->vitesse * perso->sens,0,0);
    perso->centerX += perso->vitesse * perso->sens;
    collisionLateral(perso, level);
   
 	perso->centerY += perso->gravite++;

    if(CollisionRoof(perso, level) == 1){
         perso->saute = false;
         perso->gravite = 10;
        perso->centerY += perso->gravite++;
    }
    if(collisionGround(perso, level)) return;
    
}
