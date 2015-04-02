#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "image.h"
#include "affichage.h"
#include "tab2Ddynamique.h"
#include "testReconnaissance_v2.h"




/*La fonction qui va comparer l'image à la lettre BanqueDeDonnees est 
un tableau à deux dimensions de 16 lignes 
(les 16 proportions des lettres de l'unicode) et de 26 colonnes
pour le moment (les 26 lettre de l'alphabet tirées de l'unicode.) */

void comparaison(Image imSource, int banqueDeDonnees[NB_DECOUP][NB_LETTRES],char banqueDeDonneeAsso[NB_LETTRES], Ecran ecran)
{
  int tabProp[NB_DECOUP];
  Image tabImages[NB_DECOUP];
  int i=0;
  char lettre;

  decoupageCadre(imSource, tabImages);
	  
  for(i=0;i<=NB_DECOUP-1;i++)
    {
      tabProp[i]=trouverProportion(tabImages[i]);
    }

  lettre=trouverLettre(tabProp,banqueDeDonnees,banqueDeDonneeAsso,imSource,ecran);
  printf("%c",lettre);
}


//La fontion qui va découper le cadre de l'image en 16

void decoupageCadre(Image imLettre,Image tabImages[NB_DECOUP])
{
  int j=0;
  int i=0;
  // Initialisation des Images
  for (i=0;i<=NB_DECOUP-1;i++)
    {
      tabImages[i].nbLines = (imLettre.nbLines)/4;					// Il reste à gérer le cas ou nbLines n'est pas divisible par 4.
      tabImages[i].nbColumns = (imLettre.nbColumns)/4;
    }
  for (j=0;j<=NB_DECOUP-1;j++)
    {
      remplirCadre(tabImages, tabImages[j], j, imLettre);
    }
}
		
// Remplissage des Images de tabImages
void remplirCadre(Image tabImages[NB_DECOUP], Image imSecante , int cadre, Image imLettre)	
{
  int temp1 =0;
  int temp2=0;
  int i=0;
  int j=0;
		
  if (cadre <= 3 )													// Les temp1  et temp2 vont permettre de situer imSecante dans imLettre.
    {
      temp1 = imSecante.nbColumns;
      for (i=0;i<= imSecante.nbLines-1; i++)
	{
	  for (j=0; j<= imSecante.nbColumns-1;j++)					
	    {
	      **(imSecante.t2D[i][j])= imLettre->t2D[i][temp1 + j];
	    }
						
	}
    }
  if ((3 < cadre) && (cadre <= 7) )												// On réitère pour la deuxième ligne d'images coupées dans imLettre
    {
      temp1 = (cadre - 4)*imSecante.nbColumns;
      temp2 = imSecante.nbLines;
      for (i=0;i<= imSecante.nbLines-1; i++)
	{
	  for (j=0; j<= imSecante.nbColumns-1;j++)					
	    {
	      imSecante->t2D[i][j]=imLettre->t2D[temp2 + i][temp1 + j];
	    }
						
	}
    }
		
  if ((7 < cadre) && (cadre <= 11) )												// On réitère pour la troisième ligne d'images coupées dans imLettre
    {
      temp1 = (cadre - 8)*imSecante.nbColumns;
      temp2 = 2*imSecante.nbLines;
      for (i=0;i<= imSecante.nbLines-1; i++)
	{
	  for (j=0; j<= imSecante.nbColumns-1;j++)					
	    {
	      imSecante->t2D[i][j]=imLettre->t2D[temp2 + i][temp1 + j];
	    }
						
	}
    }
  if ((11 < cadre) && (cadre <= 15) )												// On réitère pour la dernière ligne d'images coupées dans imLettre
    {
      temp1 = (cadre - 12)*imSecante.nbColumns;
      temp2 = 3*imSecante.nbLines;
      for (i=0;i<= imSecante.nbLines-1; i++)
	{
	  for (j=0; j<= imSecante.nbColumns-1;j++)					
	    {
	      imSecante->t2D[i][j]=imLettre->t2D[temp2 + i][temp1 + j];
	    }
						
	}
    }
}

//La fonction qui va trouver les proportions de pixels noir (=<150) dans les découpages précédents
int trouverProportion(Image petitCarre)
{
  int i=0;
  int j=0;
  int pNoirs=0;

  for(i=0;i<petitCarre.nbLines;i++)
    {	
      for(j=0;j<petitCarre.nbColumns;j++)
	{
	  if(**(petitCarre.t2D[i][j])<=150)
	    {
	      pNoirs++;
	    }
	}	
    }
	  
  return(pNoirs/(petitCarre.nbLines * petitCarre.nbColumns));
}

