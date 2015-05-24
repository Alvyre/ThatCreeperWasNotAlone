#ifndef COLISION_H
#define COLISION_H 
#include <SDL/SDL.h>
#include <math.h>
#include "main.h"
#include "perso.h"
#include "initialisation/level.h"


bool collisionTop(Personnage *perso, int** level);
bool collisionGround(Personnage *perso, int** level);
void collisionLateral(Personnage *perso, int** level);
bool collisionRoof(Personnage *perso, int** level);
void collisionsJoueur(Personnage *perso1, Personnage *perso2);
#endif /* COLISION_H */