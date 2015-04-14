#include "perso.h"

void initPerso(Personnage *personnage, int width, int height, int posCaseX, int posCaseY, Color3f color){

	personnage->centerX = posCaseX + TAILLE_CASE /2;
	personnage->centerX = posCaseY+ TAILLE_CASE /2;
	personnage->posCaseX = posCaseX;
	personnage->posCaseY = posCaseY;
	personnage->posX = posCaseX * TAILLE_CASE;
	personnage->posY = posCaseY * TAILLE_CASE;
	personnage->width = width;
	personnage->height = height;
	personnage->color.r = color.r;
	personnage->color.g = color.g;
	personnage->color.b = color.b;
	personnage->gravite = 0;
	personnage->vitesse = 5;
	personnage->sens = 0;
	personnage->lateral = false;
	personnage->saute = false;
	personnage->repos = true;
}