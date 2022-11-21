#include "population.h"

Population p_insert_head(Population p, Individual i) {
    Population new_p = (Population) malloc(sizeof(IndivListElem));
    new_p->next = p;
    new_p->indiv = i;
    if (p != NULL) {
        p->prev = new_p;
    }
    return new_p;
}

Population random_indiv_list_init_I(u_int32_t pop_size, u_int8_t indiv_size) {
    Population p = NULL;
    for (int i=0; i<pop_size; i++) {
        p = p_insert_head(p, random_bit_list_init_I(indiv_size));
    }
    return p;
}

void print_population(Population p) {
    IndivListElem* e = p;
    int8_t i = 0;
    while (e != NULL) {
        print_bitlist(e->indiv);
        e = e->next;
        if (i == 8) {
            printf("\n");
            i = 0;
        } else {
            printf(" ");
            i++;
        }
    }
}

static void _swap(IndivListElem* a, IndivListElem* b) {
    Individual tmp = a->indiv;
    a->indiv = b->indiv;
    b->indiv = tmp;
}

static IndivListElem* _partition(IndivListElem *l, IndivListElem *h) {

    double x = f1(bit_list_value(h->indiv), SIZE);

    IndivListElem *i = l;

    for (IndivListElem *j = l; j != h; j = j->next) {
        if (f1(bit_list_value(j->indiv), SIZE) > x) {
            _swap(i, j);
            i = i->next;
        }
    }
    _swap(i, h);
    return i;
}


void quicksort(IndivListElem* l, IndivListElem *h) {
    if (h != NULL && l != h && l != h->next) {
        IndivListElem *p = _partition(l, h);
        quicksort(l, p->prev);
        quicksort(p->next, h);
    }
}

void pop_select(Population p, u_int8_t t_select) {

    IndivListElem* e_select = p;
    u_int8_t i = 0;

    for (IndivListElem* e = p; e != NULL; e = e->next) {
        if (i == t_select) {
            i = 0;
            e_select = p;
        }
        e->indiv = e_select->indiv;
        i++;
        e_select = e_select->next;
    }
}

/* Population cross_pop(Population p) {
    
} */

void free_pop(Population *p) {
    if (*p != NULL) {
        free_pop(&(*p)->next);
        free_indiv(&(*p)->indiv);
        free(*p);
        *p = NULL;
    }
}