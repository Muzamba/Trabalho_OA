#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <string.h>
#include "lista.h"
#define REG_SIZE 64
#define IND_SIZE 30

int proxChar(FILE* ponteiro, const char simbolo);
int proxCharRep(FILE* ponteiro, const char simbolo);
int makeInd1(const char* arquivo, const char* nome);
int makeInd2(const char* data, const char* arquivo, const char* nome);
int tamNum(int num);
int verSeTem(FILE* ponteiro, const char* string);
int insereLista(const char* local);
void print_arq(char* filename);
int arquSort(const char* nome, int tam);



#endif
