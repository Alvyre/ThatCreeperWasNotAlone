/************************************/
/*   Gestion du joueur              */
/************************************/

function gestionJoueur():void {

	// variables
	perso.sens = int(droite)-int(gauche);				// direction sur X
	perso.monte = int(haut)-int(bas)					// direction sur Y
	perso.sauter = -int(haut)*11						// saut
	aucune = !droite && !gauche && !haut && !bas		// aucune action
	lateral = droite || gauche;							// mouvement latéral
		
	// déplacements 
	deplacementJoueur()									// déplacements du perso
	
	// mouvements
	if(perso.taille==0){								// si Mario est petit
		
		if (perso.sens) perso.scaleX = perso.sens;		// oriente le perso
		if (aucune) mouvement(1);						// repos 
		if (lateral) mouvement(2); 						// droite et gauche
		if (perso.gravite<0) mouvement(3); 				// saute
		if (perso.gravite>0) mouvement(4); 				// tombe
	}
	
	if(perso.taille==1){								// SI LE PERSO EST GRAND
		if (perso.sens) perso.scaleX = perso.sens;		// oriente le perso
		if (aucune) mouvement(5);						// repos 
		if (lateral) mouvement(6); 						// droite et gauche
		if (perso.gravite<0) mouvement(7); 				// saute
		if (perso.gravite>0) mouvement(8); 				// tombe
	}
}

// mouvements du perso
function mouvement(mouv):void {
	if (perso.currentFrame != mouv) {					// si le mouvement est différent de celui à effectuer
		perso.gotoAndStop(mouv);						// effectue le nouveau mouvement
	}
}

// vérifie si Mario est Mort
function verifMort():void{
	if((perso.y>=540)||(c<=0)) mort();
}

// fonction qui gère la mort
function mort():void{
	perso.mort = true;
	grille.removeChild(perso);
	removeEventListener(Event.ENTER_FRAME, main);		// supprime le moteur
	playerTheme.stop();									// arret du son
	tps.stop();											// arret du timer
	
	perso.vie-=1;										// le perso perd une vie
	life.text = perso.vie;								// MAJ  affichage vie
	if(perso.vie>0){									// si le perso a encore des vies
		respawn.start();								// lancement du timer respawn
		addChild(mario);								// ajour du mannequin et placement
		mario.x=Gw/2;
		mario.y=520;
		mario.play();
		if(mute==false) playerBruitage = mortSound.play();// lancement du son mort;
	}
	else{												// si plus de vie GAME OVER
	supprVar();
	}
}


// fonction pour le spawn de Mario
function spawn(e:TimerEvent):void{
	compt-=1;
	if(compt<=0){
		perso.visible=true;
		removeChild(mario);
		if(mute==false) playerTheme = theme.play(10,1); // lancement du son theme
		tps.reset();
		c = 100;										// RAZ du temps
		tps.start();									// reprise du timer imparti
		respawn.reset();
		compt=4; 										// remise a zéro du compteur
		reboot();										// reboot les var
	}
}

