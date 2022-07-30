#ifndef _INFIXTOPOSFIX_H
#define _INFIXTOPOSFIX_H
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

typedef struct _node{
	char character;
	float characterInt;
	struct _node* next;
} node;


char* getExpression();

node* createNode();

//void printStack(node* stack);

void delet (node* stack, char* posfixStr);

void insertOnStack(char character, node* stack);

void insertOnStackInt(float characterInt, node* stack);

void removeOnStack(node* stack);

void putOnString(char* str,char character);

char* createString();

void infixToPosfix(char* infixStr, node* stack, char* posfixStr);

int checkHierarchy(char character);

char cutString(char* infixStr,int i);

float evaluatePosfixExp(node* stack ,char* posfixStr);

#endif
