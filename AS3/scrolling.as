/************************************/
/*   Gestion Scrolling              */
/************************************/

function scrolling():void{
	
	var C:int=0;													// ligne d'affichage
	var L:int=0;													// colonne d'affichage

	// scrolling horizontal
	if(mapW>Gx){													// si la map est plus large que la zone d'affichage
			
		var X:Number = 		perso.x;								// position du héro sur X
		var minX:Number = 	Gx*dT;									// position minimale du scrolling sur X
		var maxX:Number = 	map[0].length*T-minX;					// position maximale du scrolling sur X

		if(X>=minX && X<=maxX){										// si le héro n'est pas près d'un bord
			grille.x = -X+minX;										// scrolling de la grille sur X
			while (C<Gx+1){											// tant que la colonne est inférieure au nombre de colonnes max de la zone d'affichage
				with (decor.getChildByName("t_0_"+C)){				// avec chaque colonnes de la ligne 0
					if (x+grille.x<-T){								// si elle sort à gauche
						changeColonne(C,x+Gw+T,-grille.x/T+Gx);		// replace la colonne à droite
						break;										// stoppe la boucle
					}
					if (x+grille.x>Gw){								// si elle sort à droite
						changeColonne(C,x-Gw-T,-grille.x/T);		// replace la colonne à gauche
						break;										// stoppe la boucle
					}
				}
				C++;												// incrémente les colonnes
			}
		}
	}
	
	//scrolling vertical
	if(mapH>Gy){													// si la map est plus haute que la zone d'affichage
		
		var Y:Number = 		perso.y;								// position du héro sur Y
		var minY:Number = 	Gy*dT;									// position minimale du scrolling sur Y
		var maxY:Number = 	map.length*T-minY						// position maximale du scrolling sur Y

		if(Y>=minY && Y<=maxY){										// si le héro n'est pas près d'un bord 
			grille.y = -Y+minY;										// scrolling de la grille sur Y
			while (L<Gy+1){											// tant que la ligne est inférieure au nombre de lignes max de la zone d'affichage
				with (decor.getChildByName("t_"+L+"_0")){			// avec chaque lignes de la colonne 0
					if (y+grille.y<-T){								// si elle sort en haut
						changeLigne(L,y+Gh+T,-grille.y/T+Gy);		// replace la ligne en bas
						break;										// stoppe la boucle
					}	
					if (y+grille.y>Gh){								// si elle sort en bas
						changeLigne(L,y-Gh-T,-grille.y/T);			// replace la ligne en haut
						break;										// stoppe la boucle
					}
				}
				L++;												// incrémente les lignes
			}
		}
	}
}

// replace une ligne
function changeLigne(L:int,P:Number,Y:int):void{
	var C:int=Gx+1;													// colonne max de la zone d'affichage
	var f:int;														// frame à afficher
	while (C--) {													// tant qu'il reste des colonnes
		with (decor.getChildByName("t_"+L+"_"+C)){					// avec la tuile de la case
			y = P;													// place la tuile sur Y
			f = map[Y][int(x/T)];									// trouve la bonne frame
			if(f>0 && f!=56 && f!=57 && f!=55) (decor.getChildByName("t_"+L+"_"+C)).gotoAndStop(f);	
			else (decor.getChildByName("t_"+L+"_"+C)).gotoAndStop("vide");// affiche la bonne frame
		}
	}
}

// replace une colonne
function changeColonne(C:int,P:Number,X:int):void{
	var L:int=Gy+1;													// lignes max de la zone d'affichage
	var f:int;														// frame à afficher
	while (L--) {													// tant qu'il reste des lignes
		with (decor.getChildByName("t_"+L+"_"+C)){					// avec la tuile de la case
			x = P;													// place la tuile sur X
			f = map[int(y/T)][X];									// trouve la bonne frame
			if(f>0 && f!=56 && f!=57 && f!=55) (decor.getChildByName("t_"+L+"_"+C)).gotoAndStop(f);
			else (decor.getChildByName("t_"+L+"_"+C)).gotoAndStop("vide");// affiche la bonne frame
		}
	}
}

// replace la grille au début
function replaceGrille():void{
	grille.x = 0;		
	grille.y = 0;
}