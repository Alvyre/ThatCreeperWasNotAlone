#ifndef LEVEL_H
#define LEVEL_H
#include "moteur/main.h"
#include <stdbool.h>

typedef struct Tile
{
	int value;
	bool is_solid;

}Tile;


typedef struct Level {
 int width;
 int height;
 int persoActive;
 Tile** map;
}Level;

Level* initLevel(Level* level, int width, int height);
void freeLevel(Level* level);
void creeDecor(Level* level);
Level* loadLevelFromFile(char const * path, int persoInfos[3][8], int *nbrPerso);
char const *selectLevelFromNumber(int levelNumber);

#endif /* LEVEL_H */
