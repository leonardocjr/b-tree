#ifndef BTREE_H
#define BTREE_H
#define MAX_KEYS 3

typedef struct no {
    int total;
    int chaves[MAX_KEYS];
    struct no* filhos[MAX_KEYS + 1];
    struct no* pai;
} No;

typedef struct arvoreB {
    No* raiz;
    int ordem;
} ArvoreB;

No* criarNo();

void splitNo(ArvoreB* arvore, No* no);

void insert(ArvoreB* arvore, int chave);

void printDot(No* no);

void printTree(ArvoreB* arvore);

#endif