#include "moteur/deplacements.h"
#include "moteur/main.h"
#include "moteur/colision.h"

/************************************/
/*   Gestion des déplacements       */
/************************************/

void deplacementJoueur(Personnage *perso, int** level){

    // Déplace en X
    if (perso->sens)
    {
        //printf("%d\n", testCollision(perso, level));
        // Collision devant --> on ne peut que reculer
        if (collisionLateral(perso, level) == 1 && perso->sens == -1)
        {

                perso->centerX += perso->vitesse * perso->sens;

        }
        // Collision devant --> on ne peut qu'avance
        if (collisionLateral(perso, level) == -1 && perso->sens == 1)
        {

            perso->centerX += perso->vitesse * perso->sens;

        }
        // Pas de collisions --> avance
        if (collisionLateral(perso, level) == 0)
        {
            perso->centerX += perso->vitesse * perso->sens;
        }
        
    }

    // Gravité s'applique toujours meme si le perso ne saute pas
    perso->centerY += perso->gravite++;
    
    // if(perso->gravite < 0 && collisionTop(perso, level)) return;
     if(collisionGround(perso, level)) return;
    
    //testCollision(perso, level);

    
}
