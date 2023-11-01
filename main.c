#include <stdio.h>
#include <stdlib.h>
#include "btree.c"

int main() {
	
    ArvoreB* arvore = NULL;
    arvore = criarArvore();
    printf("- INSERE: 2\n");
	inserir(arvore, 2);
    print2D(arvore);
    printf("\n------------------------------------\n");
    printf("- INSERE: 15\n");
	inserir(arvore, 15);
    print2D(arvore);
    printf("\n------------------------------------\n");
    printf("- INSERE: 9\n");
    inserir(arvore, 9);
    print2D(arvore);
    printf("\n------------------------------------\n");
    printf("- INSERE: 12\n");
    inserir(arvore, 12);
    print2D(arvore);
    printf("\n------------------------------------\n");
    printf("- INSERE: 22\n");
    inserir(arvore, 22);
    print2D(arvore);
    printf("\n------------------------------------\n");
    printf("- INSERE: 11\n");
    inserir(arvore, 11);
    print2D(arvore);
    printf("\n------------------------------------\n");
    printf("- INSERE: 13\n");
    inserir(arvore, 13);
    print2D(arvore);
    printf("\n------------------------------------\n");
    printf("- INSERE: 4\n");
    inserir(arvore, 4);
    print2D(arvore);
    printf("\n------------------------------------\n");
    printf("- REMOVE: 2\n");
    remover(arvore, 2);
    print2D(arvore);
    printf("\n------------------------------------\n");
    printf("- INSERE: 10\n");
    inserir(arvore, 10);
    print2D(arvore);
    printf("\n------------------------------------\n");
    printf("- INSERE: 17\n");
    inserir(arvore, 17);
    print2D(arvore);
    printf("\n------------------------------------\n");
    printf("- INSERE: 29\n");
    inserir(arvore, 29);
    print2D(arvore);
    printf("\n------------------------------------\n");
    printf("- INSERE: 19\n");
    inserir(arvore, 19);
    print2D(arvore);
    printf("\n------------------------------------\n");
    printf("- REMOVE: 11\n");
    remover(arvore, 11);
    print2D(arvore);

    return 0;
}