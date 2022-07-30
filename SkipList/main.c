#include "skipList.h"
// o Programa recebe a entrada e ou E para sair
int main() {
	int result,level,value,*size;
	char op;
	node* head = createHead();
	setbuf(stdin,NULL);
	size =(int*) calloc(TAM+1,sizeof(int));
	
	do{	
		result = -1;
		scanf("%c", &op);
		
		if(op == 'I' || op == 'i'){
			scanf("%i%i", &value,&level);
			result = insertList(head,value,level,&(size[0]));
		}
		
		else if(op != 'A' && op != 'a' && op != 'e' && op != 'E') {
			scanf("%i", &value);
		}
		if(op == 'R' || op == 'r') result = removeList(head,value,&(size[0]));
			
		if(op == 'B' || op == 'b') searchList(head,value,1,size[0]);
		
		if(op == 'P' || op == 'p') printListH(head,value);
		
		if(op == 'A' || op == 'a') printList(head);
			
		if(result == 1) puts("true");
		if(result == 0) puts("false");
		
	}while(op!='e' && op!='E');
	return 0;
}
