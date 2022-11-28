#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include <stdlib.h>
#include <stdio.h>

#include "individu.h"
#include "population.h"
#include "param.h"

void afficherIndiv(Individu i, Param *param);
void afficherPop(Population p, Param *param);


#endif