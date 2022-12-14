#ifndef __CLI_H__
#define __CLI_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "individu.h"
#include "population.h"
#include "config.h"

void clear();
void afficherIndiv(Individu indiv, struct config *conf);
void afficherPop(Population pop, struct config *conf);
void configurer(struct config *conf);


#endif