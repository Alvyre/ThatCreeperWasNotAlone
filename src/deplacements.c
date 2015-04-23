#include "deplacements.h"
#include "main.h"

/************************************/
/*   Gestion des déplacements       */
/************************************/


// Touches de direction


void directions(Personnage *perso, SDL_Event e) {
    if(e.type == SDL_KEYDOWN){

    	switch(e.key.keysym.sym){
            case SDLK_RIGHT :
            	deplacement(perso, 1);
            break; 

            case SDLK_LEFT : 
            	deplacement(perso, -1);
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
        		deplacement(perso, 0);
            break;
        default : break;
		}
	}
}

void deplacement(Personnage *perso, int sens) {  
	perso->sens = sens; //direction du perso 
	perso->posX += perso->vitesse * perso->sens;// position du perso en px
	perso->posCaseX = perso->posX / TAILLE_CASE ; // position du perso en case
	perso->lateral = true;
}