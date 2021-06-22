#include <stdio.h>
#include <stdlib.h>

int main(){

  char* puntero=malloc(1);

  free(puntero);

  free(puntero);

  return 0;
}
