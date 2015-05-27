#ifndef LEVEL_H
#define LEVEL_H
#include "moteur/main.h"

typedef struct Level {
 int width;
 int height;
 int** map;
}Level;

Level* initLevel(Level* level, int width, int height);
void freeLevel(Level* level);
void creeDecor(Level* level);
Level* loadLevelFromFile(char const * path, int persoInfos[3][8], int *nbrPerso);
char const *selectLevelFromNumber(int levelNumber);

#endif /* LEVEL_H */
