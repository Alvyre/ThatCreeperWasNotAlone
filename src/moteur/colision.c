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
        box.pos.x += persos[i].dir.x * persos[i].vitesse;
        box.pos.y += persos[i].dir.y /*+ persos[i].gravite++*/;
        bool canMove = true;

        for (j = 0; j < nbJoueurs; ++j){
            if (i == j)
                continue;

            if (collide(box, persos[j].box)){
                canMove = false;
            }
        }
        if (canMove && persos[i].active) persos[i].box = box;
    }
}




bool collide(AABB a, AABB b){
   if((b.pos.x >= a.pos.x + a.size.x)      // trop à droite
    || (b.pos.x + b.size.x <= a.pos.x)     // trop à gauche
    || (b.pos.y >= a.pos.y + a.size.y)     // trop en bas
    || (b.pos.y + b.size.y <= a.pos.y))    // trop en haut
          return false; 
   else
          return true; 
}

void collisionsDecor(Personnage* persos, int nbJoueurs, int **level){
    int i,j,k;
    for ( k = 0; k < nbJoueurs; ++k){
        AABB boxPerso = persos[k].box;
        boxPerso.pos.x += persos[k].dir.x * persos[k].vitesse;
        boxPerso.pos.y += persos[k].dir.y + persos[k].gravite++;
        bool canMove = true;

        for ( i = persos[k].box.pos.y-10; i < (persos[k].box.pos.y+persos[k].box.size.y)+10 ; ++i){
            for (j = persos[k].box.pos.x-10; j < (persos[k].box.pos.x+persos[k].box.size.x)+10; ++j){
                if(i/32>=0 && j/32>=0 && i/32<=29 && j/32<=39){
                    
                    if(level[i/32][j/32] == 1){
                        //if(persos[k].active) printf("i = %d j = %d\n",i,j );
                        AABB boxDecor;
                        boxDecor.size.x = TAILLE_CASE;
                        boxDecor.size.y = TAILLE_CASE;
                        boxDecor.pos.x = j;
                        boxDecor.pos.y = i;
                        if(collide(boxPerso, boxDecor)){
                            canMove = false;
                            persos[k].gravite = persos[k].defaultGravite;
                            //printf("collisions decor !\n");
                        }
                    }
                }
            }
        }
        if (canMove && persos[k].active) persos[k].box = boxPerso;
    }
    


}