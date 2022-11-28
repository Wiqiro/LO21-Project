#ifndef __POPULATION_H__
#define __POPULATION_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "individu.h"
#include "param.h"

typedef struct pElem {
    Individu indiv;
    struct pElem* next;
    struct pElem* prev;
} PElem;

typedef PElem* Population;

Population popInit(uint32_t taillePop, Param *param);
void quicksort(Population p, Param *param);
void selectPop(Population p, Param *param);
void viderPop(Population *p);

#endif