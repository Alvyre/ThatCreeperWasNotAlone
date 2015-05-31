#ifndef DEPLACEMENTS_H
#define DEPLACEMENTS_H 

#include <SDL/SDL.h>

#include "moteur/perso.h"
#include "moteur/camera.h"
#include "initialisation/level.h"

void deplacementJoueur(Personnage *persoHandler, int nbrPerso, Level *level);

#endif /* DEPLACEMENTS_H */
