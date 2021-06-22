#include <stdio.h>

int main(){

  char* puntero_invalido=(void*)0x1234;
  char lectura1 = puntero_invalido[0];

  return 0;
}
