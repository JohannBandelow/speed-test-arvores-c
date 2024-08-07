#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

long int bCount = 0;

typedef struct noB {
    int total;
    int* chaves;
    struct noB** filhos;
    struct noB* pai;
} NoB;

typedef struct arvoreB {
    NoB* raiz;
    int ordem;
} ArvoreB;

ArvoreB* criarArvoreB(int);
NoB* criaNoB(ArvoreB*);
void percorreArvoreB(NoB*);
int pesquisaBinariaB(NoB*, int);
int localizaChaveB(ArvoreB*, int);
NoB* localizaNoB(ArvoreB*, int);
void adicionaChaveNoB(NoB*, NoB*, int);
int transbordoB(ArvoreB*, NoB*);
NoB* divideNoB(ArvoreB*, NoB*);
void adicionaChaveRecursivoB(ArvoreB*, NoB*, NoB*, int);
void inserir(ArvoreB*, int);
void remover(ArvoreB*, int);
void removerChaveRecursivoB(ArvoreB*, NoB*, int);
void removerChaveNoB(NoB*, int);

ArvoreB* criarArvoreB(int ordem) {
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = ordem;
    a->raiz = criaNoB(a);

    return a;
}

NoB* criaNoB(ArvoreB* arvore) {
    int max = arvore->ordem * 2;
    NoB* noB = malloc(sizeof(NoB));

    noB->pai = NULL;

    noB->chaves = malloc(sizeof(int) * (max + 1));
    noB->filhos = malloc(sizeof(NoB) * (max + 2));
    noB->total = 0;

    for (int i = 0; i < max + 2; i++) {
        bCount++;
        noB->filhos[i] = NULL;
    }

    return noB;
}

void percorreArvoreB(NoB* noB) {
    bCount++;
    if (noB != NULL) {
        bCount++;
        for (int i = 0; i < noB->total; i++) {
            bCount++;
            percorreArvoreB(noB->filhos[i]);

            printf("%d ", noB->chaves[i]);
        }

        percorreArvoreB(noB->filhos[noB->total]);
    }
}

int pesquisaBinariaB(NoB* noB, int chave) {
    int inicio = 0, fim = noB->total - 1, meio;

    while (inicio <= fim) {
        bCount++;

        meio = (inicio + fim) / 2;

        bCount++;
        if (noB->chaves[meio] == chave) {
            return meio;	
        }
        else if (noB->chaves[meio] > chave) {
            fim = meio - 1;
        }
        else {
            inicio = meio + 1;
        }
    }
    return inicio;
}

int localizaChaveB(ArvoreB* arvore, int chave) {
    NoB* noB = arvore->raiz;

    bCount++;
    while (noB != NULL) {
        bCount++;
        int i = pesquisaBinariaB(noB, chave);

        bCount++;
        if (i < noB->total && noB->chaves[i] == chave) {
            return 1;
        }
        else {
            noB = noB->filhos[i];
        }
    }

    return 0;
}

NoB* localizaNoB(ArvoreB* arvore, int chave) {
    NoB* noB = arvore->raiz;

    bCount++;
    while (noB != NULL) {
        bCount++;

        int i = pesquisaBinariaB(noB, chave);

        bCount++;
        if (noB->filhos[i] == NULL)
            return noB;
        else
            noB = noB->filhos[i];
    }

    return NULL;
}

void adicionaChaveNoB(NoB* noB, NoB* novo, int chave) {
    int i = pesquisaBinariaB(noB, chave);

    bCount++;
    for (int j = noB->total - 1; j >= i; j--) {
        bCount++;
        noB->chaves[j + 1] = noB->chaves[j];
        noB->filhos[j + 2] = noB->filhos[j + 1];
    }

    noB->chaves[i] = chave;
    noB->filhos[i + 1] = novo;

    noB->total++;
}

int transbordoB(ArvoreB* arvore, NoB* noB) {
    bCount++;

    return noB->total > arvore->ordem * 2;
}

