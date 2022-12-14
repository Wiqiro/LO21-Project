#ifndef __PARAM_H__
#define __PARAM_H__

#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

struct configuration {
    uint8_t longIndiv;
    uint16_t taillePop;
    uint16_t nGen;
    float pCroise;
    float tSelect;
    double (*fQualite)(double, uint8_t);
};


#endif