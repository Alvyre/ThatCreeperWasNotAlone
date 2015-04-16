#include <GL/gl.h>
#include <GL/glu.h>
#include "main.h"

// TODO : taille
void dessinCarre(int filled, int posX, int posY){
  if(filled==1){
    glBegin(GL_POLYGON);
  }else{
    glBegin(GL_LINE_LOOP);
  }
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