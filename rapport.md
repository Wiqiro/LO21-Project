# Rapport de projet LO21





## Introduction

Ce projet vise à implémenter des algorithmes génétiques simplifiés en utilisant des types abstraits de données *Individu* et *Population*, afin résoudre des problèmes d'optimisation. Dans le cadre de ce projet, les individus sont représentés par des listes de bits, ce qui facilite leur manipulation. Une population est quant à elle représentée par une liste d'individus.  
L'algorithme dans sa globalité consiste à sélectionner les meilleurs individus d'une population pour ensuite les "reproduire", créant une nouvelle génération, et ainsi de suite.



## I. Type abstrait *Individu*


#### Initialisation aléatoire de la liste de bits

L'algorithme d'initialisation aléatoire d'un doit créer une nouvelle liste de taille *longIndiv* dont chaque bit prend aléatoirement la valeur 0 ou 1 avec une probabilité égale. Il doit être réalisé en version itérative et récursive.

La version itérative est constituée d'une simple boucle qui ajoute une bit aléatoire en tete *longIndiv* fois:

```
Fonction initIndivI(longIndiv: Entier): Individu
Début:
	i: Individu <- Ø
	pour i: Entier de 0 à longIndiv - 1 faire
		i <- insérerTête(i, bitAléatoire(0.5))
	fait
	initIndivI <- i
Fin
```


La version récursive quant à elle ajoute un bit aléatoire en tete d'une liste aléatoire de taille *longIndiv-1* crée par un appel récursif à elle-même:

```
Fonction initIndivR(longIndiv: Entier): Individu
Début:
	si longIndiv = 0 alors
		initIndivR <- Ø
	sinon
		longIndiv <- insérerTête(initIndivR(longIndiv – 1), bitAléatoire(0.5))
	finsi		
Fin
```
On notera l'utilisation d'une fonction *bitAléatoire*, qui retourne un bit aléatoire selon la probabilité de tomber sur 1 passée en argument. Son implémentation est détaillée plus loin.

<hr>

#### Valeur d’un individu

Cet algorithme parcours la liste de l'individu afin d'en déterminer sa valeur, qui est une simple conversion de la liste en décimal. Il se résume à une "découverte" de la liste au fur et à mesure, en se basant sur le fait qu'ajouter un bit à un nombre binaire revient à multiplier revient à doubler sa valeur décimale et y ajouter la valeur du nouveau bit.
```
Fonction valeurIndiv(i: Individu): Entier
Début:
	e: IElem <- tete(i)
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

#### Fonctions supplémentaires


zyegfuiozdfi

sdqfqsf

sqf

sd

qf

qs

f

<hr>

## II. Type abstrait "Population"

#### Initialisation aléatoire de la liste d’individus

Cet algorithme est similaire à la version itérative de l'algorithme d'initialisation d'individu adapté à une population. Pour initialiser chaque individu, il fait appel à la fonction *initIndivI*.
```
Fonction initPop(taillePop: Entier, longIndiv; Entier): Population
Début:
	p: Population <- Ø
	pour i: Entier de 0 à taillePop faire
		p <- insérerTête(p, initIndivI(longIndiv))
	fait
Fin
```

<hr>

#### Tri de la liste à l’aide de *Quicksort*


Quicksort est un algorithme de tri qui récursif utilisant l'approche "divide and conquer". Il consiste à sélectionner un élément pivot et à  partitionner les autres éléments en deux sous-listes, selon s'ils sont inférieurs ou supérieurs au pivot. Les sous-listes sont ensuite triées récursivement, jusqu'à rencontrer le cas d'une liste vide ou d'un seul élément.

Cet algorithme est un algorithme de tri rapide et efficace, avec une complexité moyenne de O(n · log n), mais il peut dégénérer: dans le pire cas, il sera d'une complexité de O(n²). Selon ce que l'on souhaire trier, le choix du pivot peut jouer un rôle majeur dans la chance de rencontrer le pire cas. Par exemple, la méthode Mo3 (médiane des trois), qui consiste à choisir comme pivot la médiane de trois éléments de la liste, permet d'améliorer considérablement la stabilité de l'algorithme. Cependant, il faut prendre en compte que le choix du pivot est également couteux. Dans ce cas, nous aurons à trier au plus des populations de 200 individus: un choix stratégique de pivot aura un impact invisible sur le temps d'exécution de l'algorithme, d'autant plus qu'il aurait fallu calculer la valeur d'un individu 3x à chaque partitionnement pour la méthode Mo3. C'est pourquoi le pivot choisi est simplement l'élément en queue.

```
Fonction partitionner(tete: PElem, queue: PElem, longIndiv: Entier, fQualite: Fonction<Réel, Entier>): PElem
Début
	pivot: Réel <- fQualite(valeurIndiv(queue), longIndiv)
	i: PElem <- tete
	j: PElem <- tete

	tant que j ≠ queue faire
		si fQualite(valeurIndiv(j), longIndiv) > pivot alors
			echanger(i, j)
			i <- succ(i)
		finsi
		j <- succ(j)
	fait
	echanger(i, queue)
	partitionner <- i
