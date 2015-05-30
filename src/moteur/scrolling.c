#include "moteur/scrolling.h"

void initCam(Personnage *perso, Camera *camera){
	camera->currentX = WINDOW_WIDTH/2;
	camera->currentY = WINDOW_HEIGHT/2;
}

void moveCamera(Personnage *perso, Camera *camera, Level* level){

	// MAx position caméra = level->width*TAILLE_CASE - WINDOW_WIDTH/2
	// Min position caméra = 0


	// Perso va vers la gauche
	if (perso->gauche && camera->currentX - WINDOW_WIDTH/2 >= 0)
	{
		glTranslatef(perso->vitesse,0,0);
		camera->currentX -= perso->vitesse;	
			
	}

	// Perso va vers la droite
	if (perso->droite && camera->currentX < level->width*TAILLE_CASE - WINDOW_WIDTH/2)
	{
		glTranslatef(-perso->vitesse,0,0);
		camera->currentX = camera->currentX +perso->vitesse;
	}

	// Si perso trop en arrière par rapport à la caméra
	if (camera->currentX - perso->box.pos.x > WINDOW_WIDTH/4)
	{
		while(camera->currentX - perso->box.pos.x > WINDOW_WIDTH/4 && camera->currentX - WINDOW_WIDTH/2 >= 0){
			glTranslatef(1,0,0);
			camera->currentX -= 1;	
		}
	}

	// si perso trop en avance sur la caméra
	if (perso->box.pos.x - camera->currentX > WINDOW_WIDTH/4)
	{
		while(perso->box.pos.x - camera->currentX > WINDOW_WIDTH/4 && camera->currentX + WINDOW_WIDTH/2 <= level->width*TAILLE_CASE){
			glTranslatef(-1,0,0);
			camera->currentX += 1;	
		}
	}

}
