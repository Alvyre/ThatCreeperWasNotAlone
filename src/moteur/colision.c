/************************************/
/*   Gestion des collisions         */
/************************************/

#include "moteur/colision.h"

/**
 * Teste les collisions sur le haut du personnnage, sur toute sa largeur
 * 
 * @param *perso
 */
void collisionTop(Personnage *perso, int** level){
	int i = 0;
	int halfWidth = (int)ceil(perso->width/2.0);
	// colonne (grille) du perso, concernée par la colision (sens)
    int column = convertPixelToCase(perso->centerX + perso->vitesse * perso->sens);
	 // Haut perso
    int topPerso = convertPixelToCase(perso->centerY) - perso->height/2;

    // Parcours, les cases comprises entre le début et la fin du perso (en largeur)
    for (i = column-halfWidth; i <= column+halfWidth; i++)
    {
        if (level[topPerso][i] == 1 )
        {
            perso->gravite = 0;
            perso->gravite++;
        }
    }
}

/**
 * Parcours les cases devant et derière selon la largeur du solide et teste les collisions
 * FIXME : bug avec des perso ayant une hauteur impaire
 * 
 * @param *perso
 */
void collisionGround(Personnage *perso, int** level){
	int i = 0;
	// colonne (grille) du perso, concernée par la colision (sens)
	int column = convertPixelToCase(perso->centerX + perso->vitesse * perso->sens);
	//ligne (grille) du point bas du perso, on considère que ses pieds sont à 1 pixel du bord de la case
	int line = convertPixelToCase(perso->centerY+(perso->height/2.0));

	int halfHeight = (int)ceil(perso->height/2.0);

    for (i = column - perso->width/2; i <= column + perso->width/2; i++)
    {
        if (level[line+perso->height/2][i] == 1)
        {
            perso->gravite = 0;
            perso->centerY = convertCaseToPixel(line + halfHeight) - convertCaseToPixel(halfHeight);
        }
    }
}

/**
 * Collision latérales
 * Parcours les cases devant et derrière le solide, selon sa largeur puis test les collisions
 * Parcours le level en hauteur depuis le bas du solide jusqu'a sa hauteur maximum à la recherche d'obstacles
 * 
 * @param *perso
 */
void collisionLateral(Personnage *perso, int** level){
	int i = 0;
    int halfWidth = (int)ceil(perso->width/2.0);
    // colonne (grille) du perso, concernée par la colision (sens)
    int column = convertPixelToCase(perso->centerX + perso->vitesse * perso->sens);
    //ligne (grille) du point bas du perso, on considère que ses pieds sont à 1 pixel du bord de la case
    int line = convertPixelToCase(perso->centerY+(perso->height/2.0));
    float gap = 0;

    for (i = line + (perso->height-2)/2; i > line; i--)
    {

        if (level[i][column + halfWidth] == 1 || column+halfWidth >= convertPixelToCase(WINDOW_WIDTH))
        {
            if (perso->sens == 1){
                perso->centerX = convertCaseToPixel(column+halfWidth) - convertCaseToPixel(perso->width/2.0);
            }           
        }
        // si la case précédente est un bloc ou n'existe pas (bord)
        if (level[i][column-halfWidth] == 1 || column-halfWidth < 0){
            if (perso->sens == -1){
                // FIXME : trouver une façon plus propre d'ajouter 1 
                // pour les largeurs paires et 0.5 pour les impaires
                if ((perso->width)%2 == 0){
                    gap = 1;
                } else {
                    gap = 0.5;
                }
                perso->centerX = convertCaseToPixel(column+gap);
            }
        }
    }
}