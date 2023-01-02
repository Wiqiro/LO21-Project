#include "population.h"

/**
 * @brief Insère un individu en tête tete'une population
 * 
 * @param pop La population recevant le nouvel élément
 * @param indiv L'individu à insérer en tête
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
 * @brief Initialise aléatoirement une nouvelle population
 * 
 * @param conf Passage par adresse des parametres du programme
 * @return Population un pointeur sur la tête de la population créée
 */
Population initPop(struct config *conf) {
    Population pop = NULL;
    for (uint16_t i = 0; i < conf->taillePop; i++) {
        pop = _insererTete(pop, initIndivI(conf->longIndiv));
    }
    return pop;
}

/**
 * @brief Echange les valeurs de deux éléments de populations
 * 
 * @param a Elément à échanger avec b
 * @param b Elément à échanger avec a
 */
static void _echanger(PElem *a, PElem *b) {
    Individu tmp = a->indiv;
    a->indiv = b->indiv;
    b->indiv = tmp;
}

/**
 * @brief Fonction de partition de l'algorithme quicksort choisissant comme pivot
 * le dernier élément et plaçant l'intégralité des valeurs inférieures à celui-ci après lui
 * 
 * @param tete Pointeur vers la tête de la liste à partitionner
 * @param queue Pointeur vers la queue de la liste à partitionner
 * @param conf Passage par adresse des parametres du programme
 * @return PElem* pointeur vers le pivot placé correctement dans la liste partitionnée
 */
static PElem *_partitionner(PElem *tete, PElem *queue, struct config *conf) {
    double valPivot = qualiteIndiv(queue->indiv, conf);
    PElem *i = tete;

    for (PElem *j = tete; j != queue; j = j->next) {
        if (qualiteIndiv(j->indiv, conf) > valPivot) {
            _echanger(i, j);
            i = i->next;
        }
    }
    _echanger(i, queue);
    return i;
}


/**
 * @brief Procédure de tri qui partitionne une liste pour ensuite trier récursivement les
 * listes à gauche et à droite du pivot
 * 
 * @param tete Pointeur vers la tête de la liste à trier
 * @param queue Pointeur vers la queue de la liste à trier
 * @param conf Passage par adresse des parametres du programme
 */
static void _quicksort(PElem *tete, PElem *queue, struct config *conf) {
    if (queue != NULL && tete != queue && tete != queue->next) {
        PElem *pivot = _partitionner(tete, queue, conf);
        _quicksort(tete, pivot->prev, conf);
        _quicksort(pivot->next, queue, conf);
    }
}

/**
 * @brief Simplifie l'appel à la procédure quicksort
 * 
 * @param pop Population à trier
 * @param conf Passage par adresse des parametres du programme
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
 * @brief Sélectionne les premiers éléments d'une population pour les recopier jusqu'à la fin de la liste
 * 
 * @param pop Population à sélectionner
 * @param conf Passage par adresse des parametres du programme
 */
void selectPop(Population pop, struct config *conf) {
    uint16_t nSelect = conf->tSelect * conf->taillePop;
    PElem* eSelect = pop;
    PElem* eParcours = pop;
    uint8_t i = 0;

    while (eParcours != NULL) {
        if (i >= nSelect) {
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
 * @brief Permet de sélectionner un individu aléatoire dans une population
 * 
 * @param pop Population dans laquelle l'individu est sélectionné
 * @param taillePop Taille de la population
 * @return Individu l'individu sélectionné aléatoirement
 */
 static Individu _indivAleatoire(Population pop, uint16_t taillePop) {
    uint16_t pos = rand() % taillePop;
    for (uint16_t i = 0; i < pos; i++) {
        pop = pop->next; //la tete de pop n'est pas changée en dehors de la fonction
    }
    return copierIndiv(pop->indiv);
}


/**
 * @brief Permet de croiser une population en créant une nouvelle population composée d'individus
 * de la première population sélectionnés aléatoirement et croisés entre eux
 * 
 * @param pop La population à croiser
 * @param conf Passage par adresse des parametres du programme
 * @return Population la nouvelle population croisée
 */
Population croiserPop(Population pop, struct config *conf) {
    Population pop2 = NULL;
    for (uint32_t i = 0; i < conf->taillePop/2; i++) {
        pop2 = _insererTete(pop2, _indivAleatoire(pop, conf->taillePop));
        pop2 = _insererTete(pop2, _indivAleatoire(pop, conf->taillePop));
        croiserIndiv(pop2->indiv, pop2->next->indiv, conf->pCroise);
    }
    if (conf->taillePop % 2 == 0) {
        pop2 = _insererTete(pop2, _indivAleatoire(pop, conf->taillePop));
    }
    return pop2;
}

/**
 * @brief Vide une population en supprimant récursivement chaque individu
 * 
 * @param pop La population a vider
 */
void viderPop(Population *pop) {
    if (*pop != NULL) {
        viderPop(&(*pop)->next);
        supprIndiv(&(*pop)->indiv);
        free(*pop);
        *pop = NULL;
    }
}
