int makeInd2(const char* data, const char* indice, const char* nome, const char* listaInvertida) {
    FILE *ponteiro1, *ponteiro2, *ponteiro3, *ponteiro4;
    char aux[3];
    int aux2, aux3;
    int valor;
    int cont = 0;
    char aux4;

    ponteiro1 = fopen(data, "r");
    if(ponteiro1 == NULL) {
        return 0;
    }
    ponteiro2 = fopen(indice, "r+");
    if(ponteiro1 == NULL) {
        return 0;
    }
    ponteiro3 = fopen(nome, "w+");
    ponteiro4 = fopen(listaInvertida, "w");
    aux4 = fgetc(ponteiro2);
    
    while(!feof(ponteiro2)){
        fputc(aux4, ponteiro4);
        aux4 = fgetc(ponteiro2);
    }
    fseek(ponteiro2, 0, 0);
    fclose(ponteiro4);
    arquSort(listaInvertida, 1);
    ponteiro4 = fopen(listaInvertida, "r+");
    
    
    while(1) {
        proxChar(ponteiro4, '|');
        if(feof(ponteiro4)){
            break;
        }
        fscanf(ponteiro4, "%d", &aux2);
        
        fseek(ponteiro4, -tamNum(aux2), 1);
        //proxChar(ponteiro2, '|');
        fseek(ponteiro1, aux2 + 52, 0);
        fgets(aux, 3, ponteiro1);
        


        if((valor = verSeTem(ponteiro3, aux)) < 0) {
            //fseek(ponteiro3, 0, 2);
            fputs(aux, ponteiro3);
            fputc('|',ponteiro3);
            fprintf(ponteiro3, "%d", cont * IND_SIZE);
            fprintf(ponteiro4, "%d", -1);
            //printf("%d\n", tamNum(cont * IND_SIZE));
            for(int i = 0;i <  5 - tamNum(cont * IND_SIZE);++i){
                fputc('.', ponteiro3);
            }
            for(int i = 0;i < 3;++i){
                fputc('.',ponteiro4);
            }
            fputc('\n', ponteiro3);
        } else {
            //valor--;
            fseek(ponteiro3, valor * IND2_SIZE, 0);
            proxChar(ponteiro3, '|');
            //fseek(ponteiro3, -1, 1);
            fscanf(ponteiro3, "%d", &aux3);
            printf("%d\n", aux3);
            fprintf(ponteiro4, "%d", aux3);
        //fseek(ponteiro3, 1, 1);
            fseek(ponteiro3, valor * IND2_SIZE, 0);
            proxChar(ponteiro3, '|');
            //fseek(ponteiro3, -1, 1);
            fprintf(ponteiro3, "%d", cont * IND_SIZE);
            for(int i = 0;i < 5 - tamNum(cont * IND_SIZE);++i){
                fputc('.', ponteiro3);
            }
            for(int i = 0;i < 5-tamNum(aux3);++i){
                fputc('.', ponteiro4);
            }
            fputc('\n', ponteiro3);
        }
    
        
        /*
        */
        //proxChar(ponteiro4, '\n');
        //proxCharRep(ponteiro2, '.');
        cont++;
    }
    

    fclose(ponteiro1);
    fclose(ponteiro2);
    fclose(ponteiro3);
    fclose(ponteiro4);
    return 1;

    

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
            //fputc('|',ponteiro2);
            //for(int i = 0;i < 5;++i) {
              //  fputc('.', ponteiro2);
            //}
            fputc('\n', ponteiro2);
            proxChar(ponteiro1, '\n');
            flag = 0;
            cont1 = 0;
            cont2++;
        }
    }
}

int arquSort(const char* nome, int flag) {
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
        //printf("%s", aux.string);
        push(list,aux);
        if(feof(ponteiro))
            break;
        aux2 = 0;
    }
    listSort(list, flag);
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
void listSort(lista* list, int flag) {
    node* pont;
    data aux;
    int opt;
    int flag1 = 1;
    
    while(flag1){
        
        flag1 = 0;
        for(pont = list->head; pont->prox != NULL;pont = pont->prox) {
            if(!flag){
                opt = strcmp(pont->info.string, pont->prox->info.string);
                if (opt > 0){
                    aux = pont->info;
                    pont->info = pont->prox->info;
                    pont->prox->info = aux;
                    flag1 = 1;
                }
            }else {
                opt = strcmp(pont->info.string, pont->prox->info.string);
                if (opt < 0){
                    aux = pont->info;
                    pont->info = pont->prox->info;
                    pont->prox->info = aux;
                    flag1 = 1;

                }
            }
        }
    }
}
