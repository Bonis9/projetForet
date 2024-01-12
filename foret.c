#include <stdio.h>
#include <stdlib.h>
#include "includes/foret.h"
#include "includes/dimForet.h"
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <conio.h>

void afficherConsigne()
{
    printf("\n____________________________________\n");
    printf("|'q' : Pour quitter la simulation  |\n");
    printf("|'d' : Pour faire une iteration    |\n");
    printf("|'g' : Modifier une case           |\n");
    printf("\n\n");
}
forestCell** forestCreation(dimensionForet *dimForet)
{
    forestCell** forest1 = (forestCell **)calloc(dimForet->m, sizeof(forestCell*));

    if (forest1 == NULL)
    {
        fprintf(stderr,"Erreur d'allocation de la foret\n");
        exit(1);
    }
    
    //-------------Création de la partie n du double tableau----------------
    for(int i=0; i<dimForet->m; ++i)
    {   
        forest1[i] = (forestCell*)calloc(dimForet->n, sizeof(forestCell));
        if (forest1[i] == NULL) 
        {
            fprintf(stderr,"Erreur d'allocation de la foret\n");
            exit(1);
        }
    }
    return forest1;
}



void Menu()
{
    printf("\n");
    printf(" ***************************************************\n");
    printf(" *\tBienvenue a la simulation d'incendie !\t   *\n");
    printf(" ***************************************************\n");
    printf("\n");
}
void afficherForet(dimensionForet *dimForet, forestCell** forest, int itr)
{
    system("cls");
    Menu();

    //Affiche les chiffres sur les côtés
    for(int k=0; k<dimForet->n; k++)
    {   
        if(k==0)
        {
            printf("    ");
        }
        if(k >= 10)
        {
            printf("[%d]", k);
        }
        if(k < 9)
        {   
            printf("[%d]|",k);
        }
        if(k == 9)
        {   
            printf("[%d] ",k);
        }
        if(k == dimForet->n-1)
        {   
            printf("\n");
        }
    }
    

    for(int i=0; i<dimForet->m; i++)
    {   
        if(i<10){printf(" [%d] ",i);}
        else{printf("[%d] ",i);}

        for(int j=0; j<dimForet->n; j++)
        {
            printf(" %c  ", forest[i][j].type);
        }

        if(i<10){printf(" [%d] ",i);}
        else {printf("[%d] ",i);}
        printf("\n");
    }
    
    //Affiche les chiffres sur les côtés
    for(int k=0; k<dimForet->n; k++)
    {   
        if(k==0)
        {
            printf("    ");
        }
        if(k >= 10)
        {
            printf("[%d]", k);
        }
        if(k < 9)
        {   
            printf("[%d]|",k);
        }
        if(k == 9)
        {   
            printf("[%d] ",k);
        }
        if(k == dimForet->n-1)
        {   
            printf("\n");
        }
    }

    printf("\n");
    printf("Vous etes a l'iteration %d.\n", itr);
    afficherConsigne();
    usleep(250000);
}


unsigned char fillingChoice()
{
    unsigned char choice;
    printf("\nSouhaitez-vous remplir la foret mannuellement?\nTapez 'O' pour Oui et 'N' pour Non : ");
    
    do 
    {
        scanf("%c", &choice);
    }while(choice != 'O' && choice != 'N' && choice != 'o' && choice != 'n');

    return choice;
}


void autoFilling(dimensionForet *dimForet, forestCell** forest)
{
    int asciiType;
    srand(time(NULL));

    for(int i=0; i<dimForet->m; i++)
    {
        for(int j=0; j<dimForet->n; j++)
        {
            asciiType = 1 + rand()%6;
            switch(asciiType)
            {
                case 4:
                    forest[i][j].type = 43; //SOL
                    break;
                case 3:
                    forest[i][j].type = 42; //ARBRE
                    break;
                case 1:
                    forest[i][j].type = 32; //FEUILLE
                    break;
                case 2:
                    forest[i][j].type = 35; //ROCHE
                    break;
                case 6:
                    forest[i][j].type = 120; //HERBE
                    break;
                case 5:
                    forest[i][j].type = 47; //EAU
                    break;
            }
        }
    }
    afficherForet(dimForet, forest, 0);
}


