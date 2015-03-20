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
  int tabProp[26];
  Image tabImages[26];
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

char trouverLettre(int tabProp[],int bDD[][], char bDDAssos[])
{
  int prop=0;
  int lettre=0;
  int ecartMinimal;
  int ecartActuel;
  int lettreProche[26];
  int caractere;
  for(prop=0;prop<26;prop++)
    {
      lettreProche[prop]= 0;
    }
  for(prop=0;prop<26;prop++)
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
	      lettreProche[prop]= lettreProche[prop]*27 + lettre ; // En utilisant *1000 on risque un dépassement de mémoire 
	    }
	}
    }

  caractere = choixLettre(lettreProche, bDD[][], bDDAssos[]); // Va donner la colonne de bDD correspondant à la bonnne lettre.
  return bDDAssos[caractere];
}

int choixLettre (int tab[], int bDD[][], char bDDAssos[])
{
  //----------------------------------------------
  //Certaines de ces variables seront incorporées dans les fonctions plus tard
  int compteur[26];
  int i=0;
  int j=0;
  int a=0;
  int b=0;
  int m=0;
  //----------------------------------------------

  //----------------------------------------------
  //Fonction initTab
  for(j=0;j<26;j++)
    {      
      compteur[j]=0;
    }
  //----------------------------------------------

  //----------------------------------------------
  //Ici il faut mettre une fonction pour compter les correspondances
  for (i=0;i<26;i++)
    {
      a=tab[i];
      while(a!=0)
	{
	  b=a%27;
	  a=(a-b)/27;
	  b--;
	  for(j=0;j<26;j++)
	    {
	      if(b==j)
		{
		  compteur[j]++;
		}
	    }
	}
    }
  //-----------------------------------------------

  //-----------------------------------------------
  //Ici il faut mettre une fonction maxTab
  m=compteur[0];
  for(j=1;j<26;j++)
    {
      if(m<compteur[j])
	{
	  m=compteur[j];
	}
    }
  //-----------------------------------------------
}
