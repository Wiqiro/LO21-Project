#include "individu.h"


/**
 * @brief Insere un bit en tete d'un individu
 * 
 * @param indiv L'individu recevant le nouvel élément
 * @param val La valeur du bit (0 ou 1)
 * @return Individu un pointeur sur la tete du nouvel individu
 */
Individu insererTeteIndiv(Individu indiv, Bit val) {
    Individu new_i = (Individu) malloc(sizeof(IElem));
    *new_i = (IElem) {.next = indiv, .val = val};
    return new_i;
}

/**
 * @brief Retourne un bit aléaoire selon un probabilité donnée
 * 
 * @param prob Probabilité pour le bit d'être 1
 * @return Bit
 */
static Bit _bitAleatoire(double prob) {
    return (rand() <= prob * RAND_MAX);
}

/**
 * @brief Initialise aléatoirement un nouvel individu de manière itérative
 * 
 * @param longIndiv Longueur de l'individu à initialiser
 * @return Individu un pointeur sur la tête du nouvel individu
 */
Individu initIndivI(uint8_t longIndiv) {
    Individu indiv = NULL;
    for (uint8_t x=0; x<longIndiv; x++) {
        indiv = insererTeteIndiv(indiv, _bitAleatoire(0.5));
    }
    return indiv;
}

/**
 * @brief Initialise aléatoirement un nouvel individu à l'aide d'un appel récursif
 * créant un individu de taille longIndiv - 1
 * 
 * @param longIndiv Longueur de l'individu à initialiser
 * @return Individu un pointeur sur la tête du nouvel individu
 */
Individu initIndivR(uint8_t longIndiv) {
    if (longIndiv == 0) {
        return NULL;
    } else {
        return insererTeteIndiv(initIndivR(longIndiv - 1), rand()%2);
    }
}

/**
 * @brief Créé récursivement une copie d'un invividu en réallouant la mémoire qui lui est associée 
 * 
 * @param indiv Individu à copier
 * @return Individu pointeur vers la tête du nouvel individu
 */
Individu copierIndiv(Individu indiv) {
    if (indiv != NULL) {
        return insererTeteIndiv(copierIndiv(indiv->next), indiv->val);
    } else {
        return NULL;
    }
}

/**
 * @brief Remplace les valeurs d'un nouvel individu par les valeurs d'un individu donné
 * 
 * @param indiv Individu recevant les valeurs du modèle
 * @param modele Individu modèle
 */
void remplacerIndiv(Individu indiv, Individu modele) {
    if (indiv != NULL && modele != NULL) {
        indiv->val = modele->val;
        remplacerIndiv(indiv->next, modele->next);
    }
}

/**
 * @brief Calcul de la valeur d'individu, i.e. la conversion en décimale de la liste
 * 
 * @param indiv Individu dont la valeur est calculée
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

/**
 * @brief Calcul de la qualité d'un individu
 * 
 * @param indiv Individu dont la qualité est calculée
 * @param conf Passage par adresse des parametres du programme
 * @return double qualité de l'individu
 */
double qualiteIndiv(Individu indiv, struct config *conf) {
    return conf->fQualite(valeurIndiv(indiv), conf->longIndiv);
}

/**
 * @brief Première fonction de qualité
 * 
 * @param valIndiv Valeur de l'individu
 * @param longIndiv Longueur de l'individu
 * @return double qualité de l'individu
 */
double f1(double valIndiv, uint8_t longIndiv) {
    double X = (valIndiv / (1 << longIndiv)) * 2 - 1;
    return -X * X;
}

/**
 * @brief Seconde fonction de qualité
 * 
 * @param valIndiv Valeur de l'individu
 * @param longIndiv Longueur de l'individu
 * @return double qualité de l'individu
 */
double f2(double valIndiv, uint8_t longIndiv) {
    double X = (valIndiv / (1 << longIndiv)) * 4.9 + 0.1;
    return -log(X);
}

/**
 * @brief Echange les valeurs de deux éléments de listes d'individu
 * 
 * @param a Elément à échanger avec b
 * @param b Elément à échanger avec a
 */
static void _echanger(IElem *a, IElem *b) {
    Bit tmp = a->val;
    a->val = b->val;
    b->val = tmp;
}

/**
 * @brief Croise deux individus avec une probabilité pCroise d'échanger 
 * les éléments des deux listes à chaque position
 * 
 * @param indiv1 Individu à croiser avec indiv2
 * @param indiv2 Individu à croiser avec indiv1
 * @param pCroise Probabilité d'echanger deux éléments
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
 * @brief Supprime un individu en libérant récursivement la mémoire allouée à chaque élément
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