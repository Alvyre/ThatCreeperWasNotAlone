#ifndef COLISION_H
#define COLISION_H 
#include <SDL/SDL.h>
#include <math.h>
#include "main.h"
#include "perso.h"
#include "initialisation/level.h"


void collisions(Personnage* persos, int nbJoueurs, int **level);
bool collisionsAvecMap(AABB boxPerso, Personnage* perso, int** level, int widthLevel, int heightLevel);
bool collisionAvecJoueur(Personnage* persos, int nbJoueurs, AABB boxPerso,  int numeroJoueur);
bool collide(AABB a, AABB b);


#define SOLIDE 1		//bloc de type solide
#define END_PERSO_1 2			//bloc de type fin du jeu
#define END_PERSO_2 3
#define END_PERSO_3 4

#endif /* COLISION_H */