//La fonction demande combien de fois un élément doit être ajouté, puis elle procède à l'ajout. À la fin, toutes les cases non sélectionnées seront automatiquement transformées en feuilles.
void manualFilling(dimensionForet *dimForet, forestCell** forest)
{
    int foret[dimForet->m][dimForet->n];
    int combien=1; 

    for(int i=0; i<dimForet->m; i++) // Remplir la matrice de selection avec des valeurs croissantes
    {
        for(int j=0; j<dimForet->n; j++)
        {
            foret[i][j]=combien;
            combien++;
        }
    }
    
    char *tab[8]={"sol","arbre","feuille","roche","herbe","eau"}; // Tableau de chaînes de caractères représentant les éléments de la forêt
    
    for (int i = 0; i < 8; i++)
    {
        int nb_de_fois, nb, l = 0;
        printf("Entrez le nombre de %s que vous souhaitez : ", tab[i]);        
        scanf("%d",&nb_de_fois);
        for (int j = 0; j < nb_de_fois; j++)
        {
            for(int i=0; i<dimForet->m; i++)
            {

                for(int j=0; j<dimForet->n; j++)
                {
                    if (foret[i][j] == nb)
                    {
                        printf("\t", foret[i][j]);
                    }
                    else
                    printf("[%d]\t", foret[i][j]);
                }
                printf("\n");
            }
            
            printf("Choisissez votre case : ");
            scanf("%d", &nb);
            printf("Vous avez choisi la case numero [%d]\n", nb);
            for(int k=0; k<dimForet->m; k++)
            {
                for(int j=0; j<dimForet->n; j++)
                {
                    if( foret[k][j] == nb)
                    {
                        switch(i+1)
                        {
                            case 1:
                                forest[k][j].type = 43; //SOL
                                break;
                            case 2:
                                forest[k][j].type = 42; //ARBRE
                                break;
                            case 3:
                                forest[k][j].type = 32; //FEUILLE
                                break;
                            case 4:
                                forest[k][j].type = 35;//ROCHE
                                break;
                            case 5:
                                forest[k][j].type = 120;//HERBE
                                break;
                            case 6:
                                forest[k][j].type = 47;//EAU
                                break;
                        }
                       afficherForet(dimForet, forest, 0);
                    }
                }
            }
            
        }
        
    }
      for(int k=0; k<dimForet->m; k++)
            {
                for(int j=0; j<dimForet->n; j++)
                {
                    if(forest[k][j].type == '\0')
                    {
                      forest[k][j].type = 32;
                    }
                }
            }
    printf("La foret finale ressemble a ceci :\n");
    afficherForet(dimForet, forest, 0);
}


void elementsStates(dimensionForet *dimForet, forestCell** forest)
{
    for(int i=0; i<dimForet->m; i++)
    {
        for(int j=0; j<dimForet->n; j++)
        {
            switch(forest[i][j].type)
            {
                case 43: //SOL
                    forest[i][j].degree = 0;
                    forest[i][j].state = 0;
                    break;
                case 42: //ARBRE
                    forest[i][j].degree = 4;
                    forest[i][j].state = 0;
                    break;
                case 32: //FEUILLE
                    forest[i][j].degree = 2;
                    forest[i][j].state = 0;
                    break;
                case 35: //ROCHE
                    forest[i][j].degree = 5;
                    forest[i][j].state = 0;
                    break;
                case 47: //EAU
                    forest[i][j].degree = 0;
                    forest[i][j].state = 0;
                    break;
                case 120: //HERBE
                    forest[i][j].degree = 3;
                    forest[i][j].state = 0;
                    break;
            }
        }
    }
}