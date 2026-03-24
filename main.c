#include "BTree.h"
#include <stdio.h>
#include <string.h>

int main() {
  FILE *registro = fopen("registro.txt", "rb+");
  if (!registro) {
    registro = fopen("registro.txt", "wb+");
  }

  BTree arvore = NULL;

  Registro r;
  long posicao = 0;

  while (fread(&r, sizeof(Registro), 1, registro)) {
    inserir(arvore, r.matricula, posicao);
    posicao += sizeof(Registro);
  }

  int opcao;

  do {
    printf("\n1 - Cadastrar\n2 - Pesquisar\n3 - Gravar\n4 - Sair\n");
    scanf("%d", &opcao);

if (opcao == 1) {
    Registro novo;

    printf("Matricula: ");
    scanf("%d", &novo.matricula);
    
    // LIMPEZA DO BUFFER AQUI
    while (getchar() != '\n'); 

    printf("Nome: ");
    fgets(novo.nome, 50, stdin);
    // O fgets mantém o \n no final da string. Se quiser remover:
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Telefone: ");
    fgets(novo.telefone, 20, stdin);
    novo.telefone[strcspn(novo.telefone, "\n")] = 0;

    fseek(registro, 0, SEEK_END);
    long pos = ftell(registro);

    fwrite(&novo, sizeof(Registro), 1, registro);
    inserir(arvore, novo.matricula, pos);
}

    else if (opcao == 2) {
      int mat;
      printf("Matricula: ");
      scanf("%d", &mat);

      long pos = buscar(arvore, mat);

      if (pos == -1) {
        printf("Não encontrado.\n");
      } else {
        fseek(registro, pos, SEEK_SET);
        fread(&r, sizeof(Registro), 1, registro);

        printf("Nome: %s\n", r.nome);
        printf("Telefone: %s\n", r.telefone);
      }
    } else if (opcao == 3) {
      FILE *out = fopen("registro_arvore.txt", "w");

      fprintf(out, "RAIZ: %p\n", arvore);
      gravar(arvore, out);

      fclose(out);

      printf("Árvore gravada.\n");
    }
  } while (opcao != 4);

  liberar(arvore);
  fclose(registro);

  return 0;
}
