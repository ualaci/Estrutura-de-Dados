//Uarlley do Nascimento Amorim - 2018205346
//Ualaci dos Anjos Junior - 2017102015

//Inclusão das bibliotecas padrões do C
//--------------------------------------------------------------------------------------------------------
#ifndef _BST_H
#define _BST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//--------------------------------------------------------------------------------------------------------
//Definicao da estrutura que segura o elemento de informacao
//--------------------------------------------------------------------------------------------------------
typedef struct {
    int frequencia;
    char caractere;
}Info;

//--------------------------------------------------------------------------------------------------------
//Definicao da estrutura BSTNode
//--------------------------------------------------------------------------------------------------------
typedef struct tnode {
    struct tnode* left;
    struct tnode* right;
    int freq;//possui um campo frequencia para nos nao-folha
    Info* info;//apenas os nos folha possuem um campo info
}BSTNode;

//--------------------------------------------------------------------------------------------------------
//Definiçao da estrutura de um no de lista
//--------------------------------------------------------------------------------------------------------
typedef struct lnode {
    struct lnode* next;
    BSTNode* bstnode; //Contem um ponteiro para um no de arvore para utilizar no algoritmo de Ruffman
}Node;

//--------------------------------------------------------------------------------------------------------
//Funcao que seleciona e retorna a frequencia presente em um no de lista
//--------------------------------------------------------------------------------------------------------
int getFreq(Node* node);

//--------------------------------------------------------------------------------------------------------
//Funcao que seleciona e retorna o caractere de um no de lista
//--------------------------------------------------------------------------------------------------------
char getBstChar(Node* node);

//--------------------------------------------------------------------------------------------------------
//Funcao que insere um elemento elemento em uma lista
//--------------------------------------------------------------------------------------------------------
Node* insertList(Node* head, BSTNode* bstnode);

//--------------------------------------------------------------------------------------------------------
//Funcao que cria e retorna um nó de lista
//--------------------------------------------------------------------------------------------------------
Node* createNode(BSTNode* bstnode);

//--------------------------------------------------------------------------------------------------------
//Funcao que cbusca e retorna a posicao de um elemento na lista
//--------------------------------------------------------------------------------------------------------
int searchList(Node* head, char caractere);

//--------------------------------------------------------------------------------------------------------
//Funcao que cria o elemento de informacao tanto dos BSTNodes e dos Nodes
//--------------------------------------------------------------------------------------------------------
Info* createInfo(char caractere, int freq);

//--------------------------------------------------------------------------------------------------------
//Funcao que cria um nó para uma BST
//--------------------------------------------------------------------------------------------------------
BSTNode* createBSTNode(Info* info, int freq);

//--------------------------------------------------------------------------------------------------------
//Funcao que calcula a altura de uma BST
//--------------------------------------------------------------------------------------------------------
int heightBST(BSTNode* root);

//--------------------------------------------------------------------------------------------------------
//Funcao que libera a memoria alocada por uma arvore
//--------------------------------------------------------------------------------------------------------
void destroyBST(BSTNode* root);

//--------------------------------------------------------------------------------------------------------
//Funcao que imprime as ocorrencias de um caractere em uma lista
//--------------------------------------------------------------------------------------------------------
void imprimeOcorrencias(Node* head);

//--------------------------------------------------------------------------------------------------------
//Funcao imprime a arvore de Huffman utilizando o caminho em-ordem
//--------------------------------------------------------------------------------------------------------
void imprimeCodHuffman(BSTNode* root);
#endif