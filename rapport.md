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
	indiv: Individu <- Ø
	pour i: Entier de 0 à longIndiv - 1 faire
		indiv <- insérerTête(indiv, bitAléatoire(0.5))
	fait
	initIndivI <- indiv
Fin

longIndiv: Entier: longueur de l'individu initialisé
indiv: Individu: nouvel individu
i: Entier: variable d'itération de 0 à longIndiv
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

longIndiv: Entier: longueur de l'individu initialisé
```
On notera l'utilisation d'une fonction *bitAléatoire*, qui retourne un bit aléatoire selon la probabilité de tomber sur 1 passée en argument. Son implémentation est détaillée plus loin.


<hr>

#### Valeur d’un individu

Cet algorithme parcours la liste de l'individu afin d'en déterminer sa valeur, qui est une simple conversion de la liste en décimal. Il se résume à une "découverte" de la liste au fur et à mesure, en se basant sur le fait qu'ajouter un bit à un nombre binaire revient à doubler sa valeur décimale et y ajouter la valeur du nouveau bit.
```
Fonction valeurIndiv(indiv: Individu): Entier
Début:
	e: IElem <- tete(indiv)
	val: Entier <- 0
	tant que e ≠ Ø faire
		val <- 2·val + valeur(e)
		e <- succ(e)
	fait
	valeurIndiv <- val
Fin

indiv: Individu: individu dont la valeur est calculée
e: IElem: variable d'itération traversant l'individu indiv
val: Entier: valeur de l'individu
```
<hr>

#### Qualité d’un individu

La qualité d’un individu est calculée selon les fonction *f1* et *f2* données par 
`f1(x) = -X²` et `f2(x) = -ln(X)`
avec `X = (x/2^longIndiv)(B-A) + A`

D'un point de vue algoritmique, cela donne:

```
Fonction f1(valIndiv: Entier, longIndiv: Entier): Entier
Début
	X: Entier <- 2(valIndiv / 2^longIndiv) - 1
	f1 <- -X²
Fin

Fonction f2(valIndiv: Entier, longIndiv: Entier): Entier
Début
	X: Entier <- 4.9(valIndiv / 2^longIndiv) + 0.1
	f1 <- -ln(X)
Fin

valIndiv: valeur de l'individu dont la qualité est calculée
longIndiv: longueur de l'individu dont la qualité est calculée
X: Réel: mise à l'échelle préalable au calcul de f1 et f2
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

indiv1: Individu, indiv2: Individu: individus à croiser entre eux
pCroise: Réel: probabilité d'échanger les éléments de chaque liste à chaque itération
```

<hr>

#### Fonctions supplémentaires

Ces fonctions ont été créées pour aider à la manipulation du type *Individu* et sont utilisées par les fonctions du type *Population*:

- CopierIndiv: fonction récursive qui retourne une copie d'un individu

  ```
  Fonction copierIndiv(indiv: Individu): Individu
  Début
  	si indiv ≠ Ø alors
  		copierIndiv <- insererTete(copierIndiv(succ(tete(indiv))), valeur(indiv))
  	sinon
  		copierIndiv <- Ø
  	finsi
  Fin
  
  indiv: Individu: individu à copier
  ```

- Remplacer Indiv: procédure récursive qui remplace un individu par les bits d'un autre individu, sans en créer un nouveau

  ```
  Procédure remplacerIndiv(indiv: Individu, modele: Individu)
  Début
  	si indiv ≠ Ø et modele ≠ Ø alors
  		valeur(tete(indiv)) <- valeur(tete(modele))
  		remplacerIndiv(succ(tete(indiv)), succ(tete(modele)))
  	finsi
  Fin
  
  indiv: Individu: individu recevant la chaine du modèle
  modele: Individu: individu à recopier dans indiv
  ```
  
  

<hr>

## II. Type abstrait "Population"

#### Initialisation aléatoire de la liste d’individus

Cet algorithme est similaire à la version itérative de l'algorithme d'initialisation d'individu adapté à une population. Pour initialiser chaque individu, il fait appel à la fonction *initIndivI*.
```
Fonction initPop(taillePop: Entier, longIndiv; Entier): Population
Début:
	pop: Population <- Ø
	pour i: Entier de 0 à taillePop faire
		pop <- insérerTête(pop, initIndivI(longIndiv))
	fait
