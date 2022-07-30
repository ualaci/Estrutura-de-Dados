#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*	Faca um programa, em linguagem C que escolha aleatoriamente X valores inteiros armazenando-os em um vetor chamado "listasimples".Construa um vetor adicional
	de ponteiros (chamado apontadores), tambem contendo X posicoes. Em seguida, aponte cada elemento do vetor apontadores para a posicao inversa correspondente
	no vetor listasimples, imprima o vetor listasimples na ordem apontada pelo apontador.*/	


int main(){
	int TAM;
	
	printf("insira o tamanho da lista");
	scanf("%i", &TAM);
	
	int listasimples[TAM];
	int i,j=0;
	int *apontadores;
	
	for (i=0;i<TAM;i++){
		apontadores = (int*)malloc(TAM*sizeof(int));
	}
	
	srand((unsigned)time(NULL));
	
	for(i=0;i<TAM;i++){	// preenche o vetor lista simples com valores aleatorios
		listasimples[i] = rand()%1000;
	}
	for(i=TAM-1;i>-1;i--){	// aponta os apontadores para a listasimples como pedido no exercicio
		apontadores[j]=listasimples[i];
		j++;
	}
	
	
	// impressao dos valores
	for(i=0;i<TAM;i++){
		printf("[%i]\t",listasimples[i]);
	}
	printf("\n");
	
	for(i=0;i<TAM;i++){
		printf("[%i]\t",apontadores[i]);
	}
	
	
	
	
}
