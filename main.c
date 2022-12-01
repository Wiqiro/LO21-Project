#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "population.h"
#include "individu.h"
#include "affichage.h"




/* Param param = {
    .longIndiv = 8,
    .taillePop = 16,
    .nGen = 90,
    .pCroise = 0.5,
    .tSelect = 0.7,
    .fonc = f1
}; */


Param param = {
    .longIndiv = 2,
    .taillePop = 20000,
    .nGen = 1,
    .pCroise = 1,
    .tSelect = 1,
    .fonc = f1
};

int main(int argc, char *argv[]) {
    system("clear");
    srand(time(NULL));
    //configurer(&param);
    clock_t timer = clock();


    Population p = popInit(&param);
    printf("Linked List before sorting \n");
    printf("%ldµs", (clock() - timer));
    timer = clock();
    //afficherPop(p, &param);


    quicksort(p, &param);
    printf("\n\nLinked List after sorting \n");
    printf("%ldµs", (clock() - timer));
    timer = clock();
    //afficherPop(p, &param);

    /* selectPop(p, &param);
    printf("\n\nLinked List after selection \n");
    printf("%ldµs", (clock() - timer)/1000);
    timer = clock();
    //afficherPop(p, &param); */


    /* Population p2 = croiserPop(p, &param);
    printf("\n\nLinked List after crossing \n");
    printf("%ldµs", (clock() - timer)/1000);
    timer = clock();
    //afficherPop(p2, &param);

    viderPop(&p2); */

    viderPop(&p);
 
    printf("\n");
    return 0;
}
