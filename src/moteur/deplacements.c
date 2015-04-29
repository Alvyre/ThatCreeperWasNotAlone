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
        Cs = (perso->centerX + perso->vitesse * perso->sens) / TAILLE_CASE;                                                                         // colonne (grille) du perso, concernée par la colision (sens)
        
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
