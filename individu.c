#include "individu.h"


static Individu _insererTete(Individu i, Bit val) {
    Individu new_i = (Individu) malloc(sizeof(IElem));
    new_i->next = i;
    new_i->val = val;
    return new_i;
}


static Bit _bitAleatoire(double prob) {
    return (rand() <= prob * RAND_MAX);
}

Individu indivInitI(int8_t longIndiv) {
    Individu i = NULL;
    for (int x=0; x<longIndiv; x++) {
        i = _insererTete(i, _bitAleatoire(0.5));
    }
    return i;
}

Individu indivInitR(int8_t longIndiv) {
    if (longIndiv == 0) {
        return NULL;
    } else {
        return _insererTete(indivInitR(longIndiv - 1), rand()%2);
    }
}


uint64_t valeurIndiv(Individu i) {
    IElem* e = i;
    uint64_t value = 0;
    while (e != NULL) {
        value = 2*value + e->val;
        e = e->next;
    }
    return value;
}

static double _pow2(uint8_t x) {
    return 1 << x;
}


double qualite(uint64_t x, Param *param) {
    double X = (x / _pow2(param->longIndiv)) * (param->qualite.B - param->qualite.A) + param->qualite.A;
    return param->qualite.fonc(X);
}

static void _echanger(IElem* a, IElem* b) {
    Bit tmp = a->val;
    a->val = b->val;
    b->val = tmp;
}

void croiserIndiv(Individu i1, Individu i2, double pCroise) {
    while (i1 != NULL && i2 != NULL) {
        if (_bitAleatoire(pCroise)) {
            _echanger(i1, i2);
        }
        i1 = i1->next;
        i2 = i2->next;
    }
}

void supprIndiv(Individu *i) {
    if (*i != NULL) {
        supprIndiv(&(*i)->next);
        free(*i);
        *i = NULL;
    }
}