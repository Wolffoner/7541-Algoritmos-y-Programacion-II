#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "ansicolor.h"
#include "sudoku.h"


Sudoku* crear_sudoku(){
  Sudoku* sudoku = malloc(sizeof(Sudoku));
  if(sudoku)
    bzero(sudoku->tablero, sizeof(Sudoku));
  return sudoku;
}

int destruir_sudoku(Sudoku* sudoku){
  if(sudoku)
    free(sudoku);
}

int mostrar(Sudoku* sudoku){
  printf(ANSI_COLOR_CYAN"┏━┯━┯━┳━┯━┯━┳━┯━┯━┓\n"ANSI_RESET);
  for(int j=0;j<9;j++){
    for(int i=0;i<9;i++){
      printf(ANSI_COLOR_CYAN"%s"ANSI_RESET, i%3==0?"┃":"│");
      if(sudoku->tablero[j][i].es_pista)
        printf(ANSI_COLOR_RED ANSI_BOLD);
      int n=sudoku->tablero[j][i].numero;
      printf("%c" ANSI_RESET, n==0?' ':'0'+n);
    }
    if(j==8)
      printf(ANSI_COLOR_CYAN"┃\n┗━┷━┷━┻━┷━┷━┻━┷━┷━┛\n" ANSI_RESET);
    else if(j%3==2){
      printf(ANSI_COLOR_CYAN "┃\n┣━┿━┿━╋━┿━┿━╋━┿━┿━┫\n" ANSI_RESET);
    }
    else printf(ANSI_COLOR_CYAN"┃\n┠─┼─┼─╂─┼─┼─╂─┼─┼─┨\n" ANSI_RESET);
  }
}

int cambiar_casillero(Sudoku* sudoku, int x, int y, int valor, int es_pista){
  if(!sudoku)
    return 0;
  if(valor<0 || valor>9)
    return 0;
  
  sudoku->tablero[y][x].numero = valor;
  sudoku->tablero[y][x].es_pista = es_pista;
  
  return 1;
}

int validar_casillero(Sudoku* sudoku, int x, int y){
  if(!sudoku)
    return 0;

  int mascaraFila=0;
  int mascaraColumna=0;
  int mascaraSector=0;
  int bit=0;

  //validar fila y columna
  for(int i=0;i<9;i++){
    int vFila = sudoku->tablero[y][i].numero;
    int vColumna = sudoku->tablero[i][x].numero;

    if(vFila!=0){

      bit = 1<<vFila;
      if(mascaraFila&bit)
        return 0;

      mascaraFila |= bit;
    }

    if(vColumna!=0){
      bit=1<<vColumna;
      if(mascaraColumna&bit)
        return 0;

      mascaraColumna |= bit;
    }
  }

  //validar sector
  for(int j=(y/3)*3;j<(y/3)*3+3;j++){
    for(int i=(x/3)*3;i<(x/3)*3+3;i++){
      int v = sudoku->tablero[j][i].numero;
      
      if(v!=0){
        bit = 1 << v;
        if(mascaraSector&bit)
          return 0;

        mascaraSector |= bit;
      }
    }
  }
  
  return 1;
}

int proximo_casillero_libre(Sudoku* sudoku, int *x, int *y){
  if(!sudoku)
    return 0;
  for(int j=0;j<9;j++)
    for(int i=0;i<9;i++){
      int v = sudoku->tablero[j][i].numero;
      if(v == 0){
        *x = i;
        *y = j;
        return 1;
      }
    }
  return 0;
}
