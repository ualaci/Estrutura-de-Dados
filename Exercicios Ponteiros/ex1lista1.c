#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/*	Faca um programa, em linguagem C que escolha aleatoriamente 50 valores inteiros armazenando-os em um vetor chamado "litasimples".Crie duas variaveis
	chamadas respectivamente ptr_menor e ptr_maior.Em seguida, aponte estas variaveis, respectivamente, para o menor e o maior elemento desse vetor*/	


int main(){
	int listasimples[50];
	int i;
	int *ptr_menor=&listasimples[0] , *ptr_maior=&listasimples[0];
	
	srand((unsigned)time(NULL));
	
	for(i=0;i<50;i++){
		listasimples[i] = rand()%1000;
	}
	
	for(i=1;i<50;i++){	// aponta os ponteiros ptr_maior e ptr_menor para o maior e o menor valor existente no vetor, respectivamente.
		if (*ptr_menor>listasimples[i])
			ptr_menor = &listasimples[i];
		if (*ptr_maior<listasimples[i])
			ptr_maior = &listasimples[i];
		
	}
	// impressao dos valores
	for(i=0;i<50;i++){
		printf("[%i]\t",listasimples[i]);
	}
	printf("\n");
	
	printf("o maior valor eh: %i \no menor valor eh: %i", *ptr_menor,*ptr_maior);
	
	
	
}
