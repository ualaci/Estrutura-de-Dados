#ifndef _SKIPLIST_H
#define _SKIPLIST_H

#include <stdio.h>
#include <stdlib.h>
#define TAM 5//constante referente ao nivel maximo da lista

// o Programa recebe a entrada e ou E para sair

typedef struct _node{//struct utilizada para a alocacao dos nos.
	int value;
	int level;
	struct _node** next;
}node;

typedef struct {//struct utilizada para armazenar os elementos do caminho de busca da funcao searchList.
	node** pointer;
	int size;
}search;

node* createNode(int value, int level);//cria um no e o retorna com os campos preenchidos com os parametros de entrada.

node* createHead();//cria um no e o retorna com valores inteiros iguais a zero e os ponteiros apontando pra nulo para ser utilizado como no cabeca.

int isEmptyList(node* head);//verifica se a lista esta vazia e retorna 1 caso verdade e 2 caso falso.

search* searchList(node* h, int value, int isPrintTrue, int size);//busca um elemento na lista e retorna o caminho de busca por esse elemento.

int insertList(node* h, int value, int level, int* size);//insere um elemento na lista e retorna 1 em caso de sucesso e 2 em caso de falha.

int removeList(node* h, int value, int *size);//remove um elemento na lista e retorna 1 em caso de sucesso e 2 em caso de falha.

void printList(node* head);//imprime a lista toda.

void printListH(node* head, int level);//imprime os elementos contidos num determinado nivel da lista.




#endif
