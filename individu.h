#ifndef __INDIVIDU_H__
#define __INDIVIDU_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "param.h"



typedef uint8_t Bit;


typedef struct iElem {
    Bit val;
    struct iElem* next;
} IElem;

typedef IElem* Individu;


Individu indivInitI(int8_t longIndiv);
Individu indivInitR(int8_t longIndiv);
void afficherIndiv(Individu i, Param *param);
uint64_t valeurIndiv(Individu i);
double qualite(uint64_t x, Param *param); //TODO:
void croiserIndiv(Individu i1, Individu i2, double pCroise);
void supprIndiv(Individu *i);

#endif