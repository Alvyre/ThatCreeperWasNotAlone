#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>


#include "moteur/main.h"
#include "initialisation/level.h"
#include "formes/draw.h"
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
  int loop = 1;
  int nbrPerso = 0;
  int j = 0;
  bool menu = false;
  int levelNumber = 2;

  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  setVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);

  SDL_WM_SetCaption("Thomas Was Alone", NULL);

  // Création du level
  int **level = calloc(LINES + COLUMNS, sizeof(int*));
  initLevel(level);
  int persoInfos[3][8];
  //FIXME : Choose level in menu 
  levelStart:
  loadLevelFromFile(level, selectLevelFromNumber(levelNumber), persoInfos, &nbrPerso);
  //creation camera
  Camera camera;
  
  //Tous les perso sont ils à leur case de fin
  bool end = false;
  //test
  Personnage *persoHandler;
  persoHandler = calloc(3,sizeof(Personnage));

  for (j = 0; j < nbrPerso; j++)
  {
    Color3f persoColor;
    persoColor.r = (float)persoInfos[j][4]; // cast en float car color
    persoColor.g = (float)persoInfos[j][5]; // cast en float car color
    persoColor.b = (float)persoInfos[j][6]; // cast en float car color
    // perso, width, height, caseX, caseY, color
    initPerso(&persoHandler[j], j, persoInfos[j][2], persoInfos[j][3], persoInfos[j][0], persoInfos[j][1], persoColor, persoInfos[j][7]);
  }

  // Par défaut perso 1 actif
  initCam(&persoHandler[0], &camera);
  glPushMatrix();
  persoHandler[0].active = true;

  //glScalef(1.2,1.2,0);
  centerCam(&persoHandler[0], &camera);

  GLuint textureID[10];
  loadTexture("./img/level1.jpg", textureID, 1);
  loadTexture("./img/level2.jpg", textureID, 2);
  loadTexture("./img/level3.jpg", textureID, 3);
  

  while(loop) {
    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    glClear(GL_COLOR_BUFFER_BIT);
    if (menu)
    {
      dessinMenu(textureID);
    } else {
      /* AFFICHAGE */
      creeDecor(level);

      // Gestion des fins de niveaux
      // Vérifie que chaque perso est sur sa case de fin,
      // dans le cas échéant, passe au niveau suivant
      // FIXME : switch dégueux trouver autre chose (essayer avec un for sur le nombre de perso, marche pas)
      switch(nbrPerso){
        case 1:
          if (persoHandler[0].end)
          {
            end = true;
          }
          break;
        case 2:
          if (persoHandler[0].end && persoHandler[1].end)
          {
            end = true;
          }
          break;
        case 3:
          if (persoHandler[0].end && persoHandler[1].end && persoHandler[2].end)
          {
            end = true;
          }
          break;
      }
     if (end) 
     {
        // Il n'y a que trois niveaux si on est au 3ème et qu'on le fini, retour au menu
        if (levelNumber < 3)
        {
          levelNumber++;
          goto levelStart;
          end = true;
        } else {
          // FIXME : When menu is done
          menu = true;
          break;
        }
     }
     /**** FIN GESTION NIVEAUX ******/

      for (j = 0; j < nbrPerso; j++)
      {
        glColor3f(persoHandler[j].color.r, persoHandler[j].color.g, persoHandler[j].color.b);  // Affichage du joueur
        dessinPerso(&persoHandler[j]);
        glColor3f(1, 1, 1);
      }

      /* GESTION JOUEUR */

      gestionJoueur(persoHandler, nbrPerso);
      deplacementJoueur(persoHandler, nbrPerso, level, &camera);

      // cursor
      for (j = 0; j < nbrPerso; j++)
      {
        if (persoHandler[j].active)
        {
          if(persoHandler[j].cursorTimer<180) {
            dessinActiveCursor(&persoHandler[j]);
            persoHandler[j].cursorTimer++;
          }
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

    }
    
    SDL_GL_SwapBuffers();
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      /* GESTION TOUCHE */
      for (j = 0; j < nbrPerso; j++)
      {
        if (persoHandler[j].active)
        {
          appuyer(&persoHandler[j],e);
          relacher(&persoHandler[j],e);
        }
      }      

      switch(e.type) {
        case SDL_QUIT:
          loop = 0;
          break;
          
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
              free(persoHandler);
              persoHandler = NULL;
              loop = 0;
              break;

            case SDLK_TAB:
              changeFocus(persoHandler, nbrPerso, &camera);
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
