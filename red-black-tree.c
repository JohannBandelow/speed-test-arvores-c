#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct No {
    int data;
    Color color;
    struct No* parent;
    struct No* left;
    struct No* right;
} No;

typedef struct {
    No* raiz;
} ArvoreRubroNegra;

No* createNode(int data) {
    No* newNode = (No*)malloc(sizeof(No));
    newNode->data = data;
    newNode->color = RED;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

ArvoreRubroNegra* criaArvoreRubroNegra() {
    ArvoreRubroNegra* newTree = (ArvoreRubroNegra*)malloc(sizeof(ArvoreRubroNegra));
    newTree->raiz = NULL;
    return newTree;
}

void leftRotate(ArvoreRubroNegra* tree, No* x) {
    No* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        tree->raiz = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rightRotate(ArvoreRubroNegra* tree, No* y) {
    No* x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        tree->raiz = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void insertFixup(ArvoreRubroNegra* tree, No* z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            No* y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            No* y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->raiz->color = BLACK;
}

void inserir(ArvoreRubroNegra* tree, int data) {
    No* z = createNode(data);
    No* y = NULL;
    No* x = tree->raiz;

    while (x != NULL) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == NULL) {
        tree->raiz = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }

    insertFixup(tree, z);
}

void inorderTraversal(No* node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("%d ", node->data);
        inorderTraversal(node->right);
    }
}

No* treeMinimum(No* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

void transplant(ArvoreRubroNegra* tree, No* u, No* v) {
    if (u->parent == NULL) {
        tree->raiz = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

void deleteFixup(ArvoreRubroNegra* tree, No* x) {
    while (x != tree->raiz && x->color == BLACK) {
        if (x == x->parent->left) {
            No* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->raiz;
            }
        } else {
            No* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->raiz;
            }
        }
    }
    x->color = BLACK;
}

void remover(ArvoreRubroNegra* tree, int data) {
    No* z = tree->raiz;
    while (z != NULL) {
        if (data == z->data) {
            break;
        } else if (data < z->data) {
            z = z->left;
        } else {
            z = z->right;
        }
    }
    if (z == NULL) {
        printf("Node not found.\n");
        return;
    }
    No* y = z;
    Color yOriginalColor = y->color;
    No* x;
    if (z->left == NULL) {
        x = z->right;
        transplant(tree, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(tree, z, z->left);
    } else {
        y = treeMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL) {
                x->parent = y;
            }
        } else {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (yOriginalColor == BLACK) {
        deleteFixup(tree, x);
    }
}

int main() {
    ArvoreRubroNegra* tree = criaArvoreRubroNegra();

    FILE* file = fopen("build/values.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    int value;
    while (fscanf(file, "%d", &value) != EOF) {
        inserir(tree, value);
    }

    while(fscanf(file, "%d", &value) != EOF) {
        remover(tree, value);
    }

    fclose(file);
    return 0;
}