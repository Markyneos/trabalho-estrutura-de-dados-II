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

void insertNonFull(struct BTreeNode *node, int key) {
    int i = node->num_keys - 1;
    
    if (node->is_leaf) {
        // Insert key into the sorted order
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        // Find the child to insert the key
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }
        i++;
        
        if (node->children[i]->num_keys == M - 1) {
            // Split child if it's full
            splitChild(node, i);
            
            // Determine which of the two children is the new one
            if (node->keys[i] < key) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Function to insert a key into the B-tree
void insert(struct BTreeNode **root, int key) {
    struct BTreeNode *node = *root;

    if (node == NULL) {
        // Create a new root node
        *root = createNode(true);
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
    } else {
        if (node->num_keys == M - 1) {
            // Split the root if it's full
            struct BTreeNode *new_root = createNode(false);
            new_root->children[0] = node;
            splitChild(new_root, 0);
            *root = new_root;
        }
        insertNonFull(*root, key);
    }
}


int main() {

  return 0;
}
