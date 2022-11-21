#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "population.h"
#include "individu.h"



int main(int argc, char *argv[]) {

    srand(time(NULL));
    Population p = random_indiv_list_init_I(20, SIZE);

 
    printf("Linked List before sorting \n");
    print_population(p);
    IndivListElem* last = p;
    if (p != NULL) {
        while (last->next != NULL) {
            last = last->next;
        }
    }

    quicksort(p, last);
    printf("\nLinked List after sorting \n");
    print_population(p);

    /* pop_select(p, 10);
    printf("Linked List after selection \n");
    print_population(p); */

    free_pop(&p);
 
    return 0;
}
