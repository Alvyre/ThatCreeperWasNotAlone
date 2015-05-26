#include "formes/draw.h"

void dessinCarre(int posX, int posY, Color3f *color){
  glColor3f(color->r,color->g,color->b);

  glBegin(GL_POLYGON);
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
     // glVertex2f(perso->centerX-(perso->width*TAILLE_CASE/2),perso->centerY-(perso->height*TAILLE_CASE/2));
    // Haut droite
        glVertex2f(perso->box.pos.x + perso->box.size.x,perso->box.pos.y );
     // glVertex2f(perso->centerX+(perso->width*TAILLE_CASE/2),perso->centerY-(perso->height*TAILLE_CASE/2));
    // Bas droite
        glVertex2f(perso->box.pos.x + perso->box.size.x,perso->box.pos.y + perso->box.size.y );
     // glVertex2f(perso->centerX+(perso->width*TAILLE_CASE/2),perso->centerY+(perso->height*TAILLE_CASE/2));
    // Bas gauche
        glVertex2f(perso->box.pos.x ,perso->box.pos.y + perso->box.size.y );
     // glVertex2f(perso->centerX-(perso->width*TAILLE_CASE/2),perso->centerY+(perso->height*TAILLE_CASE/2));

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
