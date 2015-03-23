int main ( int argc, char *argv[] ) 
	{
	  Image imSource,imDest;
	  int cote;
	  Ecran ecran;
	  
	  if ( argc != 4 ) { 
		fprintf ( stderr, "Usage : %s nomFichierSource nomFichierDest cote\n",
			  argv[0] );
		exit ( EXIT_FAILURE );
	  }
	  
	  cote = atoi ( argv[3] );
	  if ( cote%2 != 1 ) { 
		fprintf ( stderr, "Le cote de la fenetre doit etre impair\n" );
		exit ( EXIT_FAILURE );
	  }
			 
	  imSource = lireImage ( argv[1] );

	  ecran = initialiserAffichage ( imSource.nbColonnes,
					 imSource.nbLignes, argv[1] );
	  usleep ( 10000 );
	  afficherImage ( ecran, &imSource );
	  sleep ( 1 );
	  comparaison(imSource,banqueDeDonnees,ecran);
	  sleep ( 3 );
	  printf ( "\nEcriture fichier...\n" );
	  ecrireImage ( imDest, argv[2] );
	  libererAffichage ( ecran );

	  // desallocation memoire
	  imSource.t2D = desallouer ( imSource.t2D );
	  imDest.t2D=desallouer ( imDest.t2D );
	  return EXIT_SUCCESS;
	}