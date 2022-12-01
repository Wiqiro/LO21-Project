#include "population.h"

uint32_t nb = 0;

/**
 * @brief insère un individu en tête tete'une population
 * 
 * @param p la population recevant le nouvel élément
 * @param i l'individu à insérer en tête
 * @return Population un pointeur sur la tête de la nouvelle population
 */
static Population _insererTete(Population p, Individu i) {
    Population new_p = (Population) malloc(sizeof(PElem));
    *new_p = (PElem) {.indiv = i, .next = p, .prev = NULL};
    if (p != NULL) {
        p->prev = new_p;
    }
    return new_p;
}


/**
 * @brief initialise aléatoirement une nouvelle population
 * 
 * @param param passage par adresse des parametres du programme
 * @return Population un pointeur sur la tête de la population créée
 */
Population popInit(Param *param) {
    Population p = NULL;
    for (uint32_t i = 0; i < param->taillePop; i++) {
        p = _insererTete(p, indivInitI(param->longIndiv));
    }
    return p;
}

/**
 * @brief échange les valeurs de deux éléments de populations
 * 
 * @param a élément à échanger avec b
 * @param b élément à échanger avec a
 */
static void _echanger(PElem *a, PElem *b) {
    Individu tmp = a->indiv;
    a->indiv = b->indiv;
    b->indiv = tmp;
}

/**
 * @brief fonction de partition de l'algorithme quicksort choisissant comme pivot
 * le dernier élément et plaçant l'intégralité des valeurs inférieures à celui-ci après lui
 * 
 * @param tete pointeur vers la tête de la liste à partitionner
 * @param queue pointeur vers la queue de la liste à partitionner
 * @param param passage par adresse des parametres du programme
 * @return PElem* pointeur vers le pivot placé correctement dans la liste partitionnée
 */
static PElem* _partitionner(PElem *tete, PElem *queue, Param *param) {
    double valPivot = param->fonc(valeurIndiv(queue->indiv), param->longIndiv);
    PElem *i = tete;

    for (PElem *j = tete; j != queue; j = j->next) {
        if (param->fonc(valeurIndiv(j->indiv), param->longIndiv) > valPivot) {
            _echanger(i, j);
            i = i->next;
        }
    }
    nb++;
    _echanger(i, queue);
    return i;
}

/**
 * @brief procédure de tri qui partitionne une liste pour ensuite trier récursivement les
 * listes à gauche et à droite du pivot
 * 
 * @param tete pointeur vers la tête de la liste à trier
 * @param queue pointeur vers la queue de la liste à trier
 * @param param passage par adresse des parametres du programme
 */
static void _quicksort(PElem* tete, PElem *queue, Param *param) {
    if (queue != NULL && tete != queue && tete != queue->next) {
    
        PElem *pivot = _partitionner(tete, queue, param);
        _quicksort(tete, pivot->prev, param);
        _quicksort(pivot->next, queue, param);
    }

}

/**
 * @brief simplifie l'appel à la procédure quicksort
 * 
 * @param p population à trier
 * @param param passage par adresse des parametres du programme
 */
void quicksort(Population p, Param *param) {
    if (p != NULL) {
        PElem* queue = p;
        while (queue->next != NULL) {
            queue = queue->next;
        }
        _quicksort(p, queue, param);
    }
    printf("\nnb d'itération: %d\n", nb);
}


/**
 * @brief sélectionne les premiers éléments d'une population pour les recopier jusqu'à la fin de la liste
 * 
 * @param p population à sélectionner
 * @param param passage par adresse des parametres du programme
 */
void selectPop(Population p, Param *param) {

    uint32_t nSelect = param->tSelect * param->taillePop;
    PElem* eSelect = p;
    PElem* eParcours = p;
    uint8_t i = 0;

    while (eParcours != NULL) {
        if (i >= nSelect) {
            supprIndiv(&eParcours->indiv);
            eParcours->indiv = copierIndiv(eSelect->indiv);
        }

        eSelect = eSelect->next;
        eParcours = eParcours->next;
        if (++i % nSelect == 0) {
            eSelect = p;
        }
    }
}


/**
 * @brief permet de sélectionner un individu aléatoire dans une population
 * 
 * @param p la population dans laquelle l'individu est sélectionné
 * @param param passage par adresse des parametres du programme
 * @return Individu l'individu sélectionné aléatoirement
 */
 Individu _indivAleatoire(Population p, Param *param) {
    uint32_t pos = rand() % param->taillePop;
    for (uint32_t i = 0; i < pos; i++) {
        p = p->next;
    }
    return copierIndiv(p->indiv);
}


/**
 * @brief permet de croiser une population en créant une nouvelle population composée d'individus
 * de la première population sélectionnée aléatoirement et croisés entre eux
 * 
 * @param p la population à croiser
 * @param param passage par adresse des parametres du programme
 * @return Population la nouvelle population croisée
 */
Population croiserPop(Population p, Param *param) {
    Population p2 = NULL;
    for (uint32_t i = 0; i < param->taillePop/2; i++) {
        p2 = _insererTete(p2, _indivAleatoire(p, param));
        p2 = _insererTete(p2, _indivAleatoire(p, param));
        croiserIndiv(p2->indiv, p2->next->indiv, param->pCroise);
    }
    if (param->taillePop % 2 == 0) {
        p2 = _insererTete(p2, _indivAleatoire(p, param));
        //TODO: changer toussa
    }
    return p2;
}

/**
 * @brief vide une population en supprimant récursivement chaque individu
 * 
 * @param p la population a vider
 */
void viderPop(Population *p) {
    if (*p != NULL) {
        viderPop(&(*p)->next);
        supprIndiv(&(*p)->indiv);
        free(*p);
        *p = NULL;
    }
}