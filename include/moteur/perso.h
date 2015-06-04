#ifndef PERSO_H
#define PERSO_H


#include "moteur/main.h"
#include "initialisation/level.h"
#include <stdbool.h>

typedef struct Vector2i {
 int x, y;
}Vector2i;

typedef struct AABB {
 Vector2i pos, size;
}AABB;


typedef struct Personnage
{
	int id;
	//position et direction
	AABB box;
	Vector2i dir;
	int initialPosY;
	int initialPosX;
	//couleur
	Color3f color;
	// variables touches
	bool gauche;
	bool droite;
	bool haut;
	bool bas;
	// variables déplacements
	int defaultGravite;
	int gravite;
	int vitesse;
	int sens;
	// variables mouvements
	bool saute;
	// perso actif (controlable) ou pas
	bool active;
	int cursorTimer;
	bool end;
}Personnage;


#include "moteur/camera.h"

void initPerso(Personnage *personnage, int id, int width, int height, int posCaseX, int posCaseY, Color3f color, int gravite);
void gestionJoueur(Personnage *persoHandler, int nbrPerso);
void changeFocus(Personnage *persoHandler, int nbrPerso, Level* level);


#endif /* PERSO_H */
