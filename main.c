#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "includes/foret.h"
#include "includes/dimForet.h"
#include "includes/incendie.h"
#include "includes/modification.h"


int main(void)
{
    int recup;
    unsigned char fillingChoosed;
    int c;

    dimensionForet dimForet;
    VERIF verif; //NEW
    COORDINATES coor; //NEW
    TEMP temp;

    Menu();

    //---Choisir la taille de la forêt 
    forestSize(&dimForet);

    //Initialisation foret
    forestCell** forest = forestCreation(&dimForet);

    printf("\nVous aurez %d elements dans votre foret\n", dimForet.m*dimForet.n);
    if(dimForet.m*dimForet.n >=20)
    {   
        printf("\n**********************************************************\n");
        printf("*    Ceci represente un nombre important d'elements.     *\n");
        printf("* Il est conseille de choisir le remplissage automatique.*\n");
        printf("**********************************************************\n");
    }
    //Choix d'un remplissage automatique ou manuel
    fillingChoosed = fillingChoice();
    
    //Remplissage de la forêt en fonction du choix
    if(fillingChoosed == 'N' || fillingChoosed == 'n')
    {
        autoFilling(&dimForet, forest);
    }
    if(fillingChoosed == 'O' || fillingChoosed == 'o')
    {
        manualFilling(&dimForet, forest);
    }

    printf("Choisir la LIGNE du depart du feu : ");
    scanf("%d", &coor.i);
    printf("Choisir la COLONNE du depart du feu : ");
    scanf("%d", &coor.j);
    
    elementsStates(&dimForet, forest);

    //Met en feu le point de départ
    miseEnFeu(coor.j, coor.j,forest);
    afficherForet(&dimForet, forest, 0);

    //Initialisation des variables de contrôle
    initVerifVar(&verif);
    initTempVar(&temp);


    while (1) 
    {
        c = getch(); 

        if(c != 113)
        {
            if(c == 100) 
            {
                if(verif.ctr == 0) 
                {
                    storedForPropa(coor.i, coor.j, &verif, &temp);
                }
                //Propagation du feu
                propagation(&coor.j, &coor.j, &dimForet, &verif, &temp, forest);
            }
            if(c == 103)
            {
                recup = modifierElement(forest);
                printf("Faites 'd' pour revenir a l'it%cration\n", 130);
            }
        }
        else 
        {
            break;
        }

    }
    printf("Incendie termin%c\n", 130);
    
    return 0;
}