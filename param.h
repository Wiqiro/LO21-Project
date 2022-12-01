#ifndef __PARAM_H__
#define __PARAM_H__

#include <stdlib.h>
#include <math.h>
#include <stdint.h>


typedef struct {
    uint8_t longIndiv;
    uint32_t taillePop;
    uint32_t nGen;
    float pCroise;
    float tSelect;
    double (*fonc)(double, uint8_t);

} Param;


#endif