Fin


Procedure quicksort(tete: PElem, queue: PElem, longIndiv: Entier, fQualite: Fonction<Réel, Entier>)
Début
	si queue ≠ Ø et tete ≠ queue et tete ≠ succ(queue)
		PElem p = partitionner(tete, queue, longIndiv, fQualite)
		quicksort(tete, précédent(p), longIndiv, fQualite)
		quicksort(succ(p), queue, longIndiv, fQualite)
	finsi
Fin
```
<hr>
#### Sélectionner les meilleurs individus



Recopier algo et expliquer les deux conditions dans la boucle

```
Procédure selectPop(p: Population, tSelect: Réel, taillePop: Entier)
Début
	nSelect: Entier <- tSelect · taillePop
	eParcours: PElem <- tete(p)
	eSelect: PElem <- Ø
	i: Entier <- 0
	tant que eParcours ≠ Ø faire
		eSelect <- tete(p)
		si i = tSelect alors
			i <- 0
			eSelect <- tete(p)
		finsi
		valeur(eParcours) <- valeur(eSelect)
		i <- i+1
		eParcours <- succ(eParcours)
		eSelect <- succ(eParcours)
	fait
Fin
```

<hr>
#### Croiser une population

Expliquer qu'on créé un 2e individu et le "raccourci" pris par croiserPop

```
Individu indivAleatoire(pop: Population, taillePop: Entier)
Début
	pos: Entier <- valAléatoire(0, taillePop)
	pour i de 0 à pos faire
		tete(pop) <- succ(tete(pop))
	fait
	indivAleatoire <- copierIndiv(valeur(pop))
Fin

Population croiserPop(pop: Population, taillePop: Entier, pCroise, Réel)
Début
	Population pop2 <- Ø
	pour i: Entier de 0 à taillePop/2 faire
		pop2 <- insererTete(pop2, indivAleatoire(pop, taillePop))
		pop2 <- insererTete(pop2, indivAleatoire(pop, taillePop))
		croiserIndiv(valeur(tete(pop2)), valeur(succ(tete(pop2))), pCroise)
	fait
	si taillePop % 2 = 0 alors
		pop2 <- insererTete(pop2, indivAleatoire(pop, taillePop))
	fait
	croiserPop <- pop2
Fin
```





## III. Implémentation en C

#### Implémentation du type *Individu*

Comme indiqué dans le sujet, le type *Bit* est un entier non signé sur 8 bits, équivalent au type *char*

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

#### Implémentation du type *Population*

Le type *Population*, quant à lui est implémenté sous la forme d'une liste doublement chainée. En effet, l'algorithme *Quicksort* demande de pouvoir visiter un élément précédent dans la liste. Il est bien sûr possible de l'implémenter sur une liste simplement chaînée mais cela demande d'utiliser des pointeurs supplémentaires, ce qui aurait pour effet le nombre d'opérations effectuées. De plus, l'utilisation d'une liste doublement chaînée pour la population a un impact négligeable sur la mémoire, étant donné que chaque élément de cette population contient déjà un individu.

```c
typedef struct pElem {
    Individu indiv;
    struct pElem *next;
    struct pElem *prev;
} PElem;

