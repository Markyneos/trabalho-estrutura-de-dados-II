#include <stdio.h>
#ifndef BTREE_H
#define BTREE_H

typedef struct Dados Dados;

typedef struct Pagina Pagina;

typedef Pagina *BTree;

BTree criarNode(int folha);

void split(BTree pai, int index);

BTree carregarBTree(FILE *arquivo);

void cadastrar(FILE *arquivo, int matricula, char *nome, char *telefone, BTree arvore);

#endif // BTREE_H
