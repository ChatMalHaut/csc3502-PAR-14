#ifndef _TESTRECONNAISSANCEV2_H
#define _TESTRECONNAISSANCEV2_H 1

#define NB_LETTRES 26
#define NB_DECOUP 16


void comparaison(Image imSource, int banqueDeDonnees[NB_DECOUP][NB_LETTRES],char banqueDeDonneeAsso[NB_LETTRES], Ecran ecran);
void decoupageCadre(Image imLettre,Image tabImages[NB_DECOUP], int cote);
void remplirCadre(Image tabImages[NB_DECOUP], Image imSecante , int cadre, Image imLettre);
int trouverProportion(Image petitCarre);
void initTab(int tab[],int borne, int valeur);
void correspondances(int tab[], int compteur[]);
void maxTab(int tab[], int borne, int *max, int *nb);
int choixFinal(int compteur, int max, Ecran ecran, Image imSource, int bDDAssos[]);
int choixLettre (int tab[], int bDD[NB_DECOUP][NB_LETTRES], char bDDAssos[NB_LETTRES], Image imLettre);
char trouverLettre(int tabProp[],int bDD[NB_DECOUP][NB_LETTRES], char bDDAssos[NB_LETTRES], Image imLettre,Ecran ecran);

#endif
