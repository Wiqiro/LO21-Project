#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "population.h"
#include "individu.h"

double _negLog(double x) {
    return -log(x);
}

static double _negSquare(double x) {
    return -x * x;
}

Param param = {
    .longIndiv = 8,
    .taillePop = 40,
    .nGen = 90,
    .pCroise = 50,
    .tSelect = 20,
    .qualite = {
        .fonc = _negSquare,
        .A = -1,
        .B = 1
    }
};

int main(int argc, char *argv[]) {
    system("clear");
    srand(time(NULL));
    Population p = popInit(20, &param);

 
    printf("Linked List before sorting \n");
    afficherPop(p, &param);


    quicksort(p, &param);
    printf("\n\nLinked List after sorting \n");
    afficherPop(p, &param);

    /* selectPop(p, 10);
    printf("\n\nLinked List after selection \n");
    afficherPop(p); */
    


    viderPop(&p);
 
    return 0;
}
