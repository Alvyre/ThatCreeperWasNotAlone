#ifndef CARRE_H
#define CARRE_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h> 
#include "moteur/main.h"
#include "moteur/perso.h"
#include <math.h>

void dessinCarre(int i, int j, Color3f *color);
void dessinEmptyCarre(int posX, int posY, Color3f *color);
void dessinPerso(Personnage *perso);
void dessinActiveCursor(Personnage *perso);
void dessinMenu(GLuint textureID[10]);
void loadTexture(const char* filename, GLuint textureID[10], int numTexture);
#endif
