#include "cli.h"

/**
 * @brief Efface la console
 * 
 */
void clear() {
    system("clear");
}

/**
 * @brief Affiche la chaine de bit correspondante à un individu
 * 
 * @param indiv Individu à afficher
 * @param conf Passage par adresse des parametres du programme
 */
void afficherIndiv(Individu indiv, struct config *conf) {
    printf("[");
    IElem* pop = indiv;
    while (pop != NULL) {
        printf("%d", pop->val);
        pop = pop->next;
    }
    printf("]\n");
}


/**
 * @brief Permet l'entrée de la configuration du programme
 * 
 * @param conf Passage par adresse des parametres à remplir
 */
void configurer(struct config *conf) {
    char buffer[64];

    do {
        printf("Choisissez la longueur d'un individu (entre 8 et 16) ");
        fgets(buffer, 64, stdin);
        conf->longIndiv = strtoul(buffer, NULL, 10);
    } while (conf->longIndiv < 8 || conf->longIndiv > 16);

    do {
        printf("Choisissez la taille d'une population (entre 20 et 200) ");
        fgets(buffer, 64, stdin);
        conf->taillePop = strtoul(buffer, NULL, 10);
    } while (conf->taillePop < 20 || conf->taillePop > 200);
    
    do {
        printf("Choisissez le nombre de générations (entre 20 et 200) ");
        fgets(buffer, 64, stdin);
        conf->nGen = strtoul(buffer, NULL, 10);
    } while (conf->nGen < 20 || conf->nGen > 200);

    do {
        printf("Choisissez la probabilité de croisement entre deux individus (entre 0.1 et 0.9) ");
        fgets(buffer, 64, stdin);
        conf->pCroise = strtof(buffer, NULL);
    } while (conf->pCroise < 0.1 || conf->pCroise > 0.9);

    do {
        printf("Choisissez le taux de sélection d'une population (entre 0.1 et 0.9) ");
        fgets(buffer, 64, stdin);
        conf->tSelect = strtof(buffer, NULL);
    } while (conf->tSelect < 0.1 || conf->tSelect > 0.9);

    do {
        printf("Choisissez la fonction de qualité à utiliser (f1 ou f2) ");
        fgets(buffer, 64, stdin);
    } while (buffer[0] != 'f' || (buffer[1] != '1' && buffer[1] != '2') || buffer[2] != '\n');
    if (buffer[1] == '1') {
        conf->fQualite = f1;
    } else {
        conf->fQualite = f2;
    }
}