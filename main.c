#include "BTree.h"
#include <stdio.h>
#include <stdlib.h>

void menu(BTree arvore) {
  while (1) {
    int opcao = 4;
    printf("1.Cadastrar\n2.Pesquisar\n3.Gravar\n0.Sair\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    switch (opcao) {
    case 1:
      int matricula, telefone;
      char *nome;
      printf("Digite a matrícula: ");
      scanf("%d", &matricula);
      printf("Digite o nome: ");
      fgets(nome, 50, stdin);
      printf("Digite o telefone: ");
      scanf("%d", &telefone);
      cadastrar(matricula, nome, telefone, arvore);
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
  BTree arvore = criarBTree(0);
  FILE *registro;
  if ((registro = fopen("registro.txt", "w")) == NULL) {

  } else {
    registro = fopen("registro.txt", "a");
  }
  menu(arvore);
}
