/************************************/
/*   Gestion des déplacements       */
/************************************/

function deplacementJoueur():void{
	
	var L:int;																// ligne (grille) du centre du perso
	var C:int; 																// colonne (grille) du centre du perso
	var Ls:int;																// ligne (grille) du point bas du perso, on considère que ses pieds sont à 1 pixel du bord de la case
	var Cs:int;																// colonne (grille) du bord du perso dans le sens de son déplacement
	var A:Object;															// la tuile située sous le perso
	var B:Object; 															// la tuile située aux pieds du perso
	var X:Object;															// tuile des objets
	var Y:Number;															// position sur Y avant déplacement
	var P:Array;															// tableau de positions
	
	with(perso){															// avec le perso
		
		x += vit*sens; 														// déplace sur X
		
		L =  y/T;															// ligne (grille) du centre du perso
		C =  x/T;															// colonne (grille) du centre du perso
		Ls = (y+T-1)/T;														// ligne (grille) du point bas du perso, on considère que ses pieds sont à 1 pixel du bord de la case
		Cs = (x+vit*sens)/T;												// colonne (grille) du perso, concernée par la colission (sens)
		
		P =  checkLateral(perso,L,Cs,vit*2,(y-dT)/T);						// collisions latérales
		
		L =  P[0];															// nouvelle valeur de L
		Cs = P[1];															// nouvelle valeur de Cs
		A =  stock[L][C];													// la tuile située sous le perso
		B =  stock[Ls][C];													// la tuile située aux pieds du perso
		X = map[Ls][C];														// tuile des objets pour  verification
		Y =  (L-1)*T;														// la position sur Y avant collision	
	
		if ((X==56) || (X==57) || (X==60)){
			checkObjet(Ls,C);												// collision objets case moitié basse perso
		}
		if (checkPentes(perso,A,B,Ls,C)) return;							// collision pentes
			
		y += gravite; 														// déplace sur Y
													
		if (gravite<0 && checkPlafond(perso,C,(y-dT)/T,vit*2,dT))return; 	// collision plafond
		if (A.nuage   && checkNuage(perso,Y)) return;						// collision nuages	
		if (A.solide  && checkSolide(perso,Y)) return;						// collision tout solide
		
		if (gravite++>T) gravite=T;											// gravité
	}
}

