#include <stdio.h>

void funcion1(){
  int i;
  printf("Valor de i dentro de funcion1: %i\n", i);
  i=1212121212;
}

void funcion2(){
  char i, j,k,l;
  printf("Valor de i y j dentro de funcion2: %i,%i,%i,%i\n", i, j,k,l);
}


int main(){

  int i;

  printf("Valor de i en main: %i\n", i);

  funcion1();
  funcion1();
  funcion2();

  return 0;
}
