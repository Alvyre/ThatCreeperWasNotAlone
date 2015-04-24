#ifndef DEPLACEMENTS_H
#define DEPLACEMENTS_H 


#include "perso.h"
#include <SDL/SDL.h>


void appuyer(Personnage *perso, SDL_Event e);
void relacher(Personnage *perso, SDL_Event e);
// void directions(Personnage *perso, SDL_Event e, int **map);
void deplacement(Personnage *perso, int** map); 

#endif /* DEPLACEMENTS_H */