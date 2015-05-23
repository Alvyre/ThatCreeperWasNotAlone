#include "moteur/scrolling.h"

void initCam(Personnage *perso, Camera *camera){

	camera->formerX = 0;
	camera->formerY = 0;
	camera->currentX = perso->centerX;
	camera->currentY = perso->centerY;
}

void scrolling(Camera *camera){
	int distanceX = camera->currentX - camera->formerX;
	int distanceY = camera->currentY - camera->formerY;

	if(camera->currentX < WINDOW_WIDTH/2){
		glPopMatrix();
		glTranslatef(0,0,0);			// retour au début
		glPushMatrix();
	} 
	else glTranslatef(-distanceX,0,0);
}

void centerCam(Personnage *perso, Camera *camera){

	camera->formerX = camera->currentX;
	camera->formerY = camera->currentY;

	camera->currentX = perso->centerX;
	camera->currentY = perso->centerY;

	int distanceX = camera->currentX - camera->formerX;
	int distanceY = camera->currentY - camera->formerY;
	float epsilon = 0.001;
	float temp = distanceX;
	//scrolling(camera);

	//FIXME Smooth scroll
	while(temp > epsilon || temp < -epsilon){
		temp *=0.2;
		printf("temp = %f\n",temp);
		glTranslatef(-temp,0,0);
	}
}