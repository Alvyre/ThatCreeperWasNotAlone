#ifndef DEPLACEMENTS_H
#define DEPLACEMENTS_H 

#include <SDL/SDL.h>

#include "moteur/perso.h"
#include "moteur/scrolling.h"

void deplacementJoueur(Personnage *perso, int** level, Camera *camera);


#endif /* DEPLACEMENTS_H */