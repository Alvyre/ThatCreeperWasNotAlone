#ifndef COLISION_H
#define COLISION_H 

#include "main.h"
#include "perso.h"
#include <SDL/SDL.h>

void checkLateral(Personnage *perso,int L, int C, uint D, int H, int* result, int** level);
bool checkSolide(Personnage *perso,uint Y);
bool checkPlafond(Personnage *perso,int C,int L,uint D,uint H, int **level);
bool hit(Personnage *perso,uint Y);

#endif /* COLISION_H */