Fin

taillePop: Entier: taille de la population à initialiser
longIndiv: Entier: longueur des individus de la population
pop: Population: nouvelle population créée
i: Entier: variable d'itération de 0 à taillePop
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
		PElem e = partitionner(tete, queue, longIndiv, fQualite)
		quicksort(tete, précédent(e), longIndiv, fQualite)
		quicksort(succ(e), queue, longIndiv, fQualite)
	finsi
Fin

tete: PElem: tete assumée par l'algorithme de la liste à trier
queue: PElem: queue assumée par l'algorithme de la liste à trier
longIndiv: Entier: longueur des individus à trier
fQualite: Fonction: fonction de qualité utilisée (f1 ou f2)
pivot: Réel: valeur de l'élément pris en pivot (dernier élément)
i: PElem, j: PElem: variables d'itération utilisées lors du partitionnement de la liste
e: élément correspondant au pivot une fois la liste partitionnée
```
<hr>

#### Sélectionner les meilleurs individus



Cette procédure a pour but de sélectionner les meilleurs individus d'une population donnée selon un taux *tSelect*. Dans un premier temps, il calcule le nombre d'individu à recopier, puis remplace les individus de la population en boucle par les *nSelect* premiers individus. Pour cela, deux variables d'itération sont nécessaires: la première, *eSelect*, boucle sur les *nSelect* premiers éléments tandis que *eParcours* parcours toute la population pour y recpoier la valeur de *eSelect*.

On notera que la mémoire n'est pas réallouée et qu'aucun individu n'est créé: on remplace simplement les bits des individus de la population au fur et à mersure

```
Procédure selectPop(pop: Population, tSelect: Réel, taillePop: Entier)
Début
	nSelect: Entier <- tSelect · taillePop
	si nSelect = 0 alors nSelect <- 1 finsi
	
    eParcours: PElem <- tete(pop)
    eSelect: PElem <- tete(pop)
    i: Entier <- 0
        
    tant que eParcours ≠ Ø faire
        si i >= tSelect alors
            remplacerIndiv(valeur(tete(eParcours)), valeur(tete(eSelect)))
        finsi
        eSelect <- succ(eSelect)
        eParcours <- succ(eParcours)
            
        i <- i + 1
        si i % nSelect = 0 alors
            eSelect <- tete(pop)
        finsi
    fait
Fin

pop: Population: population à sélectionner
tSelect: Réel: taux de sélection de la population à sélectionner
taillePop: Entier: taille de la population à sélectionner
nSelect: Entier: nombre d'éléments à sélectionner
eParcours: PElem: variable d'itération sur pop recevant la valeur de eSelect au long du parcours
eSelect: PElem: variable d'itération sur les nSelect premiers éléments de pop
i: Entier: entier correspondant à la place de eSelect dans pop
```

<hr>

#### Croiser une population 

L'algorithme de croisement d'une population créé une nouvelle population constituée des individus de la population d'origine sélectionnés aléatoirement et croisés deux à deux. On créé la nouvelle liste en insérant en tête deux éléments de la liste d'origine, puis en les croisant, et ainsi de suite jusqu'a ce que la liste soit de taille *taillePop*. On remarque que si *taillePop* est impaire, le dernier élément de la liste est sélectionné aléatoirement mais n'est pas croisé, car il n'a pas de "partenaire".

```
Individu indivAleatoire(pop: Population, taillePop: Entier)
Début
	pos: Entier <- valAléatoire(0, taillePop)
	pour i: Entier de 1 à pos faire
		tete(pop) <- succ(tete(pop))
	fait
	indivAleatoire <- copierIndiv(valeur(pop))
