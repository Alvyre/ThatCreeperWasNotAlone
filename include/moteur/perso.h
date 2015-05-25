#ifndef PERSO_H
#define PERSO_H


#include "moteur/main.h"
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

	bool active; // perso actif (controlable) ou pas
	int cursorTimer;
	bool end;

	//test
	AABB box;
	Vector2i dir;

}Personnage;


#include "moteur/scrolling.h"

void initPerso(Personnage *personnage, int id, int width, int height, int posCaseX, int posCaseY, Color3f color, int gravite);
void gestionJoueur(Personnage *persoHandler, int nbrPerso);
void changeFocus(Personnage *persoHandler, int nbrPerso, Camera *camera);


#endif /* PERSO_H */
