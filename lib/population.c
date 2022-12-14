#include "population.h"

/**
 * @brief insère un individu en tête tete'une population
 * 
 * @param pop la population recevant le nouvel élément
 * @param indiv l'individu à insérer en tête
 * @return Population un pointeur sur la tête de la nouvelle population
 */
static Population _insererTete(Population pop, Individu indiv) {
    Population new_p = (Population) malloc(sizeof(PElem));
    *new_p = (PElem) {.indiv = indiv, .next = pop, .prev = NULL};
    if (pop != NULL) {
        pop->prev = new_p;
    }
    return new_p;
}


/**
 * @brief initialise aléatoirement une nouvelle population
 * 
 * @param conf passage par adresse des parametres du programme
 * @return Population un pointeur sur la tête de la population créée
 */
Population popInit(struct config *conf) {
    Population pop = NULL;
    for (uint16_t i = 0; i < conf->taillePop; i++) {
        pop = _insererTete(pop, indivInitI(conf->longIndiv));
    }
    return pop;
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
 * @param conf passage par adresse des parametres du programme
 * @return PElem* pointeur vers le pivot placé correctement dans la liste partitionnée
 */
static PElem* _partitionner(PElem *tete, PElem *queue, struct config *conf) {
    double valPivot = conf->fQualite(valeurIndiv(queue->indiv), conf->longIndiv);
    PElem *indiv = tete;

    for (PElem *j = tete; j != queue; j = j->next) {
        if (conf->fQualite(valeurIndiv(j->indiv), conf->longIndiv) > valPivot) {
            _echanger(indiv, j);
            indiv = indiv->next;
        }
    }
    _echanger(indiv, queue);
    return indiv;
}


/**
 * @brief procédure de tri qui partitionne une liste pour ensuite trier récursivement les
 * listes à gauche et à droite du pivot
 * 
 * @param tete pointeur vers la tête de la liste à trier
 * @param queue pointeur vers la queue de la liste à trier
 * @param conf passage par adresse des parametres du programme
 */
static void _quicksort(PElem* tete, PElem *queue, struct config *conf) {
    if (queue != NULL && tete != queue && tete != queue->next) {
        PElem *pivot = _partitionner(tete, queue, conf);
        _quicksort(tete, pivot->prev, conf);
        _quicksort(pivot->next, queue, conf);
    }
}

/**
 * @brief simplifie l'appel à la procédure quicksort
 * 
 * @param pop population à trier
 * @param conf passage par adresse des parametres du programme
 */
void quicksort(Population pop, struct config *conf) {
    if (pop != NULL) {
        PElem* queue = pop;
        while (queue->next != NULL) {
            queue = queue->next;
        }
        _quicksort(pop, queue, conf);
    }
}


/**
 * @brief sélectionne les premiers éléments d'une population pour les recopier jusqu'à la fin de la liste
 * 
 * @param pop population à sélectionner
 * @param conf passage par adresse des parametres du programme
 */
void selectPop(Population pop, struct config *conf) {

    uint16_t nSelect = conf->tSelect * conf->taillePop;
    PElem* eSelect = pop;
    PElem* eParcours = pop;
    uint8_t i = 0;

    while (eParcours != NULL) {
        if (i >= nSelect) {
            /* supprIndiv(&eParcours->indiv);
            eParcours->indiv = copierIndiv(eSelect->indiv); */
            remplacerIndiv(eParcours->indiv, eSelect->indiv);
        }

        eSelect = eSelect->next;
        eParcours = eParcours->next;
        if (++i % nSelect == 0) {
            eSelect = pop;
        }
    }
}


/**
 * @brief permet de sélectionner un individu aléatoire dans une population
 * 
 * @param pop la population dans laquelle l'individu est sélectionné
 * @param conf passage par adresse des parametres du programme
 * @return Individu l'individu sélectionné aléatoirement
 */
 Individu _indivAleatoire(Population pop, struct config *conf) {
    uint16_t pos = rand() % conf->taillePop;
    for (uint16_t i = 0; i < pos; i++) {
        pop = pop->next;
    }
    return copierIndiv(pop->indiv);
}


/**
 * @brief permet de croiser une population en créant une nouvelle population composée d'individus
 * de la première population sélectionnée aléatoirement et croisés entre eux
 * 
 * @param pop la population à croiser
 * @param conf passage par adresse des parametres du programme
 * @return Population la nouvelle population croisée
 */
Population croiserPop(Population pop, struct config *conf) {
    Population p2 = NULL;
    for (uint32_t i = 0; i < conf->taillePop/2; i++) {
        p2 = _insererTete(p2, _indivAleatoire(pop, conf));
        p2 = _insererTete(p2, _indivAleatoire(pop, conf));
        croiserIndiv(p2->indiv, p2->next->indiv, conf->pCroise);
    }
    if (conf->taillePop % 2 == 0) {
        p2 = _insererTete(p2, _indivAleatoire(pop, conf));
    }
    return p2;
}

/**
 * @brief vide une population en supprimant récursivement chaque individu
 * 
 * @param pop la population a vider
 */
void viderPop(Population *pop) {
    if (*pop != NULL) {
        viderPop(&(*pop)->next);
        supprIndiv(&(*pop)->indiv);
        free(*pop);
        *pop = NULL;
    }
}