char trouverLettre(int tabProp[NB_DECOUP],int bDD[NB_DECOUP][NB_LETTRES], char bDDAssos[NB_LETTRES], Image imLettre, Ecran ecran)
{
  int prop=0;
  int lettre=0;
  int ecartMinimal;
  int ecartActuel;
  int lettreProche[NB_DECOUP];
  int caractere;
  initTab(lettreProche,NB_DECOUP,0);
  for(prop=0;prop<NB_DECOUP;prop++)
    {
      ecartMinimal = fabs(tabProp[prop]-bDD[prop][0]);
      for(lettre=1;lettre<=NB_LETTRES;lettre++)
	{
	  ecartActuel= fabs(tabProp[prop]-bDD[prop][lettre]);
	  if(ecartActuel < ecartMinimal)
	    {
	      ecartMinimal = ecartActuel;
	      lettreProche[prop]=lettre;
	    }
	  else if (ecartActuel==ecartMinimal)
	    {
	      lettreProche[prop]= lettreProche[prop]*29 + lettre ; // En utilisant *1000 on risque un dépassement de mémoire 
	    }
	}
    }

  caractere = choixLettre(lettreProche, bDD, bDDAssos, imLettre, ecran); // Va donner la colonne de bDD correspondant à la bonnne lettre.
  return bDDAssos[caractere];
}





int choixLettre (int tab[], int bDD[NB_DECOUP][NB_LETTRES], char bDDAssos[NB_LETTRES], Image imLettre, Ecran ecran)
{
  //----------------------------------------------
  int compteur[NB_LETTRES];
  int max=0;
  int choix;
  //----------------------------------------------

  //----------------------------------------------
  initTab(compteur,NB_LETTRES,0);
  //----------------------------------------------

  //----------------------------------------------
  correspondances(tab,compteur);
  //-----------------------------------------------

  //-----------------------------------------------
  maxTab(compteur,NB_LETTRES,&max,&choix);
  //-----------------------------------------------

  //-----------------------------------------------
  //Ajouter la fonction qui, en cas de plusieurs correspondances maximales demande à l'utilisateur de choisir entre celles-ci (c'est là qu'on utilise bDDAssos et imLettre).

  if(choix!=1)
    {
      return(choixFinal(compteur, max, ecran, imLettre, bDDAssos));
    }
  else
    {
      return(max);
    }
}



void initTab(int tab[],int borne, int valeur)
{
  int i=0;
  for(i=0;i<borne;i++)
    {      
      tab[i]=valeur;
    }
}


void correspondances(int tab[], int compteur[])
{
  int i=0;
  int a=0;
  int b=0;
  int j=0;

  for (i=0;i<NB_LETTRES;i++)
    {
      a=tab[i];
      while(a!=0)
	{
	  b=a%29;
	  a=(a-b)/29;
	  b--;
	  for(j=0;j<NB_LETTRES;j++)
	    {
	      if(b==j)
		{
		  compteur[j]++;
		}
	    }
	}
    }
}


void maxTab(int tab[], int borne, int *max, int *choix)
{
  int i=0;
  *choix=1;
  *max=tab[0];
  for(i=1;i<borne;i++)
    {
      if(*max<tab[i])
	{
	  *max=tab[i];
	  *choix=1;
	}
      else if(*max==tab[i])
	{
	  *max=tab[i];
	  *choix=choix+1;
	}
    }
}

int choixFinal(int compteur[], int max, Ecran ecran, Image imSource, char bDDAssos[NB_LETTRES]){
  int i=0;
  int j=0;
  int casMultiple[NB_LETTRES];
  int a;
  char uChoix;
  for(j=0;j<NB_LETTRES;j++)
    {
      if((compteur[j])==max)
	{
	  casMultiple[i]=j;
	  i++;
	}
    }
  casMultiple[i]=666;
  printf("Oups, nous n'avons pas trouvé quelle est cette lettre :");
  afficherImage(ecran,&imSource);
  printf("laquelle est-ce ?");
  j=0;
  while(casMultiple[j]!=666);
  {
    a=casMultiple[j];
    printf("%c \n",bDDAssos[a]);
    a++;
  }
  scanf("%c",&uChoix);
  for(i=0;i<NB_LETTRES;i++)
    {
      if(bDDAssos[i]==uChoix)
	{
	  return(i);
	}
    }
}
