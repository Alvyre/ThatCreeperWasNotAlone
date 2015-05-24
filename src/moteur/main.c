#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>


#include "moteur/main.h"
#include "initialisation/level.h"
#include "formes/carre.h"
#include "moteur/perso.h"
#include "moteur/touche.h"
#include "moteur/deplacements.h"
#include "moteur/scrolling.h"
#include "moteur/colision.h"

static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape(int winWidth, int winHeight) {
  glViewport(0, 0, winWidth, winHeight);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //gluOrtho2D(left,right,top,bot);
  gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
}

void setVideoMode(int winWidth, int winHeight) {
  if(NULL == SDL_SetVideoMode(winWidth, winHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  reshape(WINDOW_WIDTH, WINDOW_HEIGHT);
}

int main(int argc, char** argv) {


  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  setVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);

  SDL_WM_SetCaption("Thomas Was Alone", NULL);

  int loop = 1;
  int **level = calloc(LINES + COLUMNS, sizeof(int*));
  // Création du level
  initLevel(level);
  //FIXME : Choose level in menu 
  char const *path = "./levels/level-2.csv";
  loadLevelFromFile(level, path);

  //creation camera
  Camera camera;

  //test
  Personnage *persoHandler;
  persoHandler = calloc(3,sizeof(Personnage));


  //creation perso;

  Color3f RED;
  RED.r = 1;
  RED.g = 0;
  RED.b = 0;


  Color3f BLUE;
  BLUE.r = 0;
  BLUE.g = 0;
  BLUE.b = 1;



  Color3f GREEN;
  GREEN.r = 0;
  GREEN.g = 1;
  GREEN.b = 0;

  // perso, width, height, caseX, caseY, color
  initPerso(&persoHandler[0], 2, 2, 4, 26, RED);
  initPerso(&persoHandler[1], 2, 2, 10, 5, BLUE);
  initPerso(&persoHandler[2],  2, 2, 2, 5, GREEN);

  // Par défaut perso 1 actif
  initCam(&persoHandler[0], &camera);
  glPushMatrix();
  persoHandler[0].active = true;

  //glScalef(1.2,1.2,0);
  centerCam(&persoHandler[0], &camera);
  

  while(loop) {
    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    glClear(GL_COLOR_BUFFER_BIT);

    /* AFFICHAGE */

    creeDecor(level);                                           // Affichage décor

    glColor3f(persoHandler[0].color.r, persoHandler[0].color.g, persoHandler[0].color.b);  // Affichage du joueur
    dessinPerso(&persoHandler[0]);
    glColor3f(1, 1, 1);

    glColor3f(persoHandler[1].color.r, persoHandler[1].color.g, persoHandler[1].color.b);  // Affichage du joueur
    dessinPerso(&persoHandler[1]);
    glColor3f(1, 1, 1);

    glColor3f(persoHandler[2].color.r, persoHandler[2].color.g, persoHandler[2].color.b);  // Affichage du joueur
    dessinPerso(&persoHandler[2]);
    glColor3f(1, 1, 1);

    /* GESTION JOUEUR */

    if (persoHandler[0].active)
    {
      gestionJoueur(persoHandler, level, &camera);
      collisionsJoueur(&persoHandler[0], &persoHandler[1]);
      collisionsJoueur(&persoHandler[0], &persoHandler[2]);
      if(persoHandler[0].cursorTimer<180) {
        dessinActiveCursor(&persoHandler[0]);
        persoHandler[0].cursorTimer++;
      }
    }
    if (persoHandler[1].active)
    {
      
      gestionJoueur(persoHandler, level, &camera);
      collisionsJoueur(&persoHandler[1], &persoHandler[0]);
      collisionsJoueur(&persoHandler[1], &persoHandler[2]);
      if(persoHandler[1].cursorTimer<180) {
        dessinActiveCursor(&persoHandler[1]);
        persoHandler[1].cursorTimer++;
      }
    }
    if (persoHandler[2].active)
    {

      gestionJoueur(persoHandler, level, &camera);
      collisionsJoueur(&persoHandler[2], &persoHandler[1]);
      collisionsJoueur(&persoHandler[2], &persoHandler[0]);
      if(persoHandler[2].cursorTimer<180) {
        dessinActiveCursor(&persoHandler[2]);
        persoHandler[2].cursorTimer++;
      }
    }
    
    // camera

    if(camera.is_transition == false) scrolling(&camera);
    else if(camera.is_transition == true){
      if(camera.Dx < -0.001 || camera.Dx > 0.001){
        smoothTransition(&camera);
      }
      else camera.is_transition = false;
    }

    SDL_GL_SwapBuffers();
        SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }

      /* GESTION TOUCHE */
    if (persoHandler[0].active)
    {
      appuyer(&persoHandler[0],e);
      relacher(&persoHandler[0],e);
    }
    if (persoHandler[1].active)
    {
      appuyer(&persoHandler[1],e);
      relacher(&persoHandler[1],e);
    }
    if (persoHandler[2].active)
    {
      appuyer(&persoHandler[2],e);
      relacher(&persoHandler[2],e);
    }
      

      switch(e.type) {                 
        case SDL_VIDEORESIZE:
        WINDOW_WIDTH  = e.resize.w;
        WINDOW_HEIGHT = e.resize.h;
        setVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
        break;

        case SDL_KEYDOWN:
          switch(e.key.keysym.sym){
            case 'q' : 
            case SDLK_ESCAPE :
              freeLevel(level);
              loop = 0;
              break;
            case SDLK_TAB:
              changeFocus(&persoHandler[0], &persoHandler[1], &persoHandler[2], &camera);
              break;
              default : break;
          }
        break;

        default:
        break;
      }
    }

    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  SDL_Quit();

  return EXIT_SUCCESS;
}
