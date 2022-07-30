//Uálaci dos Anjos Júnior
//Uarlley Nascimento Amorim
//disciplina de estrutura de dados 2

/*Definição das funções que serão utilizadas na avaliação da implementação da AVL */
#include "Teste.h" //Inclusão da estrutura e cabeçalho das funções

//--------------------------------------------------------------------------------------------------------
int wordValue(char* word){
    int soma=0,i; //Definição da variavel soma, que armazena o valor número de uma string.
    for(i=0;i<strlen(word);i++) soma+=(int)(word[i]); /* Percorre toda a string somando
                                                        o valor número de seus caracteres*/
    return soma; // retorna a soma dos caracteres.
}
//--------------------------------------------------------------------------------------------------------
int calculaPeso(char* modelo, long numeroSerie){
    return wordValue(modelo) + numeroSerie%1000; /*Calcula o valor valor númerico da string modelo e
                                                    soma com o resto da divisão do numero de serie por 1000*/
}
//--------------------------------------------------------------------------------------------------------
Info* createInfo(char *categoria, char* fabricante, long long numeroSerie, char *modelo, float preco){
    Info* info = (Info*)malloc(sizeof(Info)); //Alocação de memoria para os dados do produto
    if (!info) return NULL;
    if(info){  //Define os dados apenas se a alocação de memória for bem sucedida.

        //Os campos de texto são preenchidos apenas se a alocação de memória dos mesmos for bem sucedida
        if(info->categoria = (char*)malloc(53*sizeof(char)))
            strcpy(info->categoria,categoria);
        else return NULL;

        if(info->fabricante = (char*)malloc(53*sizeof(char)))
            strcpy(info->fabricante,fabricante);
        else return NULL;

        if(info->modelo = (char*)malloc(53*sizeof(char)))
            strcpy(info->modelo, modelo);
        else return NULL;

        //Como os demais campos não necessitam de alocação dinâmica, basta utilizar a declaração padrão
        info->numeroSerie = numeroSerie;
        info->preco = preco;
        //Utiliza a função calculaPeso para determinar o peso de um produto na arvore
        info->peso = calculaPeso(modelo, numeroSerie);
    }
    return info; //Retorna o produto com todos seus dados definidos ou simplesmente NULL.
}
//--------------------------------------------------------------------------------------------------------
int compKey(void* key , void* info){

    /*Casting das variaveis do tipo generico para os tipos referentes
    ao peso e informação do produto*/
    int* peso = (int*) key;
    Info* auxInfo = (Info*)info;
    /*Compara o peso do produto com o peso do produto informado e retorna os valores
    referentes ao resultado da comparação*/
    if (*peso == auxInfo->peso) return 0;
    if(*peso > auxInfo->peso) return 1;
    return -1;
}

//--------------------------------------------------------------------------------------------------------
int compInfo(void* A, void* B){
    /*Casting dos parametros de tipo generico para o tipo informação de um produto*/
    Info* a = (Info*)A;
    Info* b = (Info*)B;

    /*Compara o peso A com o peso do produto B e retorna os valores
    referentes ao resultado da comparação*/
    if (a->peso > b->peso) return 1;
    if(a->peso < b->peso) return -1;
    return 0;
}
//--------------------------------------------------------------------------------------------------------
void copy(void* A, void* B){
    /*Casting dos parametros de tipo generico para o tipo informação de um produto*/
    Info* a = (Info*)A;
    Info* b = (Info*)B;

    /*Copia as variaveis que não precisam de alocação dinâmica*/
    a->peso = b->peso;
    a->preco = b->preco;
    a->numeroSerie =  b->numeroSerie;

    /*Utiliza a função strcopy para copiar os dados de tipo char* de um produto a para um produto b*/
    strcpy(a->fabricante, b->fabricante);
    strcpy(a->modelo, a->modelo);
    strcpy(a->categoria, a->categoria);
}
//--------------------------------------------------------------------------------------------------------
void liberaDados(void* informacao){
    /*Casting do parametro de tipo genérico para o tipo informação de um produto*/
    Info* info = (Info*)informacao;

    /*Liberação da memoria alocada dinamicamente pelas variáveis de tipo char*/
    free(info->categoria);
    free(info->modelo);
    free(info->fabricante);
}
//--------------------------------------------------------------------------------------------------------
void imprimeDados(void* informacao){
    /*Casting do parametro de tipo genérico para o tipo informação de um produto*/
    Info* info = (Info*)informacao;

    /*Impressão dos dados do produto*/
    printf("\n----------------------\n");
    printf("Categoria: %s\n", info->categoria);
    printf("Fabricante: %s\n", info->fabricante);
    printf("Modelo: %s\n", info->modelo);
    printf("Numero de Série: %lld\n",info->numeroSerie);
    printf("Preço: R$ %.2f\n", info->preco);
    printf("----------------------\n");
}




