#ifndef COLISION_H
#define COLISION_H 
#include <SDL/SDL.h>
#include <math.h>
#include "main.h"
#include "perso.h"
#include "initialisation/level.h"


void collisions(Personnage* persos, int nbJoueurs, Level *level);
bool collisionsAvecMap(AABB boxPerso, Personnage* perso, Level *level);
bool collisionAvecJoueur(Personnage* persos, int nbJoueurs, AABB boxPerso,  int numeroJoueur);
bool collide(AABB a, AABB b);



#define END_PERSO_1 -1			//bloc de type fin du jeu
#define END_PERSO_2 -2
#define END_PERSO_3 -3

#endif /* COLISION_H */
