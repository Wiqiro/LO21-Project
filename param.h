#ifndef __PARAM_H__
#define __PARAM_H__

#include <stdlib.h>
#include <math.h>
#include <stdint.h>


typedef struct {
    uint8_t longIndiv;
    uint32_t taillePop;
    uint32_t nGen;
    double pCroise;
    double tSelect;

    struct {
        double (*fonc)(double);
        int8_t A, B;
    } qualite;

} Param ;


#endif