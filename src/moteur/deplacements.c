#include "moteur/deplacements.h"
#include "moteur/main.h"
#include "moteur/colision.h"

/************************************/
/*   Gestion des déplacements       */
/************************************/

void deplacementJoueur(Personnage *perso, int** level){

    // Déplace en X
    if (perso->droite || perso->gauche)
    {
        perso->centerX += perso->vitesse * perso->sens;
    }

    // Gravité s'applique toujours meme si le perso ne saute pas
    perso->centerY += perso->gravite++;
    
    collisionTop(perso, level);
    collisionGround(perso, level);
    collisionLateral(perso, level);
    
}
