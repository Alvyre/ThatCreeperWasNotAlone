#include "moteur/deplacements.h"
#include "moteur/main.h"
#include "moteur/colision.h"
#include "initialisation/level.h"

/************************************/
/*   Gestion des déplacements       */
/************************************/

void deplacementJoueur(Personnage *perso, int** level){

    int ligne;                                                                                                                                          // ligne (grille) du centre du perso
    int colonne;                                                                                                                                          // colonne (grille) du centre du perso
    int Ls;                                                                                                                                         // ligne (grille) du point bas du perso, on considère que ses pieds sont à 1 pixel du bord de la case
    int Cs;                                                                                                                                         // colonne (grille) du bord du perso dans le sens de son déplacement
    int A;                                                                                                                                          // la tuile située sous le perso
    uint Y;                                                                                                                                         // position sur Y avant déplacement
    int* P = calloc(2,sizeof(int));                                                                                                                 // tableau de positions

    // Déplace en X
    if (perso->droite || perso->gauche)
    {
        perso->centerX += perso->vitesse * perso->sens;
    }

    // ligne (grille) du centre du perso
    ligne =  perso->centerY/TAILLE_CASE;
    // colonne (grille) du centre du perso
    colonne =  perso->centerX/TAILLE_CASE;

    // Gravité s'applique toujours meme si le perso ne saute pas
    int gravite = perso->gravite;
    //perso->gravite++;
    gravite++;
    perso->centerY += gravite;
    
    // ligne (grille) du point bas du perso, on considère que ses pieds sont à 1 pixel du bord de la case
    Ls = (perso->centerY+(perso->height/2))/TAILLE_CASE; 
    // colonne (grille) du perso, concernée par la colision (sens)
    Cs = (perso->centerX + perso->vitesse * perso->sens) / TAILLE_CASE;
    
    // FIXME : bug avec des perso ayant une hauteur impaire
    if (level[Ls+perso->height/2][Cs] == 1)
    {
        gravite = 0;
        perso->centerY = convertCaseToPixel(Ls + perso->height/2) - TAILLE_CASE*(perso->height/2.0);
    }

    if (perso->haut)
    {
        perso->centerY += perso->saute;
    }
        
    //checkLateral(perso,ligne,Cs,perso->vitesse*2,(perso->centerY-TAILLE_CASE/2)/TAILLE_CASE,P,level);                                               // collisions latérales
        
    //     ligne =  P[0];                                                                                                                                  // nouvelle valeur de L
    //     // Cs = P[1];                                                                                                                                  // nouvelle valeur de Cs
         //Y =  (ligne-1)*TAILLE_CASE;                                                                                                                     // la position sur Y avant collision    


        //if (perso->gravite <= 0 ) return;    // collision plafond
        //if (level[ligne][colonne] == 1  && checkSolide(perso,Y)) return;                                                                                                // collision tout solide

        // Passe au moins une fois dans ce if ??
        //if (perso->gravite++>TAILLE_CASE) perso->gravite=TAILLE_CASE;                                                                               // gravité
        free (P);
}
