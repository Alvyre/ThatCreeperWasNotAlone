#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "formes/carre.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape(int winWidth, int winHeight) {
  glViewport(0, 0, winWidth, winHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1000., 1000., -1000.*winHeight/(float)winWidth, 1000.*winHeight/(float)winWidth);
}

void setVideoMode(int winWidth, int winHeight) {
  if(NULL == SDL_SetVideoMode(winWidth, winHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  reshape(winWidth, winHeight);
}

int main(int argc, char** argv) { 

    unsigned int windowWidth  = WINDOW_WIDTH;
    unsigned int windowHeight = WINDOW_HEIGHT;

    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
   
    setVideoMode(windowWidth, windowHeight);

    SDL_WM_SetCaption("Thomas Was Alone", NULL);

    int loop = 1;
    float mouvement_x = 0;
    float mouvement_y = 0;
    float x = 0;
    float y = 0;
    while(loop) {
       /* temps au dÃ©but de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        glClear(GL_COLOR_BUFFER_BIT);

        dessinCarre(1);

        glTranslatef(x, y, 0);


        SDL_GL_SwapBuffers();

        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }

            switch(e.type) {                 
                case SDL_VIDEORESIZE:
                  windowWidth  = e.resize.w;
                  windowHeight = e.resize.h;
                  setVideoMode(windowWidth,windowHeight);
                  break;

                case SDL_KEYDOWN:
                  switch(e.key.keysym.sym){
                    case 'q' : 
                    case SDLK_ESCAPE : 
                      loop = 0;
                      break;

                    case SDLK_RIGHT :
                      mouvement_x = 1;
                      break;

                    case SDLK_LEFT : 
                      mouvement_x = -1;
                      break;

                    case SDLK_SPACE :
                      mouvement_y = 1;
                      break;

                    default : break;
                  }
                  break;

                  case SDL_KEYUP:
                  switch(e.key.keysym.sym){
                    case SDLK_RIGHT :
                      if (mouvement_x > 0)
                      {
                        mouvement_x = 0;
                      }
                      break;

                    case SDLK_LEFT : 
                      if (mouvement_x < 0)
                      {
                        mouvement_x = 0;
                      }
                      break;

                    case SDLK_SPACE :
                      if (mouvement_y > 0)
                      {
                        mouvement_y = 0;
                      }
                      break;

                    default : break;
                  }
                  break;
                 
                default:
                  break;
            }
        }

        if (mouvement_x != 0)
        {
          x += mouvement_x;
        } else {
          x = 0;
        }
        
        if (mouvement_y != 0)
        {
          y += mouvement_y;
        } else {
          y = 0;
        }


      Uint32 elapsedTime = SDL_GetTicks() - startTime;
      if(elapsedTime < FRAMERATE_MILLISECONDS) {
        SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
      }
    }
  
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
