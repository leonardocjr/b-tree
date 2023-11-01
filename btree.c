#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

ArvoreB* criarArvore() {
    ArvoreB* novaArvore = (ArvoreB*)malloc(sizeof(ArvoreB));
    if (novaArvore == NULL) {
        printf("Erro na alocacao de memoria.\n");
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
        printf("Erro na alocacao de memoria.\n");
        return NULL;
    }
    novo->total = 0;
    for (i = 0; i <= MAX_KEYS; i++) {
        novo->filhos[i] = NULL;
    }
    novo->pai = NULL;
    return novo;
}

void split(ArvoreB* arvore, No* no) {
    int i, j;
    No* pai = no->pai;
    No* novo = criarNo();
    int medianaIndex = (MAX_KEYS) / 2;
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

void inserir(ArvoreB* arvore, int chave) {
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
                split(arvore, folha);
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

void merge(ArvoreB* arvore, No* no, int index) {
    int i;
    No* esquerda = no->filhos[index];
    No* direita = no->filhos[index + 1];

    // Move a chave pai[index] do nó atual para o nó da esquerda
    esquerda->chaves[esquerda->total] = no->chaves[index];
    esquerda->total++;

    // Copia as chaves e filhos da direita para a esquerda
    for (i = 0; i < direita->total; i++) {
        esquerda->chaves[esquerda->total] = direita->chaves[i];
        esquerda->filhos[esquerda->total] = direita->filhos[i];
        esquerda->total++;
    }

    // Atualiza os filhos da direita no nó atual
    for (i = index; i < no->total - 1; i++) {
        no->chaves[i] = no->chaves[i + 1];
        no->filhos[i + 1] = no->filhos[i + 2];
    }

    no->total--;

    free(direita);
}

void remove_chave(No* no, int chave, int index) {
    int i;
    for (i = index; i < no->total - 1; i++) {
        no->chaves[i] = no->chaves[i + 1];
    }
    no->total--;
}

void remove_recursiva(ArvoreB* arvore, No* no, int chave) {
    int index = 0;
    int i;
    while (index < no->total && no->chaves[index] < chave) {
        index++;
    }

    if (index < no->total && no->chaves[index] == chave) {
        // A chave está presente no nó atual
        if (no->filhos[index] != NULL) {
            // Se o nó tem filhos à esquerda, substitua a chave pela maior chave no filho à esquerda
            No* pred = no->filhos[index];
            while (pred->filhos[pred->total] != NULL) {
                pred = pred->filhos[pred->total];
            }
            int predecessor = pred->chaves[pred->total - 1];
            no->chaves[index] = predecessor;
            remove_recursiva(arvore, pred, predecessor);
        } else {
            // Se o nó não tem filhos, simplesmente remova a chave
            remove_chave(no, chave, index);
        }
    } else {
        // A chave não está no nó atual, então desça para o filho apropriado
        No* filho = no->filhos[index];
        if (filho == NULL) {
            // A chave não está na árvore, saia
            return;
        }
        if (filho->total == MAX_KEYS) {
            // Se o filho tiver o número mínimo de chaves, tente equilibrá-lo
            if (index > 0 && no->filhos[index - 1]->total > MAX_KEYS) {
                // Se o filho à esquerda tiver chaves extras, empreste uma chave do pai
                for (i = filho->total; i > 0; i--) {
                    filho->chaves[i] = filho->chaves[i - 1];
                }
                filho->chaves[0] = no->chaves[index - 1];
                if (filho->filhos[0] != NULL) {
                    for (i = filho->total + 1; i > 0; i--) {
                        filho->filhos[i] = filho->filhos[i - 1];
                    }
                    filho->filhos[0] = no->filhos[index - 1]->filhos[no->filhos[index - 1]->total];
                }
                no->chaves[index - 1] = no->filhos[index - 1]->chaves[no->filhos[index - 1]->total - 1];
                no->filhos[index - 1]->total--;
                filho->total++;
            } else if (index < no->total && no->filhos[index + 1]->total > MAX_KEYS) {
                // Se o filho à direita tiver chaves extras, empreste uma chave do pai
                filho->chaves[filho->total] = no->chaves[index];
                if (filho->filhos[0] != NULL) {
                    filho->filhos[filho->total + 1] = no->filhos[index + 1]->filhos[0];
                }
                no->chaves[index] = no->filhos[index + 1]->chaves[0];
                for (i = 0; i < no->filhos[index + 1]->total - 1; i++) {
                    no->filhos[index + 1]->chaves[i] = no->filhos[index + 1]->chaves[i + 1];
                }
                if (no->filhos[index + 1]->filhos[0] != NULL) {
                    for (i = 0; i < no->filhos[index + 1]->total; i++) {
                        no->filhos[index + 1]->filhos[i] = no->filhos[index + 1]->filhos[i + 1];
                    }
                }
                no->filhos[index + 1]->total--;
                filho->total++;
            } else {
                // Nenhum dos filhos tem chaves extras, então funda-os
                if (index > 0) {
                    merge(arvore, no, index - 1);
                    index--;
                } else {
                    merge(arvore, no, index);
                }
                remove_recursiva(arvore, no->filhos[index], chave);
            }
        } else {
            // O filho tem espaço suficiente, continue a remoção recursiva
            remove_recursiva(arvore, filho, chave);
        }
    }
}

void remove_chave_arv(ArvoreB* arvore, int chave) {
    No* raiz = arvore->raiz;

    // Caso especial: se a raiz for a única chave e for igual à chave que estamos tentando remover
    if (raiz->total == 1 && raiz->chaves[0] == chave) {
        arvore->raiz = raiz->filhos[0];
        free(raiz);
    } else {
        remove_recursiva(arvore, raiz, chave);
    }
}

void remover(ArvoreB* arvore, int chave) {
    if (arvore == NULL || arvore->raiz == NULL) {
        return;
    }
    remove_chave_arv(arvore, chave);

    // Se a raiz não tiver chaves, torne o filho restante a nova raiz
    if (arvore->raiz->total == 0) {
        No* novaRaiz = arvore->raiz->filhos[0];
        free(arvore->raiz);
        arvore->raiz = novaRaiz;
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
        print2DUtil(no->filhos[i], space, no->chaves[i]);
}

void print2D(ArvoreB *arvore) {
   print2DUtil(arvore->raiz, 0, -1);
}