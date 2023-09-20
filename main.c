#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

//-----------------------Elements du tableau-------------------------------
typedef struct forestCell
{
	int forestType;
	unsigned short int degree;
	unsigned short int state;
} forestCell;

//-------------------------Initialisation foret----------------------------
forestCell** forest = NULL;

//------Menu Demarrer-------
void menuDemarrer(int *m, int *n)
{
	printf("Choisir la longueur de la foret (Min 5, Max 40) : ");
	scanf("%d", m);	
	printf("Choisir la largeur de  la foret (Min 5, Max 40) : ");
	scanf("%d", n);
}

//----------------Choix de du remplissage de la foret-----------------------
unsigned char fillingChoice()
{
	printf("\nSouhaitez-vous remplir la foret mannuellement?\nTapez 'O' pour Oui et 'N' pour Non : ");
	unsigned char choice;
	do 
	{
		scanf("%c", &choice);
	}while(choice != 'O' && choice != 'N' && choice != 'o' && choice != 'n');

	return choice;
}

//-------------------------Conversion Num-ASCII-----------------------------
void autoFilling(int m, int n)
{
	int asciiType;
	srand(time(NULL));

	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			asciiType = 1 + rand()%6;
			switch(asciiType)
			{
				case 1:
					forest[i][j].forestType = 32;
					break;
				case 2:
					forest[i][j].forestType = 35;
					break;
				case 3:
					forest[i][j].forestType = 42;
					break;
				case 4:
					forest[i][j].forestType = 43;
					break;
				case 5:
					forest[i][j].forestType = 47;
					break;
				case 6:
					forest[i][j].forestType = 120;
					break;
			}
			usleep(490);
		}
	}
}

//-----------------------Affichage de la foret-----------------------------
void displayForest(int m, int n)
{
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			printf("%c ", forest[i][j].forestType);
		}
		printf("\n");
	}
		
}



int main(void)
{
	int m,n;
	menuDemarrer(&m, &n);

	//--------------------------Création de la foret-----------------------
	forest = (forestCell **)calloc(m, sizeof(forestCell*));//Creation de la partie x du double tableau et init toutes les cas à 0
	
	//-------------Création de la partie y du double tableau----------------
	for(int i=0; i<m; ++i)
	{	
		forest[i] = (forestCell*)calloc(n, sizeof(forestCell));
	}
	int pdm = 5;
	unsigned char fillingChoosed = fillingChoice();

	if(fillingChoosed == 'N' || fillingChoosed == 'n')
	{
		autoFilling(m, n);
	}
	
	//---------------------------------------------------------------------
	displayForest(m, n);
	return 0;
}