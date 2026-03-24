#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>

#define M 4

typedef struct Registro {
    int matricula;
    char nome[50];
    char telefone[20];
} Registro;

typedef struct Pagina {
    int qtdChaves;
    int chaves[M - 1];
    long posicao[M - 1];
    struct Pagina *filhos[M];
    int folha;
} Pagina;

typedef Pagina *BTree;

BTree criarPagina(int folha);

void split(BTree x, int i);

void inserirNaoCheio(BTree x, int k, long pos);

void inserir(BTree pagina, int k, long pos);

long buscar(BTree x, int k);

void liberar(BTree x);

void gravar(BTree x, FILE *f);

#endif // BTREE_H
