#include "head.h"

int main(int argc, char const *argv[]) {
   
    if(argc < 3){
        printf("Número incorreto de arquivos passados! Passe dois arquivos como parâmetro!\n");
        return 0;
    }

    while (1){

        printf("Os arquivos %s e %s foram passados como parâmetros. O que deseja fazer?\n", argv[1], argv[2]);
        printf("\n------------------ OPÇÕES--------------------------------\n");
        printf("Visualizar os arquivos passados - 1\n");
        printf("Inserir registro - 2\n");
        printf("Excluir registros - 3\n");
        printf("Atualizar registros - 4\n");
        printf("Criar arquivo de índices primários - 5\n");
        printf("Criar arquivo de índices secundários (Lista Invertida) - 6\n");
        printf("Intercalação (merge) - 7\n");
        printf("Exit - 0\n");
    

        short int option;
        char c;
        scanf("%hd", &option);

        if (option == 0) break;

        switch(option){

            case 1:
                printf("Você escolheu visualizar os arquivos passados\n");
            break;

            case 2:
                printf("Você escolheu inserir um novo registro\n");
             break;

            case 3:
                printf("Você escolheu excluir um registro\n");
            break;

            case 4:
                printf("Você escolheu atualizar um registro\n");
            break;

            case 5:
                printf("Você escolheu criar um arquivo de índices primários\n");

                makeInd1(argv[1], "indicelista1.ind");
                printf("\n------------ Arquivo de índices referentes ao arquivo %s------------\n", argv[1]);
                print_arq("indicelista1.ind");

                makeInd1(argv[2], "indicelista2.ind");
                printf("\n------------ Arquivo de índices referentes ao arquivo %s------------\n", argv[2]);
                print_arq("indicelista2.ind");

            break;

            case 6:
                printf("Você escolheu criar um arquivo de índices secudários (lista invertida)\n");

                makeInd2(argv[1], "indicelista1.ind", "indicesec1.indsec");
                printf("\n-------------- Arquivo de índices secundários referentes ao arquivo  %s -----------\n", argv[1]);
                print_arq("indicesec1.indsec");
            
                makeInd2(argv[2], "indicelista2.ind", "indicesec2.indsec");
                printf("\n-------------- Arquivo de índices secundários referentes ao arquivo  %s -----------\n", argv[2]);
                print_arq("indicesec2.indsec");
            break;

            case 7:
                printf("Você escolheu fazer um merge nos arquivos\n");
            break;  

            default:
                printf("Opção inválida!\n");  
        }

        printf("\nAperte ENTER para voltar ao menu\n\n");
        scanf("%c", &c);
        scanf("%c", &c);

    }    

    
    
    return 0;
}


