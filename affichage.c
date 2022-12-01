#include "affichage.h"

void configurer(Param *param) {
    char buffer[64];

    do {
        printf("Choisissez la longueur d'un individu (entre 1 et 30) ");
        fgets(buffer, 64, stdin);
        param->longIndiv = strtoul(buffer, NULL, 10);
    } while (param->longIndiv < 1 || param->longIndiv > 30);

    do {
        printf("Choisissez la taille d'une population (entre 1 et 100,000) ");
        fgets(buffer, 64, stdin);
        param->taillePop = strtoul(buffer, NULL, 10);
    } while (param->taillePop < 1 || param->taillePop > 100000);
    
    do {
        printf("Choisissez le nombre de générations (entre 1 et 100,000) ");
        fgets(buffer, 64, stdin);
        param->nGen = strtoul(buffer, NULL, 10);
    } while (param->nGen < 1 || param->nGen > 100000);

    do {
        printf("Choisissez la probabilité de croisement entre deux individus (entre 0 et 1) ");
        fgets(buffer, 64, stdin);
        param->pCroise = strtof(buffer, NULL);
    } while (param->pCroise < 0 || param->pCroise > 1);

    do {
        printf("Choisissez le taux de sélection d'une population (entre 0 et 1) ");
        fgets(buffer, 64, stdin);
        param->tSelect = strtof(buffer, NULL);
    } while (param->tSelect < 0 || param->tSelect > 1);

    do {
        printf("Choisissez la fonction de qualité à utiliser (f1 ou f2) ");
        fgets(buffer, 64, stdin);
    } while (buffer[0] != 'f' || (buffer[1] != '1' && buffer[1] != '2') || buffer[2] != '\n');
    if (buffer[1] == '1') {
        param->fonc = f1;
    } else {
        param->fonc = f2;
    }
}

void afficherIndiv(Individu i, Param *param) {
    printf("[");
    IElem* p = i;
    while (p != NULL) {
        printf("%d", p->val);
        p = p->next;
    }
    printf("]");
    printf("%.2f ", param->fonc(valeurIndiv(i), param->longIndiv));
}


void afficherPop(Population p, Param *param) {
    PElem* e = p;
    int8_t i = 0;
    while (e != NULL) {
        afficherIndiv(e->indiv, param);
        e = e->next;
        if (i == 8) {
            printf("\n");
            i = 0;
        } else {
            printf(" ");
            i++;
        }
    }
}
