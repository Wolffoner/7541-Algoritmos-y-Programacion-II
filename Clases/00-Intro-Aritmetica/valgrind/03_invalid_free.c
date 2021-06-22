#include <stdio.h>
#include <stdlib.h>

int main(){

  char* puntero=(void*)0x1234;

  free(puntero);

  return 0;
}
