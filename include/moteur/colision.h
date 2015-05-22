#ifndef COLISION_H
#define COLISION_H 
#include <SDL/SDL.h>
#include <math.h>
#include "main.h"
#include "perso.h"
#include "initialisation/level.h"


bool collisionTop(Personnage *perso, int** level);
bool collisionGround(Personnage *perso, int** level);
int collisionLateral(Personnage *perso, int** level);
int testCollisonGround(Personnage *perso, int** level);
#endif /* COLISION_H */