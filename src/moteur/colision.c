/************************************/
/*   Gestion des collisions         */
/************************************/

#include "moteur/colision.h"

/************* Fonction de collisions principale *************/

void collisions(Personnage* persos, int nbJoueurs, int **level){
    
    /** Séparation des collisions selon les x & les y pour une meilleure gestion des mouvements **/
    /** Un personnage peut effectuer un mouvement (x,y), mais aussi (x,0) ou (0,y)              **/
    /** Utilisation de boucle for pour affiner les collisions par pixel                         **/
    /** On teste d'abord avec la map et ensuite avec les autres personnages                     **/

    int i,j,k,l;

    /* Pour chaque joueur on vérifie les collisions */
    for ( k = 0; k < nbJoueurs; ++k){
        AABB boxPerso = persos[k].box;
        bool canMove;
        
    /* Collisions Latérales */
        for(i=0; i< persos[k].vitesse; i++){
            boxPerso.pos.x += persos[k].dir.x *i; 
            canMove = true;
            if(collisionsAvecMap(boxPerso, level, 40, 30)) canMove = false;
            if(collisionAvecJoueur(persos, nbJoueurs, boxPerso, k)) canMove = false; 
            if (canMove)
                persos[k].box = boxPerso;
            else 
                boxPerso = persos[k].box;
        }

    /* Collisions toit */
        for(l = 0; l>= persos[k].dir.y;l--){
            boxPerso.pos.y -=1;
            canMove = true;
            if(collisionsAvecMap(boxPerso, level, 40, 30))
                canMove = false;
            if(collisionAvecJoueur(persos, nbJoueurs, boxPerso, k))
                canMove = false;
            if (canMove) 
                persos[k].box = boxPerso;
            else 
                boxPerso = persos[k].box;
        }
        
    /* Collisions sol */
        for(j = 0; j< persos[k].gravite; ++j ){
            boxPerso.pos.y += 1;
            canMove = true;
            if(collisionsAvecMap(boxPerso, level, 40, 30))
                canMove = false;
            if(collisionAvecJoueur(persos, nbJoueurs, boxPerso, k))
                canMove = false;
            if (canMove)
                persos[k].box = boxPerso;
            else{
                persos[k].gravite = persos[k].defaultGravite;
                persos[k].saute = false;
                persos[k].dir.y = 0;
            }
        }
        persos[k].gravite++;
    } 
}

/************* Fonction de collisions map *************/

/** On parcourt les cases pour trouver si le personnage est en collisions avec un bloc non vide (!=0) **/

bool collisionsAvecMap(AABB boxPerso, int** level, int widthLevel, int heightLevel){
    int x,y;
    AABB boxCase;
    boxCase.size.x = TAILLE_CASE;
    boxCase.size.y = TAILLE_CASE;

    for (x = 0; x < widthLevel; ++x){           // a optimiser avec pos perso
        for (y = 0; y < heightLevel; ++y){
            if (level[y][x] == SOLIDE){
                boxCase.pos.x = x*TAILLE_CASE;
                boxCase.pos.y = y*TAILLE_CASE;
                if (collide(boxPerso, boxCase))
                    return true;
            }
        }
    }
    return false;
}

/************* Fonction de collisions joueurs *************/

/** On parcourt tous les personnages du jeu et on teste les collisions **/
/** le continue; sert à exclure le personnage actif                    **/

bool collisionAvecJoueur(Personnage* persos, int nbJoueurs, AABB boxPerso,  int numeroJoueur){
    int j;
    for (j = 0; j < nbJoueurs; ++j){
        if (numeroJoueur == j)
            continue;

        if (collide(boxPerso, persos[j].box)) 
            return true;
    }
    return false;
}

/************* Fonction de collisions type AABB *************/

bool collide(AABB a, AABB b){
   if((b.pos.x >= a.pos.x + a.size.x)       // trop à droite
    || (b.pos.x + b.size.x <= a.pos.x)      // trop à gauche
    || (b.pos.y >= a.pos.y + a.size.y)      // trop en bas
    || (b.pos.y + b.size.y <= a.pos.y))     // trop en haut
      return false; 
  else
      return true; 
}


