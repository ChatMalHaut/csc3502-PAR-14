#ifndef _TAB2D_DYNAMIQUE_H
#define _TAB2D_DYNAMIQUE_H 1

/* Module de gestion d'un tableau dynamique 2D nbLignes x nbColonnes 
   de pixels codes sur un octet ( 256 niveaux de gris ) */

#include "image.h"

  // Declaration des fonctions allouer et desallouer

Pixel **allouer ( int nbLignes, int nbColonnes );
Pixel **desallouer ( Pixel **t2D );

#endif