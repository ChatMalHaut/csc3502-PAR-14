/* Affichage en temps reel sur un probleme de lissage

   Ce module ne fonctionne qu'en mode "TrueColor"
     - affichage sur 16 ou 24 plans

   Definition  du module affichage */

#include <stdlib.h>
#include <stdio.h>
#include "affichage.h"


Ecran initialiserAffichage ( int largeur, int hauteur, char *nomFichier ) 
{ 
  
  Ecran screen;
  Window racine;
  int ecran;
  unsigned long noir, blanc;
  int i,v;

  // Ouverture de l'affichage
  if ( ( screen.display = XOpenDisplay ( "" ) ) == NULL ) 
  {
    fprintf ( stderr, "Can't open display\n" ); 
    exit ( EXIT_FAILURE );
  }

  // Connexion a un serveur
  ecran = DefaultScreen ( screen.display );
  racine = RootWindow ( screen.display, ecran );
  noir = BlackPixel ( screen.display, ecran );
  blanc = WhitePixel ( screen.display, ecran );

  // Creation de la fenetre
  screen.fen = XCreateSimpleWindow ( screen.display, racine, 0, 0,
				     largeur, hauteur, 0, noir, blanc );

  // Creation d'un contexte graphique
  screen.gc = XCreateGC ( screen.display, screen.fen, 0, 0 );
  XStoreName ( screen.display, screen.fen, nomFichier );
  XMapWindow ( screen.display, screen.fen) ;
  XMoveWindow ( screen.display, screen.fen, 0, 0 );

  screen.nbEcran = DefaultScreen ( screen.display );

  // On recupere le nombre de plans de bits
  screen.nbPlans = DisplayPlanes ( screen.display, screen.nbEcran );
  screen.visual = XDefaultVisual ( screen.display, screen.nbEcran );

  switch ( screen.nbPlans ) 
  {
  case 8  : fprintf ( stderr, "Ne fonctionne qu'en mode TrueColor\n" );
            fprintf ( stderr, "Affichage sur 24 ou 16 plans\n" );
	    exit ( EXIT_FAILURE );
  case 16 : //printf ( "Affichage sur 16 plans\n" );
            break;
  case 24 : //printf ( "Affichage sur 24 plans\n" );
            break;
  default : fprintf ( stderr, "Erreur...\n" );
  }

  // Les masques pour les 3 composantes
  screen.mask[RED] = screen.visual->red_mask;
  screen.mask[GREEN] = screen.visual->green_mask;
  screen.mask[BLUE] = screen.visual->blue_mask;

  // on en deduit les decalages et nombres de bits
  // pour les 3 composantes
  for ( i=0; i<NB_RGB; i++) //  masques decalages nb_bits
  { 
    v = screen.mask[i];    
    screen.shift[i] = 0;     // R ff0000     16       8
    while ( !(v&1) ) 
	{     //24 G   ff00      8       8  
      v >>= 1;               // B     ff      0       8
      screen.shift[i]++;
    }                        // R   f800     11       5  
    screen.bits[i] = 0;    //16 G    7e0      5       6  
    while ( v&1 ) 
	{          // B     1f      0       5
      v >>= 1;
      screen.bits[i]++;
    }
  }

  // Allocation pour stocker l'image
  if ( ( screen.tImage = calloc ( hauteur*largeur,
				  sizeof(unsigned int) ) ) == NULL ) 
  {
    fprintf ( stderr, "Erreur alloc tImage\n" );
    exit ( EXIT_FAILURE );
  }

  // Creation de la pixmap
  screen.ximage = XCreateImage ( screen.display, screen.visual,
				 screen.nbPlans, ZPixmap, 0,
				 screen.tImage, largeur, hauteur, 8, 0 );
  XFlush ( screen.display );
  return screen;
}

void libererAffichage ( Ecran ecran ) 
{

  // Liberation memoire
  free ( ecran.tImage );

  // Liberation du contexte graphique
  XFreeGC ( ecran.display, ecran.gc );

  // Destruction de la fenetre
  XDestroyWindow ( ecran.display, ecran.fen );

  // Fermeture de la connexion
  XCloseDisplay ( ecran.display );
}

void afficherImage ( Ecran ecran, Image *pIm ) {

  int x,y,i,pixRGB;
  Pixel pix;

  for ( x=0; x<pIm->nbLignes; x++ )
    for ( y=0; y<pIm->nbColonnes; y++ ) 
	{

      pixRGB = 0;
      for ( i=0; i<NB_RGB; i++ ) 
	  {
		pix = pIm->t2D[x][y];
		pix >>= (8-ecran.bits[i]);
		pixRGB |= (pix<<ecran.shift[i])&ecran.mask[i];
      }
      XPutPixel ( ecran.ximage, y, x, pixRGB );
    }
	
  XPutImage ( ecran.display, ecran.fen, ecran.gc, ecran.ximage, 0, 0, 0, 0, pIm->nbColonnes, pIm->nbLignes );
  XFlush ( ecran.display );
}

void changerLigne ( Ecran ecran, Image *pIm, int y ) {
  
  int x,i,pixRGB;
  Pixel pix;
  for ( x=0; x<pIm->nbColonnes; x++ ) {

    pixRGB = 0;
    for ( i=0; i<NB_RGB; i++ ) {
      pix = pIm->t2D[y][x];
      pix >>= (8-ecran.bits[i]);
      pixRGB |= (pix<<ecran.shift[i])&ecran.mask[i];
    }
    XPutPixel ( ecran.ximage, x, y, pixRGB );
  }
  XPutImage ( ecran.display, ecran.fen, ecran.gc, ecran.ximage, 0, 0, 0, 0,
	      pIm->nbColonnes, pIm->nbLignes );
  XFlush ( ecran.display );
}

void changerBloc ( Ecran ecran, Image *pIm, int y, int h ) {
  
  int x,yy,i,pixRGB;
  Pixel pix;

  for ( yy=y-h+1; yy<=y; yy++ )
    for ( x=0; x<pIm->nbColonnes; x++) {

      pixRGB = 0;
      for ( i=0; i<NB_RGB; i++ ) {
	pix = pIm->t2D[yy][x];
	pix >>= (8-ecran.bits[i]);
	pixRGB |= (pix<<ecran.shift[i])&ecran.mask[i];
      }
      XPutPixel ( ecran.ximage, x, yy, pixRGB );
    }
  XPutImage ( ecran.display, ecran.fen, ecran.gc, ecran.ximage, 0, 0, 0, 0,
	      pIm->nbColonnes, pIm->nbLignes );
  XFlush ( ecran.display );
}

// On pourrait egalement definir une fonction changerColonne
