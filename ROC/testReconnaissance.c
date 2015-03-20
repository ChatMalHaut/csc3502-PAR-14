#include <stdlib>
#include <stdio>
#include <maths.h>

//

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
  lisserImage ( cote, imSource, &imDest, ecran );
  sleep ( 3 );
  printf ( "\nEcriture fichier...\n" );
  ecrireImage ( imDest, argv[2] );
  libererAffichage ( ecran );

  // desallocation memoire
  imSource.t2D = desallouer ( imSource.t2D );
  imDest.t2D=desallouer ( imDest.t2D );
  return EXIT_SUCCESS;
}

//La fonction qui va comparer l'image à la lettre
void comparaison(Image imSource, int banqueDeDonnees[][])
{
  int tabProp[16];
  Image tabImages[16];
  int i=0;
  char lettre;

  decoupageCadre(imSource, tabImages);
  
  for(i=0;i<=15;i++)
    {
      tabProp[i]=trouverProportion(tabImage[i]);
    }

  lettre=trouverLettre(tabProp,banqueDeDonnees);
  printf("%c",&lettre);
}


//La fontion qui va découper le cadre de l'image en 16
void decoupageCadre(Image cadre,Image tabImages[])
{
  
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
	  if(petitCarre.Pixel[i][j]<=150)
	    {
	      pNoirs++;
	    }
	}
    }
  
  return(pNoirs/(petitCarre.nbLines * petitCarre.nbColumns));
}

char trouverLettre(int tabProp[],int bDD[][], int bDDAssos[])
{
  int prop=0;
  int lettre=0;
  int ecartMinimal;
  int ecartActuel;
  int lettreProche[16];
  int caractere;
  for(prop=0;prop<=15;prop++)
    {
      lettreProche[prop]= 0;
  }
  for(prop=0;prop<16;prop++)
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
	  else if (ecartActuel=ecartMinimal)
	    {
	      lettreProche[prop]= lettreProche[prop]*27 + lettre ;
	    }
	}
    }

  caractere = choixLettre(lettreProche);
  return bDD[caractere];
}

int choixLettre (int tab[])
{
  int compteur=0;
  
  for(i=0;i<26;i++)
    {
      while(a!=0)
	{
	  a=tab[i];
	}
    }
}
