#ifndef _IMAGE_H
#define _IMAGE_H 1

/* Definition des types Pixel et Image
   Une image est un tableau 2D de nbLignes x nbColonnes 
   de pixels codes sur un octet ( 256 niveaux de gris ) */

typedef unsigned char Pixel;

typedef struct { int nbLines;
		 int nbColumns;
		 Pixel **t2D;	 } Image;

    
/* Declaration des fonctions de lecture-ecriture */

Image lireImage ( char *nomFichier );
void ecrireImage ( Image image, char *nomFichier );

#endif
