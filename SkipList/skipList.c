#include "skipList.h"
// o Programa recebe a entrada e ou E para sair
node* createNode(int value, int level){
	/*Funcao que cria o no que sera inserido na lista. Essa funcao e responsavel por alocar dinamicamente o no
	e em caso de sucesso retornar esse no com os campos de nivel e valor preenchidos com os valores passados como parametro*/
	node* newNode = (node*) calloc(1,sizeof(node));
	newNode->next = (node**) calloc(TAM,sizeof(node*));
	if(!newNode) exit(1);
	newNode->level = level;
	newNode->value = value;
	return newNode;
}

node* createHead(){
	/*essa funcao e semelhante a de criacao do no, a unica diferenca eh que como o no criado e um no cabeca
	nao ha a necessidade de preenchimento dos campos de valor e nivel*/
	node* newHead = (node*) calloc(1,sizeof(node));
	newHead->next = (node**) calloc(TAM,sizeof(node*));
	return newHead;
}

int isEmptyList(node* head){
	/*Funcao que analisa se a lista esta vazia e retorna o correspondente booleano*/
	int i = 0;
	for(i=0;i<TAM;i++){// loop que verifica ponteiro para proximo do no cabeca, se nenhum apontar para um no , evidentemente a lista estara vazia.
		if (head->next[i]) return 0;
	}
	return 1;
}


search* searchList(node* h, int value, int isPrintTrue, int size){/*Funcao que realiza a busca de um determinado no na lista.
	Essa busca eh realizada de tal forma que ela ira percorrer o caminho de busca ate esse no e ira retornar esse caminho.*/
	node* aux = h;// h eh a cabeca da lista.
	node* aux2;
	search* pathVector = NULL;//PathVector eh o vetor de caminho correspondente ao caminho percorrido em busca do no.
	int i;//Contador referente ao nivel.
	int j = 0;//J eh o contador referente a posicao atual do vetor de posicoes.
	int k = 0;
	
	pathVector = (search*) calloc(size,sizeof(search));
	pathVector->pointer = (node**) calloc(5,sizeof(node*));
	pathVector->pointer[j] = h;
	j++;
	pathVector->size = j;
	
	for(i=TAM-1;i>=0;i--){//Loop que realiza o percurso em busca do no requisitado.
		if(aux) while(aux->next[i] && aux->next[i]->value < value){
			if(aux->next[i]->value == value) k++;
			pathVector->pointer[j] = aux->next[i];
			j++;
			pathVector->size = j;
			aux = aux->next[i];
		}
	}
		if(isPrintTrue) for(i=1;i<pathVector->size;i++) printf("%i %i\n", pathVector->pointer[i]->value, pathVector->pointer[i]->level);
		if(k) puts("true");
		if(!k) puts("false");
		return pathVector;
}

int insertList(node* h, int value, int level, int* size){
	if(level!=1) while(size[level] > size[level-1]/2 && level!=1) level--;
	search* path = searchList(h,value,0,size[0]);//path e ponteiro que aponta para o vetor de caminhos retornado pela funcao searchList.
	int i=0;//contador correspondente a
	int currentLevel;//contador que corresponde ao nivel atual no primeiro loop, e a posicao do vetor de ponteiros que apontam para o caminho percorrico pela funcao searchList.
	node* newNode = createNode(value, level);
	int a; // contador de incremento do contador de tamanho de cada nivel;
	if(isEmptyList(h)){//Loop do caso correspondente a lista vazia.
		for(i=0;i<level;i++) {
			h->next[i] = newNode;
			(size[0])+=1;//Incremento do contador do tamanho da lista.
			for(a=1;a<=level;a++) (size[a]) +=1;//incremendo do tamanho de cada nivel da lista
			return 1;
		}
	}
	for(currentLevel=0;currentLevel<TAM;currentLevel++){//Loop que verifica se o valor que se deseja inserir ja se encontra na lista.
		if(path->pointer[(path->size)-1]->next[currentLevel] && path->pointer[(path->size)-1]->next[currentLevel]->value == value) return 0;
	}
	
	for(i=0;i<path->size;i++){//Loop do caso geral. Percorre o caminho retornado pelo searchList, e refaz os apontamentos para inserir o novo no quando valido.
		for(currentLevel=0;currentLevel<TAM;currentLevel++){
			
			if(currentLevel > level) break;// condicional de otimizacao
			if(!(path->pointer[i]->next[currentLevel]))// se o ponteiro next na posicao fornecida pelo contador i estiver apontando pra NULL, e seu nivel for menor ou igual ao nivel do no inserido, o apontamento eh refeito.
					if(currentLevel <= level-1){
						newNode->next[currentLevel] = &(*(path->pointer[i]->next[currentLevel]));
						path->pointer[i]->next[currentLevel] = newNode;
					}
			
			if(path->pointer[i]->next[currentLevel]){// quando o ponteiro next na posicao fornecida pelo contador i estiver apontando para um valor maior do que o que se deseja inserir e o nivel for menor do que o que se deseja inserir , eh refeito o apontamento para inserir o no requisitado.		
				if(path->pointer[i]->next[currentLevel]->value > newNode->value){
					newNode->next[currentLevel] = &(*(path->pointer[i]->next[currentLevel]));
					path->pointer[i]->next[currentLevel] = newNode;
				}
			}
		}
	}
	for(a=1;a<=level;a++) (size[a]) +=1;//incremendo do tamanho de cada nivel da lista
	(size[0])+=1;// sempre que houver um retorno true eh necessario incrementar o tamanho da lista visto que apos a insercao seu tamanho aumentou.
	return 1;
}

