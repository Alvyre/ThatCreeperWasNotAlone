/************************************/
/*   Gestion des touches            */
/************************************/
#include "moteur/touche.h"
#include "moteur/main.h"

// Appuyer sur une touche
void appuyer(Personnage *perso, SDL_Event e){
    if(e.type == SDL_KEYDOWN){

        switch(e.key.keysym.sym){
            case SDLK_RIGHT :
                perso->droite = true;
            break; 

            case SDLK_LEFT : 
                perso->gauche = true;
            break;

            case SDLK_UP : 
                perso->haut = true;
            break;

            case SDLK_DOWN : 
                perso->bas = true;
            break;

            case SDLK_SPACE :
                    perso->haut = true;
            break;

            default : break;

        }
    }
}
// Appuyer sur une touche
void relacher(Personnage *perso, SDL_Event e){
    if(e.type == SDL_KEYUP){

        switch(e.key.keysym.sym){
            case SDLK_RIGHT :
                perso->droite = false;
            break; 

            case SDLK_LEFT : 
                perso->gauche = false;
            break;

            case SDLK_UP : 
                perso->haut = false;
            break;

            case SDLK_DOWN : 
                perso->bas = false;
            break;

            case SDLK_SPACE :
                    perso->haut = false;
            break;

            default : break;

        }
    }
}