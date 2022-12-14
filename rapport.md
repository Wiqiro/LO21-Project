# Rapport de projet LO21



## Introduction

Le projet vise à implémenter des algorithmes génétiques simplifiés en utilisant des types abstraits de données *Individu* et *Population* pour résoudre des problèmes d'optimisation. Dans le cadre de ce projet, les individus sont représentés par des listes de bits, ce qui facilite leur manipulation. Une population est quant à elle représentée par une liste d'individus.  
L'algorithme dans sa globalité consiste à sélectionner les meilleurs individus d'une population pour ensuite les "reproduire", créant une nouvelle génération, et ainsi de suite.



## I. Type abstrait "Individu"



Le type “Individu” est représenté par une suite de bits de longueur *longIndiv* donnée.

<hr>


#### Initialisation aléatoire de la liste de bits

L'algorithme d'initialisation aléatoire d'un doit créer une nouvelle liste de taille longIndiv dont chaque bit prend aléatoirement la valeur 0 ou 1 avec une probabilité égale.
Il doit également être donné en version itérative et récursive.

La version itérative est constituée d'une simple boucle qui ajoute une bit aléatoire en tête *longIndiv* fois:

```
Fonction indivInitI(longIndiv: Entier): Individu
Début:
	i: Individu <- Ø
	pour i: Entier de 0 à longIndiv - 1 faire
		i <- insérerTête(i, bitAléatoire(0.5))
	fait
	indivInitI <- i
Fin
```


La version récursive quant à elle ajoute un bit aléatoire en tête d'une liste aléatoire de taille *longIndiv-1* crée par un appel récursif à elle-même:

```
Fonction indivInitR(longIndiv: Entier): Individu
Début:
	si longIndiv = 0 alors
		indivInitR <- Ø
	sinon
		longIndiv <- insérerTête(indivInitR(longIndiv – 1), bitAléatoire())
	finsi		
Fin
```
<hr>

#### Valeur d’un individu

Cet algorithme parcours la liste d'individu afin d'en déterminer sa valeur, qui est une simple conversion de la liste en décimal. Il se résume à une "découverte" de la liste au fur et à mesure, où l'on multiplie par 2 la valeur de la liste déjà parcourue à chaque passage sur un nouvel élément (ajouter un chiffre à un nombre binaire revient à multiplier revient à doubler sa valeur décimale et y ajouter la valeur du nouveau bit).
```
Fonction valeurIndiv(i: Individu): Entier
Début:
	e: IElem <- tête(i)
	val: Entier <- 0
	tant que e ≠ Ø faire
		val <- 2·val + valeur(e)
		e <- succ(e)
	fait
	valeurIndiv <- val
Fin
```
<hr>

#### Qualité d’un individu

La qualité d’un individu est calculée selon les fonction *f1* et *f2* données par 
`f1(x) = -X²` et `f2(x) = -ln(X)`
avec `X = (x/2^longIndiv)(B-A) + A`

```
Fonction qualite(i: Individu, f(x): Fonction)
Début

Fin
```

<hr>

#### Croisement de deux individus

La fonction de croisement de deux individus parcours chaque individu parallèlement avec une probabilité *pCroise* d'échanger les éléments des deux listes à chaque itération.
```
Procédure croiserIndiv(indiv1: Individu, indiv2: Individu, pCroise: Réel)
Début
	tant que indiv1 ≠ Ø et  indiv2 ≠ Ø faire
		si bitAléatoire(pCroise) = 1 alors
			echanger(indiv1, indiv2)
		finsi
		indiv1 <- succ(indiv1)
		indiv2 <- succ(indiv2)
	fait
Fin
```

<hr>

## II. Type abstrait "Population"



#### Initialisation aléatoire de la liste d’individus

Cet algorithme est similaire à la version itérative de l'algorithme d'initialisation d'individu adapté à une population. Pour initialiser chaque individu, il fait appel à la fonction *indivInitI*.
```
Fonction popInit(taillePop: Entier, longIndiv; Entier): Population
Début:
	p: Population <- Ø
	pour i: Entier de 0 à taillePop faire
		p <- insérerTête(p, indivInitI(longIndiv))
	fait
Fin
```

<hr>

#### Tri de la liste à l’aide de Quicksort

```
Fonction partitionner(d: PElem, f: PElem): PElem
Début
	pivot: Réel <- qualité(valeur(f), longIndiv)
	i: PElem <- d
	j: PElem <- d

	tant que j ≠ f faire
		si qualité(valeur(j), longIndiv) > pivot alors
			échanger(i, j)
			i <- succ(i)
		finsi
		j <- succ(j)
	fait
	échanger(i, f)
	partitionner <- i
Fin

Procédure quicksort(d: PElem, f: PElem)
Début
	si d ≠ Ø et d ≠ f et d ≠ succ(f)
		PElem p = partition(d, f)
		quicksort(d, précédent(p))
		quicksort(succ(p), f)
	finsi
Fin
```
<hr>

