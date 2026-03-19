#include "BTree.h"
#include <stdio.h>
#include <stdlib.h>

void menu(BTree arvore, FILE *arquivo) {
  while (1) {
    int opcao = 4;
    printf("1.Cadastrar\n2.Pesquisar\n3.Gravar\n0.Sair\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    unsigned int matricula;
    char nome[50], telefone[11];
    switch (opcao) {
    case 1:
      printf("Digite a matrícula: ");
      scanf("%d", &matricula);
      printf("Digite o nome: ");
      fgets(nome, 50, stdin);
      printf("Digite o telefone: ");
      fgets(telefone, 11, stdin);
      cadastrar(arquivo, matricula, nome, telefone, arvore);
      break;
    case 2:
      break;
    case 3:
      break;
    case 0:
      return;
    }
  }
}

int main() {
  BTree arvore;
  FILE *registro;
  if ((registro = fopen("registro.txt", "w")) == NULL) {
    arvore = criarNode(1);
  } else {
    registro = fopen("registro.txt", "a");
    arvore = carregarBTree(registro);
  }
  menu(arvore, registro);

  return 0;
}
