#include "affichage.h"

void afficherIndiv(Individu i, Param *param) {
    printf("[");
    IElem* p = i;
    while (p != NULL) {
        printf("%d", p->val);
        p = p->next;
    }
    printf("]");
    printf("%.2f ", qualite(valeurIndiv(i), param));
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
