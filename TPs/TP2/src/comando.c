#include "comando.h"

struct _comando_t {
    const char* nombre;
    const char* descripcion;
    ejecutar_comando_t ejecutar;
};


comando_t* comando_crear( const char* nombre, const char* descripcion, void (*ejecutar_comando_t)(void*, char**, void*)) {
  if(!nombre || !descripcion || !ejecutar_comando_t){
    return NULL;
  }
    comando_t* comando = calloc(1, sizeof(comando_t));
    if(!comando)
        return NULL;
    comando->nombre = nombre;
    comando->descripcion = descripcion;
    comando->ejecutar = ejecutar_comando_t;

    return comando;
}

ejecutar_comando_t obtener_ejecutar_comando(comando_t* comando){
  if(!comando)
    return NULL;
  return comando->ejecutar;
}

char* obtener_nombre_comando(comando_t* comando){
  if(!comando)
    return NULL;
  return (char*) comando->nombre;
}

char* obtener_descripcion_comando(comando_t* comando){
  if(!comando)
    return NULL;
  return (char*) comando->descripcion;
}

void comando_destruir(comando_t* comando){
  if(comando)
    free(comando);
}
