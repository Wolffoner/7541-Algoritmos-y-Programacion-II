#include <stdio.h>
#include <stdlib.h>

char** perder_indirecto(){
  char** bloque_principal = malloc(sizeof(char*));
  bloque_principal[0] = malloc(1);
  return bloque_principal;
}

int main(){

  char** indirecto = perder_indirecto();

  return 0;
}
