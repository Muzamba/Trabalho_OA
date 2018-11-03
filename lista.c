#include "lista.h"


lista* createList() {
    lista* aux = (lista*)malloc(sizeof(lista));
    aux->size = 0;
    aux->head = NULL;
    return aux;
}

void push(lista* p, data item) {
    node* aux1 = (node*)malloc(sizeof(node));
    aux1->prox = p->head;
    aux1->info = item;
    p->head = aux1;
    p->size++;
}

data pop(lista* p) {
    node* aux = p->head;
    data item = aux->info;
    p->head = aux->prox;
    free(aux);
    p->size--;
    return item;
}

void destroyList(lista* p) {
  data aux;
  for (; p->size != 0;pop(p));
  free(p);
}

void listSort(lista* list, int tam) {
    node* pont;
    data aux;
    int opt;
    int flag = 1;
    
    while(flag){
        
        flag = 0;
        for(pont = list->head; pont->prox != NULL;pont = pont->prox) {
            opt = strncmp(pont->info.string, pont->prox->info.string, tam);
            if (opt > 0){
                aux = pont->info;
                pont->info = pont->prox->info;
                pont->prox->info = aux;
                flag = 1;
            }
        }
    }
}