#ifndef LEVEL_H
#define LEVEL_H
#include <stdbool.h> //FXIME
#include <stdio.h> // FIXME
#include <stdlib.h> //FIXME

void initLevel(int** level);
void freeLevel(int** level);
void creeDecor(int **level);
bool isPixelGround(int pixelX, int pixelY, int **level);
int convertPixelToCase(int pixel);
int convertCaseToPixel(int Case);


#endif /* LEVEL_H */