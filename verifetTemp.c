#include <stdio.h>
#include <stdlib.h>
#include "includes/verifetTemp.h"

void initVerifVar(VERIF *verif)
{
	verif->stateAtOne = 1;
    verif->ctr = 0;
    verif->allocAuth = 0;
    verif->iterationNumber = 0;
    verif->frmTOLCtr = 0;
    verif->propagationDone = 0;
    verif->allocAuth = 0;
    verif->stateAtOneNumber = 0;
    verif->dataTransmitted = 0;
}


void initTempVar(TEMP *temp)
{
    temp->tempX = NULL;
    temp->tempY = NULL;
    temp->frmTOLX = NULL;
    temp->frmTOLX = NULL;
    temp->newVarX = NULL;
    temp->newVarY = NULL;
}

void freeTemp(TEMP *temp)
{
    free(temp->tempX);
    free(temp->tempY);
    free(temp->frmTOLX);
    free(temp->frmTOLY);
    free(temp->newVarX);
    free(temp->newVarY);
}