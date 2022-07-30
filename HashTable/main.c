#include "HashTable.h"

int main (){
	int i=0,j=0,key,key1,pos=0,size,op=-1;
	hash **hs;
	puts("");
	printf("Entre com o tamanho da tabela: ");
	scanf("%i",&size);
	hs=(hash**)calloc(size,sizeof(hash*));
	
	puts("----------------------------------------------------MENU----------------------------------------------------------------");
	puts("Entre com a opcao:\n1 - Inserir\n2 - Imprimir\n3 - Remover\n4 - Buscar elemento\n0 - Sair");
	puts("\n-----------------------------------------------------------------------------------------------------------------------");
	
	while(op!=0){
		
		scanf("%i",&op);
		switch(op){
			
		case(1):
			printf("Entre com a chave para inserir: ");
			scanf("%i",&key);
			hash *newHash=createNode(key);
			pos=hashing(key,size);
			hs=insertTable(hs,newHash,pos,size);						
			break;
			
		case(2):
			printTable(hs,size);
			break;
			
		case(3):
			printf("Entre com a chave: ");
			scanf("%i",&key);
			pos=hashing(key,size);
			hs=removeTable(hs,key,pos);
			break;
			
		case(4):
			printf("Entre com um valor a ser buscado: ");
			scanf("%i",&key1);
			pos=hashing(key1,size);
			searchElem(hs,size,key1,pos);
			break;
		}
	}
}
