#include "infixToPosfix.h"

int cicle = 0;
// FUNCAO QUE RECEBE A STRING INFIXA
char* getExpression(){

   	char character , *str = NULL;
	int count1 = 0, count2 = 1;
	
	str = (char *) malloc(10 * sizeof(char) + 1);
	
	printf("Informe a expressao:");
	
	while ((character = getchar()) != '\n' && character != EOF && character != '\0')
	{
		if (count2 == 10) {
			str = (char *) realloc(str, strlen(str) + 10 * sizeof(char) + 1);
			count2 = 1;
		}

		*(str + count1 * sizeof(char)) = character;

		count1++;
		count2++;
	}
	
	*(str + count1 * sizeof(char)) = '\0';
	
	puts("\n\n");
	
	printf("%s\n\n", str);
    return str;
}

node* createNode(){
	node* newNode = (node*) calloc(1, sizeof(node));
	if (!newNode){
		printf("Erro de alocacao, ABORTANDO ------------------");
		exit (1);
	}
	return newNode;
}
//FUNCAO DE INSERCAO DE UM NO COM DADO CHAR NA PILHA
void insertOnStack(char character, node* stack){
	
	node* newNode = createNode();
	newNode->character = character;
	newNode->next = stack->next;
	stack->next = newNode;
}

//FUNCAO DE INSERCAO DE UM NO COM DADO FLOAT NA PILHA
void insertOnStackInt(float characterInt, node* stack){
	
	node* newNode = createNode();
	newNode->characterInt = characterInt;
	newNode->next = stack->next;
	stack->next = newNode;
}

//FUNCAO QUE IMPRIME OS CAMPOS CHAR DE CADA NO DA PILHA
void printStack(node* stack){
	node* aux = stack->next;
	while(aux){
		aux = aux->next;
	}
}

// FUNCAO QUE IMPRIME OS CAMPOS FLOAT DE CADA NO DA PILHA
void printStackInt(node* stack){
	node* aux = stack->next;
	printf("Pilha:\t");
	while(aux){
		printf("|%f|", aux->characterInt);
		aux = aux->next;
	}
	printf("\n\n");
}

//FUNCAO QUE REMOVE UM NO DA PILHA
void removeOnStack(node* stack){
	if(stack->next){
	node* aux = stack->next;
	stack->next = stack->next->next;
	free(aux);
	}
}

// FUNCAO QUE INSERE UM CARACTER NUMA STRING DINAMICA, USADA NO PROGRAMA PARA INSERIR OS ELEMENTOS DE INFIXSTR EM POSFIXSTR
void putOnString(char* str,char character){
	setbuf(stdin ,NULL);
	char* charPointer = &character;
	if (cicle==1) str = (char*) realloc(str, strlen(str)+sizeof(char));
	strcat(str,charPointer);
	cicle = 1;
}

// FUNCAO QUE ANALIZA A HIERARQUIA DE CADA CARACTERE
int checkHierarchy(char character){
	int hierarchy;
	if (character == ')') {hierarchy = 4;}
	else if (character == '(') {hierarchy = -1;}
	else if (character == '*' || character == '/' || character == '%' ) { hierarchy = 2;}
	else if (character == '+' || character == '-' ) {hierarchy = 1;}
	else {hierarchy = 0; }
	return hierarchy;
}

//FUNCAO QUE ALOCA UM ESPACO DE MEMORIA PARA UM PONTEIRO DE STRING
char* createString(){
	char* newString = (char*) calloc(1,sizeof(char));
	return newString;
}

// FUNCAO QUE INSERE UM CARACTERE ESPECIFICO DE UMA STRING DINAMICA EM UMA VARIAVEL DO TIPO CHAR
char cutString(char* infixStr,int i){
	char character = infixStr[strlen(infixStr)-i];
	return character;
}

// FUNCAO QUE DELETA OS PARENTESES E INSERE OS ELEMENTOS ENTRE OS PARENTESES EM UMA STRING (NO PROGRAMA NA STRING POSFIXA)
void delet (node* stack, char* posfixStr){
		node* aux0 = stack->next;
		while (aux0->character != '('){
			
			if(aux0->character!=')' || aux0 == NULL) {
				putOnString(posfixStr, aux0->character);
				node* aux2 = aux0;
				aux0 = aux0->next;
				free (aux2);
			}
			
			if (aux0->character == '('){
				stack->next = aux0->next;

			}	
		}
		free(aux0);
	}

