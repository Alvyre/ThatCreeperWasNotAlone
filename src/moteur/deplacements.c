#include "moteur/deplacements.h"
#include "moteur/main.h"
#include "moteur/colision.h"
#include "initialisation/level.h"

/************************************/
/*   Gestion des déplacements       */
/************************************/

void deplacementJoueur(Personnage *perso, int** level){

    int Ls;                                                                                                                                         // ligne (grille) du point bas du perso, on considère que ses pieds sont à 1 pixel du bord de la case
    int Cs;                                                                                                                                         // colonne (grille) du bord du perso dans le sens de son déplacement

    // Déplace en X
    if (perso->droite || perso->gauche)
    {
        perso->centerX += perso->vitesse * perso->sens;
    }

    // Saut
    // FIXME : long press
    if (perso->haut)
    {
        perso->gravite = -10;
        perso->haut = false;
    }

    // Gravité s'applique toujours meme si le perso ne saute pas
    perso->centerY += perso->gravite++;
    
    // ligne (grille) du point bas du perso, on considère que ses pieds sont à 1 pixel du bord de la case
    Ls = convertPixelToCase(perso->centerY+(perso->height/2.0));
    // colonne (grille) du perso, concernée par la colision (sens)
    Cs = convertPixelToCase(perso->centerX + perso->vitesse * perso->sens);
    

    /****************************************
            A DEPLACER DANS FONCTIONS
            UNE FOIS LES TEST TERMINES
    ****************************************/
    // Collisions avec le sol
    // Parcours les cases devant et derière selon la largeur du solide et teste les collisions
    // FIXME : bug avec des perso ayant une hauteur impaire
    int k = 0;
    for (k = Cs - perso->width/2; k <= Cs + perso->width/2; k++)
    {
        if (level[Ls+perso->height/2][k] == 1)
        {
            perso->gravite = 0;
            perso->centerY = convertCaseToPixel(Ls + perso->height/2.0) - convertCaseToPixel(perso->height/2.0);
        }
    }


    // Collision latérales
    // Parcours les cases devant et derrière le solide, selon sa largeur puis test les collisions
    // Parcours le level en hauteur depuis le bas du solide jusqu'a sa hauteur maximum à la recherche d'obstacles
    // Trouver d'ou vient cette putain de formule magique :  Ls + (perso->height-2)/2
    int i = 0;
    int j = 0;
    for (i = Ls + (perso->height-2)/2; i > Ls-perso->height; i--)
    {
        for (j = Cs - perso->width; j < Cs+perso->width; j++)
        {
            if (level[i][Cs+1] == 1)
            {
                if (perso->sens == 1){
                    perso->centerX = convertCaseToPixel(Cs+1) - convertCaseToPixel(perso->width/2.0);
                }
               
            }
            if (level[i][Cs-1] == 1){
                if (perso->sens == -1){
                    perso->centerX = convertCaseToPixel(Cs)+(perso->width *(TAILLE_CASE/2));
                }
            }
        }
    }

    /********************************
          TODO : COLLISIONS CIEL
    ********************************/
}
