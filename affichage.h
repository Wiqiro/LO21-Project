#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "individu.h"
#include "population.h"
#include "configuration.h"


void configurer(struct configuration *config);
void afficherIndiv(Individu indiv, struct configuration *config);
void afficherPop(Population pop, struct configuration *config);


#endif