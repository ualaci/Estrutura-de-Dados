#include "HashTable.h"

int hashing(int key,int size){
	int pos=key%size;
	return pos;}
	
hash* createNode(int key){
	hash *newHash=(hash*)malloc(sizeof(hash));
	newHash->key=key;
	newHash->next=NULL;
	return newHash;
}
	
hash** insertTable(hash **hs,hash *newHash, int pos,int size){
	if (hs[pos]==NULL){
		hs[pos]=newHash;
		return hs;
	}
		
	else{
		newHash->next= hs[pos];
		hs[pos]=newHash;
		return hs;
	}
}
		
hash** removeTable(hash **hs,int key,int pos){
	hash *aux1=hs[pos],*ant=NULL;
	if (aux1==NULL){
		puts("\nValor nao existente");
		return hs;
	}
		
	if (aux1->key==key){
		hs[pos]=aux1->next;
		free(aux1);
		return hs;
	}
		
	while(aux1!=NULL && aux1->key!=key){
		ant=aux1;
		aux1=aux1->next;
	}
	
	if (aux1==NULL){
		puts("\nValor nao existente");
		return hs;
	}
		
	if (aux1->next!=NULL && aux1->key==key){
		ant->next=aux1->next;
		aux1->next=NULL;
		free(aux1);
		return hs;
	}
		
	if (aux1->next==NULL && aux1->key==key){
		free(aux1);
		ant->next=NULL;				
		return hs;
	}
		
	if (aux1->key==key){
		ant->next=aux1->next;
		aux1->next=NULL;
		free(aux1);
		return hs;
	}
}
		
void printTable(hash **hs,int size){
	int i=0;
	puts("");
	for(i=0;i<size;i++){
		hash *aux=hs[i];
		while(aux!=NULL){
			printf("%i\t",aux->key);
			aux=aux->next;
		}
		puts("");
	}
}
		
void searchElem(hash **hs,int size,int key,int pos){
	hash *aux=hs[pos];
	
	if (aux==NULL)	{
		puts("Nao se encontra na tabela\n");
		return ;
	}
		
	while(aux!=NULL && aux->key!=key) aux=aux->next;
	
	if (aux==NULL)	{
		puts("\nNao se encontra na tabela");
		return;
	}
	
	if (aux->key==key)	puts("\nSe encontra na tabela");
}






