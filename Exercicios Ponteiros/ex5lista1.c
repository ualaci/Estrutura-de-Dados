#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*	fazer um programa que receba um vetor de N posicoes e com um vetor de ponteiro de N/2 posicoes aponte para os N/2 menores
	menores valores do vetor inicial	*/ 
int main(){
	int TAM; //Tamanho do vetor
	int a,i,j,n=0,k; // Contadores e o sinalizador "n"
	
	int *listasimples; //declaracao do vetor principal
	int **apontadores,*aux; //declaracao do vetor de ponteiros e do vetor auxiliar
	
	printf("digite o tamanho do vetor");
	scanf("%i", &TAM);

	//alocacao dinamica dos vetores:
	srand ((unsigned)time(NULL));
	listasimples= (int*)malloc(TAM*sizeof(int));
	aux= (int*)malloc(TAM/2*sizeof(int));
	apontadores = (int**)malloc(TAM*sizeof(int*));
	
	
	//insercao de valores aleatorios no vetor principal
	for(i=0;i<TAM;i++){
		listasimples[i] = rand();
	}
	
	//identificando o maior valor do vetor principal
	
	k=listasimples[i];
	
	for(i=0;i<TAM;i++){
			if (k<listasimples[i])
			k=listasimples[i];
	}
	for(i=0;i<TAM;i++){
		aux[i]=k+1;
	}
	// inserindo um valor que sera sempre maior que o maior valor do vetor principal em cada posicao do vetor aux
	for(i=0;i<TAM/2;i++){
		apontadores[i] = &aux[i];
	}

	//apontando os N/2 menores valores para cada posicao do vetor de ponteiros em ordem crescente
	for(i=0;i<TAM/2;i++){

		//verificando a posicao i do vetor de ponteiro com todas as posicoes do vetor principal e pegando o menor numero do vetor principal contanto que esse valor nao esteja no vetor de ponteiros
		for(j=0;j<TAM;j++){
		n=0;

			if (*(apontadores[i])>listasimples[j]){
			
				//verificando se o valor a ser comparado do vetor principal ja nao esta sendo apontado por nenhuma outra posicao do vetor de ponteiros
				for(k=0;k<TAM/2;k++){
					if ((&listasimples[j])==(apontadores[k])){
						n=1;
					}
						
						}
							}
			// faz a posicao i do ponteiro apontar para a posicao j que esta sendo analizada caso essa posicao ja nao esteja sendo apontada por nenhuma outra posicao do vetor de ponteiro
			if(n==0 && (*(apontadores[i])>listasimples[j])){
				apontadores[i]=&listasimples[j];}}
		
	}
	
	//impressao dos vetores
	for(i=0;i<TAM;i++){
		printf("[%i]\t",listasimples[i]);
	}
	printf("\n");
	
	for(i=0;i<TAM/2;i++){
		printf("[%i]\t", *apontadores[i]);
	}
	
	}
