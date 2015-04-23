#include "deplacements.h"
#include "main.h"

/************************************/
/*   Gestion des déplacements       */
/************************************/


// Touches de direction


void directions(Personnage *perso, SDL_Event e, int **map) {
    if(e.type == SDL_KEYDOWN){

    	switch(e.key.keysym.sym){
            case SDLK_RIGHT :
            	deplacement(perso, 1, map);
            break; 

            case SDLK_LEFT : 
            	deplacement(perso, -1, map);
            break;

            case SDLK_SPACE :
                if (perso-> saute == false)
                {
                    perso->saute = true;
                    perso->gravite = -30;
                }
            break;

            default : break;

      	}

    }
    else if(e.type == SDL_KEYUP){               
		switch(e.key.keysym.sym){
        	case SDLK_RIGHT :
        	case SDLK_LEFT : 
        		deplacement(perso, 0, map);
            break;
        default : break;
		}
	}
}

void deplacement(Personnage *perso, int sens, int **map) {  
	perso->sens = sens;   //direction du perso 
    perso->posX += perso->vitesse * perso->sens;  // deplacement en x
    perso->centerX = perso->posX + (perso->width*TAILLE_CASE)/2;  // maj centre X du perso   
    perso->centerY = perso->posY + (perso->height*TAILLE_CASE)/2;

    int C = (perso->centerX + (perso->width*TAILLE_CASE/2) * perso->sens)/TAILLE_CASE; // colonne à tester
    int L = (perso->centerY - (perso->height*TAILLE_CASE/2))/ TAILLE_CASE;  // ligne à tester
    
    //Colision latéral                          
    for (; L<perso->centerY/TAILLE_CASE+1; L++) {
        if (map[L][C]==1) {
            perso->centerX = C*TAILLE_CASE + TAILLE_CASE/2 -TAILLE_CASE*perso->sens;
            perso->posX = perso->centerX - (perso->width*TAILLE_CASE)/2;
        }
    }

}
