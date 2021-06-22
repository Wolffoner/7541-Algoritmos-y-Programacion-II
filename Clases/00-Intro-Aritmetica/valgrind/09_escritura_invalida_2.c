#include <stdio.h>
#include <stdlib.h>

int main(){

  char* puntero=malloc(1);

  free(puntero);

  puntero[0] = 1;

  return 0;
}
