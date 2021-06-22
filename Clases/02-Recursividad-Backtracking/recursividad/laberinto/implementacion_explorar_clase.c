#include <stdio.h>
#include "laberinto.h"

int explorar_laberinto(Laberinto* lab){
  mostrar_laberinto(lab);
  char bloque = mirar_posicion_actual(lab);

  if(es_salida(bloque))
    return 1;

  if(es_pared(bloque))
    return 0;

  if(es_marca(bloque))
    return 0;

  marcar_posicion_actual(lab);

  //me muevo izq
  moverse(lab, -1, 0);
  if(explorar_laberinto(lab)==1)
    return 1;
  moverse(lab, 1, 0);

  //me muevo der
  moverse(lab, 1, 0);
  if(explorar_laberinto(lab)==1)
    return 1;
  moverse(lab, -1, 0);

  //me muevo ad
  moverse(lab, 0, 1);
  if(explorar_laberinto(lab)==1)
    return 1;
  moverse(lab, 0, -1);

  //me muevo at
  moverse(lab, 0, -1);
  if(explorar_laberinto(lab)==1)
    return 1;
  moverse(lab, 0, 1);

  desmarcar_posicion_actual(lab);

  return 0;
}


int main(int argc, char* argv[]){
  if(argc < 2){
    fprintf(stderr, "%s <archivo>\n", argv[0]);
  }

  Laberinto* lab = crear_laberinto(argv[1]);

  if(lab){
   // mostrar_laberinto(lab);
    explorar_laberinto(lab);
  //  mostrar_laberinto(lab);
  }

  destruir_laberinto(lab);
  return 1;
}
