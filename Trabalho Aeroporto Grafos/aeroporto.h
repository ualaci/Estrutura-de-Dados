#include <stdio.h>
#include <stdlib.h>

// DEFINIÇÃO DO TIPO DE DADO QUE REPRESENTA UM VÉRTICE DO GRAFO, OU SEJA, UM AEROPORTO DA MALHA AÉREA
#define aeroporto int

// DEFINIÇÃO DA ESTRUTURA QUE REPRESENTA O GRAFO, OU SEJA, A MALHA AÉREA PARA UMA IMPLEMENTAÇÃO UTILLIZANDO MATRIZ DE ADJACÊNCIA
typedef struct grafoM{
    int qtdAeroportos;
    int qtdConexoes;
    int ** matrizAdj;
    float ** custo;
    float ** distancia;
    int **tempo;
}malhaAereaM;

// DEFINIÇÃO DA ESTRUTURA QUE REPRESENTA A ROTA
typedef struct rota{
    aeroporto a;
    int profundidade;
}tipoRota;

/*
    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                        >> DEFINIÇÃO DA FUNÇÕES QUE EXIBEM OS MENUS <<
    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/* >> DEFINIÇÃO DA FUNÇÃO QUE EXIBE O MENU PRINCIPAL << */
int menuPrincipal();

/* >> DEFINIÇÃO DA FUNÇÃO QUE EXIBE O MENU SECUNDÁRIO << */
int menuSecundario();

/* >> DEFINIÇÃO DA FUNÇÃO QUE EXIBE O MENU DE FUNCOES << */
int menuFuncoes();
/*----------------------------------------------------------------->>>> FIM DA DEFINIÇÃO <<<<-----------------------------------------------------------------*/

/*
    --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        >> DEFINIÇÃO DAS FUNÇÕES PARA IMPLEMENTAÇÃO DA MALHA AÉREA UTILIZANDO MATRIZ DE ADJACÊNCIA <<
    --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/* >> DEFINIÇÃO DA FUNÇÃO QUE CRIA A MALHA AÉREA << */
malhaAereaM *criarMalhaAerea();

/* >> DEFINIÇÃO DA FUNÇÃO QUE POPULA A MALHA AÉREA << */
malhaAereaM *popularMalhaAerea(malhaAereaM* M, int qtdAeroportos);

/* >> DEFINIÇÃO DA FUNÇÃO DA FUNÇÃO QUE GRAVA AS INFORMAÇÕES DO GRAFO << */
int gravar(malhaAereaM *M);

/* >> DEFINIÇÃO DA FUNÇÃO QUE IMPRIME A MALHA AÉREA << */
void imprimirMalha(malhaAereaM* M);

// DEFINIÇÃO DA FUNÇÃO QUE CARREGA AS INFORMAÇÕES DO BANCO DE DADOS
malhaAereaM *carregarMalhaAerea(malhaAereaM *M);

/* >> DEFINIÇÃO DA FUNÇÃO QUE REALIZA A BUSCA EM  PROFUNDIDADE << */
void busca(malhaAereaM* M);

/* >> DEFINIÇÃO DA FUNÇÃO QUE REALIZA A BUSCA EM  PROFUNDIDADE << */
void buscaEmProfundidade(malhaAereaM* G, int ini, int *visitado, int cont);

/* >> DEFINIÇÃO DA FUNÇÃO QUE REALIZA A BUSCA EM  LARGURA << */
void buscaEmLargura(malhaAereaM *M);


/*------------------------------------------------------------------------>>>> FIM DA DEFINIÇÃO <<<<------------------------------------------------------------------------*/


