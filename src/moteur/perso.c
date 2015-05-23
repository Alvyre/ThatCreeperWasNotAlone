#include "moteur/perso.h"
#include "moteur/deplacements.h"

void initPerso(Personnage *personnage, int width, int height, int posCaseX, int posCaseY, Color3f color){

	personnage->centerX = (posCaseX * TAILLE_CASE) + (width * TAILLE_CASE-1)/2 ;
	personnage->centerY = (posCaseY * TAILLE_CASE) + (height * TAILLE_CASE-1)/2 ;
	personnage->width = width;
	personnage->height = height;
	personnage->color.r = color.r;
	personnage->color.g = color.g;
	personnage->color.b = color.b;
	personnage->gauche = false;
	personnage->droite = false;
	personnage->haut = false;
	personnage->bas = false;
	personnage->gravite = 15;
	personnage->vitesse = 5;
	personnage->sens = 0;
	personnage->lateral = false;
	personnage->saute = false;
	personnage->repos = true;
	personnage->active = false;
}

void gestionJoueur(Personnage *perso,int** map){
	printf("perso->centerX %d\n", perso->centerX);
	perso->sens = 0;
	perso->sens = (int)perso->droite - (int)perso->gauche;
	if (perso->sens != 0)
	{
		perso->lastDirection = perso->sens;
	}
	// Booleen ou int ?
	perso->repos = (bool)(!perso->droite && !perso->gauche && !perso->haut && !perso->bas);
	perso->lateral = perso->droite || perso->gauche;


	deplacementJoueur(perso, map);
}

void changeFocus(Personnage *perso1, Personnage *perso2, Personnage *perso3){
	if (perso1->active)
	{
		perso1->active = false;
		perso2->active = true;
		return;
	}
	if (perso2->active)
	{
		perso2->active = false;
		perso3->active = true;
		return;
	}
	if (perso3->active)
	{
		perso3->active = false;
		perso1->active = true;
		return;
	}
}