#ifndef INDIVIDU_H
#define INDIVIDU_H

#include <stdlib.h>
#include <stdio.h>

typedef unsigned char Bit;

typedef struct elem {
    Bit val;
    struct elem next;
} BitListElem;

typedef BitListElem* BitList;

#endif