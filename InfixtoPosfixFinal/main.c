#include "infixToPosfix.h"

/*  Autor: Ualaci dos Anjos Junior
	Disciplina: Estrutura de Dados 1
	Intuito do Programa: Converter uma expressao valida na forma infixa para a forma posfixa e calcular essa expressao posfixa	
*/
int main(){
	fflush(stdin);
	node* stack = createNode();
	node* stackNum = createNode();
	char* posfixStr = createString();
    char* infixStr;
    printf("insira a equacao na forma infixa:\n");
    infixStr = (getExpression());
	setbuf(stdin, NULL);
    infixToPosfix(infixStr, stack, posfixStr);
    printf("\nString posfixa: %s\n", posfixStr);
    evaluatePosfixExp(stackNum, posfixStr);
    printf("\n");
    system("pause");
    return 0;
}
