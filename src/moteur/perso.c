#include "moteur/perso.h"
#include "moteur/deplacements.h"

void initPerso(Personnage *personnage, int id, int width, int height, int posCaseX, int posCaseY, Color3f color, int gravite){
	personnage->id = id;
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
	personnage->defaultGravite = gravite;
	personnage->gravite = gravite;
	personnage->vitesse = 6;
	personnage->sens = 0;
	personnage->lateral = false;
	personnage->saute = false;
	personnage->repos = true;
	personnage->active = false;
	personnage->cursorTimer = 0;
	personnage->freeze = false;
	personnage->end = false;
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
	//printf("freeze = %d\n",(int)perso->freeze );
}

void changeFocus(Personnage *persoHandler, int nbrPerso, Camera *camera){
	int i = 0;

	for (i = 0; i < nbrPerso; ++i)
	{
		
		if (persoHandler[i].active){
			persoHandler[i].active = false;
			persoHandler[i].droite = false; // évite que le perso continue son mvmt quand on le reprend
			persoHandler[i].gauche = false;
			
			if (i + 1 < nbrPerso)
			{
				persoHandler[i+1].cursorTimer = 0;
				persoHandler[i+1].active = true;
				centerCam(&persoHandler[i+1], camera);
			} else {
				persoHandler[0].cursorTimer = 0;
				persoHandler[0].active = true;
				centerCam(&persoHandler[0], camera);
			}
			return;
		}
	}


}
