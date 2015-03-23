#ifndef _TESTRECONNAISSANCEV2_H
#define _TESTRECONNAISSANCEV2_H 1

#include NB_LETTRES 26;

void comparaison(Image imSource, int banqueDeDonnees[][],char banqueDeDonneeAsso, Ecran ecran);
void decoupageCadre(Image imLettre,Image tabImages[], int cote);
void remplirCadre(Image tabImages[], Image imSecante , int cadre, Image imLettre);
int trouverProportion(Image petitCarre);
void initTab(int tab[],int borne, int valeur);
void correspondances(int tab[], int compteur[]);
void maxTab(int tab[], int borne, int *max, int *nb)
int choixFinal(int compteur, int max, Ecran ecran, Image imSource, int bDDAssos[])
int choixLettre (int tab[], int bDD[][], char bDDAssos[], Image imLettre);
char trouverLettre(int tabProp[],int bDD[][], char bDDAssos[], Image imLettre,Ecran ecran);

#endif