typedef PElem *Population;
```

<hr>

#### Structure *config*

Pour passer aux fonctions les paramètres du programme, la structure *config* a également été créée.

```c
struct config {
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
struct config conf; 
configurer(&conf); //Entrée des paramètres de la population
...
quicksort(pop, &conf);
selectPop(pop, &conf);
```

Seul un pointeur vers la structure est passée aux fonctions demandant plus d'un paramètre du programme pour éviter trop "d'empilement" lors des appels récursifs.

On notera également le pointeur sur fonction *fQualite* présent dans la structure, qui permet de choisir la fonction que l'on va appliquer pour calculer la qualité d'un individu lors de son tri. En l'occurence, il prendra les valeurs des adresses de *f1* ou *f2*.

<hr>

#### Fonction *bitAleatoire*

Je n'ai pas proposé d'algorithme pour cette foncton car elle dépend uniquement du language dans lequel elle est implémentée:

```c
static Bit _bitAleatoire(double prob) {
    return (rand() <= prob * RAND_MAX);
}
```

Elle est cependant intéressante car elle retourne un test booléen correspondant à un bit qui prendra la valeur 1 si la condition est vraie et 0 si elle est fausse. La fonction *rand()* renvoie un entier pseudo-aléatoire dans l'intervalle de 0 à *RAND_MAX*. Ainsi, la valeur renvoyée par la condition aura une probabilité égale à *prob* d'être un 1.

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

On remarquera que chaque élément libéré est remplacé par *NULL*, ce qui n'est pas obligatoire mais reste une bonne pratique.

Pour m'assurer que chaque parcelle de mémoire allouée est bien libérée, j'ai utilisé l'outil *valgrind*, disponible sous linux.

```
==29898== HEAP SUMMARY:
==29898==     in use at exit: 0 bytes in 0 blocks
==29898==   total heap usage: 686,802 allocs, 686,802 frees, 11,314,048 bytes allocated
==29898== 
==29898== All heap blocks were freed -- no leaks are possible
```

La dernière ligne nous indique que l'intégralité de la mémoire est bel et bien libérée

<hr>

#### Compilation du projet

Le projet est compilé sous linux à l'aide de l'outil *Make*, permettant d'automatiser la compilation. Un premier *Makefile* dans le répertoire *libs/ProjetLO21* va compiler une librairie dynamique *libProjetLO21.so* contenant les types *Individu* et *Population* ainsi que les opérations qui leur sont associées. 
Le *Makefile* à la racine du projet va quant à lui créer une exécutable *main* lié à la librairie *ProjetLO21*. Cela permet de de séparer la compilation de la librairie et du programme de test afin de pouvoir utiliser la librairie indépendamment dans d'autres programmes.

Pour compiler le projet dans sa globalité, il suffit de lancer le *Makefile* situé à la racine avec les options suivantes:

- *make*:  compile le programme avec la librairie *ProjetLO21*
- *make clean*: supprime l'intégralité des fichiers compilés
- *make run*: compile le programme et lance automatiquement l'exécutable *main* en liant la librairie
- *make check*: compile le programme et le lance avec la commande *valgrind* pour vérifier les leaks de mémoire

```
.
├── cli.c
├── cli.h
├── main.c
├── Makefile
└── libs
    └── ProjetLO21
        ├── config.h
        ├── individu.c
        ├── individu.h
        ├── Makefile
        ├── population.c
        └── population.h
```

<hr>

## IV. Résultats



#### Présentation des résultats

De manière à tester le programme, il est possible d'influencer sur les paramètres suivants:

- Longueur d'un individu *longIndiv* entre 8 et 16

- Probabilité de croisement d'un bit entre deux individus *pCroise* entre 0.1 et 0.9

- Taille de la population *taillePop* entre 20 et 200

- Taux de sélection *tSelect* entre 0.1 et 0.9

- Nombre de générations *nGen* entre 20 et 200

Le programme se présente sous cette forme une fois lancé:

```
Choisissez la longueur d'un individu (entre 8 et 16) 16
Choisissez la taille d'une population (entre 20 et 200) 200
Choisissez le nombre de générations (entre 20 et 200) 20
Choisissez la probabilité de croisement entre deux individus (entre 0.1 et 0.9) 0.5
Choisissez le taux de sélection d'une population (entre 0.1 et 0.9) 0.3
Choisissez la fonction de qualité à utiliser (f1 ou f2) f1
```

Après la validation, le programme exécute le boucle principale et affiche le meilleur individu de la population après 200 générations. Le résultat se présente sous cette forme:

```
Génération 200 / 200

Meilleur individu:
        Qualité: 1.216245
        Chaine: [0000101001000010]
```

J'ai exécuté le programme avec différents jeux d'essais, en faisant varier les différents paramètres pour déterminer leur influence sur les résultats obtenus

<hr>

#### Influence de la fonction qualité

Paramètres utilisés:  *longIndiv = 8	pCroise = 0.5	taillePop = 20	tSelect = 0.2	nGen = 200	f1*	

| Individu | Qualité   |
| -------- | --------- |
| 01100110 | -0.041260 |
| 01111101 | -0.000549 |
| 01111101 | -0.000549 |
| 10000000 | 0.000000  |
| 10000100 | -0.000977 |
| 10001101 | -0.010315 |
| 01111001 | -0.002991 |
| 10000001 | -0.000061 |
| 01110101 | -0.007385 |
| 01111100 | -0.000977 |

En changeant le paramètre *f1* -> *f2*:

| Individu | Qualité  |
| -------- | -------- |
| 00011000 | 0.580935 |
| 00000000 | 2.302585 |
| 00101010 | 0.101030 |
| 00000010 | 1.978466 |
| 00000000 | 2.302585 |
| 00000011 | 1.848826 |
| 00000000 | 2.302585 |
| 00010001 | 0.854747 |
| 00000000 | 2.302585 |
| 00000100 | 1.734080 |

On voit ici que...

<hr>

#### Influence de *longIndiv*

Paramètres utilisés:  *longIndiv = 8	pCroise = 0.5	taillePop = 80	tSelect = 0.2	nGen = 200,	f2*

| Individu | Qualité  |
| -------- | -------- |
| 00000000 | 2.302585 |
| 00000000 | 2.302585 |
| 00000000 | 2.302585 |
| 00000000 | 2.302585 |
| 00000000 | 2.302585 |
| 00000000 | 2.302585 |
| 00000000 | 2.302585 |
| 00000010 | 1.978466 |
| 00000000 | 2.302585 |
| 00000000 | 2.302585 |

En changeant le paramètre *longIndiv* = 8 -> 16:

| Individu| Qualité |
| :--------------- | :------- |
| 0000000000000001 | 2.301838 |
| 0000000000000010 | 2.301091 |
| 0000000000000010 | 2.301091 |
| 0000000000000000 | 2.302585 |
| 0000000000100000 | 2.278941 |
| 0000000000010000 | 2.290693 |
| 0000000000001000 | 2.296621 |
| 0000000000000000 | 2.302585 |
| 0000000000000010 | 2.301091 |
| 0000000000001000 | 2.296621 |

On remarque que, alors que les meilleurs individus de courte taille sont presque tous parfaits, alors que quand la simulation est lancée avec des individus de 16 bits, beaucoup ne sont pas parfaits. En effet, plus l'individu est complexe, plus il faudra d'itérations pour arriver à l'individu parfait.

Pour faire un parallèle la résolution de problèmes d'optimisation, plus un problème est complexe et plus il a de paramètres, plus il sera couteux de s'approcher de la solution idéale.

<hr>

#### Influence de *nGen*

Paramètres utilisés: *longIndiv = 16	pCroise = 0.9	taillePop = 80	tSelect = 0.9	nGen = 20,	f2*

| Individu         | Qualité  |
| ---------------- | -------- |
| 0000000000000000 | 2.302585 |
| 0000000010100011 | 2.187586 |
| 0000000001001011 | 2.248025 |
| 0000000000100000 | 2.278941 |
| 0000000001000001 | 2.255130 |
| 0000000000000000 | 2.302585 |
| 0000100010000000 | 1.336760 |
| 0000000000000000 | 2.302585 |
| 0000000000100000 | 2.278941 |
| 0000000000001011 | 2.294394 |

En changeant le paramètre *nGen* = 20 -> 200:

| Individu         | Qualité  |
| ---------------- | -------- |
| 0000000000000000 | 2.302585 |
| 0000000001000000 | 2.255843 |
| 0000000000000000 | 2.302585 |
| 0000000000000000 | 2.302585 |
| 0000000000000010 | 2.301091 |
| 0000000001000000 | 2.255843 |
| 0000000000000000 | 2.302585 |
| 0000000000000000 | 2.302585 |
| 0000000000000000 | 2.302585 |
| 0000000000000010 | 2.301091 |

Comme attendu, le paramètre *nGen* a une influence sur la valeur des meilleurs individus

<hr>

#### Influence de *pCroise*

Paramètres utilisés:  *longIndiv = 16	pCroise = 0.2	taillePop = 30	tSelect = 0.9	nGen = 20,	f2*

| Individu         | Qualité  |
| ---------------- | -------- |
| 0000000010011000 | 2.194944 |
| 0000100000001000 | 1.371512 |
| 0000000010000010 | 2.209825 |
| 0001001011000010 | 0.778626 |
| 0000000001011001 | 2.238162 |
| 0000000000001000 | 2.296621 |
| 0000000000000011 | 2.300345 |
| 0000001000000110 | 1.975227 |
| 0000000001100000 | 2.233267 |
| 0000000000000101 | 2.298854 |

En changeant le paramètre *pCroise* = 0.2 -> 0.5:

| Individu         | Qualité  |
| ---------------- | -------- |
| 0000000000000010 | 2.301091 |
| 0000000000001010 | 2.295136 |
| 0000000000000010 | 2.301091 |
| 0000000000001100 | 2.293653 |
| 0000000010000010 | 2.209825 |
| 0000000000000001 | 2.301838 |
| 0000000000000000 | 2.302585 |
| 0000000000000011 | 2.300345 |
| 0000000001000000 | 2.255843 |
| 0000000011001100 | 2.160628 |

<hr>

#### Influence de *taillePop*

Paramètres utilisés:  *longIndiv = 16	pCroise = 0.5	taillePop = 20	tSelect = 0.5	nGen = 200,	f2*

| Individu         | Qualité  |
| ---------------- | -------- |
| 0000000000100000 | 2.278941 |
| 0000010000100000 | 1.720620 |
| 0000000011110000 | 2.137542 |
| 0000000010001000 | 2.205745 |
| 0000001000011000 | 1.965572 |
| 0000000100001100 | 2.119948 |
| 0000001000010010 | 1.968780 |
| 0000000000001100 | 2.293653 |
| 0000001000100000 | 1.961311 |
| 0000000000001010 | 2.295136 |

En changeant le paramètre *taillePop* = 20 -> 80:

| Individu         | Qualité  |
| ---------------- | -------- |
| 0000000000000000 | 2.302585 |
| 0000000000000000 | 2.302585 |
| 0000000000000000 | 2.302585 |
| 0000000000000000 | 2.302585 |
| 0000000000000000 | 2.302585 |
| 0000000000000000 | 2.302585 |
| 0000000000000000 | 2.302585 |
| 0000000000000010 | 2.301091 |
| 0000000000000000 | 2.302585 |
| 0000000000000000 | 2.302585 |

<hr>


#### Influence de *tSelect*

Paramètres utilisés:  *longIndiv = 16	pCroise = 0.5	taillePop = 30	tSelect = 0.1	nGen = 20,	f2*

| Individu         | Qualité  |
| ---------------- | -------- |
| 0000010000000110 | 1.731543 |
| 0000100010001001 | 1.334202 |
| 0000001001000001 | 1.943924 |
| 0000000011110000 | 2.137542 |
| 0001000010000001 | 0.877322 |
| 0000010000110000 | 1.713958 |
| 0010000000000110 | 0.338346 |
| 0000110000100100 | 1.101479 |
| 0000000000001000 | 2.296621 |
| 0000010000101100 | 1.715619 |

En changeant le paramètre *tSelect* = 0.1 -> 0.9:

| Individu         | Qualité  |
| ---------------- | -------- |
| 0000000000001000 | 2.296621 |
| 0000000000000000 | 2.302585 |
| 0000000000000100 | 2.299599 |
| 0000000010100000 | 2.189588 |
| 0000000010001001 | 2.205066 |
| 0000000000100000 | 2.278941 |
| 0000000010000010 | 2.209825 |
| 0000000000100000 | 2.278941 |
| 0000000010001000 | 2.205745 |
| 0000000000000100 | 2.299599 |

<hr>

## Conclusion








JUSTIFIER LE FAIT QUE AVEC F1 LES MEILLEURS INDIVIDUS SONT PARFOIS DES 1



*William Imbert	-	Université de Technologie de Belfort-Montbéliard	-	https://github.com/Wiqiro*