#include "func.h"


int proxChar(FILE* ponteiro, const char simbolo) {
    char aux;
    
    aux = fgetc(ponteiro);
    while(aux != simbolo) {
        if(feof(ponteiro)){
            return 0;
        }
        aux = fgetc(ponteiro);
    }
    return 1;
}

int proxCharRep(FILE* ponteiro, const char simbolo) {
    char aux;
    char cont = 0;
    
    aux = fgetc(ponteiro);
    while(aux == simbolo) {
        if(feof(ponteiro)){
            return 0;
        }
        aux = fgetc(ponteiro);
    }
    return 1;
}

int tamNum(int num) {
    int cont = 1;

    while((num / 10) != 0) {
        num /= 10;
        cont++;
    }
    return cont;
}


int makeInd1(const char* arquivo, const char* nome) {
    FILE *ponteiro1, *ponteiro2;
    char aux;
    int  flag = 0;
    int cont1 = 0;
    int cont2 = 0;

    ponteiro1 = fopen(arquivo, "r");
    if(ponteiro1 == NULL) {
        return 0;
    }
    ponteiro2 = fopen(nome, "w");

    while(1) {
        aux = fgetc(ponteiro1);
        if(feof(ponteiro1)){
            fclose(ponteiro1);
            fclose(ponteiro2);
            return 1;
        }
        if(aux == ' ') {
            flag++;
        } else if(flag <= 1){
            fputc(aux, ponteiro2);
            cont1++;
        } else {
            fputc('.',ponteiro2);
            fprintf(ponteiro2, "%d", cont2 * REG_SIZE);
            for(int i = 0;i < (IND_SIZE - cont1 - tamNum(cont2 * REG_SIZE) - 2);++i) {
                fputc('.',ponteiro2);
            }
            fputc('\n', ponteiro2);
            proxChar(ponteiro1, '\n');
            flag = 0;
            cont1 = 0;
            cont2++;
        }
    }
}
int verSeTem(FILE* ponteiro, const char* string) {
    if(ponteiro == NULL) {
        return -1;
    }
    int cont = 1;
    char aux1;
    char aux[2];
    fseek(ponteiro, 0, 0);
    aux1 = fgetc(ponteiro);
    fseek(ponteiro, -1, 1);
    while(aux1 != -1) {
        fgets(aux, 3, ponteiro);
        if(!strcmp(string, aux)) {
            return cont;
        }
        cont++;
        proxChar(ponteiro, '\n');
        aux1 = fgetc(ponteiro);
        fseek(ponteiro, -1, 0);

    }
    return 0;
}


int makeInd2(const char* data, const char* arquivo, const char* nome) {
    FILE *ponteiro1, *ponteiro2, *ponteiro3;
    char aux[2];
    int aux2;
    int valor;

    ponteiro1 = fopen(data, "r");
    if(ponteiro1 == NULL) {
        return 0;
    }
    ponteiro2 = fopen(arquivo, "r+");
    if(ponteiro1 == NULL) {
        return 0;
    }
    ponteiro3 = fopen(nome, "w+");

    proxChar(ponteiro2, '.');
    fscanf(ponteiro2, "%d", &aux2);
    proxChar(ponteiro2, '.');
    fseek(ponteiro1, aux2 + 52, 0);
    fgets(aux, 3, ponteiro1);
    if(!(valor = verSeTem(ponteiro3, aux))) {
        fputs(aux, ponteiro3);
        for(int i = 0;i < (IND_SIZE - 2 - tamNum(aux2) - 1);++i) {
            fputc('.',ponteiro3);
        }
        fprintf(ponteiro3, "%d\n", aux2);
        fprintf(ponteiro2, "%d", -1);
    } else {
        valor--;
        fseek(ponteiro3, valor * IND_SIZE, 0);
        proxChar(ponteiro3, '.');
        proxCharRep(ponteiro3, '.');
        fscanf(ponteiro3, "%d", &valor);
        fprintf(ponteiro2, "%d", valor);
    
    }
    

    proxCharRep(ponteiro2, '.');

    proxChar(ponteiro2, '.');
    fscanf(ponteiro2, "%d", &aux2);
    proxChar(ponteiro2, '.');
    fseek(ponteiro1, aux2 + 52, 0);
    fgets(aux, 3, ponteiro1);
    if(!(valor = verSeTem(ponteiro3, aux))) {
        fputs(aux, ponteiro3);
        for(int i = 0;i < (IND_SIZE - 2 - tamNum(aux2) - 1);++i) {
            fputc('.',ponteiro3);
        }
        fprintf(ponteiro3, "%d\n", aux2);
        fprintf(ponteiro2, "%d", -1);
    } else {
        valor--;
        fseek(ponteiro3, valor * IND_SIZE, 0);
        proxChar(ponteiro3, '.');
        proxCharRep(ponteiro3, '.');

        valor = 10;
        fscanf(ponteiro3, "%d", &valor);
        fprintf(ponteiro2, "%d", valor);
    
    }



    


    

    
    
    
    

    
    if(feof(ponteiro1)){
        fclose(ponteiro1);
        fclose(ponteiro2);
        return 1;
    }
    fclose(ponteiro1);
    fclose(ponteiro2);
    fclose(ponteiro3);
    return 1;

    

}