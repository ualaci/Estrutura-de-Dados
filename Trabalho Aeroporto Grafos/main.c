#include "aeroporto.h"

int main(){
    malhaAereaM *M = NULL;
    int qtdAeroportos = 0;
    int opPrincipal = 0;
    int opSecundario = 0;
    int opFuncoes = 0;

    M = criarMalhaAerea(); // CRIANDO A MALHA AÉREA
    do{
        opPrincipal = menuPrincipal();
        if(opPrincipal == 1 || opPrincipal == 2){
            do{
                opSecundario = menuSecundario();
                if(opSecundario == 1 || opSecundario == 2){
                    if(opSecundario == 1){
                        M = carregarMalhaAerea(M); // CARREGANDO BANCO DE DADOS
                    }else if(opSecundario == 2){
                        printf("Informe a quantidade de aeroportos da malha aerea: ");
                        scanf("%d", &qtdAeroportos);
                        M = popularMalhaAerea(M, qtdAeroportos);
                        // gravar(M); // GRAVANDO INFORMAÇÕES NO BANCO DE DADOS
                    }else if(opSecundario == 0){
                        printf("Saindo...\n");
                    }else{
                        printf("Opcao invalida!...\n");
                    }
                    opFuncoes = menuFuncoes();
                    if(opFuncoes == 1){
                        //
                    }
                }
            }while(opSecundario != 0);
        }else if(opPrincipal == 0){
            printf("Saindo...\n");
        }else{
            printf("Opcao invalida!!\n");
        }
    }while(opPrincipal != 0);


    //buscaEmLargura(M);
    imprimirMalha(M);
    printf("---------------->>MATRIZ DE DISTANCIA<<----------------\n");
    busca(M);
    return 0;
}



