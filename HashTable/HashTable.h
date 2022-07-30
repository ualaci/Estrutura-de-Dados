#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _hash{
	int key;
	struct _hash *next;
	}hash;

int hashing(int key,int size);

hash* createNode(int key);

hash** insertTable(hash **hs,hash *newHash, int pos,int size);

hash** removeTable(hash **hs,int key,int pos);

void printTable(hash **hs,int size);

void searchElem(hash **hs,int size,int key,int pos);

#endif