// FUNCAO QUE CHAMA A MAIOR PARTE DAS FUNCOES PARA FAZER A CONVERSAO DA EXPRESSAO INFIXA PARA A EXPRESSAO POSFIXA
void infixToPosfix(char* infixStr, node* stack, char* posfixStr){
	int i;
	int insertCase;
	char character;
	int hierarchy;
	int hierarchyNext;
	int forLimit = 0;

	
	for(i=strlen(infixStr);i>0;i--){

		character = cutString(infixStr,i);
		hierarchyNext = 500;	

		hierarchy = checkHierarchy(character);
		
// SWITCH CASE PARA O CASO DE CADA PRIORIDADE
		switch (hierarchy){
			case 0:
				putOnString(posfixStr, character);
				break;
				
			case 1:
				if(stack->next){
					hierarchyNext = checkHierarchy(stack->next->character);
					if (hierarchyNext >= hierarchy) {
						putOnString(posfixStr, stack->next->character);
						removeOnStack(stack);	
					}
				}
				insertOnStack(character, stack);
				break;
				
			case 2:
				if (stack->next){
					if (hierarchyNext == hierarchy) {
						hierarchyNext = checkHierarchy(stack->next->character);
						putOnString(posfixStr, stack->next->character);
						removeOnStack(stack);		
					}
				}
				insertOnStack(character, stack);
				
				break;
			case -1:
				insertOnStack(character, stack);
				break;
				
			case 4:
				forLimit++;
				delet(stack, posfixStr);
				break;
		}
	}
	while(stack->next){
		if (stack->next->character != '(' ){
			putOnString(posfixStr, stack->next->character);
		}
		removeOnStack(stack);
	
	}
}

// FUNCAO QUE CALCULA A EXPRESSAO POSFIXA E RETORNA SEU VALOR
float evaluatePosfixExp(node* stack ,char* posfixStr){
	int i, num1Int,num2Int,num3Int,j=1,k, confirm;
	char character;
	char character2;
	int characterInt;
	char* charPointer = &character, *charPointer2 = &character2;
	float num1, num2,num3;
	char* letter = (char*) calloc(1,sizeof(char));
	char* value = (char*) calloc(1,sizeof(char));
	
	for(i=strlen(posfixStr);i>0;i--){
		confirm = 0;
		character = cutString(posfixStr,i);
		
		if(isalpha(character) || isdigit(character)){
			if (isalpha(character)){
				for(k=0;k<j+1;k++){
					if (strcmp(letter, charPointer) == 0){
						strcpy(charPointer, value);
						confirm = 1;
					}
				}
			if(confirm == 0){	
				letter = (char*) realloc(value, sizeof(char));
				value = (char*) realloc(value, sizeof(char));
				strcpy(letter+j, charPointer);
				printf("Insira o valor da Incognita %c:\n", *charPointer);
				gets(charPointer);
				strcpy(value+j, charPointer);
				j++;
				setbuf(stdin, NULL);
			}
				
			}
			characterInt = atof(charPointer);
			insertOnStackInt(characterInt , stack);
		}
		else
			if(stack->next || !stack->next){

				num1 = stack->next->characterInt;
				num2 = stack->next->next->characterInt;
				
				removeOnStack(stack);
				removeOnStack(stack);
				if (character == '*') {
				num3 = num1*num2;
				}
				else if (character == '/') num3 = num2/num1;
				
				else if (character == '%') {
					num2Int = (int) num2;
					num1Int = (int) num1;
					num3Int = num2Int % num1Int;
					num3 = (float) num3Int;
				}
				
				else if (character == '+'){
				num3 = num1+num2;}
				else if (character == '-'){
					num3 = num2-num1;
				}
				
				insertOnStackInt(num3, stack);

			}
	}
	printf("Resultado = %.2f", stack->next->characterInt);
}
