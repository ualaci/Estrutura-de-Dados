#include "aeroporto.h"

/*
    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                        >> IMPLEMENTAÇÃO  DA FUNÇÕES QUE EXIBEM OS MENUS <<
    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/* >> IMPLEMENTAÇÃO DA FUNÇÃO QUE EXIBE O MENU PRINCIPAL << */
int menuPrincipal(){
    int op = 0;

    printf("1. UTILIZAR MATRIZ DE ADJACENCIA | 2. LISTA DE ADJACENCIA | 0. SAIR \n ");
    scanf("%d", &op);

    return op;
}

/* >> IMPLEMENTAÇÃO DA FUNÇÃO QUE EXIBE O MENU SECUNDÁRIO << */
int menuSecundario(){
    int op = 0;

    printf("1. CARREGAR ARQUIVO | 2. CONSTRUIR NOVA MALHA AEREA | 0. SAIR \n ");
    scanf("%d", &op);

    return op;
}

/* >> IMPLEMENTAÇÃO DA FUNÇÃO QUE EXIBE O MENU DE FUNCOES << */
int menuFuncoes(){
    int op = 0;

    printf("1. INSERIR NOVO AEROPORTO | 2. REMOVER AEROPORTO | 3. BUSCAR AEROPORTO | 4. INFORMACOES DA MALHA AEREA |  5. DESTRUIR MALHA | 0. SAIR \n ");
    scanf("%d", &op);

    return op;
}

/*---------------------------------------------------------------------------->>>> FIM DA IMPLEMENTAÇÃO <<<<----------------------------------------------------------------------------*/

/*
    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                >>IMPLEMENTAÇÃO DAS FUNÇÕES QUE MANIPULAM A MALHA AÉREA UTILIZANDO MATRIZ DE ADJACÊNCIA<<
    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/* >> IMPLEMENTAÇÃO DA FUNÇÃO QUE CRIA A MALHA AÉREA << */
malhaAereaM *criarMalhaAerea(){
    malhaAereaM *M = (malhaAereaM *)calloc(1, sizeof(malhaAereaM));

     /* -- VERIFICANDO SE A ALOCAÇÃO DA MALHA AÉREA FOI BEM SUCEDIDA. CASO NÃO SEJA, O PROGRAMA É ABORTADO -- */
    if(!M){
        printf("Erro de alocacao! Abortando o programa...\n");
        exit(1);
    }

    return M;
}

/* >> IMPLEMENTAÇÃO DA FUNÇÃO QUE INICIALIZA A MALHA AÉREA << */
malhaAereaM *inicializarMalhaAerea(malhaAereaM *M, int qtdAeroportos){
    int i = 0;

    /* -- INICIALIZANDO AS CARACTERÍSTICAS DA MALHA  --*/
    M->qtdAeroportos = qtdAeroportos;
    M->qtdConexoes = 0;
    M->matrizAdj = (int **)calloc(qtdAeroportos, sizeof(int *));
    M->custo = (float **)calloc(qtdAeroportos, sizeof(float *));
    M->distancia = (float **)calloc(qtdAeroportos, sizeof(float *));
    M->tempo = (int **)calloc(qtdAeroportos, sizeof(int *));
    for(i = 0; i < qtdAeroportos; i++){
        M->matrizAdj[i] = (int *)calloc(qtdAeroportos, sizeof(int));
        M->custo[i] = (float *)calloc(qtdAeroportos, sizeof(float));
        M->distancia[i] = (float *)calloc(qtdAeroportos, sizeof(float));
        M->tempo[i] = (int *)calloc(qtdAeroportos, sizeof(int));
    }
    return M;
}

// FUNÇÃO QUE POPULA A MALHA AEREA
malhaAereaM *popularMalhaAerea(malhaAereaM *M, int qtdAeroportos){
    int i;
    int j;
    int destino;
    int qtdConexoes;
    int tempo;
    float custo;
    float distancia;

    /* -- INICIALIZANDO AS CARACTERÍSTICAS DA MALHA  --*/
    M->qtdAeroportos = qtdAeroportos;
    M->qtdConexoes = 0;
    M->matrizAdj = (int **)calloc(qtdAeroportos, sizeof(int *));
    M->custo = (float **)calloc(qtdAeroportos, sizeof(float *));
    M->distancia = (float **)calloc(qtdAeroportos, sizeof(float *));
    M->tempo = (int **)calloc(qtdAeroportos, sizeof(int *));
    for(i = 0; i < qtdAeroportos; i++){
        M->matrizAdj[i] = (int *)calloc(qtdAeroportos, sizeof(int));
        M->custo[i] = (float *)calloc(qtdAeroportos, sizeof(float));
        M->distancia[i] = (float *)calloc(qtdAeroportos, sizeof(float));
        M->tempo[i] = (int *)calloc(qtdAeroportos, sizeof(int));
        printf("Informe a quantidade de conexoes do aeroporto: A[%d]: ", i+1);
        scanf("%d", &qtdConexoes);
        for(j = 0; j < qtdConexoes; j++){
            printf(">>Origem: A[%d]<<\n", i+1);
            printf("Destino:");
            scanf("%d", &destino);
            printf("Origem:\t Destino:\n");
            printf("A[%d]\t A[%d]", i+1, destino);
            M->matrizAdj[i][destino-1] = 1;
            printf("\nCusto da viagem (R$): ");
            scanf("%f", &custo);
            M->custo[i][destino-1] = custo;
            printf("Distancia da viagem (km): ");
            scanf("%f", &distancia);
            M->custo[i][destino-1] = distancia;
            printf("Tempo da viagem (h): ");
            scanf("%d", &tempo);
            M->tempo[i][destino-1] = tempo;
            M->qtdConexoes++;
        }
    }
    return M;
}

