#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "population.h"
#include "individu.h"
#include "affichage.h"

double f1(double x) {
    return -x * x;
}

double f2(double x) {
    return -log(x);
}


Param param = {
    .longIndiv = 8,
    .taillePop = 2000000,
    .nGen = 90,
    .pCroise = 50,
    .tSelect = 0.5,
    .qualite = {
        .fonc = f1,
        .A = -1,
        .B = 1
    }
};

/* Param param = {
    .longIndiv = 12,
    .taillePop = 40,
    .nGen = 90,
    .pCroise = 50,
    .tSelect = 20,
    .qualite = {
        .fonc = _negLog,
        .A = 0.1,
        .B = 5
    }
}; */

int main(int argc, char *argv[]) {
    system("clear");
    srand(time(NULL));
    Population p = popInit(&param);

 
    printf("Linked List before sorting \n");
    //afficherPop(p, &param);


    /* quicksort(p, &param);
    printf("\n\nLinked List after sorting \n");
    afficherPop(p, &param);

    selectPop(p, &param);
    printf("\n\nLinked List after selection \n");
    afficherPop(p, &param); */
    

    afficherIndiv(p->indiv, &param);
    //viderPop(&p);
 
    return 0;
}
