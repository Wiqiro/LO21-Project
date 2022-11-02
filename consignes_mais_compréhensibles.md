# Projet LO21

## Type individu

Liste chainée de bits de longeur donnée

- Initialiser aléatoirement liste de bits (itératif + récursif)
- Donner valeur d'une liste de bits
- Croiser deux listes (intervertir les éléments selon une proba donnée)
- Qualité d'un individu f1(x) = −X² avec : X = (x / 2^longIndiv) * (B−A) + A, A=−1, B=1, longIndiv=8

## Type population

Liste chainée d'individus
- Initialiser aléatoirement une population
- Trier la liste par qualité décroissante avec Quicksort
- Sélection des meilleurs individus en coupant la liste et en recopiant les 1ers individus après
- Croiser une population: créer une nouvelle population d’individus sélectionnés aléatoirement deux à deux dans P1 et croisés entre eux.

## Programme
>Initialiser la Population   
Répéter nGen fois   
Début   
Croiser la Population   
Trier la Population 
Sélectionner la Population  
Fin 
Afficher le meilleur Individu de la Population  

## Rapport
- Choix de conception et d'implémentation
- Algos + explications
- Jeux d'essais
- Commentaires sur les résultats