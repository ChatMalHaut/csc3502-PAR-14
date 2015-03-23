#ifndef _AFFICHAGE_H
#define _AFFICHAGE_H 1

/* Interface du module affichage */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "image.h"

  // Definition du type Ecran

#define NB_RGB 3

typedef struct { Display *display;
                 Window fen;
                 GC gc;
                 Visual *visual;
                 XImage *ximage;
                 int nbEcran;
                 int nbPlans;
                 char *tImage;
                 int mask[NB_RGB];
                 int shift[NB_RGB];
                 int bits[NB_RGB];} Ecran;

  // Gestion des couleurs

typedef enum { RED, GREEN, BLUE } RGB;

  // Declaration des fonctions d'affichage

Ecran initialiserAffichage ( int largeur,
			     int hauteur, char *nomFichier );
void libererAffichage ( Ecran ecran );
void afficherImage ( Ecran ecran, Image *pIm );
void changerLigne ( Ecran ecran, Image *pIm, int y );
void changerBloc ( Ecran ecran, Image *pIm, int y, int h );

#endif
