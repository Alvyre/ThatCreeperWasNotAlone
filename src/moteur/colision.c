/************************************/
/*   Gestion des collisions         */
/************************************/

#include "moteur/colision.h"

/**
 * Parcours les cases devant et derière selon la largeur du solide et teste les collisions
 * FIXME : bug avec des perso ayant une hauteur impaire : il se place bien mais ne veut plus sauter à moins de définir une gravité énorme à chaque saut genre -25 dans touche.c
 * 
 * @param *perso
 */
 bool collisionGround(Personnage *perso, int** level){
    int i = 0;
	// colonne (grille) du perso, concernée par la colision (sens)
   int column = convertPixelToCase(perso->centerX + perso->vitesse * perso->sens);
	//ligne (grille) du point bas du perso, on considère que ses pieds sont à 1 pixel du bord de la case
   int line = convertPixelToCase(perso->centerY + (perso->height/2.0));

   int halfWidth = (perso->width/2.0);
   int halfHeight = (int)ceil(perso->height/2.0);

   // FIXME : Trouver une façon plus propre de régler ça
   // if (perso->lastDirection == 1)
   // {  
        for (i = floor((perso->centerX)/32 - halfWidth); i <= ceil((perso->centerX)/32 + halfWidth); i++)
        {
            
           if (level[line + halfHeight][i] == 1)
           {
            perso->gravite = 10;
            perso->centerY = convertCaseToPixel(line + perso->height/2.0) - convertCaseToPixel(perso->height/2.0);
            perso->saute = false;
            return true;

            }
        }
    // } else {
    //     for (i = column - halfWidth; i <= column + halfWidth; i++)
    //     {
    //         if (level[line + halfHeight][i] == 1)
    //         {
    //             perso->gravite = 10;
    //             perso->centerY = convertCaseToPixel(line + perso->height/2.0) - convertCaseToPixel(perso->height/2.0);
    //             perso->saute = false;
    //             return true;

    //         }
    //     }
    // }
    return false;
}

int collisionLateral(Personnage *perso, int** level){

    int Y = perso->centerY;
    int X = perso->centerX;

    float halfWidth = perso->width/2.0;
    float halfHeight = perso->height/2.0;

    int C = floor((X + (halfWidth*TAILLE_CASE) * perso->sens) / TAILLE_CASE);    
    int L = floor((Y - (halfHeight*TAILLE_CASE)) / TAILLE_CASE);
 
    // latéral                          
    for (; L < (Y/TAILLE_CASE) +floor(halfHeight); L++) {
        if (level[L][C]==1 && perso->sens == 1) {
            perso->centerX = C * TAILLE_CASE + floor(halfWidth) - halfWidth*TAILLE_CASE * perso->sens -2;
        }
        else if (level[L][C]==1 && perso->sens == -1) {
            if(perso->width %2==0) perso->centerX = C * TAILLE_CASE - floor(halfWidth) - perso->width*TAILLE_CASE * perso->sens +1;
            else                   perso->centerX = C * TAILLE_CASE - floor(halfWidth) - perso->width*TAILLE_CASE * perso->sens +1;
        }
        printf("L = %d\n",L );
    }
}




    // // Bas du perso
    // int i1 = floor(convertPixelToCase(perso->centerX) - perso->width/2.0); // FIXME : impaire width
    // int j1 = floor(convertPixelToCase(perso->centerY) - perso->height/2.0);

    // // Haut du perso
    // int i2 = ceil(convertPixelToCase(perso->centerX) + perso->width/2.0); // FIXME : impaire width
    // int j2 = ceil(convertPixelToCase(perso->centerY) + perso->height/2.0);    

    // int i = 0;
    // int j = 0;

    // // Latéral
    // for (i = i1; i <= i2; i++)
    // {
    //     // Haut et bas
    //     for (j = j1; j <= j2 -1; j++)
    //     {
    //         //printf("j %d\n", j);
    //         if (level[j][i] == 1)
    //         {

    //             // // Collisions avant ou arrière
    //             // if (i > i1)
    //             // {
    //             //     return 1;
    //             // }else {
    //             //     return -1;
    //             // }
    //         }
    //     }
    // }
    // return 0;
    //}

int testCollisonGround(Personnage *perso, int** level){
    int i1 = floor(convertPixelToCase(perso->centerX) - perso->width/2.0); // FIXME : impaire width
    int j1 = floor(convertPixelToCase(perso->centerY) - perso->height/2.0);

    // Haut du perso
    int i2 = ceil(convertPixelToCase(perso->centerX) + perso->width/2.0); // FIXME : impaire width
    int j2 = ceil(convertPixelToCase(perso->centerY) + perso->height/2.0);   

    int i = 0;
    int j = 0;

    // Latéral
    for (i = i1; i <= i2; i++)
    {
        // Haut et bas
        for (j = j1; j <= j2; j++)
        {
            if (level[j][i] == 1)
            {
                // collision haut ou bas
               if (j > j1)
                {
                    //printf("-1\n");
                    return -1;
                } else {
                    //printf("1\n");
                    return 1;
                }
            }
        }
    }
    return 0;

}
