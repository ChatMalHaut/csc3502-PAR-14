	#include <stdlib>
	#include <stdio>
	#include <maths.h>

	#define NB_LETTRES 26

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
	  comparaison(imSource,banqueDeDonnees,ecran);
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
void comparaison(Image imSource, int banqueDeDonnees[][],char banqueDeDonneeAsso, Ecran ecran)
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

	  lettre=trouverLettre(tabProp,banqueDeDonnees,banqueDeDonneeAsso,ecran);
	  printf("%c",&lettre);
	}


	//La fontion qui va découper le cadre de l'image en 16

	void decoupageCadre(Image imLettre,Image tabImages[], int cote)
	{
		int j=0;
		int i=0;
		// Initialisation des Images
		for (i=0;i<=15)
		{
			tabImages[i].nbLines = (imLettre.nbLines)/4;					// Il reste à gérer le cas ou nbLines n'est pas divisible par 4.
			tabImages[i].nbColumns = (imLettre.nbColumnsl)/4;
		}
		for (j=0;j<=15;j++)
		{
			remplirCadre(tabImages, tabImages[j], j, imLettre);
		}
	}
		
		// Remplissage des Images de tabImages
	void remplirCadre(Image tabImages[], Image imSecante , int cadre, Image imLettre)	
	{
		int temp1 =0;
		int temp2=0;
		
		if (cadre <= 3 )													// Les temp1  et temp2 vont permettre de situer imSecante dans imLettre.
		{
			temp1 = imSecante.nbColumns;
			for (i=0;i<= imSecante.nbLines-1; i++)
				{
					for (j=0; j<= imSecante.nbColumns-1;j++)					
					{
						imSecante->t2D[i][j]= imLettre->t2D[i][temp1 + j];
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
		  if(petitCarre.Pixel[i][j]<=150)
			{
			  pNoirs++;
			}
			}	
		}
	  
	  return(pNoirs/(petitCarre.nbLines * petitCarre.nbColumns));
	}

char trouverLettre(int tabProp[],int bDD[][], char bDDAssos[], Image imLettre,Ecran ecran)
	{
	  int prop=0;
	  int lettre=0;
	  int ecartMinimal;
	  int ecartActuel;
	  int lettreProche[16];
	  int caractere;
	  for(prop=0;prop<16;prop++)
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
			  lettreProche[prop]= lettreProche[prop]*29 + lettre ; // En utilisant *1000 on risque un dépassement de mémoire 
			}
		}
		}

	  caractere = choixLettre(lettreProche, bDD[][], bDDAssos[], imLettre); // Va donner la colonne de bDD correspondant à la bonnne lettre.
	  return bDDAssos[caractere];
	}





	int choixLettre (int tab[], int bDD[][], char bDDAssos[], Image imLettre)
	{
	  //----------------------------------------------
	  //Certaines de ces variables seront incorporées dans les fonctions plus tard
	  int compteur[NB_LETTRES];
	  int casMultiple[NB_LETTRES];
	  int i=0;
	  int j=0;
	  int a=0;
	  int b=0;
	  int max=0;
	  int choix;
	  //----------------------------------------------

	  //----------------------------------------------
	  //Fonction initTab
	  for(j=0;j<NB_LETTRES;j++)
		{      
		  compteur[j]=0;
		}
	  //----------------------------------------------

	  //----------------------------------------------
	  //Ici il faut mettre une fonction pour compter les correspondances
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
	  //-----------------------------------------------

	  //-----------------------------------------------
	  //Ici il faut mettre une fonction maxTab
	  max=compteur[0];
	  choix=1;
	  for(j=1;j<NB_LETTRES;j++)
		{
		  if(max<compteur[j])
		    {
		      max=compteur[j];
		      choix=1;
		    }
		  else if(max=compteur[j])
		    {
		      max=compteur[j];
		      choix++;
		    }
		}
	  //-----------------------------------------------

	  //-----------------------------------------------
	  //Ajouter la fonction qui, en cas de plusieurs correspondances maximales demande à l'utilisateur de choisir entre celles-ci (c'est là qu'on utilise bDDAssos et imLettre).

	  if(choix!=1)
	    {
	      i=0;
	      for(j=0;j<NB_LETTRES;j++)
		{
		  if(compteur[j]==max)
		    {
		      casMutliple[i]=j;
		      i++;
		    }
		}
	      casMultiple[i]=666;
              printf("Oups, nous n'avons pas trouvé quelle est cette lettre :");
	      afficherImage(ecran,&imLettre);
	      printf("laquelle est-ce ?");
	      j=0;
	      while(casMultiple[j]!=666);
	      {
		a=casMultiple[j];
		printf("%c \n",bDDAssos[a]);
		a++;
	      }
	      char uChoix;
	      scanf("%c",&uChoix);
	      for(i=0;i<NB_LETTRES;i++)
		{
		  if(bDDAssos[i]==uChoix)
		    {
		      return(i);
		    }
		}
      
	    }
	  else
	    {
	      return(max);
	    }
	    
	  //-----------------------------------------------
	}
