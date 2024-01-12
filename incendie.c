#include <stdio.h>
#include <stdlib.h>
#include "includes/incendie.h"

void miseEnFeu(int x, int y, forestCell** forest2)
{
    forest2[x][y].state = 1;
    forest2[x][y].type = 220;
}

void devientCendre(int m, int n, forestCell** forest2)
{
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(forest2[i][j].state == 1)
            {
                forest2[i][j].degree--;
                if(forest2[i][j].degree == 1) //Devient cendres
                {
                    forest2[i][j].type = 45;
                }
                if(forest2[i][j].degree == 0) //Devient cendres
                {
                    forest2[i][j].type = 64;
                }
            }

        }
    }
}

void newVarXYRealloc(int x, int y, VERIF *verif, TEMP *temp)
{
    temp->newVarX = (int *) realloc(temp->newVarX, verif->stateAtOne * sizeof(int));
    temp->newVarY = (int *) realloc(temp->newVarY, verif->stateAtOne * sizeof(int));

    temp->newVarX[verif->stateAtOne-1] = x;
    temp->newVarY[verif->stateAtOne-1] = y;                
}

void propagation(int *x, int *y, dimensionForet *dimForet, VERIF *verif, TEMP *temp, forestCell** forest2)
{

    //Propagation du feu
    if(verif->dataTransmitted == 1)
    {
        //Lancer la propagation pour toutes les valeurs stockées
        verif->stateAtOne = 0;
        
       for(int i=0; i<verif->stateAtOneNumber;i++)
        {
            if(temp->frmTOLX[i]-1 >= 0 && forest2[temp->frmTOLX[i]-1][temp->frmTOLY[i]].type != 43 && forest2[temp->frmTOLX[i]-1][temp->frmTOLY[i]].type != 47 && forest2[temp->frmTOLX[i]-1][temp->frmTOLY[i]].state == 0)
            {   //NORD
                miseEnFeu(temp->frmTOLX[i]-1, temp->frmTOLY[i], forest2);
                verif->stateAtOne++;
                newVarXYRealloc(temp->frmTOLX[i]-1, temp->frmTOLY[i], verif, temp);
            }
            if(temp->frmTOLX[i]-1 >= 0 && temp->frmTOLY[i]+1 < dimForet->n && forest2[temp->frmTOLX[i]-1][temp->frmTOLY[i]+1].type != 43 && forest2[temp->frmTOLX[i]-1][temp->frmTOLY[i]+1].type != 47 && forest2[temp->frmTOLX[i]-1][temp->frmTOLY[i]+1].state == 0) 
            {   //NORD-EST
                miseEnFeu(temp->frmTOLX[i]-1, temp->frmTOLY[i]+1, forest2);
                verif->stateAtOne++;
                newVarXYRealloc(temp->frmTOLX[i]-1, temp->frmTOLY[i]+1, verif, temp);
            }
            if(temp->frmTOLY[i]+1 < dimForet->n && forest2[temp->frmTOLX[i]][temp->frmTOLY[i]+1].type != 43 && forest2[temp->frmTOLX[i]][temp->frmTOLY[i]+1].type != 47 && forest2[temp->frmTOLX[i]][temp->frmTOLY[i]+1].state == 0)
            {   //EST
                miseEnFeu(temp->frmTOLX[i], temp->frmTOLY[i]+1, forest2);
                verif->stateAtOne++;
                newVarXYRealloc(temp->frmTOLX[i], temp->frmTOLY[i]+1, verif, temp);
            }
            if(temp->frmTOLX[i]+1 < dimForet->m && temp->frmTOLY[i]+1 < dimForet->n && forest2[temp->frmTOLX[i]+1][temp->frmTOLY[i]+1].type != 43 && forest2[temp->frmTOLX[i]+1][temp->frmTOLY[i]+1].type != 47 && forest2[temp->frmTOLX[i]+1][temp->frmTOLY[i]+1].state == 0) 
            {   //SUD-EST
                miseEnFeu(temp->frmTOLX[i]+1, temp->frmTOLY[i]+1, forest2);
                verif->stateAtOne++;
                newVarXYRealloc(temp->frmTOLX[i]+1, temp->frmTOLY[i]+1, verif, temp);
            }
            if(temp->frmTOLX[i]+1 < dimForet->m && forest2[temp->frmTOLX[i]+1][temp->frmTOLY[i]].type != 43 && forest2[temp->frmTOLX[i]+1][temp->frmTOLY[i]].type != 47 && forest2[temp->frmTOLX[i]+1][temp->frmTOLY[i]].state == 0)
            {   //SUD
                miseEnFeu(temp->frmTOLX[i]+1, temp->frmTOLY[i], forest2);
                verif->stateAtOne++;
                newVarXYRealloc(temp->frmTOLX[i]+1, temp->frmTOLY[i]+1, verif, temp);
            }
            if(temp->frmTOLX[i]+1 < dimForet->m && temp->frmTOLY[i]-1 >= 0 && forest2[temp->frmTOLX[i]+1][temp->frmTOLY[i]-1].type != 43 && forest2[temp->frmTOLX[i]+1][temp->frmTOLY[i]-1].type != 47 && forest2[temp->frmTOLX[i]+1][temp->frmTOLY[i]-1].state == 0)
            {   //SUD-OUEST
                miseEnFeu(temp->frmTOLX[i]+1, temp->frmTOLY[i]-1, forest2);
                verif->stateAtOne++;
                newVarXYRealloc(temp->frmTOLX[i]+1, temp->frmTOLY[i]-1, verif, temp);
            }
            if(temp->frmTOLY[i]-1 >= 0 && forest2[temp->frmTOLX[i]][temp->frmTOLY[i]-1].type != 43 && forest2[temp->frmTOLX[i]][temp->frmTOLY[i]-1].type != 47 && forest2[temp->frmTOLX[i]][temp->frmTOLY[i]-1].state == 0)
            {   //OUEST
                miseEnFeu(temp->frmTOLX[i], temp->frmTOLY[i]-1, forest2);
                verif->stateAtOne++;
                newVarXYRealloc(temp->frmTOLX[i], temp->frmTOLY[i]-1, verif, temp);
            }
            if(temp->frmTOLY[i]-1 >= 0 && temp->frmTOLX[i]-1 >= 0 && forest2[temp->frmTOLX[i]-1][temp->frmTOLY[i]-1].type != 43 && forest2[temp->frmTOLX[i]-1][temp->frmTOLY[i]-1].type != 47 && forest2[temp->frmTOLX[i]-1][temp->frmTOLY[i]-1].state == 0)
            {
                //NORD-OUEST
                miseEnFeu(temp->frmTOLX[i]-1, temp->frmTOLY[i]-1, forest2);
                verif->stateAtOne++;
                newVarXYRealloc(temp->frmTOLX[i]-1, temp->frmTOLY[i]-1, verif, temp);
            }
        }
        free(temp->frmTOLX); free(temp->frmTOLY);
        //On vérifie si des éléments doivent devenir cendres ou cendres éteintes
        devientCendre(dimForet->m, dimForet->n, forest2);
        verif->propagationDone = 1;
        verif->iterationNumber++;//CHANGER EN ++
        afficherForet(dimForet, forest2, verif->iterationNumber);
        
    }
    //Envoi des données, sinon quitter le programme
    envoiVerstypeOneList(dimForet, forest2, verif, temp);
    
    
}

