#ifndef SCROLLING_H
#define SCROLLING_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <stdbool.h>

#include "moteur/main.h"


typedef struct camera
{
	int formerX;
	int formerY;

	int currentX;
	int currentY;

	float Dx;
	float Dy;
	bool is_transition;
} Camera;
#include "moteur/perso.h"


void initCam(Personnage *perso, Camera *camera);
void scrolling(Camera *camera);
void centerCam(Personnage *perso, Camera *camera);
void smoothTransition(Camera *camera);

#endif /* SCROLLING_H */