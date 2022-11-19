#ifndef __POPULATION_H__
#define __POPULATION_H__

#include <stdio.h>
#include <stdlib.h>

#include "individu.h"

typedef struct indiv_list_elem {
    Individual indiv;
    struct indiv_list_elem* next;
    struct indiv_list_elem* prev;
} IndivListElem;

typedef IndivListElem* Population;
Population p_insert_head(Population p, Individual i);
Population random_indiv_list_init_I(u_int32_t pop_size, u_int8_t indiv_size);
void print_population(Population p);
void quicksort(IndivListElem* start, IndivListElem* end);
void pop_select(Population p, u_int8_t t_select);
void free_pop(Population *p);

#endif