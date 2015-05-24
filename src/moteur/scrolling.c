#include "moteur/scrolling.h"

void initCam(Personnage *perso, Camera *camera){

	camera->formerX = 0;
	camera->formerY = 0;
	camera->currentX = perso->centerX;
	camera->currentY = perso->centerY;
	camera->Dx = 0;
	camera->Dy = 0;
	camera->is_transition = false;
}

void scrolling(Camera *camera){
	camera->Dx = camera->currentX - camera->formerX;
	camera->Dy = camera->currentY - camera->formerY;

	// if(camera->currentX < WINDOW_WIDTH/2){
	// 	glPopMatrix();
	// 	glTranslatef(0,0,0);			// retour au début  // FIXME C'EST DEGUEULASSE
	// 	glPushMatrix();
	// } 
	glTranslatef(-camera->Dx,0,0);
}

void centerCam(Personnage *perso, Camera *camera){

	camera->formerX = camera->currentX;
	camera->formerY = camera->currentY;

	camera->currentX = perso->centerX;
	camera->currentY = perso->centerY;

	camera->Dx = camera->currentX - camera->formerX;
	camera->Dy = camera->currentY - camera->formerY;
	camera->is_transition = true;

}

void smoothTransition(Camera *camera){
	camera->Dx *=0.5;
	glTranslatef(-camera->Dx,0,0);
}