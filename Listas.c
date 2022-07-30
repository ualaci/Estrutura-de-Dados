#include <stdio.h>
#include <stdlib.h>

typedef struct List{
	int data;
	struct List *next;
	
} list;

/*list *createhead(void){
	list *pont = (list*)malloc(sizeof(list));
	if (pont!=NULL)
		*pont = NULL;
	return pont;
}*/

list *createhead(void){	//CRIA O NO CABECA
	list *pont = (list*)calloc(1,sizeof(list));
	return pont;
}

void remover(list* pont){	//REMOVE UM DETERMINADO ELEMENTO DA LISTA
	list* aux = pont->next;
	pont->next = aux->next;
	aux->next = NULL;
	free(aux);
}
void obliterate(list* pont){ //LIMPA A LISTA INTEIRA DA MEMORIA

	list* aux = pont; 
	
	while(pont!=NULL){
		aux = pont;
		pont = pont->next;
		free(aux);
	}
	free(pont);
}

list* search(list* pont, int value){ // PESQUISA UM DETERMINADO VALOR NA LISTA
	list* aux = pont->next;
	while(aux && aux->data != value)
		aux=aux->next;
	return aux;
}

int count(list* pont){ // CONTA O NUMERO DE ELEMENTOS DA LISTA
	if (!pont)
		return 0;
	list* aux;
	int counter;
	aux = pont;
	while(aux!=NULL){
		aux=aux->next;						//aux=*pont;
											//	*pont=*pont->next;
		counter++;
	}
	return counter;
}

int emptylist(list* pont){ //VERIFICA SE A LISTA E VAZIA
	if (!(pont))
		return 1;
	if (!pont)
		return 1;
	else
		return 0;
}

/*list insertB(list* pont, int dat){
	if (!li)
		return 0; //lista vazia
	list* aux;
	aux = (list*)malloc(sizeof(list));
	aux->data = dat; // fornece o valor para o no a ser inserido
	aux->next = (*pont);//ponteiro de aux aponta para o inicio da lista
	*pont = aux;//inicio da lista aponta para aux
	return 1;
	
}*/

void print(list* pont){	//IMPRIME A LISTA
	
	list* aux = pont->next;
	while(aux){
		printf(" |%i| ", aux->data);
		aux=aux->next;
	}
}

void printinvert(list* pont){	//IMPRIME A LISTA INVERTIDA
	int* vetaux;
	int i=0;
	vetaux = (int*)malloc(sizeof(int)*(count(pont)));
	list* aux = pont->next;
	while(aux){
		vetaux[i]=(aux->data);
		aux=aux->next;
		i++;
	}
	i=i-1;
	while(i>=0){
		printf("|%i|\t", vetaux[i]);
		i--;
	}
	free(vetaux);
}



void insertB(list* pont, list*novo){	//INSERE NO INICIO DA LISTA
	novo->next = pont->next;
	pont->next = novo; 
}

list* aloc(int data){	//ALOCA UM DETERMINADO VALOR NUM PONTEIRO DO TIPO LIST*
	list* aux = (list*)malloc(sizeof(list));
	if(aux){
		aux->data = data;
		aux->next = NULL;
	}
	return aux;
}

void insertM(list* pont, list*novo){	// INSERE NO MEIO DA LISTA
	list* aux =pont->next;
	list* before = NULL;
	while(aux && aux->data<novo->data){
		before = aux;
		aux = aux->next;
	}
	novo->next = aux;
	if (!before)
		pont->next = novo;
	else
		before->next = novo;
}

void insertE(list* pont, list* novo){	//INSERE NO FIM DA LISTA
	while(pont->next){
		pont = pont->next;
	}
	novo->next = pont->next;
	pont->next = novo;
}

list* intercal(list* pont, list* pont2, list* pont3){ //INTERCALA OS VALORES DE DUAS LISTAS NUMA NOVA LISTA
	int sizepont1, sizepont2;
	list* aux = pont;
	list* aux2 = pont2;
	sizepont1 = count(pont);
	sizepont2 = count(pont2);
	list* dataaux = NULL;
	dataaux = (list*)malloc(sizeof(list));
	if(sizepont1==sizepont2){
		while(pont!=NULL){
			dataaux->data = pont->data;
			insertE(pont3, dataaux);
			dataaux->data = pont2->data;
			insertE(pont3,dataaux);
			pont = pont->next;
			pont2 = pont2->next;
		}
	}
	if(sizepont1>sizepont2){
		while(aux2){
			insertE(pont3, aux);
			insertE(pont3,aux2);
			aux = aux->next;
			aux2 = aux2->next;
		}
		while(aux){
			insertE(pont3,aux);
			aux=aux->next;
		}
	}
	if(sizepont1>sizepont2){
		while(aux){
			insertE(pont3, aux);
			insertE(pont3,aux2);
			aux = aux->next;
			aux2 = aux2->next;
		}
		while(aux2){
			insertE(pont3,aux);
			aux=aux->next;
		}
	}
	
}

