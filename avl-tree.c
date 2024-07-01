#include <stdlib.h>
#include <string.h>
#include <stdio.h>

long int avlCount = 0;

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    int valor;
    int altura;
} No;

typedef struct arvore {
    struct no* raiz;
} Arvore;

int max(int a, int b) {
    avlCount++;
    return a > b ? a : b;
}

void balanceamento(Arvore*, No*);
int altura(No*);
int fb(No*);
No* rsd(Arvore*, No*);
No* rse(Arvore*, No*);
No* rdd(Arvore*, No*);
No* rde(Arvore*, No*);

Arvore* criar() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
  
    return arvore;
}

int vazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}

void adicionar(Arvore* arvore, int valor) {
    No* no = arvore->raiz;

    while (no != NULL) {
        avlCount++;
        if (valor > no->valor) {
            avlCount++;
            if (no->direita != NULL) {
                no = no->direita;
            } else {
                break;
            }
        } else {
            avlCount++;
            if (no->esquerda != NULL) {
                no = no->esquerda;
            } else {
                break;
            }
        }
    }

    No* novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->pai = no;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->altura = 1;

    avlCount++;
    if (no == NULL) {    
        arvore->raiz = novo;
    } else {
        avlCount++;
        if (valor > no->valor) {
            no->direita = novo;
        } else {
            no->esquerda = novo;
        }
        
        balanceamento(arvore, no);
    }
}

No* localizar(No* no, int valor) {
    while (no != NULL) {
        avlCount++;
        avlCount++;
        if (no->valor == valor) {
            return no;
        }
        
        avlCount++;
        no = valor < no->valor ? no->esquerda : no->direita;
    }

    return NULL;
}

void percorrer(No* no, void (*callback)(int)) {
    if (no != NULL) {
        percorrer(no->esquerda,callback);
        callback(no->valor);
        percorrer(no->direita,callback);
    }
}

void visitar(int valor){
    printf("%d ", valor);
}

void balanceamento(Arvore* arvore, No* no) {
    avlCount++;
    while (no != NULL) {
        avlCount++;
        no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;
        int fator = fb(no);

        avlCount++;
        if (fator > 1) {
            avlCount++;
            if (fb(no->esquerda) > 0) {
                rsd(arvore, no); 
            } else {
                rdd(arvore, no);
            }
        } else if (fator < -1) {
            avlCount++;
            if (fb(no->direita) < 0) {
                rse(arvore, no);
            } else {
                rde(arvore, no);
            }
        }

        no = no->pai; 
    }
}

int altura(No* no){
    avlCount++;
    return no != NULL ? no->altura : 0;
}

int fb(No* no) {
    int esquerda = 0,direita = 0;
  
    avlCount++;
    if (no->esquerda != NULL) {
        esquerda = no->esquerda->altura;
    }

    avlCount++;
    if (no->direita != NULL) {
        direita = no->direita->altura;
    }
  
    return esquerda - direita;
}

No* rse(Arvore* arvore, No* no) {
    No* pai = no->pai;
    No* direita = no->direita;

    avlCount++;
    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    } 
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    avlCount++;
    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        avlCount++;
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;
    direita->altura = max(altura(direita->esquerda), altura(direita->direita)) + 1;

    return direita;
}

No* rsd(Arvore* arvore, No* no) {
    No* pai = no->pai;
    No* esquerda = no->esquerda;

    avlCount++;
    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    } 
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    avlCount++;
    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        avlCount++;
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;
    esquerda->altura = max(altura(esquerda->esquerda), altura(esquerda->direita)) + 1;

    return esquerda;
}

No* rde(Arvore* arvore, No* no) {
    no->direita = rsd(arvore, no->direita);
    return rse(arvore, no);
}

No* rdd(Arvore* arvore, No* no) {
    no->esquerda = rse(arvore, no->esquerda);
    return rsd(arvore, no);
}

void remover(Arvore* arvoreAVL, int valor) {
    No* no = localizar(arvoreAVL->raiz, valor);

    avlCount++;
    while (no != NULL) {
        avlCount++;
        avlCount++;
        if (no->esquerda == NULL && no->direita == NULL) {
            avlCount++;
            if (no->pai == NULL) {
                arvoreAVL->raiz = NULL;
            } else {
                avlCount++;
                if (no->pai->esquerda == no)
                    no->pai->esquerda = NULL;
                else
                    no->pai->direita = NULL;
            }
            free(no);
            break;
        } else if (no->esquerda != NULL && no->direita != NULL) {
            No* sucessor = no->direita;
            avlCount++;
            while (sucessor->esquerda != NULL) {
                avlCount++;
                sucessor = sucessor->esquerda;
            }

            no->valor = sucessor->valor;
            no = sucessor;
        } else {
            No* filho = (no->esquerda != NULL) ? no->esquerda : no->direita;
            filho->pai = no->pai;

            avlCount++;
            if (no->pai == NULL) {
                arvoreAVL->raiz = filho;
            } else {
                if (no->pai->esquerda == no)
                    no->pai->esquerda = filho;
                else
                    no->pai->direita = filho;
            }

            free(no);
            break;
        }
    }

    if (no != NULL) {
        balanceamento(arvoreAVL, arvoreAVL->raiz);
    }
}

void executaRotinaDeInsercao(FILE *file) {
    Arvore *arvore = criar();
    int value;
    while (fscanf(file, "%d", &value) != EOF) {
       adicionar(arvore, value);
    }
}

void executaRotinaDeRemocao(FILE *file) {
    Arvore *arvore = criar();
    int value;

    while (fscanf(file, "%d", &value) != EOF) {
        adicionar(arvore, value);
    }

    while (fscanf(file, "%d", &value) != EOF) {
        remover(arvore, value);
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

    printf("%ld\n", avlCount);

    fclose(file);
    return 0;
}