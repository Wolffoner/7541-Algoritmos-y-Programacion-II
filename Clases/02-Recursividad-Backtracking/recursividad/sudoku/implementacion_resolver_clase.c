#include <stdio.h>

#include "sudoku.h"

int resolver_proximo_casillero(Sudoku* sudoku){
  
  int x,y;

  if(proximo_casillero_libre(sudoku, &x, &y)){
    for(int i=1;i<=9;i++){
      cambiar_casillero(sudoku, x, y, i, 0);
      if(validar_casillero(sudoku, x, y)){
        if(resolver_proximo_casillero(sudoku))
          return 1;
      }
    }
    cambiar_casillero(sudoku, x, y, 0, 0);
    return 0;
  }

  return 1;
}


int main(){

  Sudoku* sudoku =  crear_sudoku();
  if(!sudoku){
    perror("No se pudo crear el tablero");
    return -1;
  }

  //Pistas
  cambiar_casillero(sudoku, 4, 0, 2, 1);
  cambiar_casillero(sudoku, 2, 1, 5, 1);
  cambiar_casillero(sudoku, 6, 5, 8, 1);
  cambiar_casillero(sudoku, 3, 7, 3, 1);
  cambiar_casillero(sudoku, 1, 2, 1, 1);
  cambiar_casillero(sudoku, 8, 6, 7, 1);
  cambiar_casillero(sudoku, 4, 3, 1, 1);
  cambiar_casillero(sudoku, 5, 3, 2, 1);

  mostrar(sudoku);

  if(!resolver_proximo_casillero(sudoku))
    printf("No se pudo resolver\n");
  else
    printf("Se pudo resolver\n");

  mostrar(sudoku);

  destruir_sudoku(sudoku);
  return 0;
}
