#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

ArvoreB* criarArvore() {
    ArvoreB* novaArvore = (ArvoreB*)malloc(sizeof(ArvoreB));
    if (novaArvore == NULL) {
        printf("Erro na alocação de memória.\n");
        return NULL;
    }
    novaArvore->raiz = NULL;
    novaArvore->ordem = MAX_KEYS;
    return novaArvore;
}

No* criarNo() {
    int i;
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro na alocação de memória.\n");
        return NULL;
    }
    novo->total = 0;
    for (i = 0; i <= MAX_KEYS; i++) {
        novo->filhos[i] = NULL;
    }
    novo->pai = NULL;
    return novo;
}

void splitNo(ArvoreB* arvore, No* no) {
    int i, j;
    No* pai = no->pai;
    No* novo = criarNo();
    int medianaIndex = MAX_KEYS / 2;
    int mediana = no->chaves[medianaIndex];

    for (i = medianaIndex + 1, j = 0; i < MAX_KEYS; i++, j++) {
        novo->chaves[j] = no->chaves[i];
        novo->filhos[j] = no->filhos[i];
        if (novo->filhos[j] != NULL) {
            novo->filhos[j]->pai = novo;
        }
        no->chaves[i] = 0;
        no->filhos[i] = NULL;
    }
    novo->filhos[j] = no->filhos[i];
    if (novo->filhos[j] != NULL) {
        novo->filhos[j]->pai = novo;
    }
    no->filhos[i] = NULL;

    no->total = medianaIndex;
    novo->total = j;

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
        pai->filhos[i + 1] = pai->filhos[i];
    }

    pai->chaves[posicao] = mediana;
    pai->filhos[posicao + 1] = novo;
    pai->total++;
    novo->pai = pai;

    for(i=0; i<=no->total; i++) {
        if(no->filhos[i]) {
            no->filhos[i]->pai=no;
        }
    }
    
    for(i=0; i<=novo->total; i++) {
        if(novo->filhos[i]) {
            novo->filhos[i]->pai=novo;
        }
    }
}

void insert(ArvoreB* arvore, int chave) {
    No* no = arvore->raiz;
    if (no == NULL) {
        no = criarNo();
        no->chaves[0] = chave;
        no->total = 1;
        arvore->raiz = no;
    } else {
        No* folha = no;
        while (1) {
            if (folha -> total < MAX_KEYS) {
                int posicao = folha -> total - 1;
                while (posicao >= 0 && folha -> chaves[posicao] > chave) {
                    folha -> chaves[posicao + 1] = folha -> chaves[posicao];
                    posicao--;
                }
                folha -> chaves[posicao + 1] = chave;
                folha -> total++;
                break;
            } else {
                splitNo(arvore, folha);
                folha=folha -> pai;

                if(folha == NULL){
                    folha=arvore -> raiz;
                }

                int posicao=0;

                while(posicao < folha -> total && folha -> chaves[posicao]< chave){
                    posicao++;
                }

                if(posicao == folha -> total || folha -> chaves[posicao]> chave){
                    folha=folha -> filhos[posicao];
                }else{
                    folha=folha -> filhos[posicao + 1];
                }
            }
        }
    }
}

void print2DUtil(No *no, int space, int parent_key) {
    int i;
    if (no == NULL)
        return;
    space += 10;
    print2DUtil(no->filhos[no->total], space, no->chaves[0]);
    printf("\n");
    for (i = 10; i < space; i++)
        printf(" ");
    if (space > 10) // Não imprime a chave do pai para a raiz
        printf("(Pai: %d) ", parent_key);
    printf("[");
    for(i = 0; i < no->total; i++) {
        printf("%d", no->chaves[i]);
        if (i < no->total - 1)
            printf(", ");
    }
    printf("]\n");
    for(i = 0; i < no->total; i++)
        print2DUtil(no->filhos[i], space, no->chaves[0]);
}

void print2D(ArvoreB *arvore) {
   print2DUtil(arvore->raiz, 0, -1);
}