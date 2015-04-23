#include "main.h"
#include "level.h"
#include "formes/carre.h"

#define LINES WINDOW_HEIGHT/TAILLE_CASE //30
#define COLUMNS WINDOW_WIDTH/TAILLE_CASE //40


void initLevel(int** level){

	int i = 0;
 	int j = 0;
  	for (i = 0; i < COLUMNS; i++)
  	{
    	level[i] = calloc(COLUMNS, sizeof(int));
  	}

  	for (i = 0; i < LINES; i++)
  	{
    	for (j = 0; j < COLUMNS; j++)
    	{
      	level[i][j] = 0;
    	}
  	}
  level[25][18] = 1;
  level[25][19] = 1;
  level[26][16] = 1;
  for (j = 0; j < COLUMNS; j++)
  {
    level[27][j] = 1;
  }
}

void freeLevel(int** level){
	int i = 0;
	for(i = 0; i < COLUMNS; i++) {
		free(level[i]);
	}
	free(level);
}


void creeDecor(int **level){
	int i,j;

	for (i = 0; i < LINES; i++) // height
	{
		for (j = 0; j < COLUMNS; j++) //width
		{	
			//affiche le grid
			dessinCarre(0,j*32,i*32);
			if (level[i][j] == 1)
			{
				dessinCarre(1,j*32,i*32);
			}
		}
	}
}

bool isPixelGround(int pixelX, int pixelY, int **level){
	

	int colonne = pixelX/TAILLE_CASE;
	int line = pixelY/TAILLE_CASE;
	printf("colonne %d\n", colonne);
	printf("ligne %d\n", line);

	if (line >= 0 && colonne >= 0 && line <= LINES && colonne <= COLUMNS)
	{
		if (level[line+1][colonne] == 1)
		{
			return true;
		}
	}
	return false;
}