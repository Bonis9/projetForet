#include <stdio.h>
#include <stdlib.h>
#include "includes/modification.h"


int modifierElement(forestCell** forest) {
    int a, b, c;
    printf("Pour personnaliser un element de la foret, il vous faut saisir ses coordonnees.\n");
    printf("Numero de LIGNE de l'element a modifier : "); scanf("%d", &a);
    printf("Numero de COLONNE de l'element a modifier : "); scanf("%d", &b);

    printf("Element [%d][%d] selectionne\n\n", a,b);
    printf("Que souhaitez-vous modifier ?\n");
    printf("Tapez '1' pour le type.\n");
    printf("Tapez '2' pour le degree.\n");
    printf("Tapez '3' pour le l'etat.\n");
    printf("Votre choix : ");scanf("%d", &c);

    switch(c) {
        case 1:
        modifierType(a, b, forest);
        break;

        case 2:
        modifierDegree(a, b, forest);
        break;

        case 3:
        modifierEtat(a, b, forest);
        break;
    }
    return 7;
}

void modifierType(int i, int j, forestCell** forest) {
	char *tab[6]={"43.sol","42.arbre","32.feuille","35.roche","120.herbe","47.eau"};
    int qq = 0;
    int choix;
    printf("Un numero est associe pour chaque type disponible.\n\n");
    printf("Pour changer le type d'un element, il suffit d'ecrire son numero.\n");
    for (qq = 0; qq < 6; qq++)
    {
        int nb_de_fois, nb, l = 0;
        printf("%s ", tab[qq]);
    }printf("\n");

    printf("Faites votre choix : ");scanf("%d", &choix);
    modificateur(1, i, j, choix, forest);
}

void modifierDegree(int i, int j, forestCell** forest)
{
	int choix;
	printf("Ecrivez le nombre de degres : ");scanf("%d", &choix);
    modificateur(2, i, j, choix, forest);
}
void modifierEtat(int i, int j, forestCell** forest)
{
	int choix;
	printf("Choisissez un etat (0 ou 1) : ");scanf("%d", &choix);
    modificateur(3, i, j, choix, forest);
}

void modificateur(int a, int coorA, int coorB, int choix, forestCell** forest)
{
	switch(a)
	{
		case 1:
		forest[coorA][coorB].type = choix;
		break;

		case 2:
		forest[coorA][coorB].degree = choix;
		break;

		case 3:
		forest[coorA][coorB].state = choix;
		break;
	}
}