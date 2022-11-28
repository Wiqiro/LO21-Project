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

Population popInit(Param *param) {
    Population p = NULL;
    for (int i=0; i<param->taillePop; i++) {
        p = _insererTete(p, indivInitI(param->longIndiv));
    }
    return p;
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

void selectPop(Population p, Param *param) {

    uint32_t nSelect = param->tSelect * param->taillePop;
    PElem* eSelect = p;
    uint8_t i = 0;

    for (PElem* eParcours = p; eParcours != NULL; eParcours = eParcours->next) {
        if (i == nSelect) {
            i = 0;
            eSelect = p;
        }
        eParcours->indiv = eSelect->indiv;
        i++;
        eSelect = eSelect->next;
    }
}

 Individu _indivAleatoire(Population p) {
    /* uint32_t pos = rand() % p.taille;
    for (uint32_t i = 0; i < pos; i++) {
        p.tete = p.tete->next;
    } */
    printf("a");
    return copierIndiv(p->indiv);
}

Population croiserPop(Population p, Param *param) {
    uint32_t taillePop = 20;
    Population p2 = NULL;
    for (uint32_t i = 0; i < taillePop; i++) {
        _insererTete(p2, _indivAleatoire(p));
        _insererTete(p2, _indivAleatoire(p));
        croiserIndiv(p2->indiv, p2->next->indiv, param->pCroise);
    }
}


void viderPop(Population *p) {
    if (*p != NULL) {
        viderPop(&(*p)->next);
        supprIndiv(&(*p)->indiv);
        free(*p);
        *p = NULL;
    }
}