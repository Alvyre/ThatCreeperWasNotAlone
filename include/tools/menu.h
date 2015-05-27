#ifndef MENU_H
#define MENU_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include "moteur/main.h"

typedef struct Menu{
	bool active;
	int levelNumber;
} Menu;

void touchesMenu(SDL_Event e, Menu *menu);
void menuHandler(Menu* menu, int sens);

#endif
