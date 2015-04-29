#include "moteur/deplacements.h"
#include "moteur/main.h"
#include "moteur/colision.h"

/************************************/
/*   Gestion des déplacements       */
/************************************/

void deplacementJoueur(Personnage *perso, int** level){

    int L;                                                                                                                                          // ligne (grille) du centre du perso
    int C;                                                                                                                                          // colonne (grille) du centre du perso
    int Ls;                                                                                                                                         // ligne (grille) du point bas du perso, on considère que ses pieds sont à 1 pixel du bord de la case
    int Cs;                                                                                                                                         // colonne (grille) du bord du perso dans le sens de son déplacement
    int A;                                                                                                                                          // la tuile située sous le perso
    uint Y;                                                                                                                                         // position sur Y avant déplacement
    int* P = calloc(2,sizeof(int));                                                                                                                 // tableau de positions

        perso->centerX += perso->vitesse * perso->sens;                                                                                             // déplace sur X
        
        L =  perso->centerY/TAILLE_CASE;                                                                                                            // ligne (grille) du centre du perso
        C =  perso->centerX/TAILLE_CASE;                                                                                                            // colonne (grille) du centre du perso
        Ls = (perso->centerY+TAILLE_CASE-1)/TAILLE_CASE;                                                                                            // ligne (grille) du point bas du perso, on considère que ses pieds sont à 1 pixel du bord de la case
        Cs = (perso->centerX + perso->vitesse * perso->sens) / TAILLE_CASE;                                                                         // colonne (grille) du perso, concernée par la colission (sens)
        
        checkLateral(perso,L,Cs,perso->vitesse*2,(perso->centerY-TAILLE_CASE/2)/TAILLE_CASE,P,level);                                               // collisions latérales
        
        L =  P[0];                                                                                                                                  // nouvelle valeur de L
        Cs = P[1];                                                                                                                                  // nouvelle valeur de Cs
        A =  level[L][C];                                                                                                                           // la tuile située sous le perso
        Y =  (L-1)*TAILLE_CASE;                                                                                                                     // la position sur Y avant collision    


        perso->centerY += perso->gravite;                                                                                                           // déplace sur Y

        if (perso->gravite < 0 && checkPlafond(perso,C,(perso->centerY-TAILLE_CASE/2)/TAILLE_CASE,perso->vitesse*2,TAILLE_CASE/2,level)) return;    // collision plafond
        if (A == 1  && checkSolide(perso,Y)) return;                                                                                                // collision tout solide
        
        if (perso->gravite++>TAILLE_CASE) perso->gravite=TAILLE_CASE;                                                                               // gravité
        free (P);
    }










































/************************************/
/*   Gestion des déplacements       */
/************************************/



// void deplacement(Personnage *perso, int **map) {

//     /* deplacement latéral  */

//     perso->centerX += perso->vitesse * perso->sens;                                                // X = vitesse * sens


//     /* Colisions */

//     int C = (perso->centerX + (perso->width*TAILLE_CASE/2.0) * perso->sens)/TAILLE_CASE;          // Colonne à tester pour la colision
//     int L = perso->centerY / TAILLE_CASE-perso->height/2.0;


//     // Colision latérale
//     for (; L<perso->centerY/(TAILLE_CASE+perso->height/2.0); L++) {
//         if (map[L][C]==1) {
//             perso->centerX = C*TAILLE_CASE + TAILLE_CASE/2 -TAILLE_CASE*perso->sens;
//         }
//     }

//     // Colision sol + saut

//     perso->centerY += perso->gravite;

    
//     for (C = (perso->centerX - (perso->width*TAILLE_CASE/2) )/TAILLE_CASE; C<(perso->centerX+(perso->width*TAILLE_CASE/2))/TAILLE_CASE; C++) { 
//         if (map[L][C] == 1 && perso->centerY >= (L-perso->height/2.0)*TAILLE_CASE) {   
//             perso->centerY = (L-perso->height/2.0)*TAILLE_CASE;
//             perso->gravite = -1*(int)(perso->saute)*11;
//             return;             
//         }
//     }

//     if (perso->gravite++ > TAILLE_CASE) perso->gravite = TAILLE_CASE;

//     // Colision roof
//     if (perso->gravite < 0) {                    
//         L = (perso->centerY-(perso->height*TAILLE_CASE/2))/TAILLE_CASE;                   
//         for (C=(perso->centerX-(perso->width*TAILLE_CASE/2))/TAILLE_CASE; C<(perso->centerX+(perso->width*TAILLE_CASE/2))/TAILLE_CASE; C++) { 
//             if (map[L][C] > 0) {      
//                 perso->centerY = (L+2)*TAILLE_CASE-(perso->height*TAILLE_CASE/2);
//                 perso->gravite=1;
//             }
//         }
//     }
// }
