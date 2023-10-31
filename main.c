#include <stdio.h>
#include <stdlib.h>
#include "btree.c"

int main() {
	
    ArvoreB* arvore = NULL;
    arvore = criarArvore();
	insert(arvore, 10);
	insert(arvore, 16);
	insert(arvore, 15);
    insert(arvore, 9);
    insert(arvore, 12);
    insert(arvore, 99);
    insert(arvore, 14);
    insert(arvore, 78);
    insert(arvore, 72);
    insert(arvore, 32);
    print2D(arvore);

    return 0;
}