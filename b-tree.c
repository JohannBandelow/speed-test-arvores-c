#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
    int *keys;
    struct Node **childPointers;
    int isLeaf; 
    int numKeys;
} Node;

Node* createNode(int order) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->keys = (int*)malloc((order-1) * sizeof(int));
    newNode->childPointers = (Node**)malloc(order * sizeof(Node*));
    newNode->isLeaf = 1;
    newNode->numKeys = 0;
    return newNode;
}

void insertKey(Node* root, int key, int order) {
    if (root == NULL) {
        root = createNode(order);
        root->keys[0] = key;
        root->numKeys = 1;
    } else {
        if (root->numKeys == order - 1) {
            Node* newNode = createNode(order);
            newNode->childPointers[0] = root;
            splitChild(newNode, 0, root, order);
            insertNonFull(newNode, key, order);
            root = newNode;
        } else {
            insertNonFull(root, key, order);
        }
    }
}


void insertNonFull(Node* node, int key, int order) {
    int i = node->numKeys - 1;
    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->childPointers[i]->numKeys == order - 1) {
            splitChild(node, i, node->childPointers[i], order);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->childPointers[i], key, order);
    }
}

void splitChild(Node* parent, int index, Node* child, int order) {
    Node* newNode = createNode(order);
    newNode->isLeaf = child->isLeaf;
    newNode->numKeys = order / 2 - 1;
    // Copiar as chaves e ponteiros para o novo nó
    for (int i = 0; i < newNode->numKeys; i++) {
        newNode->keys[i] = child->keys[i + order / 2];
    }
    if (!child->isLeaf) {
        for (int i = 0; i < order / 2; i++) {
            newNode->childPointers[i] = child->childPointers[i + order / 2];
        }
    }
    child->numKeys = order / 2 - 1;
    // Abrir espaço para o novo ponteiro no nó pai
    for (int i = parent->numKeys; i > index; i--) {
        parent->childPointers[i + 1] = parent->childPointers[i];
    }
    parent->childPointers[index + 1] = newNode;
    // Mover a chave mediana para o nó pai
    for (int i = parent->numKeys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[index] = child->keys[order / 2 - 1];
    parent->numKeys++;
}


// Função para remover uma chave da árvore B
void removeKey(Node* root, int key) {
    // Implemente a lógica de remoção aqui
}

// Função para imprimir a árvore B em ordem
void printTree(Node* root) {
    // Implemente a lógica de impressão aqui
}