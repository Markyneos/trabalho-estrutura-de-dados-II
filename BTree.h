#ifndef BTREE_H
#define BTREE_H

typedef struct Dados Dados;

typedef struct Pagina Pagina;

typedef Pagina *BTree;

BTree criarBTree(int folha);

#endif // BTREE_H
