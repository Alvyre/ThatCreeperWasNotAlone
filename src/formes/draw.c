#include "formes/draw.h"

void dessinCarre(int posX, int posY, int numTexture, float offsetX, float offsetY){
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, numTexture); // minecraft

  glBegin(GL_POLYGON);
    // Haut gauche
    glTexCoord2f(offsetX, offsetY); glVertex2f(posX,posY);
    // Haut droite
    glTexCoord2f(offsetX+0.2, offsetY); glVertex2f(posX+TAILLE_CASE,posY);
    // BAs droite
    glTexCoord2f(offsetX+0.2, offsetY+0.5); glVertex2f(posX+TAILLE_CASE,posY+TAILLE_CASE);
    // Bas gauche
    glTexCoord2f(offsetX, offsetY+0.5); glVertex2f(posX,posY+TAILLE_CASE);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);

}

void dessinEmptyCarre(int posX, int posY, Color3f *color){
  glBegin(GL_LINE_LOOP);
    // Haut gauche
    glVertex2f(posX,posY);
    // Haut droite
    glVertex2f(posX+TAILLE_CASE,posY);
    // BAs droite
    glVertex2f(posX+TAILLE_CASE,posY+TAILLE_CASE);
    // Bas gauche
    glVertex2f(posX,posY+TAILLE_CASE);
  glEnd();
}

void dessinPerso(Personnage *perso){
  glBegin(GL_POLYGON);
    // Haut gauche
        glVertex2f(perso->box.pos.x,perso->box.pos.y);
    // Haut droite
        glVertex2f(perso->box.pos.x + perso->box.size.x,perso->box.pos.y );
    // Bas droite
        glVertex2f(perso->box.pos.x + perso->box.size.x,perso->box.pos.y + perso->box.size.y );
    // Bas gauche
        glVertex2f(perso->box.pos.x ,perso->box.pos.y + perso->box.size.y );

  glEnd();

}

void dessinActiveCursor(Personnage *perso){
  float i = 2*sin(perso->cursorTimer/2.0);
  glBegin(GL_TRIANGLES);
      // Haut gauche
          glVertex2f(perso->box.pos.x + perso->box.size.x/2 - (TAILLE_CASE/4), perso->box.pos.y - (TAILLE_CASE) +i );
      // glVertex2f((perso->centerX - (TAILLE_CASE/4)) -4*perso->sens , perso->centerY - (perso->height*TAILLE_CASE/2) - (TAILLE_CASE) +i);
      // Haut droite
          glVertex2f(perso->box.pos.x + perso->box.size.x/2 + (TAILLE_CASE/4) , perso->box.pos.y - (TAILLE_CASE) +i );
      // glVertex2f((perso->centerX + (TAILLE_CASE/4)) -4*perso->sens , perso->centerY - (perso->height*TAILLE_CASE/2) - (TAILLE_CASE) +i);
      // Bas millieu
          glVertex2f(perso->box.pos.x + perso->box.size.x/2, perso->box.pos.y - (TAILLE_CASE/2) +i );
      // glVertex2f((perso->centerX) -4*perso->sens , perso->centerY - (perso->height*TAILLE_CASE/2) - (TAILLE_CASE/2) +i);
  glEnd();
}

// 
void dessinMenu(){
  glEnable(GL_TEXTURE_2D);
  // FIXME : Bind texture
  glBindTexture(GL_TEXTURE_2D, 1);
  /* Dessin du quad */
  glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glTexCoord2f(1, 1);
    glVertex2f(WINDOW_WIDTH/2 + 100, WINDOW_HEIGHT/3 +50);
    glTexCoord2f(1, 0);
    glVertex2f(WINDOW_WIDTH/2 + 100, WINDOW_HEIGHT/3 -50);
    glTexCoord2f(0, 0);
    glVertex2f(WINDOW_WIDTH/2 -100,WINDOW_HEIGHT/3 -50);
    glTexCoord2f(0, 1);
    glVertex2f(WINDOW_WIDTH/2 -100,WINDOW_HEIGHT/3 +50);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);

  glBindTexture(GL_TEXTURE_2D, 2);
  glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glTexCoord2f(1, 1);
    glVertex2f(WINDOW_WIDTH/2 + 100, WINDOW_HEIGHT/2 +50);
    glTexCoord2f(1, 0);
    glVertex2f(WINDOW_WIDTH/2 + 100, WINDOW_HEIGHT/2 -50);
    glTexCoord2f(0, 0);
    glVertex2f(WINDOW_WIDTH/2 -100,WINDOW_HEIGHT/2 -50);
    glTexCoord2f(0, 1);
    glVertex2f(WINDOW_WIDTH/2 -100,WINDOW_HEIGHT/2 +50);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);

  glBindTexture(GL_TEXTURE_2D, 3);
  glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glTexCoord2f(1, 1);
    glVertex2f(WINDOW_WIDTH/2 + 100, 2*WINDOW_HEIGHT/3 +50);
    glTexCoord2f(1, 0);
    glVertex2f(WINDOW_WIDTH/2 + 100, 2*WINDOW_HEIGHT/3 -50);
    glTexCoord2f(0, 0);
    glVertex2f(WINDOW_WIDTH/2 -100,2*WINDOW_HEIGHT/3 -50);
    glTexCoord2f(0, 1);
    glVertex2f(WINDOW_WIDTH/2 -100,2*WINDOW_HEIGHT/3 +50);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);

  glDisable(GL_TEXTURE_2D);
}

