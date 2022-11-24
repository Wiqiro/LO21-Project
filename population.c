#include "population.h"

static Population _insererTete(Population p, Individu i) {
    Population new_p = (Population) malloc(sizeof(PElem));
    new_p->next = p;
    new_p->indiv = i;
    if (p != NULL) {
        p->prev = new_p;
    }
    return new_p;
}

Population popInit(uint32_t taillePop, Param *param) {
    Population p = NULL;
    for (int i=0; i<taillePop; i++) {
        p = _insererTete(p, indivInitI(param->longIndiv));
    }
    return p;
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

static void _echanger(PElem *a, PElem *b) {
    Individu tmp = a->indiv;
    a->indiv = b->indiv;
    b->indiv = tmp;
}

static PElem* _partitionner(PElem *d, PElem *f, Param *param) {

    double x = qualite(valeurIndiv(f->indiv), param);

    PElem *i = d;

    for (PElem *j = d; j != f; j = j->next) {
        if (qualite(valeurIndiv(j->indiv), param) > x) {
            _echanger(i, j);
            i = i->next;
        }
    }
    _echanger(i, f);
    return i;
}


static void _quicksort(PElem* d, PElem *f, Param *param) {
    if (f != NULL && d != f && d != f->next) {
        PElem *p = _partitionner(d, f, param);
        _quicksort(d, p->prev, param);
        _quicksort(p->next, f, param);
    }
}

void quicksort(Population p, Param *param) {
    if (p != NULL) {
        PElem* f = p;
        while (f->next != NULL) {
            f = f->next;
        }
        _quicksort(p, f, param);
    }
}

void selectPop(Population p, uint8_t tSelect) {

    PElem* e_select = p;
    uint8_t i = 0;

    for (PElem* e = p; e != NULL; e = e->next) {
        if (i == tSelect) {
            i = 0;
            e_select = p;
        }
        e->indiv = e_select->indiv;
        i++;
        e_select = e_select->next;
    }
}

/* Population cross_pop(Population p) {
    
} */

void viderPop(Population *p) {
    if (*p != NULL) {
        viderPop(&(*p)->next);
        supprIndiv(&(*p)->indiv);
        free(*p);
        *p = NULL;
    }
}