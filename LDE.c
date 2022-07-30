#include <stdio.h>
#include <stdlib.h>

typedef struct _list{
	int data;
	struct _list *next;
	struct _list *prev;
} list;

list* createhead(){
	list* head = (list*)calloc(1,sizeof(list));
	return head;
}

list* aloc(int data){
	list* novo = (list*)malloc(sizeof(list));
	novo->data = data;
	novo->next = NULL;
	novo->prev = NULL;
	return novo;
}

void insertB(list* pont, list* novo){
	novo->prev = pont->prev;
	pont->prev = novo;
	novo->next = pont;
}

void insertE(list* pont, list* novo){
	list* aux = pont;
	while(aux->next){
		aux = aux->next;
	}
	novo->next = aux->next;
	novo->prev = aux;
	aux->next = novo;
}

list* search(list* pont, int value){
	list* aux = pont;

	while(aux || aux->data == value){
		aux = aux->next;
	}
	return aux;
}

list* insertM(list* pont, list* novo){
	int data;
	list* aux = pont;
	printf("informe o valor no qual o novo valor sera inserido a frente");
	scanf("%i", &data)
	aux = search(aux, data);
	novo->prev = aux;
	novo->next = aux->next;
	aux->next = novo;
}

void delet(list* pont){
	int data;
	list* aux = pont;
	list* aux2;
	printf("informe o valor a ser removido:\n");
	while(aux->data!=data){
		aux=aux->next;
	}
	if (!aux) printf("o elemento nao se encontra na lista");
	aux->prev->next = aux->next;
	aux->next->prev = aux->prev;
	aux->next = NULL;
	aux->prev = NULL;
	free(aux);
}

void print(list* pont){
	list* aux = pont->next;
	while(aux){
		printf("|%i| ", aux->data);
		aux = aux->next;
	}
}
	

int main(){
	list* pont;
	list* novo;
	int value;
	printf("------------------------------------------------------------SELECIONA A OPERACAO A SER REALIZADA---------------------------------------------------------\n");
	printf("\n1: Inserir no comeco da lista 1");
	printf("\n2: Inserir no fim da lista");
	printf("\n3: Inserir a frente de um determinado elemento");
	printf("\n4: Imprimir a lista\n");
	
	do	{	scanf("%i", op);
		if (op==1 || op==2 || op==3){
			printf("informe o valor a ser inserido:");
			scanf("%i", &value);
			novo = aloc(value);
			if (op==1) pont = insertB(pont,novo);
			if (op==2) pont = insertE(pont,novo);
			if (op==3) pont = insertM(pont,novo);
				
		}
		if (op==4) print(pont);
		
	} while(op!=0);
	
	return 0;
	
}