/* >> IMPLEMENTAÇÃO DA FUNÇÃO QUE IMPRIME AS INFORMAÇÕES  DA MALHA AÉREA << */
void imprimirMalha(malhaAereaM *M){
    int i, j;
    if(M){
        printf("---------------->>MATRIZ DE ADJACENCIA<<----------------\n");
        for(i = 0; i < M->qtdAeroportos; i++){
                for(j = 0; j < M->qtdAeroportos; j++){
                    printf("[%d]", M->matrizAdj[i][j]);
                }
                printf("\n");
        }
        printf("---------------->>MATRIZ DE CUSTO<<----------------\n");
        for(i = 0; i < M->qtdAeroportos; i++){
                for(j = 0; j < M->qtdAeroportos; j++){
                    printf("[%.1f]", M->custo[i][j]);
                }
                printf("\n");
        }
        printf("---------------->>MATRIZ DE DISTANCIA<<----------------\n");
        for(i = 0; i < M->qtdAeroportos; i++){
                for(j = 0; j < M->qtdAeroportos; j++){
                    printf("[%.1f]", M->distancia[i][j]);
                }
                printf("\n");
        }
        printf("---------------->>MATRIZ DE TEMPO<<----------------\n");
        for(i = 0; i < M->qtdAeroportos; i++){
                for(j = 0; j < M->qtdAeroportos; j++){
                    printf("[%d]", M->tempo[i][j]);
                }
                printf("\n");
        }
    }
}

/* >> IMPLEMENTAÇÃO DA FUNÇÃO QUE LÊ AS INFORMAÇÕES  DO BANCO  DE DADOS  E INSERE NA MALHA AÉREA << */
malhaAereaM *carregarMalhaAerea(malhaAereaM *M){
    int dim;
    int linha;
    int coluna;
    FILE* conexao;
    FILE* custo;
    FILE* distancia;
    FILE* tempo;

// ABRE O ARQUIVO COM AS INFORMAÇÕES DE CONEXÃO, CUSTO, DISTANCIA E TEMPO EM MODO LEITURA
    conexao = fopen("conexao.txt","rt");
    custo = fopen("custo.txt","rt");
    distancia = fopen("distancia.txt","rt");
    tempo = fopen("tempo.txt","rt");

    // VERIFICANDO DE A ABERTURA FOI BEM SUCEDIDA, CASO CONTRÁRIO O PROGRAMA É ABORTADO
    if (!conexao || !custo ||  !distancia || !tempo) {
            printf("Erro no carregamento do banco de dados!\n");
            exit(1);
    }

    //   LENDO A DIMENSÃO DA MATRIZ
    fscanf(conexao, "%d ",&dim);

    // ATUALIZANDO A INFORMAÇÃO DA MALHA AÉREA REFERENTE A QUANTIDADE DE AEROPORTOS
    M->qtdAeroportos = dim;

    // ALOCANDO A MATRIZ DE ADJACÊNCIA, CUSTO, DISTÂNCIA E TEMPO
    M->matrizAdj = (int **)malloc(dim *sizeof(int *));
    M->custo= (float **)malloc(dim *sizeof(float *));
    M->distancia = (float **)malloc(dim *sizeof(float *));
    M->tempo = (int **)malloc(dim *sizeof(int *));
    for(linha = 0;linha < dim; linha++){
        M->matrizAdj[linha] = (int *)malloc(dim * sizeof(int));
        M->custo[linha] = (float *)malloc(dim * sizeof(float));
        M->distancia[linha] = (float *)malloc(dim * sizeof(float));
        M->tempo[linha] = (int *)malloc(dim * sizeof(int));
        for(coluna = 0; coluna < dim; coluna++){
            fscanf(conexao,"%d", &M->matrizAdj[linha][coluna]);
            fscanf(custo,"%f", &M->custo[linha][coluna]);
            fscanf(distancia,"%f", &M->distancia[linha][coluna]);
            fscanf(tempo,"%d", &M->tempo[linha][coluna]);
            if(M->matrizAdj[linha][coluna])
                M->qtdConexoes++;
        }
    }
    printf("Quantidade de conexoes: %d\n", M->qtdConexoes);
    printf("Quantidade de aeroportos: %d\n", M->qtdAeroportos);
    imprimirMalha(M);
    return M;
}

void buscaEmProfundidade(malhaAereaM* M, int ini, int *visitado, int cont){
    visitado[ini] = cont;
    int i;
        for(i=0;i<M->qtdAeroportos;i++){
            printf("i = %d\n", i);
            if ((M->matrizAdj[ini][i])!=0){

                if(!visitado[(M->matrizAdj[ini][i])])
                    buscaEmProfundidade(M,i,visitado,cont+1);

            }
        }
}

void busca(malhaAereaM *M){
    int ini = 0;
    tipoRota escala[M->qtdAeroportos];

    int visitado[M->qtdAeroportos];
    int i , cont = 1;

    for(i = 0; i <M->qtdAeroportos; i++){
        visitado[i] = 0;
        buscaEmProfundidade(M, ini, visitado, cont);
    }
        for(i = 0; i < M->qtdAeroportos; i++){
            printf("V[%d] = %d\n", i, visitado[i]);
        }
}

/* >> IMPLEMENTAÇÃO DA FUNÇÃO QUE CRIA ROTA ENTRE O AEROPORTO DE ORIGEM E DESTINO << */

