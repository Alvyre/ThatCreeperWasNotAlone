#include "moteur/perso.h"
#include "moteur/deplacements.h"

void initPerso(Personnage *personnage, int width, int height, int posCaseX, int posCaseY, Color3f color){

	personnage->centerX = (posCaseX * TAILLE_CASE) + (width * TAILLE_CASE)/2 ;
	personnage->centerY = (posCaseY * TAILLE_CASE) + (height * TAILLE_CASE)/2 ;
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
	personnage->vitesse = 6;
	personnage->sens = 0;
	personnage->lateral = false;
	personnage->saute = false;
	personnage->repos = true;
	personnage->active = false;
	personnage->cursorTimer = 0;
}

void gestionJoueur(Personnage *persoHandler){
	Personnage *perso;
	if(persoHandler[0].active) perso = &(persoHandler[0]);
	else if(persoHandler[1].active) perso = &(persoHandler[1]);
	else if(persoHandler[2].active) perso = &(persoHandler[2]);

	perso->sens = 0;
	perso->sens = (int)perso->droite - (int)perso->gauche;
	// Booleen ou int ?
	perso->repos = (bool)(!perso->droite && !perso->gauche && !perso->haut && !perso->bas);
	perso->lateral = perso->droite || perso->gauche;



	
}

void changeFocus(Personnage *perso1, Personnage *perso2, Personnage *perso3, Camera *camera){
	if (perso1->active)
	{
		perso1->active = false;
		perso1->droite = false; // évite que le perso continue son mvmt quand on le reprend
		perso1->gauche = false;
		perso2->cursorTimer = 0;
		perso2->active = true;
		centerCam(perso2, camera);
		return;
	}
	if (perso2->active)
	{
		perso2->active = false;
		perso2->droite = false;
		perso2->gauche = false;
		perso3->cursorTimer = 0;
		perso3->active = true;
		centerCam(perso3, camera);
		return;
	}
	if (perso3->active)
	{
		perso3->active = false;
		perso3->droite = false;
		perso3->gauche = false;
		perso1->cursorTimer = 0;
		perso1->active = true;
		centerCam(perso1, camera);
		return;
	}
}