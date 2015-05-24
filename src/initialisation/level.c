#include "moteur/main.h"
#include "initialisation/level.h"
#include "formes/carre.h"
#include <string.h>

#define MAX_CHAR_FILE 10000


void initLevel(int** level){

	int i = 0;

  	for (i = 0; i < COLUMNS; i++)
  	{
    	level[i] = calloc(COLUMNS, sizeof(int));
  	}
}

void loadLevelFromFile(int** level, char const * path, int persoInfos[3][7], int *nbrPerso){
	
	int i = 0;
	int j = 0;
	bool firstline = true;
	char *buffer = NULL;
	size_t length = 0;
	char *ptr = NULL;
	ssize_t read;
	int currentPerso = 0;

	FILE *file = fopen(path, "r");

	if (file == NULL)
	{
		printf("Error opening the file !\n");
		exit (EXIT_FAILURE);
	} else {

		// Parcours les lignes
		while ((read = getline(&buffer, &length, file)) != -1) {
	        if (firstline)
	        {
				// Première ligne, on récupère le nombre de perso du level
				for (j = 0, ptr = buffer; j < 1; j++, ptr++){
	        		*nbrPerso = (int)strtol(ptr, &ptr, 10);
	        	}

	        	firstline = false;
	        } else {

	        	// On récupère les infos sur les différents perso
	        	// et les place dans le tableau persoInfos
	        	if(currentPerso < *nbrPerso){
	        		for (j = 0, ptr = buffer; j < 7; j++, ptr++){
	        			persoInfos[currentPerso][j] = (int)strtol(ptr, &ptr, 10);
	        		}
	        		currentPerso++;

	        	} else {
	        		// Si on a récupéré toutes les infos sur les persos,
	        		// on passe au level
	        		for (j = 0, ptr = buffer; j < COLUMNS; j++, ptr++){
	            		level[i][j] = (int)strtol(ptr, &ptr, 10);
	        		}
	        		i++;
	        	}

	        }
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

