#include "moteur/main.h"
#include "initialisation/level.h"
#include "formes/draw.h"
#include <string.h>

Level* initLevel(Level* level, int width, int height){
	int i = 0;

	level = calloc(width + height + 2, sizeof(Tile*));
	level->map = calloc(width + height, sizeof(Tile*));
	level->width = width;
	level->height = height;
	level->persoActive = 0;

	// i nbre de lignes (height)
	// j nbre colonnes (width)
  	for (i = 0; i < height; i++)
  	{
    	level->map[i] = calloc(width, sizeof(Tile));
  	}

  	return level;
}

Level* loadLevelFromFile(char const * path, int persoInfos[3][8], int *nbrPerso){	
	int i = 0;
	int j = 0;
	bool firstLine = true;
	bool secondLine = true;
	char *buffer = NULL;
	size_t length = 0;
	char *ptr = NULL;
	ssize_t read;
	int currentPerso = 0;
	int width = 0;
	int height =0;
	Level *level;

	FILE *file = fopen(path, "r");

	if (file == NULL)
	{
		printf("Error opening the file !\n");
		exit (EXIT_FAILURE);
	} else {
		// Parcours les lignes
		while ((read = getline(&buffer, &length, file)) != -1) {
	        if (firstLine)
	        {
				for (j = 0, ptr = buffer; j < 2; j++, ptr++){
					if (j == 0)
					{
						width = (int)strtol(ptr, &ptr, 10);
					}
					if (j == 1)
					{
						height = (int)strtol(ptr, &ptr, 10);
					}
	        	}

	        	level = initLevel(level, width, height);

	        	firstLine = false;
	        } else if(secondLine) {
	        	// Première ligne, on récupère le nombre de perso du level
				for (j = 0, ptr = buffer; j < 1; j++, ptr++){
	        		*nbrPerso = (int)strtol(ptr, &ptr, 10);
	        	}

	        	secondLine = false;
	    	} else {

	        	// On récupère les infos sur les différents perso
	        	// et les place dans le tableau persoInfos
	        	if(currentPerso < *nbrPerso){
	        		for (j = 0, ptr = buffer; j < 8; j++, ptr++){
	        			persoInfos[currentPerso][j] = (int)strtol(ptr, &ptr, 10);
	        		}
	        		currentPerso++;

	        	} else {
	        		// Si on a récupéré toutes les infos sur les persos,
	        		// on passe au level
	        		for (j = 0, ptr = buffer; j < level->width; j++, ptr++){
	        			// i nbre de lignes (height)
						// j nbre colonnes (width)
	            		level->map[i][j].value = (int)strtol(ptr, &ptr, 10);
	        		}
	        		i++;
	        	}

	        }
	        
    	}
		fclose(file);
		return level;
	}
}

char const *selectLevelFromNumber(int levelNumber){
	char const *path;
	switch(levelNumber){
		case 1:
			path = "./levels/level-1.csv";
			break;
		case 2:
		  	path = "./levels/level-2.csv";
			break;
		case 3:
		  	path = "./levels/level-3.csv";
			break;
		default:
		  	path = "./levels/level-1.csv";
			break;
	}
	return path;
}

// Passer Level
// utiliser Level.width
void freeLevel(Level* level){
	int i = 0;
	for(i = 0; i < level->height; i++) {
		free(level->map[i]);
		level->map[i] = NULL;
	}
	free(level->map);
	level->map = NULL;

	free(level);
}

// Passer Level 
// utiliser Level.width
void creeDecor(Level* level){
	int i,j;
	Color3f color;
	// Par défaut carrés noirs
	color.r = 0;
	color.g = 0;
	color.b = 0;

	for (i = 0; i < level->height; i++) // height
	{
		for (j = 0; j < level->width; j++) //width
		{	
			level->map[i][j].is_solid = false;
			if (level->map[i][j].value == 3){
				dessinCarre(j*32,i*32, 4, 0.6, 0);
				level->map[i][j].is_solid = true;
			}
			if (level->map[i][j].value == 2){
				dessinCarre(j*32,i*32, 4, 0.4, 0);
				level->map[i][j].is_solid = true;
			}

			if (level->map[i][j].value == -1 || level->map[i][j].value == -2 || level->map[i][j].value == -3)
			{
				color.r = 1;
				color.g = 1;
				color.b = 1;
				dessinEmptyCarre(j*32,i*32, &color);

			}
		}
	}
}

									/**** TEXTURE INFO ****/
									/*					  */
									/*					  */
									/*	2 = terre		  */
									/*	3 = pelouse		  */
									/*					  */
									/*	7 = end perso 1	  */
									/*	8 = end perso 2	  */
									/*	9 = end perso 3	  */
									/*					  */
									/**********************/
