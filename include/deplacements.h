#ifndef DEPLACEMENTS_H
#define DEPLACEMENTS_H 


#include "perso.h"
#include <SDL/SDL.h>

void directions(Personnage *perso, SDL_Event e, int **map);
void deplacement(Personnage *perso, int sens, int **map); 

#endif /* DEPLACEMENTS_H */