void loadTexture(const char* filename, GLuint textureID[11], int numTexture){
   SDL_Surface* image;
   image = IMG_Load(filename);
   if(image == NULL){
      printf("Error : image not found : %s\n", filename);
   } 
      
  glGenTextures(1, textureID);

  glBindTexture(GL_TEXTURE_2D, numTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
  // TODO : Supprimer les texture lors de la fermeture du prog
  //glDeleteTextures(10, &textureID);
  SDL_FreeSurface(image);
}

void dessinActiveMenu(int numMenu){

  switch(numMenu){
    case 1:
      glBegin(GL_TRIANGLES);
        glVertex2f(WINDOW_WIDTH/3 + WINDOW_WIDTH/50 , WINDOW_HEIGHT/3 +10);
        glVertex2f(WINDOW_WIDTH/3 + WINDOW_WIDTH/50, WINDOW_HEIGHT/3 -10);
        glVertex2f(WINDOW_WIDTH/3 + WINDOW_WIDTH/50 +20, WINDOW_HEIGHT/3);
      glEnd();

      glBegin(GL_TRIANGLES);
        glVertex2f(2*WINDOW_WIDTH/3 - WINDOW_WIDTH/50 -20, WINDOW_HEIGHT/3);
        glVertex2f(2*WINDOW_WIDTH/3 - WINDOW_WIDTH/50 , WINDOW_HEIGHT/3 +10);
        glVertex2f(2*WINDOW_WIDTH/3 - WINDOW_WIDTH/50, WINDOW_HEIGHT/3 -10);          
      glEnd();
    break;

    case 2:
      glBegin(GL_TRIANGLES);        
        glVertex2f(WINDOW_WIDTH/3 + WINDOW_WIDTH/50 , WINDOW_HEIGHT/2 +10);
        glVertex2f(WINDOW_WIDTH/3 + WINDOW_WIDTH/50, WINDOW_HEIGHT/2 -10);
        glVertex2f(WINDOW_WIDTH/3 + WINDOW_WIDTH/50 + 20, WINDOW_HEIGHT/2);
      glEnd();

      glBegin(GL_TRIANGLES);
        glVertex2f(2*WINDOW_WIDTH/3 - WINDOW_WIDTH/50 -20, WINDOW_HEIGHT/2);
        glVertex2f(2*WINDOW_WIDTH/3 - WINDOW_WIDTH/50 , WINDOW_HEIGHT/2 +10);
        glVertex2f(2*WINDOW_WIDTH/3 - WINDOW_WIDTH/50, WINDOW_HEIGHT/2 -10);
      glEnd();
      break;

    case 3:
      glBegin(GL_TRIANGLES);
        glVertex2f(WINDOW_WIDTH/3 + WINDOW_WIDTH/50 , 2*WINDOW_HEIGHT/3 +10);
        glVertex2f(WINDOW_WIDTH/3 + WINDOW_WIDTH/50, 2*WINDOW_HEIGHT/3 -10);
        glVertex2f(WINDOW_WIDTH/3 + WINDOW_WIDTH/50 + 20, 2*WINDOW_HEIGHT/3);
      glEnd();

      glBegin(GL_TRIANGLES);
        glVertex2f(2*WINDOW_WIDTH/3 - WINDOW_WIDTH/50 -20, 2*WINDOW_HEIGHT/3);
        glVertex2f(2*WINDOW_WIDTH/3 - WINDOW_WIDTH/50 , 2*WINDOW_HEIGHT/3 +10);
        glVertex2f(2*WINDOW_WIDTH/3 - WINDOW_WIDTH/50, 2*WINDOW_HEIGHT/3 -10);
      glEnd();
      break;
  }
}