int main(){
	//DECLARACAO DE VARIAVEIS
	list* pont = NULL;
	list* pont3 = NULL;
	list* novo = NULL;
	list* searc = NULL;
	list* searc2 = NULL;
	list* pont2 = NULL;
	list* novo2 = NULL;
	int op, value;
	//CRIANDO O NO CABECA...
	pont = createhead();
	pont2 = createhead();
	pont3 = createhead();
	
	do{	//MENU DE OPERACOES	
		printf("insira o numero correspondente a operacao que deseja realizar");
		printf("\n1-inserir no inicio");
		printf("\n2-inserir ordenadamente");
		printf("\n3-verificar se a lista e vazia");
		printf("\n4-contar quantos elementos a lista possui");
		printf("\n5- imprimir a lista");
		printf("\n6- busca de um valor na lista");
		printf("\n7 remover elemento do inicio da lista");
		
		printf("\n8-inserir no inicio 2");
		printf("\n9-inserir ordenadamente 2");
		printf("\n10-verificar se a lista 2 e vazia");
		printf("\n11-contar quantos elementos a lista 2 possui");
		printf("\n12- imprimir a lista 2");
		printf("\n13- busca de um valor na lista 2");
		printf("\n14 remover elemento do inicio da lista 2");
		printf("\n15 intercalar listas");
		printf("\n16 imprimir a lista 1 invertida");
		printf("\n17 imprimir lista intercalada\n");
		scanf("%i", &op);
		// CODIGO DE CADA UMA DAS OPCOES
		if (op==1 || op==2){
			
			if(!pont){
				exit (1);
			}
			printf("informe o valor a ser inserido:");
			scanf("%i", &value);
			novo = aloc(value);
			if(!novo) {
				printf("\nERROR! ALOCATION FAILURE --------- ABORTING\n");
				exit (1);
			}
			else{
				if(op==1)
					insertB(pont, novo);
				else
					insertM(pont, novo);
			}

		}
		if(op==7){
			remover(pont);
		}
		if(op==6){
			printf("insira o valor a ser pesquisado:");
			scanf("%i",&value);
			searc = search(pont,value);
			if(searc)
				printf("\nelemento encontrado!\n");
			else
				printf("elemento nao encontrado =(\n)");
		}
		
		if (op==5)
			print(pont);
		
		//-------------------------------------------------LISTA 2------------------------------------------------------------------------------------------------	
		
		if (op==8 || op==9){
			
			if(!pont2){
				exit (1);
			}
			printf("informe o valor a ser inserido:");
			scanf("%i", &value);
			novo2 = aloc(value);
			if(!novo2) {
				printf("\nERROR! ALOCATION FAILURE --------- ABORTING\n");
				exit (1);
			}
			else{
				if(op==8)
					insertB(pont2, novo2);
				else
					insertM(pont2, novo2);
			}
		
		}
		if(op==14){
			remover(pont2);
		}
		if(op==13){
			printf("insira o valor a ser pesquisado:");
			scanf("%i",&value);
			searc2 = search(pont2,value);
			if(searc2)
				printf("\nelemento encontrado!\n");
			else
				printf("elemento nao encontrado =(\n)");
		}
		
		if (op==12)
			print(pont2);
		
		if (op==15){
			intercal(pont, pont2, pont3);
		}
		
		if (op==16)
			printinvert(pont);
			
		if(op==17){
			print(pont3);
		}
	
	} while(op!=0);
	/*
			list* aux = NULL;
			list* aux2 = NULL;
		aux2 = pont2;
		printf("aux2=pont 2, aux2:%i\n", aux2);
		printf("aux2=pont 2, aux2->next:%i\n", aux2->next);
		
		printf("pont: %i\n", pont);
		printf("pont->next: %i\n", pont->next);
		aux = pont;
		printf("aux = pont: %i\n", aux);
		printf("aux = pont aux->next: %i\n", aux->next);
		aux = NULL;
		aux = pont->next;
		printf("aux = pont->next: %i\n", aux);
		aux->next = pont;
		printf("aux->next = pont: %i\n", aux);
		aux ->next = pont->next;
		printf("aux->next = pont->next: %i\n", aux);
		pont->next = aux2;
		printf("pont->next = aux2, pont->next: %i\n",pont->next);
		printf("pont->next = aux2, aux2: %i\n",aux2);
		pont2->next = aux->next;
		printf("pont2->next = aux->next, pont2->next: %i\n",pont2->next);
		printf("pont2->next = aux->next, aux->next: %i\n",aux->next);
		aux = aux->next;
		printf("aux = aux->next, aux: %i\n", aux);*/
	return 0;
}
