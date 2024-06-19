#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

struct No {
    int key;
    struct No* left;
    struct No* right;
    int height;
};

struct No* novoNo(int key) {
    struct No* node = (struct No*)malloc(sizeof(struct No));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int height(struct No* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

struct No* rotaciona_direita(struct No* y) {
    struct No* x = y->left;
    struct No* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct No* rotaciona_esquerda(struct No* x) {
    struct No* y = x->right;
    struct No* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct No* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

struct No* inserir(struct No* node, int key) {
    if (node == NULL)
        return novoNo(key);

    if (key < node->key)
        node->left = inserir(node->left, key);
    else if (key > node->key)
        node->right = inserir(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rotaciona_direita(node);

    if (balance < -1 && key > node->right->key)
        return rotaciona_esquerda(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotaciona_esquerda(node->left);
        return rotaciona_direita(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotaciona_direita(node->right);
        return rotaciona_esquerda(node);
    }

    return node;
}

void inorder(struct No* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    struct No* root = NULL;

    FILE* file = fopen("build/values.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    int value;
    while (fscanf(file, "%d", &value) != EOF) {
        root = inserir(root, value);
    }

    fclose(file);

    return 0;
}