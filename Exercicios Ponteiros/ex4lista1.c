#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
	int TAM,i,j;//declarando contadores e tamanho do vetor
	//declarando vetor principal e vetor de ponteiros e o ponteiro auxiliar
	int *listasimples;
	int **apontadores,*aux;
	
	printf("digite o tamanho do vetor");
	scanf("%i", &TAM);
	//alocando dinamicamente e gerando valores aleatorios
	srand ((unsigned)time(NULL));
	listasimples= (int*)malloc(TAM*sizeof(int));
	apontadores = (int**)malloc(TAM*sizeof(int*));
	//inserindo valores aleatorios no vetor principal e apontando o vetor de ponteiros para esse vetor principal
	for(i=0;i<TAM;i++){
		listasimples[i] = rand()%1000;
		apontadores[i] = &listasimples[i];
	}
	// reordenando a ordem de apontamento de cada posicao do vetor de ponteiros referente as posicoes do vetor principal 
	for(i=0;i<TAM;i++){
		
		for(j=i+1;j<TAM;j++){
			
			if (*apontadores[j]<*apontadores[i]){
				aux=apontadores[i];
				apontadores[i]=apontadores[j];
				apontadores[j]=aux;
			}
				
		}
	}
	// imprimindo valores
	for(i=0;i<TAM;i++){
		printf("[%i]\t",listasimples[i]);
	}
	printf("\n");
	
	for(i=0;i<TAM;i++){
		printf("[%i]\t", *apontadores[i]);
	}
	
}
