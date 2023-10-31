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

ArvoreB* criarArvore();

No* criarNo();

void splitNo(ArvoreB* arvore, No* no);

void insert(ArvoreB* arvore, int chave);

void merge(No* no, int i);

int getSucessor(No* no, int i);

int getPredecessor(No* no, int i);

void delete(No* no, int k);

void print2DUtil(No *no, int space, int parent_key);

void print2D(ArvoreB *arvore);

#endif