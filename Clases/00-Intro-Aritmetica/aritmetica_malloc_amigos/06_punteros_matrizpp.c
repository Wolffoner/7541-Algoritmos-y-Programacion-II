#include <stdio.h>
#include <stdlib.h>

//¿Que tiene de diferente esta matriz con las anteriores?

int main(){
  int** matriz = calloc(5,sizeof(int*));

  for(int i=0;i<5;i++)
    matriz[i] = calloc(5,sizeof(int));

  matriz[3][2]=1;

  for(int y=0;y<5;y++){
    for(int x=0;x<5;x++)
      printf("%i ", matriz[y][x]);
    printf("\n");
  }
}
