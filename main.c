#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include <population.h>
#include <individu.h>
#include <config.h>

#include "cli.h"

int main(int argc, char *argv[]) {
    clear();
    srand(time(NULL));

    struct config conf;
    //configurer(&conf); //entrée des paramètres de la population
    conf = (struct config) {
        .tSelect = .9,
        .pCroise = .5,
        .longIndiv = 16,
        .taillePop = 20,
        .nGen = 200,
        .fQualite = f2
    };
    Population pop = popInit(&conf); //initialiser la population

    for (uint16_t gen = 1; gen <= conf.nGen; gen++) { //répéter nGen fois
        clear();
        printf("Génération %d / %d\n", gen, conf.nGen);
        Population tmpPop = croiserPop(pop, &conf); //croiser la population
        viderPop(&pop);
        pop = tmpPop;
        quicksort(pop, &conf); //trier la population
        selectPop(pop, &conf); //sélectionner la population
    }

    printf("\nMeilleur individu:\n\tValeur: %.6f\n\tChaine: ", conf.fQualite(valeurIndiv(pop->indiv), conf.longIndiv));
    afficherIndiv(pop->indiv, &conf);

    viderPop(&pop);
    return 0;
}