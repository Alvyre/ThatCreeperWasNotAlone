#ifndef SCROLLING_H
#define SCROLLING_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include "moteur/perso.h"
#include "moteur/main.h"
#include "initialisation/level.h"


typedef struct camera
{
	int x;
	int y;
} Camera;



void initCam(Personnage *perso, Camera *camera);
void moveCamera(Personnage *perso, Camera *camera, Level* level);

#endif /* SCROLLING_H */