Fin

Population croiserPop(pop: Population, taillePop: Entier, pCroise, Réel)
Début
	Population pop2 <- Ø
	pour j: Entier de 0 à taillePop/2 faire
		pop2 <- insererTete(pop2, indivAleatoire(pop, taillePop))
		pop2 <- insererTete(pop2, indivAleatoire(pop, taillePop))
		croiserIndiv(valeur(tete(pop2)), valeur(succ(tete(pop2))), pCroise)
	fait
	si taillePop % 2 = 0 alors
		pop2 <- insererTete(pop2, indivAleatoire(pop, taillePop))
	fait
	croiserPop <- pop2
Fin

pop: Population: population à croiser
taillePop: Entier: taille de la population à croiser
pCroise: Réel: probabilité d'échanger chaque bit de chaque individu croisé
pos: Entier: position de l'élement sélectionné aléatoirement dans pop
i: Entier: variable d'itération sur pop de 1 à pos
j: Entier: variable d'itération sur pop de 0 à taillePop/2
pop2: Population: nouvelle population croisée
```

<hr>

## III. Implémentation en C

#### Implémentation du type *Individu*

Comme indiqué dans le sujet, le type *Bit* est représenté un entier non signé sur 8 bits, équivalent au type *char*

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

Le type *Population*, quant à lui est implémenté sous la forme d'une liste doublement chainée. En effet, l'algorithme *Quicksort* demande de pouvoir visiter un élément précédent dans la liste. Il est bien sûr possible de l'implémenter sur une liste simplement chaînée mais cela demande d'utiliser des pointeurs supplémentaires, ce qui aurait pour effet d'augmenter le nombre d'opérations effectuées. De plus, l'utilisation d'une liste doublement chaînée pour la population a un impact négligeable sur la mémoire, étant donné que chaque élément de cette population contient déjà un individu.

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

Dans ce projet, la mémoire est libérée à l'aide d'une fonction récursive pour les deux types. Libérer la mémoire allouée pour une population nécessite également de libérer chaque individu. On remarquera que chaque élément libéré est remplacé par *NULL*, ce qui n'est pas obligatoire mais reste une bonne pratique.

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
Choisissez le nombre de générations (entre 20 et 200) 200
Choisissez la probabilité de croisement entre deux individus (entre 0.1 et 0.9) 0.5
Choisissez le taux de sélection d'une population (entre 0.1 et 0.9) 0.3
Choisissez la fonction de qualité à utiliser (f1 ou f2) f1
```

Après la validation, le programme exécute le boucle principale et affiche le meilleur individu de la population après *nGen* générations. Le résultat se présente sous cette forme:

```
Génération 200 / 200

Meilleur individu:
        Qualité: 1.216245
        Chaine: [0000101001000010]
```

J'ai exécuté le programme avec différents jeux d'essais, en faisant varier les différents paramètres pour déterminer leur influence sur les résultats obtenus. Dans les tableaux suivants, chaque ligne correspond au meilleur individu trouvé par le programme, exécuté 10 fois. Les paramètres ont été choisis pour mettre en valeur l'influence de chaque paramètre sur le résultat, mais ces variations peuvent être plus dures à observer dans d'autres configurations.

<hr>

#### Influence de la fonction qualité

Paramètres utilisés:  *longIndiv = 8	pCroise = 0.5	taillePop = 20	tSelect = 0.2	nGen = 200	f1*	

| Individu         | Qualité   |
| ---------------- | --------- |
| 0111111111111111 | -0.000000 |
| 0111111111111110 | -0.000000 |
| 0111111111111111 | -0.000000 |
| 0111111111111111 | -0.000000 |
| 0111111111111111 | -0.000000 |
| 1000000000000000 | -0.000000 |
| 0111111111111111 | -0.000000 |
| 1000000000001010 | -0.000000 |
| 0111111011111111 | -0.000062 |
| 1000000000100000 | -0.000001 |

