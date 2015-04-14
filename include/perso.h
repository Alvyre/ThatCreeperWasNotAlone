#ifndef PERSO_H
#define PERSO_H


#include "main.h"
#include <stdbool.h>

typedef struct Personnage
{
	int centerX;
	int centerY;
	int width;
	int height;
	int posCaseX;
	int posCaseY;
	int posX;
	int posY;
	Color3f color;
	// variables déplacements
	int gravite;
	int vitesse;
	int sens;
	// variables mouvements
	bool lateral;
	bool saute;
	bool repos;


}Personnage;


void initPerso(Personnage *personnage, int width, int height, int posCaseX, int posCaseY, Color3f color);

#endif /* PERSO_H */