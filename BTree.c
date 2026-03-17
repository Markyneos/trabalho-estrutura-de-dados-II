#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"

#define M 4

// Ordem dos dados: matrícula, nome e telefone

typedef struct Pagina {
  unsigned int qtdChaves;
  unsigned int chaves[M - 1];
  struct Pagina *filhos[M];
  unsigned int posicao;
  int folha;
} Pagina;

typedef Pagina *BTree;

BTree criarBTree(int folha) {
  BTree novaArvore = (BTree) malloc(sizeof(BTree));
  if (novaArvore == NULL) {
    printf("Erro na alocação de memória.\n");
    exit(1);
  }
  novaArvore->folha = folha;
  novaArvore->qtdChaves = 0;

  for (int i = 0; i < M; i++) {
    novaArvore->filhos[i] = NULL;
  }

  return novaArvore;
}