#### Sélectionner les meilleurs individus

```
Procédure selectPop(p: Population, tSelect: Réel)
Début
	nSelect: Entier <- tSelect · taillePop
	eParcours: PElem <- tête(p)
	eSelect: PElem <- Ø
	i: Entier <- 0
	tant que eParcours ≠ Ø faire
		eSelect <- tête(p)
		si i = tSelect alors
			I <- 0
			eSelect <- tête(p)
		finsi
		valeur(eParcours) <- valeur(eSelect)
		i <- i+1
		eParcours <- succ(eParcours)
		eSelect <- succ(eParcours)
	fait
Fin
```

<hr>

## III. Implémentation en C



#### Implémentation du type "Individu"

Comme demandé dans la, le type *Bit* est un entier non signé sur 8 bits

```c
typedef uint8_t Bit;
```

Le type *Individu* est implémenté comme une liste simplement chainée car les opérations qui lui sont associées ne demandent jamais de visiter un élément précédent.
```c
typedef struct iElem {
    Bit val;
    struct iElem *next;
} IElem;

typedef IElem* Individu;
```

<hr>

#### Implémentation du type "Population"

Le type *Population*, quant à lui est implémenté sous la forme d'une liste doublement chainée. En effet, l'algorithme *Quicksort* demande de pouvoir visiter un élément précédent dans la liste. Il est bien sûr possible de l'implémenter sur une liste simplement chaînée mais cela demande d'utiliser des pointeurs supplémentaires dans la liste, ce qui aurait pour effet le nombre d'opérations effectuées. De plus, l'utilisation d'une liste doublement chaînée pour la population a un impact négligeable sur la mémoire, étant donné que chaque élément de cette population contient déjà un individu.

```c
typedef struct pElem {
    Individu indiv;
    struct pElem *next;
    struct pElem *prev;
} PElem;

typedef PElem *Population;
```

<hr>
#### Structure de configuration

Pour passer aux fonctions les paramètres du programme, la structure *configuration* a également été créée.

```c
struct configuration {
    uint8_t longIndiv;
    uint16_t taillePop;
    uint16_t nGen;
    float pCroise;
    float tSelect;
    double (*fQualite)(double, uint8_t);
};
```

 Voici un exemple de son utilisation:

```c
struct configuration config; 
configurer(&config); //entrée des paramètres de la population
...
quicksort(pop, &config);
selectPop(pop, &config);
```

Seul un pointeur vers la structure est passée aux fonctions demandant plus d'un paramètre du programme pour éviter trop "d'empilement" lors des appels récursifs.+

On notera également le pointeur sur fonction *fQualite* présent dans la structure, qui permet de choisir la fonction que l'on va appliquer pour calculer la qualité d'un individu lors de son tri. En l'occurence, il prendra les valeurs des adresses de *f1* ou *f2*.

<hr>

#### Gestion de la mémoire

Dans un tel programme, il est souvent nécessaire d'allouer dynamiquement de la mémoire, notamment à l'aide de la fonction *malloc*. Par conséquent, il est égalament important de penser à libérer cette mémoire. Dans le cas des listes chaînées, il faut parcourir l'intégralité de la liste en libérant chaque case mémoire allouée.

Dans ce projet, la mémoire est libérée à l'aide d'une fonction récursive pour les deux types. Libérer la mémoire allouée pour une population nécessite également de libérer chaque individu:

```c
void viderPop(Population *pop) {
    if (*pop != NULL) {
        viderPop(&(*pop)->next);
        supprIndiv(&(*pop)->indiv);
        free(*pop);
        *pop = NULL;
    }
}
```

Pour m'assurer que chaque parcelle de mémoire allouée est bien libérer, j'ai utilisé l'outil *valgrind*, disponible sous linux.

```
==29898== HEAP SUMMARY:
==29898==     in use at exit: 0 bytes in 0 blocks
==29898==   total heap usage: 686,802 allocs, 686,802 frees, 11,314,048 bytes allocated
==29898== 
==29898== All heap blocks were freed -- no leaks are possible
```

L'information *no leaks are possible* indique que l'intégralité de la mémoire est bel et bien libérée

<hr>

#### Compilation du projet

Le projet est compilé sous linux à l'aide d'un *Makefile*, outil permettant d'automatiser la compilation. A la compilation, une librairie dynamique *libProjetLO21.so*, contenant les types *Individu* et *Population* ainsi que les opérations qui leur sont associées.

Un exécutable *main* lié à la librairie *ProjetLO21* est également créé, permettant de manipuler les types de la librairie.

Les options de compilation sont les suivantes

*make*: compile le programme en créant la librairie