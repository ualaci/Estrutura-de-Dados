//Uálaci dos Anjos Júnior
//Uarlley Nascimento Amorim
//disciplina de estrutura de dados 2

#ifndef TESTE_H
#define TESTE_H
/*Definição da estrutura e funções para avaliar a implementação da AVL.*/

//Inclusão das bibliotecas padrão.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Info_{
    char* categoria; //Declaração da categoria do produto.
    char* fabricante; //Declaração do fabricante do produto.
    long long numeroSerie; //Declaração do numero de serie do produto.
    char* modelo; //Declaração do modelo de serie do produto.
    float preco; //Declaração do numero do preço do produto.

    int peso; //Declaração do peso utilizado como fator ordenação dos produtos.
}Info;
//Função que compara dois PRODUTOS. Utilizada na função de inserção
int compInfo(void* A, void* B);

//Função que calcula e retorna a soma dos caracteres de uma palavra utilizando os valores da tabela ASCII.
int wordValue(char* word);

//Função que calcula e retorna o peso de um produto, para determinar sua posição na arvore.
int calculaPeso(char* modelo, long numeroSerie);

/*Função utilizada para criar um produto. Returna um elemento de informação
contendo os dados de um produto ou NULL se a alocação de memoria de algum campo for mal sucedida*/
Info* createInfo(char* categoria, char* fabricante, long long numeroSerie, char* modelo, float preco);

//Função que copia as informações de um produto a para um produto b.
void copy(void* a, void* b);

//Função que exclui um produto e libera a memoria utilizada pelo mesmo.
void liberaDados(void* informacao);

//Função utilizada para imprimir os dados de um produto, omitindo apenas o peso.
void imprimeDados(void* informacao);

//Função que compara um número de série com um produto qualquer. Utilizada em funções de busca e remoção.
int compKey(void* key, void* info);

#endif