#include<stdlib.h>
#include<stdio.h>
#include "testReconnaissance_v2.h"
#include "image.h"
#include "affichage.h"
#include "tab2Ddynamique.h"
int main ( int argc, char *argv[] ) 
	{
	  Image imSource,imDest;
	  int cote;
	  Ecran ecran;
	  
			 
	  imSource = lireImage ( argv[1] );

	  ecran = initialiserAffichage ( imSource.nbColonnes,
					 imSource.nbLignes, argv[1] );
	  usleep ( 10000 );
	  afficherImage ( ecran, &imSource );
	  sleep ( 1 );
	  comparaison(imSource, banqueDeDonnees, banqueDeDonneeAsso, ecran);
	  sleep ( 3 );
	  printf ( "\nEcriture fichier...\n" );
	  ecrireImage ( imDest, argv[2] );
	  libererAffichage ( ecran );

	  // desallocation memoire
	  imSource.t2D = desallouer ( imSource.t2D );
	  imDest.t2D=desallouer ( imDest.t2D );
	  return EXIT_SUCCESS;
	}
