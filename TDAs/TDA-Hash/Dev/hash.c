#include <string.h>
#include <stdlib.h>
#include "hash.h"

#define FACTOR_CARGA 0.75

typedef struct nodo_hash{
  char* clave;
  void* valor;
}nodo_hash_t;

struct hash{
  nodo_hash_t** tabla_hash;
  size_t capacidad_tabla;
  size_t cant_ocupadas;
  hash_destruir_dato_t destructor;
};

size_t funcion_hash(char* clave, size_t capacidad_tabla){
  return 0;
}

bool excede_factor_carga(size_t capacidad_tabla, size_t cant_ocupadas){
  bool excedido = false;
  double resultado = ((double)capacidad_tabla/cant_ocupadas);
  if(resultado >= FACTOR_CARGA)
    excedido = true;
  return excedido;
}

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial){
  if(capacidad_inicial < 3)
    capacidad_inicial = 3;
  
  hash_t* hash = calloc(1, sizeof(hash_t));
  if(!hash)
    return NULL;

  hash->capacidad_tabla = capacidad_inicial;
  hash->destructor = destruir_elemento;
  hash->tabla_hash = calloc(1, (sizeof(nodo_hash_t)*hash->capacidad_tabla));
  if(!hash->tabla_hash)
    return NULL;

  return hash;
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento){
  return 0;
}

int hash_quitar(hash_t* hash, const char* clave){
  return 0;
}

void* hash_obtener(hash_t* hash, const char* clave){
  return NULL;
}

size_t hash_cantidad(hash_t* hash){
  return 0;
}

bool hash_contiene(hash_t* hash, const char* clave){
  return false;
}

void hash_destruir(hash_t* hash){
  free(hash->tabla_hash);
  free(hash);
}

size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
  return 0;
}

