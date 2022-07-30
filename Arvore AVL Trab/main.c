//Uálaci dos Anjos Júnior
//Uarlley Nascimento Amorim
//disciplina de estrutura de dados 2

//Programa principal para realizar os testes na AVL implementada.
#include "AVL.h"//Inclução dos cabeçalhos das funções e estruturas da AVL.
#include "Teste.h"
/*Este programa simula um inventário de produtos diversificados.
Tais produtos devem possuir:
    -categoria;
    -fabricante;
    -modelo;
    -número de série;
-   -preço em reais.
A posição dos produtos na AVL é determinada pelo campo peso presente na estrutura.
Para a busca e remoção, é utilizado como elemento de busca o número de série do produto.
Não são inseridos produtos com um mesmo número de série.*/

int main(){
    int op,ok; /*Op: variavel que define qual operação será realizada.
                ok: variável que define se a operação teve sucesso ou não.*/
    long long serie; //Variável que recebe um número de série do produto.
    char mod[53]; // Variável que recebe um número de série do produto.
    AVLNode* root = NULL; //Definição da raiz da AVL;

    while(1){ //Loop para manter o menu de operações
        //system("clear");
        printf("\n -----------------------------------\n");
        printf("| 1 - Dar entrada em um produto     |\n");
        printf("| 2 - Buscar um produto             |\n");
        printf("| 3 - Remover um produto do estoque |\n");
        printf("| 4 - Imprimir lista de produtos    |\n");
        printf("| 5 - Sair                          |\n");
        printf(" -----------------------------------\n");

        //Leitura da operação a ser realizada
        if(!scanf("%d",&op)){
            printf("Não foi possível concluir a leitura!\n");
            exit(1);
        }
        getchar();

        //Inicia a operação de inserção
        if(op==1) {
            //system("clear");
            //Variaveis que receberão os dados do novo produto
            char categoria[53];
            float preco;
            char fabricante[53];

            //Dados do elemento novo elemento:
            printf("Preencha as informações do produto:\n");
            printf("\tCategoria: ");
            if(!fgets(categoria, 53, stdin)) {
                printf("Não foi possível concluir a leitura!\n");
                exit(1);
            }
            categoria[strlen(categoria) - 1] = 0;

            printf("\tFabricante: ");
            if(!fgets(fabricante, 53, stdin)) {
                printf("Não foi possível concluir a leitura!\n");
                exit(1);
            }
            fabricante[strlen(fabricante) - 1] = 0;

            printf("\tModelo: ");
            if(!fgets(mod, 53, stdin)){
                printf("Não foi possível concluir a leitura!\n");
                exit(1);
            }
            mod[strlen(mod) - 1] = 0;

            printf("\tNúmero de Série: ");
            if(!scanf("%lld",&serie)){
                printf("Não foi possível concluir a leitura!\n");
                exit(1);
            }

            printf("\tPreço: ");
            if(!scanf("%f", &preco)){
                printf("Não foi possível concluir a leitura!\n");
                exit(1);
            }
            //Criação do elemento de informação de um produto para finalmente ser inserido na árvore
            Info *info = createInfo(categoria, fabricante, serie, mod, preco);
            if(insertAVL(&root, info, &compInfo)) printf("\nProduto inserido com sucesso!\n");
            else printf("Não foi possível inserir!\nERRO: Número de serie duplicado.\n");
            printf("Pressione enter para continuar...");
            getchar();
            getchar();
        }
        //Inicia a operação de busca
        else if(op ==2){
            //system("clear");
            AVLNode* ref;//Criação do nó temporário para receber o resultado da busca;
            printf("\tDigite o modelo do produto: ");
            if(!fgets(mod, 53, stdin)){
                printf("Não foi possível concluir a leitura!\n");
                exit(1);
            }
            mod[strlen(mod) - 1] = 0;

            printf("\tDigite o número de Série do produto:");
            if(!scanf("%lld",&serie)){
                printf("Não foi possível concluir a leitura!\n");
                exit(1);
            }
            //Realiza a busca na AVL
            int peso = calculaPeso(mod, serie);
            ref = searchAVL(root, &peso,&compKey);

            //Se o elemento não for encontrado é impresso a mensagem abaixo.
            if(ref==NULL) printf("Produto não encontrado!\n");

            //Se o elemento for encontrado, seus dados são impressos.
            else imprimeDados((Info*)ref->info);
            printf("Pressione enter para continuar...");
            getchar();
            getchar();
        }
        //Inicia a operação de remoção
        else if(op==3){
            //system("clear");
            //Realiza a leitura do modelo do produto a ser removido
            printf("\tDigite o modelo do produto: ");
            if(!fgets(mod, 53, stdin)){
                printf("Não foi possível concluir a leitura!\n");
                exit(1);
            }

            mod[strlen(mod) - 1] = 0;

            //Realiza a leitura do numero de serie do produto a ser removido
            printf("\tDigite o número de Série do produto:");
            if(!scanf("%lld",&serie)){
                printf("Não foi possível concluir a leitura!\n");
                exit(1);
            }

            int peso = calculaPeso(mod, serie);

            //Realiza e verifica se a remoção do elemento foi efetuada ou não
            if(deleteAVL(&root, &peso, &compKey , &liberaDados, &copy)) printf("Produto removido!\n");
            else printf("Não foi possível remover o produto!\nERRO: Número de serie não encontrado.\n");
            printf("Pressione enter para continuar...");
            getchar();
            getchar();
        }
        //Realiza a impressão da AVL utilizando o caminho em ordem
        else if(op==4){
            //system("clear");
            printAVL(root,&imprimeDados);
            printf("Pressione enter para continuar...");
            getchar();
        }
        /*Caso o usuário escolha sair do programa, a AVL é destruida liberando toda a memória alocada*/
        else{
          destroyAVL(root,&liberaDados);
          return 0;
        }
    }
}
