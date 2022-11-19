#ifndef __INDIVIDU_H__
#define __INDIVIDU_H__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SIZE 12

typedef u_int8_t Bit;


typedef struct bit_list_elem {
    Bit val;
    struct bit_list_elem* next;
} BitListElem;

typedef BitListElem* Individual;


Individual insert_head(Individual l, Bit val);
Individual random_bit_list_init_I(int8_t size);
Individual random_bit_list_init_R(int8_t size);
void print_bitlist(Individual l);
u_int64_t bit_list_value(Individual l);
double f1(u_int64_t x, u_int8_t size);
void cross_bitlists(Individual l1, Individual l2, float prob);
void free_indiv(Individual *i);

#endif