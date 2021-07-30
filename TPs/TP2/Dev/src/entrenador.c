#include "entrenador.h"
#include "hash.h"

struct _entrenador_t{
  char* nombre;
  size_t victorias;
  size_t cant_pokemones;
  hash_t* pokemones;
};

entrenador_t* crea_entrenador(char* nombre){
  if(!nombre)
    return NULL;
  char* nombre_aux = calloc(1, sizeof(strlen(nombre))+1);
  if(!nombre_aux)
    return NULL;
  entrenador_t* entrenador = calloc(1, sizeof(entrenador_t));
  if(!entrenador){
    free(nombre_aux);
    return NULL;
  }
  hash_t* pokemones = hash_crear(NULL, 1);
  strcpy(nombre_aux, nombre);
  entrenador->nombre = nombre;
  entrenador->victorias = 0;
  entrenador->cant_pokemones = 0;
  entrenador->pokemones = pokemones;
  return entrenador;
}

entrenador_t* cargar_entrenador(char* nombre, size_t victorias, hash_t* pokemones){
  return NULL;
}

void destruye_entrenador(entrenador_t* entrenador){
  if(!entrenador)
    return;
  free(entrenador->nombre);
  hash_destruir(entrenador->pokemones);
  free(entrenador);
}
