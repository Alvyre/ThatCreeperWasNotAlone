#ifndef DEPLACEMENTS_H
#define DEPLACEMENTS_H 


#include "moteur/perso.h"
#include <SDL/SDL.h>
#include "moteur/scrolling.h"

void deplacementJoueur(Personnage *perso, int** level, Camera *camera);
//void deplacement(Personnage *perso, int** map); 

#endif /* DEPLACEMENTS_H */