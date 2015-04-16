#include "main.h"
#include "level.h"
#include "formes/carre.h"




void creeDecor(int level[WINDOW_HEIGHT/TAILLE_CASE][WINDOW_WIDTH/TAILLE_CASE]){
	int lines = WINDOW_HEIGHT / TAILLE_CASE ;
	int columns = WINDOW_WIDTH / TAILLE_CASE ;
	int map[lines][columns];

	int i,j;

	for (i = 0; i < lines; i++) // height
	{
		for (j = 0; j < columns; j++) //width
		{	
			//affiche le grid
			//dessinCarre(0,j*32,i*32);
			if (level[i][j] == 1)
			{
				dessinCarre(1,j*32,i*32);
			}
		}
	}
}

