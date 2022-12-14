#ifndef __POPULATION_H__
#define __POPULATION_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "individu.h"
#include "configuration.h"

typedef struct pElem {
    Individu indiv;
    struct pElem *next;
    struct pElem *prev;
} PElem;

typedef PElem *Population;

Population popInit(struct configuration *config);
void quicksort(Population pop, struct configuration *config);
void selectPop(Population pop, struct configuration *config);
Population croiserPop(Population pop, struct configuration *config);
void viderPop(Population *pop);


#endif