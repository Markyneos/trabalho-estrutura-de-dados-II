#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"

BTree criarPagina(int folha) {
    BTree novaPagina = (BTree)malloc(sizeof(Pagina));
    novaPagina->folha = folha;
    novaPagina->qtdChaves = 0;

    for (int i = 0; i < M; i++) {
        novaPagina->filhos[i] = NULL;
    }

    return novaPagina;
}

void split(BTree x, int i) {
    BTree y = x->filhos[i];
    BTree z = criarPagina(y->folha);

    z->qtdChaves = (M/2) - 1;

    for (int j = 0; j < z->qtdChaves; j++) {
        z->chaves[j] = y->chaves[j + M/2];
        z->posicao[j] = y->posicao[j + M/2];
    }

    if (!y->folha) {
        for (int j = 0; j < M/2; j++) {
            z->filhos[j] = y->filhos[j + M/2];
        }
    }

    y->qtdChaves = (M/2) - 1;

    for (int j = x->qtdChaves; j >= i + 1; j--) {
        x->filhos[j+1] = x->filhos[j];
    }

    x->filhos[i + 1] = z;

    for (int j=x->qtdChaves-1; j >= i; j--) {
        x->chaves[j + 1] = x->chaves[j];
        x->posicao[j + 1] = x->posicao[j];
    }

    x->chaves[i] = y->chaves[M/2 - 1];
    x->posicao[i] = y->posicao[M/2 - 1];

    x->qtdChaves++;
}

void inserirNaoCheio(BTree x, int k, long pos) {
    int i = x->qtdChaves - 1;

    if (x->folha) {
        while (i >= 0 && k < x->chaves[i]) {
            x->chaves[i + 1] = x->chaves[i];
            x->posicao[i + 1] = x->posicao[i];
            i--;
        }

        x->chaves[i + 1] = k;
        x->posicao[i + 1] = pos;
        x->qtdChaves++;
    }
    else {
        while (i >= 0 && k < x->chaves[i]) {
            i--;
        }

        i++;

        if (x->filhos[i]->qtdChaves == M-1) {
            split(x, i);

            if (k > x->chaves[i]) {
                i++;
            }
        }

        inserirNaoCheio(x->filhos[i], k, pos);
    }
}

void inserir(BTree pagina, int k, long pos) {
    if (pagina == NULL) {
        pagina = criarPagina(1);
        pagina->chaves[0] = k;
        pagina->posicao[0] = pos;
        pagina->qtdChaves = 1;
        return;
    }

    if (pagina->qtdChaves == M - 1) {
        BTree novaPagina = criarPagina(0);
        novaPagina->filhos[0] = pagina;

        split(novaPagina, 0);

        int i = 0;
        if (k > novaPagina->chaves[0]) {
            i++;
        }

        inserirNaoCheio(novaPagina->filhos[i], k, pos);

        pagina = novaPagina;
    }
    else {
        inserirNaoCheio(pagina, k, pos);
    }
}

long buscar(BTree x, int k) {
    int i = 0;

    while (i < x->qtdChaves && k > x->chaves[i]) {
        i++;
    }

    if (i < x->qtdChaves && k == x->chaves[i]) {
        return x->posicao[i];
    }

    if (x->folha) {
        return -1;
    }

    return buscar(x->filhos[i], k);
}

void liberar(BTree x) {
    if (x == NULL) return;

    if (!x->folha) {
        for (int i = 0; i <= x->qtdChaves; i++) {
            liberar(x->filhos[i]);
        }
    }

    free(x);
}

void gravar(BTree x, FILE *f) {
    if (x == NULL) return;

    fprintf(f, "PAGINA %p | Quantidade de Chaves = %d", x, x->qtdChaves);

    for (int i = 0; i < x->qtdChaves; i++) {
        fprintf(f, "%d ", x->chaves[i]);
    }
    fprintf(f, "\n");

    if (!x->folha) {
        for (int i = 0; i <= x->qtdChaves; i++) {
            gravar(x->filhos[i], f);
        }
    }
}
