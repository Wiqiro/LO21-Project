#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include <population.h>
#include <individu.h>
#include <config.h>

#include "cli.h"

/* int main(int argc, char *argv[]) {
    clear();
    srand(time(NULL));

    struct config conf;
    configurer(&conf); //entrée des paramètres de la population

    Population pop = initPop(&conf); //initialiser la population

    for (uint16_t gen = 1; gen <= conf.nGen; gen++) { //répéter nGen fois
        clear();
        printf("Génération %d / %d\n", gen, conf.nGen);
        Population tmpPop = croiserPop(pop, &conf); //croiser la population
        viderPop(&pop);
        pop = tmpPop;
        quicksort(pop, &conf); //trier la population
        selectPop(pop, &conf); //sélectionner la population
    }

    printf("\nMeilleur individu:\n\Qualité: %.6f\n\tChaine: ", conf.fQualite(valeurIndiv(pop->indiv), conf.longIndiv));
    afficherIndiv(pop->indiv, &conf);

    viderPop(&pop);
    return 0;
} */

int main(int argc, char *argv[]) {
    clear();
    srand(time(NULL));

    struct config conf;
    //configurer(&conf); //entrée des paramètres de la population
    conf = (struct config) {
        .longIndiv = 16,
        .pCroise = .2,
        .taillePop = 40,
        .tSelect = .9,
        .nGen = 20,
        .fQualite = f2
    };

    for (int r = 0; r < 10; r++) {
        Population pop = initPop(&conf); //initialiser la population

        for (uint16_t gen = 1; gen <= conf.nGen; gen++) { //répéter nGen fois
            Population tmpPop = croiserPop(pop, &conf); //croiser la population
            viderPop(&pop);
            pop = tmpPop;
            quicksort(pop, &conf); //trier la population
            selectPop(pop, &conf); //sélectionner la population
        }

        printf("%.6f\t", qualiteIndiv(pop->indiv, &conf));
        afficherIndiv(pop->indiv, &conf);

        viderPop(&pop);

    }
    return 0;
}