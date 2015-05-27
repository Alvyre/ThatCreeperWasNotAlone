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

static unsigned int WINDOW_WIDTH = 1280; // 40
static unsigned int WINDOW_HEIGHT = 960; // 30

#define LINES WINDOW_HEIGHT/TAILLE_CASE //30
#define COLUMNS 80//WINDOW_WIDTH/TAILLE_CASE //40 /**********************FIXME*************
#endif /* MAIN_H */
