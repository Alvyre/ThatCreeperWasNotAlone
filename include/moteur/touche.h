#ifndef TOUCHE_H
#define TOUCHE_H 


#include "moteur/perso.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

void appuyer(Personnage *perso, SDL_Event e, int numPerso, Mix_Chunk *bruitages[3]);
void relacher(Personnage *perso, SDL_Event e, int numPerso, Mix_Chunk *bruitages[3]);

#endif /* TOUCHE_H */