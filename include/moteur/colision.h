#ifndef COLISION_H
#define COLISION_H 
#include <SDL/SDL.h>
#include <math.h>
#include "main.h"
#include "perso.h"
#include "initialisation/level.h"


void collisionTop(Personnage *perso, int** level);
void collisionGround(Personnage *perso, int** level);
void collisionLateral(Personnage *perso, int** level);

#endif /* COLISION_H */