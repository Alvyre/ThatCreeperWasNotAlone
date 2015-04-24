#include "perso.h"
#include "deplacements.h"

void initPerso(Personnage *personnage, int width, int height, int posCaseX, int posCaseY, Color3f color){

	personnage->centerX = (posCaseX * TAILLE_CASE) + (width * TAILLE_CASE)/2;
	personnage->centerY = (posCaseY * TAILLE_CASE) + (height * TAILLE_CASE)/2;
	personnage->posCaseX = posCaseX;
	personnage->posCaseY = posCaseY;
	personnage->posX = posCaseX * TAILLE_CASE;
	personnage->posY = posCaseY * TAILLE_CASE;
	personnage->width = width;
	personnage->height = height;
	personnage->color.r = color.r;
	personnage->color.g = color.g;
	personnage->color.b = color.b;
	personnage->gauche = false;
	personnage->droite = false;
	personnage->haut = false;
	personnage->bas = false;
	personnage->gravite = 0;
	personnage->vitesse = 5;
	personnage->sens = 0;
	personnage->lateral = false;
	personnage->saute = false;
	personnage->repos = true;
	personnage->active = false;
}

void gestionJoueur(Personnage *perso,int** map){
	perso->sens = (int)perso->droite - (int)perso->gauche;
	perso->saute = -1 * (int)(perso->haut)*11;
	perso->repos = (int)(!perso->droite && !perso->gauche && !perso->haut && !perso->bas);
	perso->lateral = perso->droite || perso->gauche;


	perso->centerX = perso->posX + (perso->width*TAILLE_CASE)/2;  // maj centre X du perso   
    perso->centerY = perso->posY + (perso->height*TAILLE_CASE)/2;

	deplacement(perso, map);
}