#ifndef BTREE_H
#define BTREE_H
#define MAX_KEYS 4
// ARVORE DE ORDEM DO 4

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

void split(ArvoreB* arvore, No* no);

void inserir(ArvoreB* arvore, int chave);

void merge(ArvoreB* arvore, No* no, int index);

void remove_chave(No* no, int chave, int index);

void remove_recursiva(ArvoreB* arvore, No* no, int chave);

void remove_chave_arv(ArvoreB* arvore, int chave);

void remover(ArvoreB* arvore, int chave);

void print2DUtil(No *no, int space, int parent_key);

void print2D(ArvoreB *arvore);

#endif