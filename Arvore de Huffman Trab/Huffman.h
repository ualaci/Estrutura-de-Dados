//Uarlley do Nascimento Amorim - 2018205346
//Ualaci dos Anjos Junior - 2017102015

#ifndef _HUFFMAN_H
#define _HUFFMAN_H
#include "BST.h"

//--------------------------------------------------------------------------------------------------------
//Definicao da estrutura de uma tabela
//--------------------------------------------------------------------------------------------------------
typedef struct tabela {
    bool* vet;//Possui um vetor de booleanos para salvar o codigo do caractere
    int size;//O tamanho do vetor de booleanos
    char caractere;//armazena o caractere salvo
}tab;

//--------------------------------------------------------------------------------------------------------
//Funcao que cria a arvore utilizando o algoritmo de Ruffman
//--------------------------------------------------------------------------------------------------------
BSTNode* huffman(Node* lista, int size);
//--------------------------------------------------------------------------------------------------------
//Funcao que cria uma nova tabela
//--------------------------------------------------------------------------------------------------------
tab* criaTabela(int sizeTree, int sizeList);

//deletar
void printTabela(tab* tabela, int sizeTab);

//--------------------------------------------------------------------------------------------------------
//Funcao que busca um caractere em uma tabela
//--------------------------------------------------------------------------------------------------------
int searchTab(tab* tabela, char caractere, int tabSize);

//--------------------------------------------------------------------------------------------------------
//Funcao que escreve os caracteres e seus respectivos codigos
//--------------------------------------------------------------------------------------------------------
void writeTab(BSTNode* root, tab tabela[],bool vet[], int *size, int* sizeTab);

//--------------------------------------------------------------------------------------------------------
//Funcao que contabiliza a quandotidade de caracteres presentes no arquivo de entrada
//--------------------------------------------------------------------------------------------------------
long long countSizeOut(tab* tabela, int sizeTab, BSTNode* root);

//--------------------------------------------------------------------------------------------------------
//Funcao busca um caractere na tabela utilizando seu codigo
//--------------------------------------------------------------------------------------------------------
int verificaInLista(bool* binVet, int ini, int fim, tab* tabela, int sizeTab);

//--------------------------------------------------------------------------------------------------------
//Funcao que escreve o arquivo de saida a partir do arquivo binario
//--------------------------------------------------------------------------------------------------------
void imprimeSaida(char* nomeSaida,bool* binVet, int size, tab* tabela,int sizeTab,long long charQnt);

//--------------------------------------------------------------------------------------------------------
//Funcao que calcula e retorna o valor binario de um  unsigned char*
//--------------------------------------------------------------------------------------------------------
bool* intToBin (unsigned char vet[], int size);
//--------------------------------------------------------------------------------------------------------
//Definição da estrutura que segura o elemento de informação
//--------------------------------------------------------------------------------------------------------
Node* leArquivo(char* nomeArquivo, int* sizeList, long long* charQnt);

//--------------------------------------------------------------------------------------------------------
//Funcao que comprime o codigo de um caractere em um codigo com 1/8 do tamanho + 1
//--------------------------------------------------------------------------------------------------------
void bitToBit(bool vet[], int size, int* posicao, unsigned char saida[]);

//--------------------------------------------------------------------------------------------------------
//Função que realiza a descompactacao
//--------------------------------------------------------------------------------------------------------
void unpack(FILE* arquivo, char* nomeSaida);

//--------------------------------------------------------------------------------------------------------
//funcao que compacta e salva o arquivo compactado
//--------------------------------------------------------------------------------------------------------
void pack(char* nomeArquivo, unsigned char saida[], int sizeSaida, tab* tabela, int sizeTab, int sizeTree, long long charQnt);

//--------------------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------------------
void writeBin(tab tabela[], char* nomeEntrada, char* nomeSaida, long long countSizeOut, int sizeTab,int sizeTree,long long charQnt);

//--------------------------------------------------------------------------------------------------------
//Definição da estrutura que segura o elemento de informação
//--------------------------------------------------------------------------------------------------------
int frequenciaNo(BSTNode* root, bool* vet);

//--------------------------------------------------------------------------------------------------------
//Funcao que libera a memoria alocada em uma tabela
//--------------------------------------------------------------------------------------------------------
void freeTabela(tab* tabela, int sizeTab);

#endif
