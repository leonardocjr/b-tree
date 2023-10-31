#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

#define MAX_KEYS 3
int i;


No* criarNo() {
    No* novo = (No*)malloc(sizeof(No));
    novo->total = 0;
    for (i = 0; i <= MAX_KEYS; i++) {
        novo->filhos[i] = NULL;
    }
    novo->pai = NULL;
    return novo;
}

void splitNo(ArvoreB* arvore, No* no) {
    No* pai = no->pai;
    No* novo = criarNo();
    int mediana = no->chaves[MAX_KEYS / 2];

    for (i = (MAX_KEYS / 2) + 1; i < MAX_KEYS; i++) {
        novo->chaves[i - ((MAX_KEYS / 2) + 1)] = no->chaves[i];
        no->chaves[i] = 0;
    }

    for (i = (MAX_KEYS / 2) + 1; i <= MAX_KEYS; i++) {
        novo->filhos[i - ((MAX_KEYS / 2) + 1)] = no->filhos[i];
        no->filhos[i] = NULL;
        if (novo->filhos[i - ((MAX_KEYS / 2) + 1)] != NULL) {
            novo->filhos[i - ((MAX_KEYS / 2) + 1)]->pai = novo;
        }
    }

    no->total = MAX_KEYS / 2;
    novo->total = (MAX_KEYS / 2) - 1;

    if (pai == NULL) {
        pai = criarNo();
        arvore->raiz = pai;
        pai->filhos[0] = no;
        no->pai = pai;
    }

    int posicao = 0;
    while (posicao < pai->total && pai->chaves[posicao] < mediana) {
        posicao++;
    }

    for (i = pai->total; i > posicao; i--) {
        pai->chaves[i] = pai->chaves[i - 1];
    }
    for (i = pai->total + 1; i > posicao + 1; i--) {
        pai->filhos[i] = pai->filhos[i - 1];
    }

    pai->chaves[posicao] = mediana;
    pai->filhos[posicao] = no;
    pai->filhos[posicao + 1] = novo;
    pai->total++;
    novo->pai = pai;
}

void insert(ArvoreB* arvore, int chave) {
    No* no = arvore->raiz;

    if (no == NULL) {
        no = criarNo();
        no->chaves[0] = chave;
        no->total = 1;
        arvore->raiz = no;
    } else {
        while (no->total == MAX_KEYS) {
            splitNo(arvore, no);
            no = no->pai;
        }

        int posicao = no->total - 1;
        while (posicao >= 0 && no->chaves[posicao] > chave) {
            no->chaves[posicao + 1] = no->chaves[posicao];
            posicao--;
        }
        no->chaves[posicao + 1] = chave;
        no->total++;
    }
}

void printTree(ArvoreB* arvore) {
    printf("graph ArvoreB {\n");
    printf("node [shape=record];\n");
    printDot(arvore->raiz);
    printf("}\n");
}

void printDot(No* no) {
    if (no == NULL) {
        return;
    }

    printf("\"%p\" [label=\"", (void*)no);
    for (i = 0; i < no->total; i++) {
        printf("%d", no->chaves[i]);
        if (i < no->total - 1) {
            printf("|");
        }
    }
    printf("\"];\n");

    for (i = 0; i <= no->total; i++) {
        if (no->filhos[i] != NULL) {
            printf("\"%p\" -- \"%p\";\n", (void*)no, (void*)no->filhos[i]);
            printDot(no->filhos[i]);
        }
    }
}


