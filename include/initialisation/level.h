#ifndef LEVEL_H
#define LEVEL_H
#include <stdbool.h> //FIXME
#include <stdio.h> // FIXME
#include <stdlib.h> //FIXME

void initLevel(int** level);
void freeLevel(int** level);
void creeDecor(int** level);
bool isPixelGround(int pixelX, int pixelY, int **level);
int convertPixelToCase(int pixel);
int convertCaseToPixel(float Case);
void loadLevelFromFile(int** level, char const * path, int persoInfos[3][8],int *nbrPerso);


#endif /* LEVEL_H */
