#include "BTree.h"
#include <stdio.h>
#include <stdlib.h>

#define M 4

// Ordem dos dados: matrícula, nome e telefone

typedef struct Chave {
  unsigned int matricula;
  long posicao;
} Chave;

typedef struct Pagina {
  unsigned int qtdChaves;
  Chave chaves[M - 1];
  struct Pagina *filhos[M];
  int folha;
} Pagina;

typedef Pagina *BTree;

BTree criarNode(int folha) {
  BTree novoNode = (BTree)malloc(sizeof(Pagina));
  if (novoNode == NULL) {
    printf("Erro na alocação de memória.\n");
    exit(1);
  }
  novoNode->folha = folha;
  novoNode->qtdChaves = 0;

  for (int i = 0; i < M; i++) {
    novoNode->filhos[i] = NULL;
  }

  return novoNode;
}

BTree carregarBTree(FILE *arquivo) {
  BTree novaArvore = (BTree)malloc(sizeof(Pagina));
  if (novaArvore == NULL) {
    printf("Erro na alocação de memória.\n");
    exit(1);
  }
  return novaArvore;
}

void cadastrar(FILE *arquivo, int matricula, char *nome, char *telefone, BTree arvore) {
  fseek(arquivo, 0, SEEK_END);
  long posicao = ftell(arquivo);
}
