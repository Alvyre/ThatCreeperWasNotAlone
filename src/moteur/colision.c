/************************************/
/*   Gestion des collisions         */
/************************************/

#include "moteur/colision.h"
// collisions latérales

void checkLateral(Personnage *perso,int L, int C, uint D, int H, int* result, int** level) {
	for (L=H; L<perso->centerY/TAILLE_CASE+1; L++) {											// vérifie toutes lignes (grille) sur lesquelles il se tient
		for (C=(perso->centerX-D)/TAILLE_CASE; C<(perso->centerX+D)/TAILLE_CASE; C++){			// vérifie toutes colonnes (grille) sur lesquelles il se tient
			if (level[L][C] == 1) {																// si le bord renconte un bloc solide en latéral
				if (perso->sens==1)  perso->centerX = C*TAILLE_CASE-D;							// colle le perso au bord du bloc (droite)
				if (perso->sens==-1) perso->centerX = C*TAILLE_CASE+D+TAILLE_CASE;				// colle le perso au bord du bloc (gauche)
			}
		}
	}
	result[0] = L;
	result[1] = C;
}




// colision avec un bloc de type solide

bool checkSolide(Personnage *perso,uint Y) {

	if(perso->centerY >= Y && hit(perso,Y)){
		return true;
	}
	return false;
}

// collision roof
bool checkPlafond(Personnage *perso,int C,int L,uint D,uint H, int **level){															
		for (C=(perso->centerX-D)/TAILLE_CASE; C<(perso->centerX+D)/TAILLE_CASE; C++) {			// cases occupées par les limites X du perso 
			if (level[L][C] == 1) {																// si la case n'est pas vide
				perso->centerY = (L+2)*TAILLE_CASE-H;											// position du perso sur Y
				perso->gravite=1;																// arrête le saut
				return true;
			}
		}
		return false;
	}

// fonction de Hit Test
	bool hit(Personnage *perso,uint Y){

		perso->centerY = Y;																		// position
		perso->gravite = perso->saute;															// saut
		return true	;																			// actions effectuées
}
