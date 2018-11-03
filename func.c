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
        fseek(ponteiro, -1, 1);
        fgets(aux, 3, ponteiro);
        if(!strcmp(string, aux)) {
            return cont;
        }
        cont++;
        proxChar(ponteiro, '\n');
        aux1 = fgetc(ponteiro);
        

    }
    return 0;
}


int makeInd2(const char* data, const char* arquivo, const char* nome) {
    FILE *ponteiro1, *ponteiro2, *ponteiro3;
    char aux[2];
    int aux2, aux3;
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


    while(1) {
        proxChar(ponteiro2, '.');
        if(feof(ponteiro2)){
            break;
        }
        fscanf(ponteiro2, "%d", &aux2);
        proxChar(ponteiro2, '.');
        fseek(ponteiro1, aux2 + 52, 0);
        fgets(aux, 3, ponteiro1);
    
        if(!(valor = verSeTem(ponteiro3, aux))) {
            fputs(aux, ponteiro3);
            fputc('.',ponteiro3);
            fprintf(ponteiro3, "%d", (aux2/REG_SIZE) * IND_SIZE);
            for(int i = 0;i < (IND_SIZE - 2 - tamNum((aux2/REG_SIZE) * IND_SIZE) - 2);++i) {
                fputc('.',ponteiro3);
            }
            fputc('\n', ponteiro3);
            fprintf(ponteiro2, "%d", -1);
        } else {
            valor--;
            fseek(ponteiro3, valor * IND_SIZE, 0);
            proxChar(ponteiro3, '.');
            proxCharRep(ponteiro3, '.');
            fseek(ponteiro3, -1, 1);
            fscanf(ponteiro3, "%d", &aux3);
            fprintf(ponteiro2, "%d", aux3);
        //fseek(ponteiro3, 1, 1);
            fseek(ponteiro3, valor * IND_SIZE, 0);
            proxChar(ponteiro3, '.');
            proxCharRep(ponteiro3, '.');
            fseek(ponteiro3, -1, 1);
            fprintf(ponteiro3, "%d", (aux2/REG_SIZE) * IND_SIZE);
    
        }

        proxCharRep(ponteiro2, '.');

    }

    fclose(ponteiro1);
    fclose(ponteiro2);
    fclose(ponteiro3);
    return 1;

    

}
int insereLista(const char* local) {
    FILE* ponteiro;
    char string[100];
    int aux;
   
    ponteiro = fopen(local, "a");

    printf("Digite a matrícula desejada: ");
    scanf("%s", string);
    while(strlen(string) != 6) {
        printf("Digite a matrícula desejada: ");
        scanf("%s", string); 
    }
    fprintf(ponteiro, "%s ", string);

    setbuf(stdin, NULL);

    printf("Digite o nome desejado: ");
    scanf("%[^\n]s", string);
    printf("%ld\n", strlen(string));
    while(strlen(string) >= 40) {
        printf("Digite o nome desejado: ");
        scanf("%[^\n]s", string); 
    }
    fprintf(ponteiro, "%s ", string);
    for(int i = strlen(string); i < 40;++i) {
        fputc(' ', ponteiro);
    }

    setbuf(stdin, NULL);

    printf("Digite a OP desejada: ");
    scanf("%s", string);
    while(strlen(string) != 2) {
        printf("Digite a OP desejada: ");
        scanf("%s", string); 
    }
    fprintf(ponteiro, "%s ", string);
    fputc(' ', ponteiro);

    setbuf(stdin, NULL);

    printf("Digite o curso desejado: ");
    scanf("%s", string);
    while(strlen(string) != 2) {
        printf("Digite o curso desejado: ");
        scanf("%s", string); 
    }
    fprintf(ponteiro, "%s ", string);
    for(int i = 0;i < 6;++i) {
        fputc(' ', ponteiro);
    }

    setbuf(stdin, NULL);

    printf("Digite a turma desejada: ");
    scanf("%s", string);
    while(strlen(string) != 1) {
        printf("Digite a turma desejada: ");
        scanf("%s", string); 
    }
    fprintf(ponteiro, "%s", string);

    setbuf(stdin, NULL);

    fputc(13, ponteiro);
    fputc('\n', ponteiro);

    fclose(ponteiro);
    return 1;
}

void print_arq(char* filename){

    FILE* fp;
    char c;

    fp = fopen(filename, "r");
    if (fp == NULL) 
    { 
        printf("Arquivo não pôde ser aberto\n"); 
        return;
    } 
  
    // Read contents from file 
    c = fgetc(fp);
    while (c != EOF) 
    { 
        printf("%c", c); 
        c = fgetc(fp); 
    } 
  
    fclose(fp);  
}


int arquSort(const char* nome, int tam) {
    FILE* ponteiro;
    lista* list;
    data aux;
    int size;

    list = createList();


    ponteiro = fopen(nome, "r+");


    while(!feof(ponteiro)) {
        for(int i = 0;i < 30;++i) {
            aux.string[i] = fgetc(ponteiro);
        }
        aux.string[30] = 0;
        if(feof(ponteiro))
                break;
        push(list, aux);
    }
    listSort(list, tam);
    fseek(ponteiro, 0, 0);

    size = list->size;
    for(int i = 0;i < size;++i) {
        aux = pop(list);
        fputs(aux.string, ponteiro);
    }
    fclose(ponteiro);

    return 1;
}
