#include "moteur/main.h"
#include "initialisation/level.h"
#include "formes/carre.h"
#include <string.h>

#define LINES WINDOW_HEIGHT/TAILLE_CASE //30
#define COLUMNS 80//WINDOW_WIDTH/TAILLE_CASE //40 /**********************FIXME*************
#define MAX_CHAR_FILE 10000


void initLevel(int** level){

	int i = 0;

  	for (i = 0; i < COLUMNS; i++)
  	{
    	level[i] = calloc(COLUMNS, sizeof(int));
  	}
}

void loadLevelFromFile(int** level, char const * path){
	
	int i = 0;
	int j = 0;
	char *buffer = NULL;
	size_t length = 0;
	char *ptr = NULL;
	ssize_t read;
	
	FILE *file = fopen(path, "r");

	if (file == NULL)
	{
		printf("Error opening the file !\n");
		exit (EXIT_FAILURE);
	} else {

		// Parcours les lignes
		while ((read = getline(&buffer, &length, file)) != -1) {
	        // Parcours les colonnes
	        for (j = 0, ptr = buffer; j < COLUMNS; j++, ptr++){
	            level[i][j] = (int)strtol(ptr, &ptr, 10);
	        }

	        i++;
    	}

		fclose(file);
		
	}
}

void freeLevel(int** level){
	int i = 0;
	for(i = 0; i < COLUMNS; i++) {
		free(level[i]);
		level[i] = NULL;
	}
	free(level);
	level = NULL;
}


void creeDecor(int **level){
	int i,j;
	Color3f color;
	// Par défaut carrés noirs
	color.r = 0;
	color.g = 0;
	color.b = 0;

	for (i = 0; i < LINES; i++) // height
	{
		for (j = 0; j < COLUMNS; j++) //width
		{	
			//affiche le grid
			//dessinCarre(0,j*32,i*32);
			if (level[i][j] == 1)
			{
				color.r = 1;
				color.g = 1;
				color.b = 1;
				dessinCarre(j*32,i*32, &color);
			}

			if (level[i][j] == 2)
			{
				color.r = 0.5;
				color.g = 1;
				color.b = 0.5;
				dessinCarre(j*32,i*32, &color);
			}
		}
	}
}

int convertPixelToCase(int pixel){

	return pixel/TAILLE_CASE;
}

int convertCaseToPixel(float Case){
	return Case*TAILLE_CASE;
}

