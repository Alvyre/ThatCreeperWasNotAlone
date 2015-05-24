#ifndef CARRE_H
#define CARRE_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "moteur/main.h"
#include "moteur/perso.h"
#include <math.h>

void dessinCarre(int i, int j, Color3f *color);
void dessinPerso(Personnage *perso);
void dessinActiveCursor(Personnage *perso);
#endif