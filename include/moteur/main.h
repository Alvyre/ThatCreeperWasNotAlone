#ifndef MAIN_H
#define MAIN_H

#ifndef TAILLE_CASE
#define TAILLE_CASE 32
#endif

typedef struct Color3f
{
	float r;
	float g;
	float b;
} Color3f;

/**** Tailles possibles : 1280 x 960 / 1024 x 768 / 800 x 600
	  /!\ Faire un make clean après changement /!\            ****/
static int WINDOW_WIDTH = 1024;
static int WINDOW_HEIGHT = 768;

#endif /* MAIN_H */
