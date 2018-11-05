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
        if(aux == '*') {
            proxChar(ponteiro1, '\n');
            cont2++;

        }else if(aux == ' ') {
            aux = fgetc(ponteiro1);
            if((aux == ' ')||(cont1 > 30)) {
                flag = 1;    
            }
            fseek(ponteiro1, -1, 1);
            
        } else if (!(flag || (cont1 >= 30))) {
            fputc(aux, ponteiro2);
            cont1++;
        } else {
            for(int i = 0;i < 30 - cont1;++i) {
                fputc('.', ponteiro2);
                
            }
            fputc('|',ponteiro2);
            fprintf(ponteiro2, "%d", cont2 * REG_SIZE);
            for(int i = 0;i < (5 - tamNum(cont2 * REG_SIZE));++i) {
                fputc('.',ponteiro2);
            }
            fputc('|',ponteiro2);
            for(int i = 0;i < 5;++i) {
                fputc('.', ponteiro2);
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
    int cont = 0;
    char aux1;
    char aux[50];
    int tam;
    tam = strlen(string)+1;
    fseek(ponteiro, 0, 0);
    aux1 = fgetc(ponteiro);
    fseek(ponteiro, -1, 1);
    while(aux1 != -1) {
        fseek(ponteiro, -1, 1);
        fgets(aux, tam, ponteiro);
        if(!strcmp(string, aux)) {
            return cont;
        }
        cont++;
        proxChar(ponteiro, '\n');
        aux1 = fgetc(ponteiro);
        

    }
    return -1;
}


int makeInd2(const char* data, const char* arquivo, const char* nome) {
    FILE *ponteiro1, *ponteiro2, *ponteiro3;
    char aux[2];
    int aux2, aux3;
    int valor;
    int cont = 0;

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
        proxChar(ponteiro2, '|');
        if(feof(ponteiro2)){
            break;
        }
        fscanf(ponteiro2, "%d", &aux2);
        proxChar(ponteiro2, '|');
        fseek(ponteiro1, aux2 + 52, 0);
        fgets(aux, 3, ponteiro1);
    
        if((valor = verSeTem(ponteiro3, aux)) < 0) {
            fseek(ponteiro3, 0, 2);
            fputs(aux, ponteiro3);
            fputc('|',ponteiro3);
            fprintf(ponteiro3, "%d", cont * IND_SIZE);
            fprintf(ponteiro2, "%d", -1);
            for(int i = 0;i <  5 - tamNum(cont * IND_SIZE);++i){
                fputc('.', ponteiro3);
            }
            fputc('\n', ponteiro3);
        } else {
            //valor--;
            fseek(ponteiro3, valor * IND2_SIZE, 0);
            proxChar(ponteiro3, '|');
            //fseek(ponteiro3, -1, 1);
            fscanf(ponteiro3, "%d", &aux3);
            fprintf(ponteiro2, "%d", aux3);
        //fseek(ponteiro3, 1, 1);
            fseek(ponteiro3, valor * IND2_SIZE, 0);
            proxChar(ponteiro3, '|');
            //fseek(ponteiro3, -1, 1);
            fprintf(ponteiro3, "%d", cont * IND_SIZE);
            for(int i = 0;i < 5 - tamNum(cont * IND_SIZE);++i){
                fputc('.', ponteiro3);
            }
    
        }

        //proxCharRep(ponteiro2, '.');
        cont++;
    }

    fclose(ponteiro1);
    fclose(ponteiro2);
    fclose(ponteiro3);
    return 1;

    

}
int insereLista(const char* local,lista* list) {
    FILE* ponteiro;
    char string[100];
    char aux;
    data aux2;
   
    ponteiro = fopen(local, "r+");
    if(list->size == 0){
        fseek(ponteiro, 0, 2);
    } else {
        aux2 = pop(list);
        printf("%d\n", aux2.end);
        fseek(ponteiro, aux2.end, 0);
    }
    
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


int arquSort(const char* nome) {
    FILE* ponteiro;
    lista* list;
    data aux;
    char aux2;
    int size;
    int i;

    list = createList();

    ponteiro = fopen(nome, "r+");
    while(1) {
        for(i = 0;aux2 != '\n';++i){
            aux2 = fgetc(ponteiro);
            if(feof(ponteiro))
            break;
            aux.string[i] = aux2;
        }
        aux.string[i] = 0;
        push(list,aux);
        if(feof(ponteiro))
            break;
        aux2 = 0;
    }
    listSort(list);
    fseek(ponteiro, 0, 0);

    size = list->size;
    for(int i = 0;i < size;++i) {
        aux = pop(list);
        fputs(aux.string, ponteiro);
    }
    fclose(ponteiro);
    destroyList(list);

    return 1;
}
void removeLista(const char* arquivo, const char* indice, const char* chave, lista* list) {
    FILE* ponteiro1;
    FILE* ponteiro2;
    data aux1;
    int aux2;
    int aux3;

    ponteiro1 = fopen(arquivo, "r+");
    ponteiro2 = fopen(indice, "r");

    aux2 = verSeTem(ponteiro2, chave);
    if(aux2 < 0){
        printf("Chave não encontrada");
        return;
    }
    //printf("%d\n", aux2);
    //aux2--;
    fseek(ponteiro2, aux2 * IND_SIZE, 0);
    proxChar(ponteiro2, '|');
    fscanf(ponteiro2, "%d", &aux3);
    aux1.end = aux3;
    
    push(list, aux1);
    //printf("%d\n", aux1.end);
    //list->head->info = aux1;
    printf("%d\n", list->head->info.end);
    fseek(ponteiro1, aux3, 0);
    fputc('*', ponteiro1);
    for(int i = 0;i < (REG_SIZE - 2);++i){
        fputc('.', ponteiro1);
    }
    fclose(ponteiro1);
    fclose(ponteiro2);
}

void atualizaLista(const char* arquivo, const char* indice){

    FILE* ponteiro1;
    FILE* ponteiro2;
    int opt, aux, opt2;
    char chave[30];
    char Registro[65];
    char string[50];
    printf("1.Com mudança de chave primaria\n");
    printf("2.Sem mudança de chave primaria\n");
    printf("Escolha o modo de atualização:");
    scanf("%d", &opt);
    while((opt != 1) && (opt != 2)){
        printf("Escolha o modo de atualização:");
        scanf("%d", &opt);
    }
    ponteiro1 = fopen(arquivo, "r+");
    if(opt == 1){
        ponteiro2 = fopen(indice, "r+");
    }else {
        ponteiro2 = fopen(indice, "r");
    }

    printf("Digite a chave do registro que quer atualizar: ");
    scanf("%s", chave);

    aux = verSeTem(ponteiro2, chave);
    while(aux < 0){
        printf("Registro não encontrado\n");
        printf("Digite a chave do registro que quer atualizar: ");
        scanf("%s", chave);
        aux = verSeTem(ponteiro2, chave);
    }
    
    fseek(ponteiro2, aux * IND_SIZE, 0);
    proxChar(ponteiro2, '|');
    fscanf(ponteiro2, "%d", &aux);

    fseek(ponteiro1, aux, 0);


    



    if(opt == 2){
        fseek(ponteiro1, 48, 1);
    }

    switch(opt){

        case 1:
            exibeReg(ponteiro1, REG_SIZE, 0);
            printf("1.Sim\n2.Não\n");
            printf("Deseja alterar a matrícula?\n");
            scanf("%d", &opt2);
            while((opt2 != 1)&&(opt2 != 2)){
                printf("1.Sim\n2.Não\n");
                printf("Deseja alterar a matrícula?\n");
                scanf("%d", &opt2);
            }
            if(opt2 == 1){
                setbuf(stdin, NULL);
                printf("Digite a nova matrícula desejada: ");
                scanf("%s", string);
                while(strlen(string) != 6) {
                    printf("Digite a nova matrícula desejada: ");
                    scanf("%s", string); 
                }
                fprintf(ponteiro1, "%s ", string);
                
            }else{
                fseek(ponteiro1, 7, 1);
            }
            exibeReg(ponteiro1, REG_SIZE, 7);
            printf("1.Sim\n2.Não\n");
            printf("Deseja alterar o nome?\n");
            scanf("%d", &opt2);
            while((opt2 != 1)&&(opt2 != 2)){
                printf("1.Sim\n2.Não\n");
                printf("Deseja alterar o nome?\n");
                scanf("%d", &opt2);
            }
            if(opt2 == 1){
                setbuf(stdin, NULL);
                printf("Digite o novo nome desejado: ");
                scanf("%[^\n]s", string);
                while(strlen(string) >= 40) {
                printf("Digite o novo nome desejado: ");
                scanf("%[^\n]s", string); 
                }
                fprintf(ponteiro1, "%s ", string);
                for(int i = strlen(string); i < 40;++i) {
                    fputc(' ', ponteiro1);
                }

                
            }else{
                fseek(ponteiro1, 41, 1);
            }
        
        case 2:
            exibeReg(ponteiro1, REG_SIZE, 48);
            printf("1.Sim\n2.Não\n");
            printf("Deseja alterar a OP?\n");
            scanf("%d", &opt2);
            while((opt2 != 1)&&(opt2 != 2)){
                printf("1.Sim\n2.Não\n");
                printf("Deseja alterar a OP?\n");
                scanf("%d", &opt2);
            }
            if(opt2 == 1){
                setbuf(stdin, NULL);
                printf("Digite a nova OP desejada: ");
                scanf("%s", string);
                while(strlen(string) != 2) {
                    printf("Digite a nova OP desejada: ");
                    scanf("%s", string); 
                }
                fprintf(ponteiro1, "%s ", string);
                fputc(' ', ponteiro1);

                
            }else {
                fseek(ponteiro1, 4, 1);
            }

            exibeReg(ponteiro1, REG_SIZE, 52);
            printf("1.Sim\n2.Não\n");
            printf("Deseja alterar o curso?\n");
            scanf("%d", &opt2);
            while((opt2 != 1)&&(opt2 != 2)){
                printf("1.Sim\n2.Não\n");
                printf("Deseja alterar o curso?\n");
                scanf("%d", &opt2);
            }
            if(opt2 == 1){
                setbuf(stdin, NULL);
                printf("Digite o novo curso desejado: ");
                scanf("%s", string);
                while(strlen(string) != 2) {
                    printf("Digite o novo curso desejado: ");
                    scanf("%s", string); 
                }
                fprintf(ponteiro1, "%s ", string);
                for(int i = 0;i < 6;++i) {
                    fputc(' ', ponteiro1);
                }

                
            }else{
                fseek(ponteiro1, 9, 1);
            }

            exibeReg(ponteiro1, REG_SIZE, 61);
            printf("1.Sim\n2.Não\n");
            printf("Deseja alterar a turma?\n");
            scanf("%d", &opt2);
            while((opt2 != 1)&&(opt2 != 2)){
                printf("1.Sim\n2.Não\n");
                printf("Deseja alterar a turma?\n");
                scanf("%d", &opt2);
            }
            if(opt2 == 1){
                setbuf(stdin, NULL);
                printf("Digite a turma desejada: ");
                scanf("%s", string);
                while(strlen(string) != 1) {
                    printf("Digite a turma desejada: ");
                    scanf("%s", string); 
                }
                fprintf(ponteiro1, "%s", string);

                
            }else{
                fseek(ponteiro1, 1, 1);
            }
            fputc(13, ponteiro1);
            fputc('\n', ponteiro1);
    }
    fclose(ponteiro1);
    fclose(ponteiro2);
    if(opt == 1){
        makeInd1(arquivo, indice);
    }

}

void exibeReg(FILE* ponteiro, int tam, int posRel){
    fseek(ponteiro, -posRel,1);
    for(int i = 0;i < tam + 2;++i){
        printf("*");
    }
    printf("\n*");
    for(int i = 0;i < tam-2;++i){
        printf("%c",fgetc(ponteiro));
    }
    printf("  *\n");
    for(int i = 0;i < tam + 2;++i){
        printf("*");
    }
    printf("\n");
    fseek(ponteiro, posRel - tam + 2, 1);
}

void upper_string(char s[]) {
   int c = 0;
   
   while (s[c] != '\0') {
      if (s[c] >= 'a' && s[c] <= 'z') {
         s[c] = s[c] - 32;
      }
      c++;
   }
}


void merge(const char* arquivo1, const char* arquivo2, char* output){

    FILE* arq1, *arq2, *ind1, *ind2, *out;
    int end1, end2;
    char reg1[REG_SIZE+1], reg2[REG_SIZE+1];
    char c;
    int i;
    
    arq1 = fopen(arquivo1, "r");
    arq2 = fopen(arquivo2, "r");
    ind1 = fopen("indicelista1.ind", "r");
    ind2 = fopen("indicelista2.ind", "r");
    out  = fopen(output, "w");

    proxChar(ind1,'|');
    proxChar(ind2,'|');

    fscanf(ind1,"%d",&end1);
    fscanf(ind2, "%d",&end2);
    printf("%d %d\n", end1, end2);


    fseek(arq1,end1,0);
    fseek(arq2,end2,0);

    //fscanf(arq1, "%[^\n]s", reg1);
    fgets(reg1,REG_SIZE,arq1);
    //reg1[IND_SIZE] = fgetc(arq1);
    fgets(reg2,REG_SIZE,arq2);
    
    //reg2[IND_SIZE] = fgetc(arq2);

    while(!(feof(ind1) && feof(ind2))){
        //printf("1\n");
        printf("\nreg1:%s\n", reg1);
        printf("reg2:%s\n", reg2);
        if(strncmp(reg1,reg2,48) < 0){
            fprintf(out,"%s", reg1);
            proxChar(ind1,'\n');
            proxChar(ind1,'|');
            fscanf(ind1,"%d",&end1);
            fseek(arq1,end1,0);
            fgets(reg1, REG_SIZE, arq1);
            //fscanf(arq1, "%[^\n]s", reg1);
            //reg1[IND_SIZE] = fgetc(arq1);
            if(feof(ind1))
                break;

        } else if(strncmp(reg1,reg2,48) > 0){
            fprintf(out,"%s", reg2);
            proxChar(ind2,'\n');
            proxChar(ind2,'|');
            fscanf(ind2, "%d",&end2);
            fseek(arq2,end2,0);
            fgets(reg2, REG_SIZE, arq2);
            //fscanf(arq2, "%[^\n]s", reg2);
            //reg2[IND_SIZE] = fgetc(arq2);
            if(feof(ind2))
                break;
        } else {
            fprintf(out,"%s", reg1);
            proxChar(ind1,'\n');
            proxChar(ind2,'\n');
            proxChar(ind1,'|');
            proxChar(ind2,'|');
            fscanf(ind1,"%d",&end1);
            fscanf(ind2, "%d",&end2);
            fseek(arq1,end1,0);
            fseek(arq2,end2,0);
            fgets(reg1, REG_SIZE, arq1);
            fgets(reg2, REG_SIZE, arq2);            
            //fscanf(arq1, "%[^\n]s", reg1);
            //fscanf(arq2, "%[^\n]s", reg2);
            //reg1[IND_SIZE] = fgetc(arq1);
            //reg2[IND_SIZE] = fgetc(arq2);
            if(feof(ind1))
                break;
            if(feof(ind2))
                break;
        }
    }





    /*if(!feof(ind1)){
        fprintf(out,"%s", reg1);
        proxChar(ind1,'\n');
        proxChar(ind1,'|');
        fscanf(ind1,"%d",&end1);
        fseek(arq1,end1,0);
        fgets(reg1, REG_SIZE, arq1);
        */
        while (!feof(ind1)){ 
            fprintf(out,"%s", reg1);
            proxChar(ind1,'\n');
            proxChar(ind1,'|');
            fscanf(ind1,"%d",&end1);
            fseek(arq1,end1,0);
            fgets(reg1, REG_SIZE, arq1);
        }
         
    /*} else if(!feof(ind2)) {
        fprintf(out,"%s", reg2);
        proxChar(ind2,'\n');
        proxChar(ind2,'|');
        fscanf(ind2,"%d",&end2);
        fseek(arq2,end2,0);
        fgets(reg2, REG_SIZE, arq2);
        */
        while (!feof(ind2)){ 
            fprintf(out,"%s", reg2);
            proxChar(ind2,'\n');
            proxChar(ind2,'|');
            fscanf(ind2,"%d",&end2);
            fseek(arq2,end2,0);
            fgets(reg2, REG_SIZE, arq2);
        }
          
    //}
 
    



    fclose(arq1);
    fclose(arq2);
    fclose(ind1);
    fclose(ind2);
    fclose(out);
}