int removeList(node* h, int value, int *size){//funcao que executa a remocao de um no da lista.
	search* pathVector = searchList(h,value,0,size[0]);// mesma definicao do path da funcao anterior.
	int i=0;//mesma definicao da funcao anterior.
	int a;
	int level=0;
	node* aux = NULL;// auxiliar que aponta para o no atual no primeiro loop e que aponta para o no achado caso achado no loop 2.
	int currentLevel;//mesma definicao da funcao anterior.
	if(&(*(pathVector->pointer[(pathVector->size)-1])) == &(*h)) for(i=0;i<TAM-1;i++) {//caso do caminho retornado pela funcao de busca ser vazio
		if(h->next[i]) if(h->next[i]->value == value){//verifica os ponteiros do no cabeça e faz a remocao caso se encontre o no buscado
			level = h->next[i]->level;
			aux = h->next[i];
			h->next[i] = h->next[i]->next[i];
		}
		free(aux);
		size[0]-=1;//incremendo do tamanho total da lista
		for(a=1;a<=level;a++) (size[a]) -=1;//incremendo do tamanho de cada nivel da lista
		return 1;
	}
	
	for(i=0;i<pathVector->size;i++){/*loop do caso geral, verifica cada posicao do vetor de ponteiros next de cada posicao
	do vetor de percurso retornado pela funcao searchList e faz a remocao caso um desses nexts apontem para o valor de busca.*/
		for(currentLevel=0;currentLevel<TAM;currentLevel++){
			if(currentLevel > (pathVector->pointer[i]->level)-1) break;
			if(pathVector->pointer[i]->next[currentLevel] && pathVector->pointer[i]->next[currentLevel]->value == value){
				level = pathVector->pointer[i]->next[currentLevel]->level;
				aux = pathVector->pointer[i]->next[currentLevel];
				pathVector->pointer[i]->next[currentLevel] = pathVector->pointer[i]->next[currentLevel]->next[currentLevel];
			}
		}
	}
	
	if(aux){/* como aux representa o no achado, se ele nao existir significa que o no nao foi achado,
		e portanto a funcao retornara 0, caso ele exista sera liberado a memoria que ele aponta e entao a funcao retornara 1.*/
		free(aux);
		size[0]-=1;//incremento do tamanho total da lista
		for(a=1;a<=level;a++) (size[a]) -=1;//incremendo do tamanho de cada nivel da lista
		return 1;
	}
	return 0;
}




void printList(node* head){//Funcao que percorre toda lista e imprime seus elementos.
	node* aux = head->next[0];
	while(aux){
		printf("%i %i\n", aux->value,aux->level);
		aux = aux->next[0];
	}
	puts("");
}

void printListH(node* head, int level){//Funcao que percorre toda lista e imprime seus elementos.
	node* aux = head->next[level-1];
	while(aux){
		printf("%i %i\n", aux->value,aux->level);
		aux = aux->next[level-1];
	}
	puts("");
}

