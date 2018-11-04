#ifndef LISTA_H
#define LISTA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Data {
    char string[100];
    int end;
}data;

typedef struct Node{
    data info;
    struct Node* prox;
}node;

typedef struct Lista {
    node* head;
    int size;
}lista;

lista* createList();
void push(lista* p, data item);
data pop(lista* p);
void destroyList(lista* p);
void listSort(lista* list);



#endif