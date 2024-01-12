#include <stdio.h>
#include <stdlib.h>
#include "includes/dimForet.h"

void forestSize(dimensionForet *dimForet) {
	printf("Choisir la largeur de la foret (Minimum 5) : ");
    scanf("%d", &dimForet->m);

    printf("Choisir la longeur de  la foret (Minimum 5) : ");
    scanf("%d", &dimForet->n);
}
