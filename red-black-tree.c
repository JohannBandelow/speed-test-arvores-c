#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int data;
    Color color;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct {
    Node* root;
} RedBlackTree;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

RedBlackTree* createRedBlackTree() {
    RedBlackTree* newTree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    newTree->root = NULL;
    return newTree;
}

void leftRotate(RedBlackTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rightRotate(RedBlackTree* tree, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        tree->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void insertFixup(RedBlackTree* tree, Node* z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
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
            Node* y = z->parent->parent->left;
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
    tree->root->color = BLACK;
}

void inserir(RedBlackTree* tree, int data) {
    Node* z = createNode(data);
    Node* y = NULL;
    Node* x = tree->root;

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
        tree->root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }

    insertFixup(tree, z);
}

void inorderTraversal(Node* node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("%d ", node->data);
        inorderTraversal(node->right);
    }
}

int main() {
    RedBlackTree* tree = createRedBlackTree();

    FILE* file = fopen("build/values.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    int value;
    while (fscanf(file, "%d", &value) != EOF) {
        inserir(tree, value);
    }

    fclose(file);
    return 0;
}