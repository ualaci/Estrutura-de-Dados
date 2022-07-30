//Uarlley do Nascimento Amorim - 2018205346
//Ualaci dos Anjos Junior - 2017102015

#include "Huffman.h"
#include <string.h>

int main() {
    char file[200];
    char out[200];
    while(1){
        puts(" ---------------------------");
        puts("|  1 - Compactar arquivo    |");
        puts("|  2 - Descompactar arquivo |");
        puts("|  3 - Sair                 |");
        puts(" ---------------------------");
        int op;
        printf("Selecione uma opcao: ");
        scanf("%d", &op);
        getchar();
        if(op == 1){
            int SIZELIST = 0;
            long long charQnt = 0;
            printf("Digite o nome do arquivo a ser compactado (exemplo.txt): ");
            fgets(file, 200, stdin);
            file[strlen(file)-1] = 0;
            system("clear");
            if(strcmp("sair", file) == 0) exit(1);
            Node* head = leArquivo(file,&SIZELIST, &charQnt);
            if(head){
                printf("\nOcorrencia dos caracteres no arquivo:");
                imprimeOcorrencias(head);
                int countSaida = 0;
                printf("Pressione enter para continuar...");
                getchar();
                system("clear");
                BSTNode* root = huffman(head, SIZELIST);

                printf("\nArvore gerada pelo algoritmo de Huffman: ");
                puts("");
                imprimeCodHuffman(root);

                printf("Pressione enter para continuar...");
                getchar();
                system("clear");

                int sizeOut = heightBST(root);
                tab *tabela = criaTabela(sizeOut, SIZELIST);
                bool *vet =(bool*) calloc(sizeOut,sizeof(bool));
                int size = 0, sizeTab = 0;

                if(SIZELIST == 1){
                    tabela[0].caractere = root->info->caractere;
                    tabela[0].size = 1;
                    tabela[0].vet[0] = 0;
                }
                else writeTab(root, tabela, vet, &size, &sizeTab);

                printf("\nCodigo gerado pelo algoritmo de Huffman: ");
                puts("");
                printTabela(tabela,SIZELIST);
                puts("");
                long long countSizeO = countSizeOut(tabela, SIZELIST,root);
                printf("\nPressione enter para continuar...");
                getchar();
                system("clear");

                printf("Digite o nome do arquivo de saida (exemplo.cpt): ");
                fgets(out, 200, stdin);
                out[strlen(out)-1] = 0;
                writeBin(tabela, file, out,countSizeO,SIZELIST,sizeOut, charQnt);
                destroyBST(root);
                freeTabela(tabela,SIZELIST);
                free(vet);
                printf("\nArquivo compactado!\nPressione enter para continuar...");
                getchar();
                system("clear");
            }
            else{
                printf("ERRO! Arquivo vazio.\n");
                printf("\nPressione enter para continuar...");
                getchar();
                system("clear");
            }
        }
        else if(op == 2){
            printf("Digite o nome do arquivo a ser compactado (exemplo.cpt): ");
            fgets(out, 200, stdin);
            out[strlen(out)-1] = 0;
            FILE* arquivo = fopen(out,"rb");
            if(!arquivo) printf("Arquivo inexistente!\n");
            else {
                printf("Digite o nome do arquivo de saida (exemplo.txt): ");
                char nomeSaida[200];
                fgets(nomeSaida,200, stdin);
                nomeSaida[strlen(nomeSaida)-1] = 0;
                unpack(arquivo, nomeSaida);
                printf("Arquivo descompactado!\nPressione enter para continuar...");
                getchar();
                system("clear");
            }

        }
        else {
            break;
        }

    }
}