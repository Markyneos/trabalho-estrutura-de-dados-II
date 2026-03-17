#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"

int main() {

  FILE *registro;
  if ((registro=fopen("registro.txt", "w")) == NULL) {

  }
  else {
    registro = fopen("registro.txt", "a");
  }
}
