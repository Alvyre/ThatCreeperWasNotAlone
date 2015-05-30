#include "moteur/perso.h"
#include "moteur/deplacements.h"


void initPerso(Personnage *personnage, int id, int width, int height, int posCaseX, int posCaseY, Color3f color, int gravite){
	personnage->id = id;
	personnage->box.pos.x = (posCaseX * TAILLE_CASE);
	personnage->box.pos.y = (posCaseY * TAILLE_CASE);
	personnage->box.size.x = (width * TAILLE_CASE);
	personnage->box.size.y = (height * TAILLE_CASE);
	personnage->dir.x = 0;
	personnage->dir.y = 0;

	personnage->color.r = color.r;
	personnage->color.g = color.g;
	personnage->color.b = color.b;
	personnage->gauche = false;
	personnage->droite = false;
	personnage->haut = false;
	personnage->bas = false;
	personnage->defaultGravite = gravite;
	personnage->gravite = gravite;
	personnage->vitesse = 4;
	personnage->sens = 0;
	personnage->saute = false;
	personnage->active = false;
	personnage->cursorTimer = 0;
	personnage->end = false;
}

void gestionJoueur(Personnage *persoHandler, int nbrPerso){
	Personnage *perso;
	int i;
	for(i = 0; i<nbrPerso;++i){
		persoHandler[i].dir.x = 0;
		if(persoHandler[i].active)
			perso = &persoHandler[i];
	}

	perso->dir.x = (int)perso->droite - (int)perso->gauche;
}

void changeFocus(Personnage *persoHandler, int nbrPerso, Level* level){
	int i = 0;

	for (i = 0; i < nbrPerso; i++)
	{
		
		if (persoHandler[i].active){
			persoHandler[i].active = false;
			persoHandler[i].droite = false; // évite que le perso continue son mvmt quand on le reprend
			persoHandler[i].gauche = false;
			
			if (i + 1 < nbrPerso)
			{
				persoHandler[i+1].cursorTimer = 0;
				persoHandler[i+1].active = true;
				level->persoActive = i+1;
			} else {
				persoHandler[0].cursorTimer = 0;
				persoHandler[0].active = true;
				level->persoActive = 0;
			}
			return;
		}
	}


}
