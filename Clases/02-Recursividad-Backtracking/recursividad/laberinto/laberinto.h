#ifndef _LABERINTO_H_
#define _LABERINTO_H_

typedef struct{
  char* bloques;
  int ancho, alto;
  int entradaX, entradaY;

  int posX, posY;
}Laberinto;

Laberinto* crear_laberinto(const char* nombre_archivo);

void destruir_laberinto(Laberinto *lab);

void mostrar_laberinto(Laberinto* lab);




char mirar_posicion(Laberinto* lab, int dx, int dy);

char mirar_posicion_actual(Laberinto* lab);

int marcar_posicion_actual(Laberinto* lab);

int desmarcar_posicion_actual(Laberinto* lab);

int moverse(Laberinto* lab, int dx, int dy);

int es_salida(char bloque);

int es_pared(char bloque);

int es_marca(char bloque);

//A implementar
//int explorar_laberinto(Laberinto* lab);

#endif
