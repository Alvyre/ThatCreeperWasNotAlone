#include "moteur/deplacements.h"
#include "moteur/main.h"
#include "moteur/colision.h"

/************************************/
/*   Gestion des déplacements       */
/************************************/

void deplacementJoueur(Personnage *perso, int** level){
    perso->centerX += perso->vitesse * perso->sens;
    collisionLateral(perso, level);

 perso->centerY += perso->gravite++;
//     // Collision haut
    if(CollisionRoof(perso, level) == 1){
         perso->saute = false;
         perso->gravite = 10;
        perso->centerY += perso->gravite++;
    }

//     // Collision bas
//     if(testCollisonGround(perso, level) == -1){
//          return;
//     }    
    // if(perso->gravite < 0 && collisionTop(perso, level)) return;
    if(collisionGround(perso, level)) return;
    
}
