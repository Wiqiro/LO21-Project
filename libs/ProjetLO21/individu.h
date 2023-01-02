#ifndef __INDIVIDU_H__
#define __INDIVIDU_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "config.h"

typedef uint8_t Bit;

typedef struct iElem {
    Bit val;
    struct iElem* next;
} IElem;

typedef IElem* Individu;

Individu insererTete(Individu indiv, Bit val);
Individu initIndivI(uint8_t longIndiv);
Individu initIndivR(uint8_t longIndiv);
Individu copierIndiv(Individu indiv);
void remplacerIndiv(Individu indiv, Individu modele);

uint32_t valeurIndiv(Individu indiv);
double qualiteIndiv(Individu indiv, struct config *conf);
double f1(double valIndiv, uint8_t longIndiv);
double f2(double valIndiv, uint8_t longIndiv);

void croiserIndiv(Individu indiv1, Individu indiv2, double pCroise);
void supprIndiv(Individu *indiv);

#endif