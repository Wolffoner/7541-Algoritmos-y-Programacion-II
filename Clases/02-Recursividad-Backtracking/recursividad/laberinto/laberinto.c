#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "laberinto.h"
#include "ansicolor.h"

int leer_bloques(Laberinto* lab, int fd){
  int x=0,y=0;
  struct stat stats;
  int ancho=0, primer_linea=1, tamanio;
  int offset=0;
  char c, *bloques = NULL;

  if(fstat(fd, &stats)==0){
    tamanio = stats.st_size;
    bloques = malloc(tamanio);
  }

  if(!bloques)
    return 0;
  
  memset(bloques, '#', tamanio);
  lab->entradaX = -1;
  
  while(read(fd, &c, 1) == 1){
    
    if(c=='\n'){
      if(primer_linea){
        ancho = x;
        primer_linea = 0;
      }
      y++;
      x=0;
    }
    else{
      offset=y*ancho+x;

      if(offset<tamanio)
        bloques[offset]=c;
      
      if(c == 'E'){
        lab->entradaX = x;
        lab->entradaY = y;
      }

      x++;
    }
  }

  lab->bloques = bloques;
  lab->ancho = ancho;
  lab->alto = y;
  if(lab->entradaX == -1){
    free(bloques);
    return 0;
  }
  lab->posX = lab->entradaX;
  lab->posY = lab->entradaY;
  
  return 1;
}

Laberinto* crear_laberinto(const char* nombre_archivo){
  Laberinto* lab = malloc(sizeof(Laberinto));
  int lectura_correcta = 1;
  
  if(!lab)
    return NULL;

  char c, *bloques=NULL;
  int tamanio = 0;
  
  int archivo = open(nombre_archivo, O_RDONLY);

  if(archivo<0){
    free(lab);
    return NULL;
  }

  lectura_correcta = leer_bloques(lab, archivo);
  
  close(archivo);
  if(lectura_correcta<=0){
    free(lab);
    lab = NULL;
  }
  return lab;
}

void destruir_laberinto(Laberinto *lab){
  if(!lab)
    return;

  if(lab->bloques)
    free(lab->bloques);

  free(lab);
}

char obtener_bloque(Laberinto* lab, int x, int y){
  if(!lab || !lab->bloques)
    return '#';

  return lab->bloques[y*lab->ancho+x];
}

int cambiar_bloque(Laberinto* lab, int x, int y, char valor){
  if(!lab || !lab->bloques)
    return -1;

  lab->bloques[y*lab->ancho+x] = valor;
  return 1;
}

void mostrar_laberinto(Laberinto* lab){
  if(!lab)
    return;
  
  for(int j=0;j<lab->alto;j++){
    for(int i=0;i<lab->ancho;i++){
      char c = obtener_bloque(lab, i, j);
      if(c=='#')
        printf(ANSI_BOLD"█"ANSI_RESET);
      else if(c=='*')
        printf(ANSI_BOLD ANSI_COLOR_YELLOW"*"ANSI_RESET);
      else if(c=='.')
        printf(ANSI_COLOR_CYAN"█"ANSI_RESET);
      else if(c=='S')
        printf(ANSI_COLOR_RED ANSI_BOLD"S"ANSI_RESET);
      else if(c=='E')
        printf(ANSI_COLOR_GREEN ANSI_BOLD"E"ANSI_RESET);
      else
        printf("%c", c);
    }
    printf("\n");
  }
  printf("\n");
}

char mirar_posicion(Laberinto* lab, int dx, int dy){
  return obtener_bloque(lab, lab->posX+dx, lab->posY+dy);
}

char mirar_posicion_actual(Laberinto* lab){
  return mirar_posicion(lab, 0, 0);
}

int marcar_posicion_actual(Laberinto* lab){
  if(mirar_posicion(lab,0,0) == ' ')
    return cambiar_bloque(lab, lab->posX, lab->posY, '.');
  return -1;
}

int desmarcar_posicion_actual(Laberinto* lab){
  if(mirar_posicion(lab,0,0) == '.')
    return cambiar_bloque(lab, lab->posX, lab->posY, '*');
  return -1;
}

int moverse(Laberinto* lab, int dx, int dy){
  if(!lab)
    return -1;

  lab->posX += dx;
  lab->posY += dy;

  return 0;
}

int es_salida(char bloque){
  return bloque=='S';
}

int es_pared(char bloque){
  return bloque=='#';
}

int es_marca(char bloque){
  return bloque=='.' || bloque=='*';
}
