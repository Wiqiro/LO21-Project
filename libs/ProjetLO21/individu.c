#include "individu.h"


/**
 * @brief insere un bit en tete d'un individu
 * 
 * @param indiv l'individu recevant le nouvel élément
 * @param val la valeur du bit (0 ou 1)
 * @return Individu un pointeur sur la tete du nouvel individu
 */
static Individu _insererTete(Individu indiv, Bit val) {
    Individu new_i = (Individu) malloc(sizeof(IElem));
    *new_i = (IElem) {.next = indiv, .val = val};
    return new_i;
}

/**
 * @brief retourne un bit aléaoire selon un probabilité donnée
 * 
 * @param prob probabilité pour le bit d'être 1
 * @return Bit
 */
static Bit _bitAleatoire(double prob) {
    return (rand() <= prob * RAND_MAX);
}

/**
 * @brief initialise aléatoirement un nouvel individu de manière itérative
 * 
 * @param longIndiv longueur de l'individu à initialiser
 * @return Individu un pointeur sur la tête du nouvel individu
 */
Individu indivInitI(uint8_t longIndiv) {
    Individu indiv = NULL;
    for (uint8_t x=0; x<longIndiv; x++) {
        indiv = _insererTete(indiv, _bitAleatoire(0.5));
    }
    return indiv;
}

/**
 * @brief initialise aléatoirement un nouvel individu à l'aide d'un appel récursif
 * créant un individu de taille longIndiv - 1
 * 
 * @param longIndiv longueur de l'individu à initialiser
 * @return Individu un pointeur sur la tête du nouvel individu
 */
Individu indivInitR(uint8_t longIndiv) {
    if (longIndiv == 0) {
        return NULL;
    } else {
        return _insererTete(indivInitR(longIndiv - 1), rand()%2);
    }
}

/**
 * @brief créé récursivement une copie d'un invividu en réallouant la mémoire qui lui est associée 
 * 
 * @param indiv individu à copier
 * @return Individu pointeur vers la tête du nouvel individu
 */
Individu copierIndiv(Individu indiv) {
    if (indiv != NULL) {
        return _insererTete(copierIndiv(indiv->next), indiv->val);
    } else {
        return NULL;
    }
}

void remplacerIndiv(Individu indiv, Individu model) {
    if (indiv != NULL && model != NULL) {
        indiv->val = model->val;
        remplacerIndiv(indiv->next, model->next);
    }
}

/**
 * @brief calcul de la valeur d'individu, indiv.e. la conversion en décimale de la liste
 * 
 * @param indiv individu dont la valeur est calculée
 * @return uint32_t valeur de l'individu
 */
uint32_t valeurIndiv(Individu indiv) {
    IElem* e = indiv;
    uint32_t value = 0;
    while (e != NULL) {
        value = 2*value + e->val;
        e = e->next;
    }
    return value;
}


double f1(double x, uint8_t longIndiv) {
    double X = (x / (1 << longIndiv)) * 2 - 1;
    return -X * X;
}

double f2(double x, uint8_t longIndiv) {
    double X = (x / (1 << longIndiv)) * 4.9 + 0.1;
    return -log(X);
}

/**
 * @brief échange les valeurs de deux éléments de listes d'individu
 * 
 * @param a élément à échanger avec b
 * @param b élément à échanger avec a
 */
static void _echanger(IElem *a, IElem *b) {
    Bit tmp = a->val;
    a->val = b->val;
    b->val = tmp;
}

/**
 * @brief croise deux individus avec une probabilité pCroise d'échanger 
 * les éléments des deux listes à chaque position
 * 
 * @param indiv1 individu à croiser avec indiv2
 * @param indiv2 individu à croiser avec indiv1
 * @param pCroise probabilité d'echanger deux éléments
 */
void croiserIndiv(Individu indiv1, Individu indiv2, double pCroise) {
    while (indiv1 != NULL && indiv2 != NULL) {
        if (_bitAleatoire(pCroise)) {
            _echanger(indiv1, indiv2);
        }
        indiv1 = indiv1->next;
        indiv2 = indiv2->next;
    }
}

/**
 * @brief supprime un individu en libérant récursivement la mémoire allouée à chaque élément
 * 
 * @param indiv l'individu à supprimer
 */
void supprIndiv(Individu *indiv) {
    if (*indiv != NULL) {
        supprIndiv(&(*indiv)->next);
        free(*indiv);
        *indiv = NULL;
    }
}