/************************************/
/*   Gestion des collisions         */
/************************************/

#include "moteur/colision.h"

/**
 * Parcours les cases devant et derière selon la largeur du solide et teste les collisions
 * 
 * 
 * @param *perso
 */
 bool collisionGround(Personnage *perso, int** level){


    int Y = perso->centerY;
    int X = perso->centerX;

    float halfHeight = perso->height/2.0;
    float halfWidth = perso->width/2.0;

    int C = (X - (halfWidth * TAILLE_CASE)) / TAILLE_CASE;
    int L = (Y + (halfHeight * TAILLE_CASE)) / TAILLE_CASE;


    for ( ; C <= floor((X + (halfWidth * TAILLE_CASE)) / TAILLE_CASE)  ; C++){

        if(level[L][C] == 1 &&  Y >=(L - halfHeight)*TAILLE_CASE){

            switch(perso->height){                                                      // SWITCH pour corriger la position selon la hauteur du perso (1-6)
                case 1:
                case 2:
                    perso->centerY = (L - halfHeight)*TAILLE_CASE - halfHeight +1 ;
                    break;
                case 3:
                case 4:
                    perso->centerY = (L - halfHeight)*TAILLE_CASE - halfHeight +2 ;
                    break;
                case 5:
                case 6:
                    perso->centerY = (L - halfHeight)*TAILLE_CASE - halfHeight +3 ;
                    break;

                default:
                    perso->centerY = (L - halfHeight)*TAILLE_CASE - halfHeight +1 ;
                    break;
            }

            perso->gravite = 10;
            perso->saute = false;
            return true;
        }
    }
    return false;
}

int collisionLateral(Personnage *perso, int** level){

    int Y = perso->centerY;
    int X = perso->centerX;

    float halfWidth = perso->width/2.0;
    float halfHeight = perso->height/2.0;

    int C = floor((X + (halfWidth*TAILLE_CASE) * perso->sens) / TAILLE_CASE);    
    int L = floor((Y - (halfHeight*TAILLE_CASE)) / TAILLE_CASE);
 
                         
    for (; L < (Y/TAILLE_CASE) +floor(halfHeight); L++) {
        if (level[L][C]==1 && perso->sens == 1) {
            perso->centerX = C * TAILLE_CASE + floor(halfWidth) - halfWidth*TAILLE_CASE * perso->sens -2;
        }
        else if (level[L][C]==1 && perso->sens == -1) {
            if(perso->width %2==0) perso->centerX = C * TAILLE_CASE - floor(halfWidth) - perso->width*TAILLE_CASE * perso->sens +1;
            else {
               perso->centerX = C * TAILLE_CASE - floor(halfWidth) - (perso->width/2.0)*TAILLE_CASE * perso->sens +1*TAILLE_CASE +1 ;
            }                 
        }
    }
}


bool CollisionRoof(Personnage *perso, int** level){

    int Y = perso->centerY;
    int X = perso->centerX;

    float halfHeight = perso->height/2.0;
    float halfWidth = perso->width/2.0;

    int C = (X - (halfWidth * TAILLE_CASE)) / TAILLE_CASE;
    int L = (Y - (halfHeight * TAILLE_CASE)) / TAILLE_CASE;

    for ( ; C <= floor((X + (halfWidth * TAILLE_CASE)) / TAILLE_CASE)  ; C++){

        if(level[L][C] == 1){
            perso->centerY = (L+2)*TAILLE_CASE - halfHeight;
        }
    }

}
