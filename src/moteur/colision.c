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
 * FIXME : bug avec des perso ayant une hauteur impaire : il se place bien mais ne veut plus sauter à moins de définir une gravité énorme à chaque saut genre -25 dans touche.c
 * 
 * @param *perso
 */
void collisionGround(Personnage *perso, int** level){
	int i = 0;
	// colonne (grille) du perso, concernée par la colision (sens)
	int column = convertPixelToCase(perso->centerX + perso->vitesse * perso->sens);
	//ligne (grille) du point bas du perso, on considère que ses pieds sont à 1 pixel du bord de la case
	int line = convertPixelToCase(perso->centerY + (perso->height/2.0));
	
	int halfWidth = (int)ceil(perso->width/2.0);
	int halfHeight = (int)ceil(perso->height/2.0);

    for (i = column - halfWidth; i <= column + halfWidth; i++)
    {
         if (level[line + halfHeight][i] == 1)
        {
            perso->gravite = 10;
            perso->centerY = convertCaseToPixel(line + perso->height/2.0) - convertCaseToPixel(perso->height/2.0);
            perso->saute = false;
           
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
    int halfHeight = (int)ceil(perso->height/2.0);
    // colonne (grille) du perso, concernée par la colision (sens)
    int column = convertPixelToCase(perso->centerX + perso->vitesse * perso->sens);
    //ligne (grille) du point bas du perso, on considère que ses pieds sont à 1 pixel du bord de la case
    int line = convertPixelToCase(perso->centerY + (perso->height/2.0));
    float gap = 0;
    
    // Parcours de bas en haut le personnage pour tester les collisions
    for (i = line + halfHeight - 1; i >= line - (perso->height/2); i--)
    {

        if (level[i][column + halfWidth] == 1 || column + halfWidth >= convertPixelToCase(WINDOW_WIDTH))
        {
            if (perso->sens == 1){
                perso->centerX = convertCaseToPixel(column + halfWidth) - convertCaseToPixel(perso->width/2.0);
            }           
        }
        // si la case précédente est un bloc ou n'existe pas (bord)
        if (level[i][column - halfWidth] == 1 || column - halfWidth < 0){
            if (perso->sens == -1){
                // FIXME : trouver une façon plus propre d'ajouter 1 
                // pour les largeurs paires et 0.5 pour les impaires
                if ((perso->width)%2 == 0){
                    gap = 1;
                } else {
                    gap = 0.5;
                }
                perso->centerX = convertCaseToPixel(column + gap);
            }
        }
    }
}