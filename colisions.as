/************************************/
/*   Gestion des collisions         */
/************************************/

// collision latérale
function checkLateral(O:Object,L:int,C:int,D:Number,H:int):Array {
	with(O){														// avec l'objet
		if(!sloped) {												// si il n'est pas sur une pente
			for (L=H; L<y/T+1; L++) {								// vérifie toutes lignes (grille) sur lesquelles il se tient
				for (C=(x-D)/T; C<(x+D)/T; C++){					// vérifie toutes colonnes (grille) sur lesquelles il se tient 
					if (stock[L][C].solide) {						// si le bord renconte un bloc solide en latéral (prévoir multiples tuiles)
						if (sens==1)  x = C*T-D;					// colle l'objet au bord du bloc (droite)
						if (sens==-1) x = C*T+D+T;					// colle l'objet au bord du bloc (gauche)
						if(O!=perso) sens*=-1;						// si l'objet testé n'est pas le perso il change de sens
					}
				}
			}
		}
	}
	return [L,C]	;												// renvoie les nouvelles valeurs de L et C
}


// collision avec un bloc de type nuage
function checkNuage(O:Object,Y:Number):Boolean {
	with(O){
		if(y>=Y && hit(O,Y)) return true;		
	}
	return false;
}


// collision avec un bloc de type pente
function checkPentes(O:Object, A:Object, B:Object, L:int, C:int):Boolean {
	with(O) {																					// avec l'objet
		if (gravite>0){																			// si l'objet tombe	
				if (B.slope==1 && y>=(L+C)*T-x && hit(O,(L+C)*T-x,true)) return true;			// si tombe dessus et depasse la pente replace sur la pente
				if (B.slope==-1 && y>=(L-C-1)*T+x && hit(O,(L-C-1)*T+x,true)) return true;		// si tombe dessus et depasse la pente replace sur la pente
		} else if (gravite==0){																	// si l'objet avance
			for (var i:int=0;i<2;i++){															// boucle sur deux cases, celle ou il se tient et celle qui est en dessous (pour les descentes)
				if (L+i<map.length){															// attention a ne pas dépasser la zone de jeu (case testée)
					if (stock[L+i][C].slope==-1 && hit(O,(L+i-C-1)*T+x,true)) return true;		// avancer a gauche sur pente
					if (stock[L+i][C].slope==1 && hit(O,(L+i+C-0.3)*T-x,true)) return true;		// avancer à droite sur pente		
				}
			}
			if (B.solide && !stock[L-1][C].solide && hit(O,(L-1)*T)) return true;				// fin de montée (gauche et droite)
			if ((stock[L][C+1].slope==1 || stock[L][C-1].slope==-1) && hit(O,L*T)){						
				if (A.solide) return true;		// fin de descente (gauche et droite)
			}
		} 
		sloped=false;																			// sinon l'objet n'est pas sur une pente
	}
	return false;
}

// collision avec un bloc de type solide
function checkSolide(O:Object,Y:Number):Boolean {
	with(O){   																					// avec l'objet
		if(y>=Y && hit(O,Y)){
			return true;
		}
	}
	return false;
}

// collision avec le bas d'un bloc
function checkPlafond(O:Object,C:int,L:int,D:Number,H:Number):Boolean{
	with(O){																// avec l'objet
		for (C=(x-D)/T; C<(x+D)/T; C++) {									// cases occupées par les limites X de l'objet 
		var temp = objets.getChildByName("t_"+L+"_"+C);						// récupération de la var
			if (stock[L][C].solide) {										// si la case n'est pas vide
				if((stock[L][C].bloc)||(temp.currentFrame==54)){			// si la case est un bloc tapable
					temp.gotoAndStop(55);									// affichage du bloc utilisé
					map[L][C]=55;											// echange la frame dans la map
					stock[L][C].bloc = false ;								// pour éviter de répéter le son
					perso.score+=150;										// gagne 150 points pour taper dans le bloc
					if(mute==false) playerBruitage = casseBrique.play();
					score.text=String(perso.score);							// MAJ score									
				}
				y = (L+2)*T-H;												// position de l'objet sur Y
				gravite=1;													// arrête le saut
				return true;
			}
		}
	}
	return false;
}



// efface l'objet
function checkObjet(L:int,C:int):void{
	map[L][C]=0;															// supprime l'objet de la map
	stock[L][C]=[];															// supprime l'objet du stock
	var temp = objets.getChildByName("t_"+L+"_"+C);
	if(temp.currentFrame==56){												// si c'est une pièce
		if(mute==false) playerBruitage = piece.play();						// lancement du son
		perso.score+=100;													// +100 point par pièce
		score.text=String(perso.score);										// affichage du score (MàJ)
	}
	if(temp.currentFrame==57){												// si c'est un champignon :
		if(perso.taille!=1) perso.taille=1;									// mario grandit s'il est petit
		if(mute==false) playerBruitage = champi.play(); 					// lancement du son
		perso.score+=200;													// gagne 200 points par champignon
		score.text=String(perso.score);										// affichage du score (MàJ)
	}
	if(temp.currentFrame==60){												// fin du jeu
		lancementFin();

	}
	objets.removeChild(objets.getChildByName("t_"+L+"_"+C));				// vide l'objet dans la liste d'affichage
}


// fonction de Hit Test
function hit(O:Object,Y:Number,S:Boolean=false):Boolean{
	with(O){
		y = Y;																// position
		gravite = sauter;													// saut
		sloped = S;															// pentes
	}
	return true	;															// actions effectuées
}
