#include <stdio.h>
#include <stdlib.h>
#include "btree.c"

#define MAX_KEYS 3

int main() {
	
    ArvoreB arvore;
    arvore.raiz = NULL;
    arvore.ordem = MAX_KEYS;
	insert(&arvore, 9);
	insert(&arvore, 1);
	insert(&arvore, 7);

    printTree(&arvore);

    return 0;
}