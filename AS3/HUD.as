/************************************/
/*   Gestion du HUD                 */
/************************************/

//vie
life.text = perso.vie;
//pseudo
pseudoDisplay.text = contenu;
//timer
tps.start();


/************************************/
/*   Fonctions                      */
/************************************/

// fonction pour le timer
function tpsImparti(e:TimerEvent):void{
	c-=1;
	temps.text=String(c);													// affichage temps restant
	score.text=String(perso.score);											// affichage du score (MàJ)
}

// fonction Main
function main(e:Event):void {
	gestionJoueur();														// gestion du joueur
	verifMort();															// verification mort du perso
	scrolling();															// fonction de scroll
}

// fonction contenant la fin du jeu si WIN
function lancementFin():void{												
		playerTheme.stop();													// arrêt du theme
		if(mute==false) playerBruitage = gagner.play(); 					// lancement du son gagner						
		tps.stop();															// arrêt du temps
		stage.removeEventListener(KeyboardEvent.KEY_DOWN, appuyer);			// desactive les fleches
		stage.removeEventListener(Event.ENTER_FRAME, main);					// desactive toutes les fonctions importantes
		if(perso.taille==0){												// fin pour petit mario
			var marioEnd:marioEndP = new marioEndP();
			marioEnd.x = perso.x;
			marioEnd.y = 512;
			perso.visible = false;
			grille.addChild(marioEnd);
			marioEnd.play();

		}
		else if( perso.taille==1){											// fin pour grand mario
			var marioEnd2:marioEndG = new marioEndG();
			marioEnd2.x = perso.x;
			marioEnd2.y = 512;
			perso.visible = false;
			grille.addChild(marioEnd2);
			marioEnd2.play();
		}
		var comptFin:Timer = new Timer (1000,7);							// compteur de 7 sec pour la musique "gagner"
		comptFin.addEventListener(TimerEvent.TIMER, fin); 					// écouteur pour la fonction pour l'affichage du score
		comptFin.start();
		var compt2:int=7;
		function fin(e:TimerEvent):void{									// fx pour remove le perso, le décor, afficher score total
			compt2-=1;
			if (compt2<=0){
				removeChild(grille);
				BG.visible = false;
				scoreTemps.text = ("Temps : "+c+" X 100 = "+(c*100));
				perso.score+=(c*100);
				scoreVie.text =("Vies : "+perso.vie +" X 50 = "+(perso.vie*50));
				perso.score+=(perso.vie*50);
				scoreTotal.text =( "Score total : " +perso.score);
				var shRecord:showRecord = new showRecord;					// bouton et fx pour aller voir les scores
				addChild(shRecord);
				shRecord.x=657,95;
				shRecord.y=500;
				shRecord.addEventListener(MouseEvent.CLICK,regarderRecord);
				function regarderRecord():void{
					gotoAndStop(6);
					if(mute==false) playerBruitage = tuyau.play(); 			// lancement du son bouton
					removeChild(shRecord);
				}
			}

		}

}

// fonction pour reboot en cas de mort
function reboot():void{	 
	stock = [];
	grille.removeChild(decor);
	grille.removeChild(objets);
	removeChild(grille);
	addChild(grille);
	perso.x=cX;
	replaceGrille();
	grille.addChild(decor);
	grille.addChild(objets);
	creeStock();												
	creeZone();		
	creeDecor();
	grille.addChild(perso);
	stage.addEventListener(Event.ENTER_FRAME, main);// main
	initPerso();
	}

// fonction de suppression de variable si Game Over
function supprVar():void{ 
	stage.removeEventListener(Event.ENTER_FRAME, main);// main
	stock = [];
	grille.removeChild(decor);
	grille.removeChild(objets);
	removeChild(grille);
	gotoAndStop(4);
}