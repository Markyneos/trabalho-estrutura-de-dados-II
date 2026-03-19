#ifndef BTREE_H
#define BTREE_H

typedef struct Dados Dados;

typedef struct Pagina Pagina;

typedef Pagina *BTree;

BTree criarBTree(int folha);

void cadastrar(int matricula, char *nome, int telefone, BTree arvore);

#endif // BTREE_H