void envoiVerstypeOneList(dimensionForet *dimForet, forestCell** forest, VERIF *verif, TEMP *temp)
{
    if(verif->propagationDone == 1)
    {
        for(int i=0;i<verif->stateAtOne;i++)
        {
            typeOneList(temp->newVarX[i], temp->newVarY[i], dimForet, verif, temp, forest);
        } 
        free(temp->newVarX); free(temp->newVarY);
    }
}


void typeOneList(int x, int y, dimensionForet *dimForet, VERIF *verif, TEMP *temp, forestCell** forest2)
{    
    if(verif->propagationDone == 1)
    {
        temp->tempX = (int *) calloc(verif->stateAtOne, sizeof(int));
        temp->tempY = (int *) calloc(verif->stateAtOne, sizeof(int));
        if(temp->tempX == NULL || temp->tempY == NULL)
        {
            fprintf(stderr,"Allocation error\n");
            exit(1);
        }
        verif->propagationDone = 0; //(Control variable) Permet d'ordonnancer l'envoie des données Il doit rester à 0 pour permettre la suite sans allocation
    }
    
    //Si ctr vaut le nombre de pt de départ à état 1, on retourne à 0
    if(verif->ctr < verif->stateAtOne-1) //Grâce à ça on ne s'enferme pas dans une boucle for
    {
        temp->tempX[verif->ctr] = x;
        temp->tempY[verif->ctr] = y;
        verif->ctr++;
    }
    else
    {
        temp->tempX[verif->ctr] = x;
        temp->tempY[verif->ctr] = y;
        verif->ctr = 0;
    }

    //Déclencher la boucle après que les tableauXetY soient vide dans propagation()
    if(verif->ctr == 0) //Grâce à ça on ne s'enferme pas dans une boucle for
    {
        verif->allocAuth = 0; //Maintenant que le stockage est terminé, on permet l'allocation mémoire pour les prochains points de départ
        verif->dataTransmitted = 0;
        verif->frmTOLCtr = 0;
        for(int i=0; i<verif->stateAtOne;i++) //Envoie des valeurs stockées à propagation()
        { 
            storedForPropa(temp->tempX[i], temp->tempY[i], verif, temp);       
        }
        free(temp->tempX); free(temp->tempY);
    }
}

void storedForPropa(int x, int y, VERIF *verif, TEMP *temp)
{
        //Stockage des données reçues avec alloc, allocAuth permet de lancer l'allocation une seule fois
        if(verif->allocAuth == 0)
        {
            temp->frmTOLX = (int *) calloc(verif->stateAtOne, sizeof(int));
            temp->frmTOLY = (int *) calloc(verif->stateAtOne, sizeof(int));
            
            if(temp->frmTOLX == NULL || temp->frmTOLY == NULL)
            {
                fprintf(stderr,"Erreur d'allocation\n");
                exit(1);
            }
            verif->stateAtOneNumber = verif->stateAtOne; //Permet de garder la valeur de stateAtOne pour la propagation
            verif->allocAuth = 1; //L'allocation ne se lance qu'une fois
        }

        if(verif->frmTOLCtr < verif->stateAtOne-1)
        {
            temp->frmTOLX[verif->frmTOLCtr] = x;
            temp->frmTOLY[verif->frmTOLCtr] = y;
            verif->frmTOLCtr++;
        }
        else
        {
            temp->frmTOLX[verif->frmTOLCtr] = x;
            temp->frmTOLY[verif->frmTOLCtr] = y;
            verif->dataTransmitted = 1;
            temp->newVarX = (int *) calloc(1, sizeof(int));
            temp->newVarY = (int *) calloc(1, sizeof(int));
        }
}