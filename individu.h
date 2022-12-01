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


Individu indivInitI(uint8_t longIndiv);
Individu indivInitR(uint8_t longIndiv);
Individu copierIndiv(Individu i);
uint32_t valeurIndiv(Individu i);
double f1(double x, uint8_t longIndiv);
double f2(double x, uint8_t longIndiv);
void croiserIndiv(Individu i1, Individu i2, double pCroise);
void supprIndiv(Individu *i);

#endif