En changeant le paramètre *f1* -> *f2*:

| Individu         | Qualité  |
| ---------------- | -------- |
| 0000000000000000 | 2.302585 |
| 0000000000000000 | 2.302585 |
| 0000000000100000 | 2.278941 |
| 0000000000000100 | 2.299599 |
| 0000000000000000 | 2.302585 |
| 0000000000000000 | 2.302585 |
| 0000000010000000 | 2.211189 |
| 0000000000000000 | 2.302585 |
| 0000000000000000 | 2.302585 |
| 0000000000000000 | 2.302585 |

On voit ici que l'individu idéal n'est pas le même suivant la fonction utilisée. Pour la fonction f1, il semble être une liste de bit tous égaux à l'exeption du premier, avec une qualité se rapprochant de 0 par le négatif. Pour f2, on semble tendre vers une liste composée uniquement de 0, avec une qualité de 2.303.

<hr>

#### Influence de *longIndiv*

Paramètres utilisés:  *longIndiv = 8	pCroise = 0.5	taillePop = 80	tSelect = 0.2	nGen = 200,	f2*

| Individu | Qualité  |
| :------- | :------- |
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

Comme attendu, le paramètre *nGen* a une influence sur la qualité du meilleurs individu: plus le nombre de générations est élevé et plus la qualité des individus est élevée. En l'occurence, on décuple le nombre de tri et de sélections de la population. Le poid de ce paramètre dans le résultat n'est cependant pas aussi élevé que ce à quoi on pourrait s'attendre, et il est souvent inutile d'aller au delà de 200 générations.

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

On observe que la qualité du meilleur individu est maximisée lorsque le paramètre *pCroise* est proche de 0.5, c'est à dire que la probabilité de croiser chaque bit de deux individus lors du croisement est maximisée. 

On notera qu'augmenter encore *pCroise* n'aura pas pour effet d'augmenter la qualité des individus, mais inversement: croiser deux individus avec une probabilité *pCroise* très élevée revient à un échange des deux individus, ce qui n'a pas d'effet comparé à une abscence de croisement. De ce fait, le résultat sera équivalent avec *pCroise* = 0.2 et *pCroise* = 1 - 0.2.

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

*taillePop* est le paramètre ayant la plus grande influence sur le résultat. Comme le montrent les tableaux ce dessus, les meilleurs individus d'une population de 20 individus après 200 générations sont assez aléatoires et on ne trouve aucun individu parfait, tandis qu'avec une population de 80 individus, la majorité des individus sont parfaits. On remarquera qu'il est plus efficace d'augmenter *taillePop* que *nGen*, du moins dans le cadre de ce projet.

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

On voit que l'augmentation de *tSelect* a augmenté la qualité des individus. Cela peut paraitre contradictoire, car un taux de sélection plus faible devrait sélectionner de meilleurs individus. Pour expliquer cela, on peut supposer qu'un taux de sélection faible serait trop "restrictif" en gardant des individus similaires, limitant donc les chances d'obtenir de meilleurs muations avec un croisement.

<hr>

## Conclusion

Nous avons vu l'intégralité des algorithmes permettant de mettre en oeuvre cette version simplifiée des algorithmes d'optimisation, ainsi que leur implémentation dans le language C. Nous avons ainsi pu observer l'influence des différents paramètres dans le résultat du programme.

Certains résultats m'ont personnellement surpris, notamment sur l'influence massive de la taille de la population sur la qualité du résultat, ou encore celle de *tSelect*, qui était opposée à mes attentes.

Pour creuser le sujet, il serait intéressant de pousser ces algorithmes vers des vrais algorithmes d'optimisation pour mieux comprendre leur contexte et leur utlilité, notamment avec des caractères autres que des bits.



*William Imbert	-	Université de Technologie de Belfort-Montbéliard	-	https://github.com/Wiqiro*