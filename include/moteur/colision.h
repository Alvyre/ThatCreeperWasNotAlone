#ifndef COLISION_H
#define COLISION_H 
#include <SDL/SDL.h>
#include <math.h>
#include "main.h"
#include "perso.h"
#include "initialisation/level.h"


//bool collisionTop(Personnage *perso, int** level);
bool collisionGround(Personnage *perso, int** level);
//void collisionLateral(Personnage *perso, int** level);
//bool collisionRoof(Personnage *perso, int** level);
bool collide(AABB a, AABB b);
bool collideWithMap(AABB boxPerso, int** level, int widthLevel, int heightLevel);
void collisionsJoueurs(Personnage* persos, int nbJoueurs);
void collisions(Personnage* persos, int nbJoueurs, int **level);
#endif /* COLISION_H */