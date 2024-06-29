#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

struct No {
    int key;
    struct No* left;
    struct No* right;
    int height;
};

struct No* criaNo(int key) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->key = key;
    novoNo->left = NULL;
    novoNo->right = NULL;
    novoNo->height = 1;
    return novoNo;
}

int altura(struct No* no) {
    if (no == NULL) {
        return 0;
    }
    return no->height;
}

int fatorBalanceamento(struct No* no) {
    if (no == NULL) {
        return 0;
    }
    return altura(no->left) - altura(no->right);
}

struct No* rotacaoDireita(struct No* y) {
    struct No* x = y->left;
    struct No* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(altura(y->left), altura(y->right)) + 1;
    x->height = max(altura(x->left), altura(x->right)) + 1;

    return x;
}

struct No* rotacaoEsquerda(struct No* x) {
    struct No* y = x->right;
    struct No* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(altura(x->left), altura(x->right)) + 1;
    y->height = max(altura(y->left), altura(y->right)) + 1;

    return y;
}

struct No* inserir(struct No* no, int key) {
    if (no == NULL) {
        return criaNo(key);
    }

    if (key < no->key) {
        no->left = inserir(no->left, key);
    } else if (key > no->key) {
        no->right = inserir(no->right, key);
    } else {
        return no;
    }

    no->height = 1 + max(altura(no->left), altura(no->right));

    int balanceamento = fatorBalanceamento(no);

    if (balanceamento > 1 && key < no->left->key) {
        return rotacaoDireita(no);
    }

    if (balanceamento < -1 && key > no->right->key) {
        return rotacaoEsquerda(no);
    }

    if (balanceamento > 1 && key > no->left->key) {
        no->left = rotacaoEsquerda(no->left);
        return rotacaoDireita(no);
    }

    if (balanceamento < -1 && key < no->right->key) {
        no->right = rotacaoDireita(no->right);
        return rotacaoEsquerda(no);
    }

    return no;
}

struct No* encontrarMinimo(struct No* no) {
    struct No* atual = no;
    while (atual->left != NULL) {
        atual = atual->left;
    }
    return atual;
}

struct No* remover(struct No* raiz, int key) {
    if (raiz == NULL) {
        return raiz;
    }

    if (key < raiz->key) {
        raiz->left = remover(raiz->left, key);
    } else if (key > raiz->key) {
        raiz->right = remover(raiz->right, key);
    } else {
        if ((raiz->left == NULL) || (raiz->right == NULL)) {
            struct No* temp = raiz->left ? raiz->left : raiz->right;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }

            free(temp);
        } else {
            struct No* temp = encontrarMinimo(raiz->right);

            raiz->key = temp->key;

            raiz->right = remover(raiz->right, temp->key);
        }
    }

    if (raiz == NULL) {
        return raiz;
    }

    raiz->height = 1 + max(altura(raiz->left), altura(raiz->right));

    int balanceamento = fatorBalanceamento(raiz);

    if (balanceamento > 1 && fatorBalanceamento(raiz->left) >= 0) {
        return rotacaoDireita(raiz);
    }

    if (balanceamento > 1 && fatorBalanceamento(raiz->left) < 0) {
        raiz->left = rotacaoEsquerda(raiz->left);
        return rotacaoDireita(raiz);
    }

    if (balanceamento < -1 && fatorBalanceamento(raiz->right) <= 0) {
        return rotacaoEsquerda(raiz);
    }

    if (balanceamento < -1 && fatorBalanceamento(raiz->right) > 0) {
        raiz->right = rotacaoDireita(raiz->right);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void executaRotinaDeInsercao(FILE *file) {
    struct No *raiz = NULL;
    int value;
    while (fscanf(file, "%d", &value) != EOF) {
        raiz = inserir(raiz, value);
    }
}

void executaRotinaDeRemocao(FILE *file) {
    struct No *raiz = NULL;
    int value;

    while (fscanf(file, "%d", &value) != EOF) {
        raiz = inserir(raiz, value);
    }

    while (fscanf(file, "%d", &value) != EOF) {
        raiz = remover(raiz, value);
    }
}

int main(int argc, char *argv[]) {
    FILE *file = fopen("build/values.txt", "r");
    if (file == NULL) {
        printf("Falha ao abrir o arquivo.\n");
        return 1;
    }

    int rotina = atoi(argv[1]);

    if (rotina == 1) {
        executaRotinaDeInsercao(file);
    }

    if (rotina == 2) {
        executaRotinaDeRemocao(file);
    }

    fclose(file);
    return 0;
}