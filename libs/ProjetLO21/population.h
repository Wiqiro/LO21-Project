#ifndef __POPULATION_H__
#define __POPULATION_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "individu.h"
#include "config.h"

typedef struct pElem {
    Individu indiv;
    struct pElem *next;
    struct pElem *prev;
} PElem;

typedef PElem *Population;

Population initPop(struct config *conf);
void quicksort(Population pop, struct config *conf);
void selectPop(Population pop, struct config *conf);
Population croiserPop(Population pop, struct config *conf);
void viderPop(Population *pop);


#endif