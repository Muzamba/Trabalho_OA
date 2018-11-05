#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <string.h>
#include "lista.h"
#define REG_SIZE 64
#define IND_SIZE 43
#define IND2_SIZE 9

int proxChar(FILE* ponteiro, const char simbolo);
int proxCharRep(FILE* ponteiro, const char simbolo);
int makeInd1(const char* arquivo, const char* nome);
int makeInd2(const char* data, const char* arquivo, const char* nome);
int tamNum(int num);
int verSeTem(FILE* ponteiro, const char* string);
int insereLista(const char* local, lista* list);
void print_arq(char* filename);
int arquSort(const char* nome);
void removeLista(const char* arquivo, const char* indice, const char* chave, lista* list);
void atualizaLista(const char* arquivo, const char* indice);
void exibeReg(FILE* ponteiro, int tam, int posRel);



#endif