NoB* divideNoB(ArvoreB* arvore, NoB* noB) {
    int meio = noB->total / 2;
    NoB* novo = criaNoB(arvore);
    novo->pai = noB->pai;

    bCount++;
    for (int i = meio + 1; i < noB->total; i++) {
        bCount++;
        novo->filhos[novo->total] = noB->filhos[i];
        novo->chaves[novo->total] = noB->chaves[i];
        bCount++;
        if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;

        novo->total++;
    }

    novo->filhos[novo->total] = noB->filhos[noB->total];
    bCount++;
    if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
    noB->total = meio;
    return novo;
}

void adicionaChaveRecursivoB(ArvoreB* arvore, NoB* noB, NoB* novo, int chave) {
    bCount++;

    adicionaChaveNoB(noB, novo, chave);

    bCount++;
    if (transbordoB(arvore, noB)) {
        int promovido = noB->chaves[arvore->ordem];
        NoB* novo = divideNoB(arvore, noB);

        bCount++;
        if (noB->pai == NULL) {

            NoB* pai = criaNoB(arvore);
            pai->filhos[0] = noB;
            adicionaChaveNoB(pai, novo, promovido);

            noB->pai = pai;
            novo->pai = pai;
            arvore->raiz = pai;
        }
        else
            adicionaChaveRecursivoB(arvore, noB->pai, novo, promovido);
    }
}

void inserir(ArvoreB* arvore, int chave) {
    NoB* noB = localizaNoB(arvore, chave);

    adicionaChaveRecursivoB(arvore, noB, NULL, chave);
}

void remover(ArvoreB* arvore, int chave) {
    bCount++;
    removerChaveRecursivoB(arvore, arvore->raiz, chave);
}

void removerChaveRecursivoB(ArvoreB* arvore, NoB* noB, int chave) {
    bCount++;
    if (noB == NULL)
        return;

    int indice = pesquisaBinariaB(noB, chave);

    bCount++;
    if (indice < noB->total && noB->chaves[indice] == chave) {
        bCount++;
        if (noB->filhos[indice] != NULL) {
            NoB* noSubstituto = noB->filhos[indice + 1];

            bCount++;
            while (noSubstituto->filhos[0] != NULL) {
                bCount++;
                noSubstituto = noSubstituto->filhos[0];
            }

            noB->chaves[indice] = noSubstituto->chaves[0];

            removerChaveRecursivoB(arvore, noSubstituto, noSubstituto->chaves[0]);
        }
        else {
            removerChaveNoB(noB, indice);
        }
    }
    else {
        removerChaveRecursivoB(arvore, noB->filhos[indice], chave);
    }
}

void removerChaveNoB(NoB* noB, int indice) {
    bCount++;
    for (int i = indice; i < noB->total - 1; i++) {
        bCount++;
        noB->chaves[i] = noB->chaves[i + 1];
        noB->filhos[i + 1] = noB->filhos[i + 2];
    }

    noB->total--;
}


void executaRotinaDeInsercao(FILE *file, int ordem) {
    ArvoreB* tree = criarArvoreB(ordem);
    int value;
    while (fscanf(file, "%d", &value) != EOF) {
        inserir(tree, value);
    }
}

void executaRotinaDeRemocao(FILE *file, int ordem) {
    ArvoreB* tree = criarArvoreB(ordem);
    int value;

    while (fscanf(file, "%d", &value) != EOF) {
        inserir(tree, value);
    }

    while (fscanf(file, "%d", &value) != EOF) {
        remover(tree, value);
    }
}

int main(int argc, char *argv[]) {
    int ordem = atoi(argv[1]);
    int rotina = atoi(argv[2]);

    FILE* file = fopen("build/values.txt", "r");
    if (file == NULL) {
        return 1;
    }

    if (rotina == 1) {
        executaRotinaDeInsercao(file, ordem);
    }

    if (rotina == 2) {
        executaRotinaDeRemocao(file, ordem);
    }

    printf("%ld\n", bCount);

    fclose(file);
    return 0;
}