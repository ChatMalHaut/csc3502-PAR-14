/* Definition des fonctions permettant de lire et d'ecrire
   une image au format PGM.
   Une image est un tableau 2D de nbLignes x nbColonnes 
   de pixels codes sur un octet ( 256 niveaux de gris ) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "tab2Ddynamique.h"

#define LONGUEUR 100
    
  // Definition de la fonction de lecture a partir d'un fichier

Image lireImage ( char *nomFichier ) {

  Image image;
  FILE *fichier;
  char ligne[LONGUEUR];
  int niveauMax;
  
  if ( ( fichier = fopen ( nomFichier, "r" ) ) == NULL ) 
  {
    fprintf ( stderr, "Erreur Ouverture fichier\n" );
    exit ( EXIT_FAILURE );
  }
  
  // Lecture de l'en-tete
  
  fgets ( ligne, LONGUEUR, fichier );
  if ( strstr ( ligne, "P5" ) == NULL ) 
  {
    fprintf ( stderr, "Erreur format image\n" );
    exit ( EXIT_FAILURE );
  }
  do 
  {
    fgets ( ligne, LONGUEUR, fichier );
  } while ( ligne[0] == '#' || ligne[0] == '\n' );
  sscanf ( ligne, "%d%d", &image.nbColumns, &image.nbLines);
  fscanf ( fichier, "%d", &niveauMax);
  fgetc ( fichier ); // pour le dernier retour a la ligne de l'en-tete

  // Reservatiom memoire
  
  image.t2D = allouer ( image.nbLignes, image.nbColonnes );
  
  // Lecture des valeurs de pixels
  
  fread ( image.t2D[0], sizeof(Pixel),
	  image.nbLines*image.nbColumns, fichier );
  
  // Fermeture du fichier
  
  fclose(fichier);
  
  return image;
}

  // Definition de la fonction d'ecriture dans un fichier 

void ecrireImage ( Image image,char *nomFichier ) 
{

  FILE *fichier;
  char *type = "P5";
  char *createur = "#CREATOR: lissage Version 1.0";
  int niveauMax = 255;
  
  
  if ( ( fichier = fopen ( nomFichier, "w" ) ) == NULL ) 
  {
    fprintf ( stderr, "Erreur Ouverture fichier\n" );
    exit ( EXIT_FAILURE );
  }
  
  // Ecriture de l'en-tete
  
  fprintf ( fichier, "%s\n%s\n", type, createur );
  fprintf ( fichier, "%d %d\n", image.nbColumns, image.nbLines );
  fprintf ( fichier, "%d\n", niveauMax );
  
  // Ecriture des valeurs de pixels
  
  fwrite ( image.t2D[0], sizeof(Pixel),
	   image.nbLines*image.nbColumns, fichier );

  // Fermeture du fichier
  
  fclose ( fichier );
}

