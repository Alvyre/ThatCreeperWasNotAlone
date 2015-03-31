/************************************/
/*   Gestion des touches            */
/************************************/

var sautStop:uint=0;

// Appuyer sur une touche
function appuyer(e:KeyboardEvent):void {
	switch (e.keyCode) {
		case 39 :
			droite=true;	// aller à droite
			break;
		case 37 :
			gauche=true;	// aller à gauche
			break;
		case 40 :
			bas=true;		// aller en bas
			break;
		case 38 :
			haut=true;		// aller en haut
	 		if((sautStop==0)&&(perso.gravite>=0)&&(perso.visible==true)&&(saute==false) && (currentFrame==3)) { // son du saut du perso
				if(mute==false) playerBruitage = saut.play();
				sautStop=1;																						// sonStop sert à éviter la répétition du son si on reste appuyé
			}
			break;
	}
}
 
// relâcher une touche
function relacher(e:KeyboardEvent):void {
	switch (e.keyCode) {
		case 39 :
			droite=false;	// aller à droite
			break;
		case 37 :
			gauche=false;	// aller à gauche
			break;
		case 40 :
			bas=false;		// aller en bas
			break;
		case 38 :
			haut=false;		// aller en haut
			sautStop=0;
			break;
	}
 
}