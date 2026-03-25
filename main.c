#include "BTree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int main() {
    FILE *registro = fopen("registro.txt", "rb+");
    if (!registro) {
        registro = fopen("registro.txt", "wb+");
    }

    BTree arvore = NULL;
    Registro r;
    long posicao = 0;

    while (fread(&r, sizeof(Registro), 1, registro)) {
        arvore = inserir(arvore, r.matricula, posicao); 
        posicao += sizeof(Registro);
    }

    int opcao;
    int lido;
    
    do {
        
        printf("\n==================================================\n");
        printf("       SISTEMA DE GERENCIAMENTO DE ALUNOS         \n");
        printf("==================================================\n");
        printf("  [ 1 ] Cadastrar Novo Aluno\n");
        printf("  [ 2 ] Pesquisar Aluno (por Matricula)\n");
        printf("  [ 3 ] Gravar Estrutura da Arvore (Dump)\n");
        printf("  [ 4 ] Sair do Sistema\n");
        printf("==================================================\n");
        printf("=> Escolha uma opcao: ");
        scanf("%d", &opcao);

        
        while (getchar() != '\n'); 

        printf("\n"); 
        switch (opcao) {
            case 1: {
                Registro novo;
                printf("--- CADASTRAR NOVO ALUNO ---\n");
                
                printf("[+] Matricula: ");
                lido = scanf("%d", &novo.matricula);
               
                if (lido != 1){
                    printf("Não pode digitar como string! \n");
                }
                while (getchar() != '\n'); 

                printf("[+] Nome Completo: ");
                fgets(novo.nome, 50, stdin);
                novo.nome[strcspn(novo.nome, "\n")] = 0; 

                printf("[+] Telefone.: ");
                fgets(novo.telefone, 20, stdin);
                novo.telefone[strcspn(novo.telefone, "\n")] = 0;

                fseek(registro, 0, SEEK_END);
                long pos = ftell(registro);
                fwrite(&novo, sizeof(Registro), 1, registro);
                fflush(registro); 

                arvore = inserir(arvore, novo.matricula, pos);
                
                printf("\n[ Sucesso ] Aluno cadastrado e indexado!\n");
               
                break;
            }

            case 2: {
                int mat;
                printf("--- PESQUISAR ALUNO ---\n");
                printf("[?] Digite a Matricula: ");
                scanf("%d", &mat);

                long pos = buscar(arvore, mat);

                if (pos == -1) {
                    printf("\n[ Aviso ] Matricula %d nao encontrada no sistema.\n", mat);
                } else {
                    fseek(registro, pos, SEEK_SET);
                    fread(&r, sizeof(Registro), 1, registro);

                    printf("\n--- DADOS ENCONTRADOS ---\n");
                    printf("  Nome.....: %s\n", r.nome);
                    printf("  Telefone.: %s\n", r.telefone);
                    printf("  (Posicao no arquivo: %ld)\n", pos); 
                    printf("-------------------------\n");
                }
                
                break;
            }

            case 3: {
                FILE *out = fopen("registro_arvore.txt", "w");
                if (out) {
                    fprintf(out, "RAIZ: %p\n", (void*)arvore);
                    gravar(arvore, out);
                    fclose(out);
                    printf("[ Sucesso ] Estrutura da arvore gravada em 'registro_arvore.txt'.\n");
                } else {
                    printf("[ Erro ] Nao foi possivel criar o arquivo de gravacao.\n");
                }
                
                break;
            }

            case 4: {
                printf("Encerrando o sistema!\n");
                printf("Ate logo!\n");
                break;
            }

            default: {
                printf("[ Erro ] Opcao invalida! Tente novamente.\n");
                
                break;
            }
        }
    } while (opcao != 4);

    liberar(arvore);
    fclose(registro);

    return 0;
}
