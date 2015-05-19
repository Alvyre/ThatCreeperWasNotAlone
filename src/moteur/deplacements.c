#include "moteur/deplacements.h"
#include "moteur/main.h"
#include "moteur/colision.h"
#include "initialisation/level.h"
#include <math.h>

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
        if (perso->haut && level[Ls+perso->height/2][k] == 1)
        {
            perso->gravite = -10;
            perso->haut = false;
        }
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
    int halfWidth = (int)ceil(perso->width/2.0);
    float gap = 0;
    for (i = Ls + (perso->height-2)/2; i > Ls; i--)
    {

        if (level[i][Cs + halfWidth] == 1 || Cs+halfWidth >= convertPixelToCase(WINDOW_WIDTH))
        {
            if (perso->sens == 1){
                perso->centerX = convertCaseToPixel(Cs+halfWidth) - convertCaseToPixel(perso->width/2.0);
            }           
        }
        // si la case précédente est un bloc ou n'existe pas (bord)
        if (level[i][Cs-halfWidth] == 1 || Cs-halfWidth < 0){
            if (perso->sens == -1){
                // FIXME : trouver une façon plus propre d'ajouter 1 
                // pour les largeurs paires et 0.5 pour les impaires
                if ((perso->width)%2 == 0){
                    gap = 1;
                } else {
                    gap = 0.5;
                }
                perso->centerX = convertCaseToPixel(Cs+gap);
            }
        }
    }

    /********************************
          TODO : COLLISIONS CIEL
    ********************************/
    // Haut perso
    int topPerso = convertPixelToCase(perso->centerY) - perso->height/2;

    // Parcours, les cases comprises entre le début et la fin du perso (en largeur)
    for (i = Cs-halfWidth; i <= Cs+halfWidth; i++)
    {
        if (level[topPerso][i] == 1 )
        {
            perso->gravite = 0;
            perso->gravite++;
        }
    }
    

}
