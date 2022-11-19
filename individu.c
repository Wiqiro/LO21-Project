#include "individu.h"


Individual insert_head(Individual l, Bit val) {
    Individual new_i = (Individual) malloc(sizeof(BitListElem));
    new_i->next = l;
    new_i->val = val;
    return new_i;
}

Individual random_bit_list_init_I(int8_t size) {
    Individual l = NULL;
    for (int i=0; i<size; i++) {
        l = insert_head(l, rand()%2);
    }
    return l;
}

Individual random_bit_list_init_R(int8_t size) {
    if (size == 0) {
        return NULL;
    } else {
        return insert_head(random_bit_list_init_R(size - 1), rand()%2);
    }
}

void print_bitlist(Individual l) {
    printf("[");
    BitListElem* p = l;
    while (p != NULL) {
        printf("%d", p->val);
        p = p->next;
    }
    printf("]");
    printf("%.2f ", f1(bit_list_value(l), SIZE));
}


u_int64_t bit_list_value(Individual l) {
    BitListElem* p = l;
    u_int64_t value = 0;
    while (p != NULL) {
        value = 2*value + p->val;
        p = p->next;
    }
    return value;
}

//make pow 2 function
double f1(u_int64_t x, u_int8_t size) {
    double X = (x / (pow(2, size))) * (1-(-1)) + (-1);
    //printf(" %.2f", -X * X);

    return -(X * X);

}

void cross_bitlists(Individual l1, Individual l2, float prob) {
    while (l1 != NULL && l2 != NULL) {
        float x = (float) (rand()%10000) / 10000;
        if (x < prob) {
            Bit tmp = l1->val;
            l1->val = l2->val;
            l2->val = tmp;
        }
        l1 = l1->next;
        l2 = l2->next;
    }
}

void free_indiv(Individual *i) {
    if (*i != NULL) {
        free_indiv(&(*i)->next);
        free(*i);
        *i = NULL;
    }
}