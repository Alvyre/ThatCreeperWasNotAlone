#include "moteur/camera.h"

void initCam(Personnage *perso, Camera *camera){
	camera->x = WINDOW_WIDTH/2;
	camera->y = WINDOW_HEIGHT/2;
}

void moveCamera(Personnage *perso, Camera *camera, Level* level){

	// En X
	// MAx position caméra = level->width*TAILLE_CASE - WINDOW_WIDTH/2
	// Min position caméra = 0

	// Perso va vers la gauche
	if (perso->gauche && camera->x - WINDOW_WIDTH/2 >= 0)
	{
		glTranslatef(perso->vitesse,0,0);
		camera->x -= perso->vitesse;	
			
	}

	// Perso va vers la droite
	if (perso->droite && camera->x < level->width*TAILLE_CASE - WINDOW_WIDTH/2)
	{
		glTranslatef(-perso->vitesse,0,0);
		camera->x = camera->x +perso->vitesse;
	}

	// Si perso trop en arrière par rapport à la caméra
	if (camera->x - perso->box.pos.x > WINDOW_WIDTH/4)
	{
		while(camera->x - perso->box.pos.x > WINDOW_WIDTH/4 && camera->x - WINDOW_WIDTH/2 >= 0){
			glTranslatef(1,0,0);
			camera->x -= 1;	
		}
	}

	// si perso trop en avance sur la caméra
	if (perso->box.pos.x - camera->x > WINDOW_WIDTH/4)
	{
		while(perso->box.pos.x - camera->x > WINDOW_WIDTH/4 && camera->x + WINDOW_WIDTH/2 <= level->width*TAILLE_CASE){
			glTranslatef(-1,0,0);
			camera->x += 1;	
		}
	}


	// EN Y
	// Si perso trop haut par rapport à la caméra
	if (camera->y - perso->box.pos.y >= WINDOW_HEIGHT/4)
	{
		while(camera->y - perso->box.pos.y > WINDOW_HEIGHT/4 && camera->y - WINDOW_HEIGHT/2 >= 0){
			glTranslatef(0,1,0);
			camera->y -= 1;	
		}
	}

	// si perso trop bas par rapport à la caméra
	if (perso->box.pos.y - camera->y >= WINDOW_HEIGHT/4)
	{	
		// Ajout de -30 pour avoir une marge de manoeuvre et voir le sol sous le perso
		while(perso->box.pos.y - camera->y > WINDOW_HEIGHT/4 - 30 && camera->y + WINDOW_HEIGHT/2 <= level->height*TAILLE_CASE){
			glTranslatef(0,-1,0);
			camera->y += 1;	
		}
	}

}
