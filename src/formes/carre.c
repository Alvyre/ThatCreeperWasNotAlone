#include <GL/gl.h>
#include <GL/glu.h>

// TODO : taille
void dessinCarre(int filled){
  if(filled==1){
    glBegin(GL_POLYGON);
  }else{
    glBegin(GL_LINE_LOOP);
  }
     // Haut gauche
     glVertex2f(-5,-5);
     // Haut droite
     glVertex2f(5,-5);
          // BAs droite
     glVertex2f(5,5);
     // Bas gauche
     glVertex2f(-5,5);

  glEnd();

}