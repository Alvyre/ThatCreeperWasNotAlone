#ifndef COLISION_H
#define COLISION_H 
#include <SDL/SDL.h>
#include <math.h>
#include "main.h"
#include "perso.h"
#include "initialisation/level.h"


void collisions(Personnage* persos, int nbJoueurs, int **level);
bool collisionsAvecMap(AABB boxPerso, int** level, int widthLevel, int heightLevel);
bool collisionAvecJoueur(Personnage* persos, int nbJoueurs, AABB boxPerso,  int numeroJoueur);
bool collide(AABB a, AABB b);


#define SOLIDE 1		//bloc de type solide
#define END 2			//bloc de type fin du jeu

#endif /* COLISION_H */