#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "population.h"
#include "individu.h"
#include "affichage.h"


int main(int argc, char *argv[]) {
    system("clear");
    srand(time(NULL));

    struct configuration config; //entrée des paramètres de la population
    configurer(&config);

    Population pop = popInit(&config); //initialiser la population

    for (uint16_t gen = 0; gen < config.nGen; gen++) { //répéter nGen fois
        system("clear");
        printf("Generation %d / %d\n", gen, config.nGen);

        Population tmpPop = croiserPop(pop, &config); //croiser la population
        viderPop(&pop);
        pop = tmpPop;
        quicksort(pop, &config); //trier la population
        selectPop(pop, &config); //sélectionner la population
    }

    quicksort(pop, &config);
    system("clear");
    printf("Meilleur individu après %d générations:\n", config.nGen);

    afficherIndiv(pop->indiv, &config);
    viderPop(&pop);
    return 0;
}
