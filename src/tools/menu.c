#include "tools/menu.h"
#include "formes/draw.h"


void touchesMenu(SDL_Event e, Menu *menu, Mix_Music *musicLevel[4], Camera *camera){
    if(e.type == SDL_KEYDOWN){
        switch(e.key.keysym.sym){
            case SDLK_DOWN : 
                menuHandler(menu, -1, musicLevel, camera);
            break;

            case SDLK_UP : 
                menuHandler(menu, 1, musicLevel, camera);
            break;

            case SDLK_RETURN :
            	menuHandler(menu, 0, musicLevel, camera);
            	
            break;

            default : break;
        }
    }
}


void menuHandler(Menu* menu, int sens, Mix_Music *musicLevel[4], Camera *camera){

	switch(sens){
		case 0:
			menu->active = false;
			glPopMatrix();
            glPushMatrix();
			Mix_HaltMusic();
			Mix_PlayMusic(musicLevel[menu->levelNumber], -1);
			break;
		case 1 :
			if (menu->levelNumber > 1)
			{
				dessinActiveMenu(menu->levelNumber--, camera);
			} else {
				menu->levelNumber = 3;
				dessinActiveMenu(menu->levelNumber, camera);
			}
			break;

		case -1 :
			if (menu->levelNumber < 3)
			{
				dessinActiveMenu(menu->levelNumber++, camera);
			} else {
				menu->levelNumber = 1;
				dessinActiveMenu(menu->levelNumber, camera);
			}
			break;

		 default : break;
	}
	
}
