#include <stdio.h>

// insercao usa recursao
#define ORDEM 4
// alocar o no, inserir na arvore, buscar e deletar a arvore inteira
// importar no pontoH que so tem o cabeçalho das funcoes
// buscar é procurar pelo no/chave na arvore, parametro arvore e no
// malloc é priomeiro desalocar a folha e dps o pai, o free é de baixo pra cima

typedef struct Arv {
  int qtdChaves; // quantidade de chaves
  int chave[ORDEM - 1];
  struct Arv *filho[ORDEM]; // sempre um a mais do que a chave do de cima
  int posOrigem[ORDEM];     // posicao da chaves do arquivo final
} Arv;

/* struct criarArv(struct Arvb){
   if (Arv == NULL){
       printf("Digite um valor real");
   }


} */

int main() {

  return 0;
}
