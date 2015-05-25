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


    int Y = perso->box.pos.y + perso->box.size.y/2;
    int X = perso->box.pos.x + perso->box.size.x/2;

    float halfWidth = perso->box.size.x/(2*TAILLE_CASE);
    float halfHeight = perso->box.size.y/(2*TAILLE_CASE);

    int C = (X - (halfWidth * TAILLE_CASE)) / TAILLE_CASE;
    int L = (Y + (halfHeight * TAILLE_CASE)) / TAILLE_CASE;


    for ( ; C <= floor((X + (halfWidth * TAILLE_CASE)) / TAILLE_CASE)  ; C++){

        if(level[L][C] == 1 &&  Y >=(L - halfHeight)*TAILLE_CASE){

            switch((int)(halfHeight*2)){                                                      // SWITCH pour corriger la position selon la hauteur du perso (1-6)
                case 1:
                case 2:
                    perso->box.pos.y = (L - halfHeight)*TAILLE_CASE - halfHeight +1 - perso->box.size.y/2.0 ;
                    break;
                case 3:
                case 4:
                    perso->box.pos.y = (L - halfHeight)*TAILLE_CASE - halfHeight +2 - perso->box.size.y/2.0 ;
                    break;
                case 5:
                case 6:
                    perso->box.pos.y = (L - halfHeight)*TAILLE_CASE - halfHeight +3 - perso->box.size.y/2.0 ;
                    break;

                default:
                    perso->box.pos.y = (L - halfHeight)*TAILLE_CASE - halfHeight +1 - perso->box.size.y/2.0 ;
                    break;
            }

            perso->gravite = perso->defaultGravite;
            perso->saute = false;
            return true;
        }
    }
    return false;
}

void collisionLateral(Personnage *perso, int** level){

    int Y = perso->box.pos.y + perso->box.size.y/2;
    int X = perso->box.pos.x + perso->box.size.x/2;

    float halfWidth = perso->box.size.x/(2*TAILLE_CASE);
    float halfHeight = perso->box.size.y/(2*TAILLE_CASE);

    int C = floor((X + (halfWidth*TAILLE_CASE) * perso->sens) / TAILLE_CASE);    
    int L = floor((Y - (halfHeight*TAILLE_CASE)) / TAILLE_CASE);
 
                         

    for (; L < (Y/TAILLE_CASE) +floor(halfHeight)-1; L++) {
        if (level[L][C]==2)
        {
            perso->end = true;   
        }
        if (level[L][C]==1 && perso->sens == 1) {
            perso->box.pos.x = C * TAILLE_CASE + floor(halfWidth) - halfWidth*TAILLE_CASE * perso->sens -2 - perso->box.size.x/2;
        }
        else if (level[L][C]==1 && perso->sens == -1) {
            if((int)(perso->box.size.x/TAILLE_CASE) %2==0) perso->box.pos.x = C * TAILLE_CASE - floor(halfWidth) - (perso->box.size.x/TAILLE_CASE)*TAILLE_CASE * perso->sens +1 - perso->box.size.x/2;
            else {
               perso->box.pos.x = C * TAILLE_CASE - floor(halfWidth) - halfWidth*TAILLE_CASE * perso->sens +1*TAILLE_CASE +1 - perso->box.size.x/2 ;
            }                 
        }

    }
}


// bool collisionRoof(Personnage *perso, int** level){

//     int Y = perso->centerY;
//     int X = perso->centerX;

//     float halfHeight = perso->height/2.0;
//     float halfWidth = perso->width/2.0;

//     int C = (X - (halfWidth * TAILLE_CASE)) / TAILLE_CASE;
//     int L = (Y - (halfHeight * TAILLE_CASE)) / TAILLE_CASE;

//     for ( ; C <= floor((X + (halfWidth * TAILLE_CASE)) / TAILLE_CASE)  ; C++){

//         if(level[L][C] == 1){
//             perso->centerY = (L+2)*TAILLE_CASE - halfHeight;
//             perso->saute = false;
//             perso->gravite = perso->defaultGravite;
//             perso->centerY += perso->gravite++;
//             return true;
//         }
//     }
//     return false;
// }


void collisionsJoueurs(Personnage* persos, int nbJoueurs){
    int i,j;
    for (i = 0; i < nbJoueurs; ++i){

        AABB box = persos[i].box;
        box.pos.x += persos[i].dir.x;
        box.pos.y += persos[i].dir.y;
        bool canMove = true;

        for (j = 0; j < nbJoueurs; ++j){
            if (i == j)
                continue;

            if (collide(box, persos[j].box)){
                canMove = false;
                printf("collisions !!\n");
            }
        }
        if (canMove) persos[i].box = box;
    }
}




bool collide(AABB a, AABB b){
    if (a.pos.x >= b.pos.x + b.size.x
     && a.pos.x <  b.pos.x + b.size.x
     && a.pos.y >= b.pos.y
     && a.pos.y <  b.pos.y + b.size.y)
        return true;

    return false;
}
