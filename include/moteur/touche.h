#ifndef TOUCHE_H
#define TOUCHE_H 


#include "moteur/perso.h"
#include <SDL/SDL.h>


void appuyer(Personnage *perso, SDL_Event e);
void relacher(Personnage *perso, SDL_Event e);

#endif /* TOUCHE_H */TOUCHE_H