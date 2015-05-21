#ifndef PERSO_H
#define PERSO_H


#include "moteur/main.h"
#include <stdbool.h>

typedef struct Personnage
{
	int centerX;
	int centerY;
	int width;
	int height;
	Color3f color;
	// variables touches
	bool gauche;
	bool droite;
	int lastDirection;
	bool haut;
	bool bas;
	// variables déplacements
	int gravite;
	int vitesse;
	int sens;
	// variables mouvements
	bool lateral;
	bool saute;
	bool repos;

	bool active; // perso actif (controlable) ou pas


}Personnage;


void initPerso(Personnage *personnage, int width, int height, int posCaseX, int posCaseY, Color3f color);
void gestionJoueur(Personnage *perso, int** map);


#endif /* PERSO_H */