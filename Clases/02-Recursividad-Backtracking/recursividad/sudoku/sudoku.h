#ifndef _SUDOKU_H_
#define _SUDOKU_H_

typedef struct{
  int numero;
  int es_pista;
}Casillero;

typedef struct {
  Casillero tablero[9][9];
} Sudoku;

Sudoku* crear_sudoku();
int destruir_sudoku(Sudoku* sudoku);

int mostrar(Sudoku* sudoku);

int cambiar_casillero(Sudoku* sudoku, int x, int y, int valor, int es_pista);
int validar_casillero(Sudoku* sudoku, int x, int y);
int proximo_casillero_libre(Sudoku* sudoku, int *x, int *y);

// A implementar
// int resolver_proximo_casillero(sudoku* sudoku);

#endif
