#include "moteur/scrolling.h"

void initCam(Personnage *perso, Camera *camera){

	camera->formerX = 0;
	camera->formerY = 0;
	camera->currentX = perso->centerX;
	camera->currentY = perso->centerY;
}

void scrolling(Camera *camera){
	int mouvementX = camera->currentX - camera->formerX;
	int mouvementY = camera->currentY - camera->formerY;
	printf("mouvementX = %d\n", mouvementX);
	printf("mouvementY = %d\n", mouvementY);

	glTranslatef(-mouvementX,0,0);
}

void centerCam(Personnage *perso, Camera *camera){

	camera->formerX = camera->currentX;
	camera->formerY = camera->currentY;

	camera->currentX = perso->centerX;
	camera->currentY = perso->centerY;

	scrolling(camera);
}