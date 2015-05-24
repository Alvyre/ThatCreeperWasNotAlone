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
  int **level = calloc(WINDOW_HEIGHT/TAILLE_CASE * WINDOW_WIDTH/TAILLE_CASE, sizeof(int*));
  // Création du level
  initLevel(level);
  //FIXME : Choose level in menu 
  char const *path = "./levels/level-2.csv";
  loadLevelFromFile(level, path);

  //creation camera
  Camera camera;

  //creation perso;
  Personnage perso1;
  Color3f RED;
  RED.r = 1;
  RED.g = 0;
  RED.b = 0;

  Personnage perso2;
  Color3f BLUE;
  BLUE.r = 0;
  BLUE.g = 0;
  BLUE.b = 1;


  Personnage perso3;
  Color3f GREEN;
  GREEN.r = 0;
  GREEN.g = 1;
  GREEN.b = 0;

  // perso, width, height, caseX, caseY, color
  initPerso(&perso1, 2, 2, 4, 26, RED);
  initPerso(&perso2, 2, 2, 10, 5, BLUE);
  initPerso(&perso3,  2, 2, 2, 5, GREEN);

  // Par défaut perso 1 actif
  initCam(&perso1, &camera);
  glPushMatrix();
  perso1.active = true;

  //glScalef(1.2,1.2,0);
  centerCam(&perso1, &camera);
  

  while(loop) {
    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    glClear(GL_COLOR_BUFFER_BIT);

    /* AFFICHAGE */

    creeDecor(level);                                           // Affichage décor

    glColor3f(perso1.color.r, perso1.color.g, perso1.color.b);  // Affichage du joueur
    dessinPerso(&perso1);
    glColor3f(1, 1, 1);

    glColor3f(perso2.color.r, perso2.color.g, perso2.color.b);  // Affichage du joueur
    dessinPerso(&perso2);
    glColor3f(1, 1, 1);

    glColor3f(perso3.color.r, perso3.color.g, perso3.color.b);  // Affichage du joueur
    dessinPerso(&perso3);
    glColor3f(1, 1, 1);

    /* GESTION JOUEUR */

    if (perso1.active)
    {
      gestionJoueur(&perso1, level, &camera);
      collisionsJoueur(&perso1, &perso2);
      collisionsJoueur(&perso1, &perso3);
      if(perso1.cursorTimer<180) {
        dessinActiveCursor(&perso1);
        perso1.cursorTimer++;
      }
    }
    if (perso2.active)
    {
      
      gestionJoueur(&perso2, level, &camera);
      collisionsJoueur(&perso2, &perso1);
      collisionsJoueur(&perso2, &perso3);
      if(perso2.cursorTimer<180) {
        dessinActiveCursor(&perso2);
        perso2.cursorTimer++;
      }
    }
    if (perso3.active)
    {

      gestionJoueur(&perso3, level, &camera);
      collisionsJoueur(&perso3, &perso2);
      collisionsJoueur(&perso3, &perso1);
      if(perso3.cursorTimer<180) {
        dessinActiveCursor(&perso3);
        perso3.cursorTimer++;
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
    if (perso1.active)
    {
      appuyer(&perso1,e);
      relacher(&perso1,e);
    }
    if (perso2.active)
    {
      appuyer(&perso2,e);
      relacher(&perso2,e);
    }
    if (perso3.active)
    {
      appuyer(&perso3,e);
      relacher(&perso3,e);
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
              //freeLevel(level);
              loop = 0;
              break;
            case SDLK_TAB:
              changeFocus(&perso1, &perso2, &perso3, &camera);
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
