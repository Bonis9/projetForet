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
            printf("[%c] ", forest[i][j].forestType);
        }
        printf("\n");
    }
        
}
//La fonction demande combien de fois un élément doit être ajouté, puis elle procède à l'ajout. À la fin, toutes les cases non sélectionnées seront automatiquement transformées en feuilles.
void Filling(int m, int n)
{
    int foret[m][n];
    int combien=0;
    // Remplir la matrice de selection avec des valeurs croissantes
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            foret[i][j]=combien;
            combien++;
        }
    }
    // Tableau de chaînes de caractères représentant les éléments de la forêt
    char *tab[8]={"sol","arbre","feuille","roche","herbe","eau","cendres","cendres éteintes"};
    
    for (int i = 0; i < 8; i++)
    {
        int nb_de_fois,nb;
        printf("Combien de cet élément souhaitez-vous : %s\n", tab[i]);        
        scanf("%d",&nb_de_fois);
        for (int j = 0; j < nb_de_fois; j++)
        {
            for(int i=0; i<m; i++)
            {
                for(int j=0; j<n; j++)
                {
                    printf("[%d]", foret[i][j]);
                }
                printf("\n");
            }
            
            printf("Choisissez votre case : ");
            scanf("%d", &nb);
            printf("Vous avez choisi la case numéro [%d]\n", nb);
            for(int k=0; k<m; k++)
            {
                for(int j=0; j<n; j++)
                {
                    if( foret[k][j] == nb)
                    {
                        switch(i+1)
                        {
                            case 1:
                                forest[k][j].forestType = '+';
                                break;
                            case 2:
                                forest[k][j].forestType = '*';
                                break;
                            case 3:
                                forest[k][j].forestType = ' ';
                                break;
                            case 4:
                                forest[k][j].forestType = '#';
                                break;
                            case 5:
                                forest[k][j].forestType = 'x';
                                break;
                            case 6:
                                forest[k][j].forestType = '/';
                                break;
                            case 7:
                                forest[k][j].forestType = '-';
                                break;
                            case 8:
                                forest[k][j].forestType = '@';
                                break;
                            
                        }
                        displayForest(m,n);
                    }
                }
            }
            
        }
        
    }
      for(int k=0; k<m; k++)
            {
                for(int j=0; j<n; j++)
                {
                    if(forest[k][j].forestType == '\0')
                    {
                      forest[k][j].forestType = ' ';
                    }
                }
            }
           
    printf("La forêt finale ressemble à ceci :\n");
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
    unsigned char fillingChoosed = fillingChoice();

    if(fillingChoosed == 'N' || fillingChoosed == 'n')
    {
        autoFilling(m, n);
    }
    if(fillingChoosed == 'O' || fillingChoosed == 'o')
    {
        Filling(m,n);
    }
    //---------------------------------------------------------------------
    displayForest(m, n);
    return 0;
}