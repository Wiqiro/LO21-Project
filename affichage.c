#include "affichage.h"

void configurer(struct configuration *config) {
    char buffer[64];

    do {
        printf("Choisissez la longueur d'un individu (entre 8 et 16) ");
        fgets(buffer, 64, stdin);
        config->longIndiv = strtoul(buffer, NULL, 10);
    } while (config->longIndiv < 8 || config->longIndiv > 16);

    do {
        printf("Choisissez la taille d'une population (entre 20 et 200) ");
        fgets(buffer, 64, stdin);
        config->taillePop = strtoul(buffer, NULL, 10);
    } while (config->taillePop < 20 || config->taillePop > 200);
    
    do {
        printf("Choisissez le nombre de générations (entre 20 et 200) ");
        fgets(buffer, 64, stdin);
        config->nGen = strtoul(buffer, NULL, 10);
    } while (config->nGen < 20 || config->nGen > 200);

    do {
        printf("Choisissez la probabilité de croisement entre deux individus (entre 0.1 et 0.9) ");
        fgets(buffer, 64, stdin);
        config->pCroise = strtof(buffer, NULL);
    } while (config->pCroise < 0.1 || config->pCroise > 0.9);

    do {
        printf("Choisissez le taux de sélection d'une population (entre 0.1 et 0.9) ");
        fgets(buffer, 64, stdin);
        config->tSelect = strtof(buffer, NULL);
    } while (config->tSelect < 0.1 || config->tSelect > 0.9);

    do {
        printf("Choisissez la fonction de qualité à utiliser (f1 ou f2) ");
        fgets(buffer, 64, stdin);
    } while (buffer[0] != 'f' || (buffer[1] != '1' && buffer[1] != '2') || buffer[2] != '\n');
    if (buffer[1] == '1') {
        config->fonc = f1;
    } else {
        config->fonc = f2;
    }
}

void afficherIndiv(Individu indiv, struct configuration *config) {
    printf("[");
    IElem* pop = indiv;
    while (pop != NULL) {
        printf("%d", pop->val);
        pop = pop->next;
    }
    printf(" | %.4f]\n", config->fonc(valeurIndiv(indiv), config->longIndiv));
}


void afficherPop(Population pop, struct configuration *config) {
    PElem* e = pop;
    while (e != NULL) {
        afficherIndiv(e->indiv, config);
        e = e->next;
        printf("\n");
    }
}
