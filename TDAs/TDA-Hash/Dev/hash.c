#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

#define FACTOR_CARGA 0.75
#define ERROR -1
#define VALIDO 0

typedef struct nodo_hash{
  const char* clave;
  void* valor;
}nodo_hash_t;

struct hash{
  nodo_hash_t** tabla_hash;
  size_t capacidad_tabla;
  size_t cant_ocupadas;
  hash_destruir_dato_t destructor;
};

size_t funcion_hash(const char* clave, size_t capacidad_tabla){
  size_t auxiliar = 0;
  for(int i = 0; i < strlen(clave); i++)
    auxiliar += clave[i];
  size_t posicion = (size_t)(auxiliar%capacidad_tabla);
  return posicion;
}

bool excede_factor_carga(size_t capacidad_tabla, size_t cant_ocupadas){
  bool excedido = false;
  if(cant_ocupadas == 0)
    cant_ocupadas = 1;
  double resultado = capacidad_tabla%cant_ocupadas;
  if(resultado >= FACTOR_CARGA)
    excedido = true;
  return excedido;
}

nodo_hash_t** nodo_hash_crear(size_t capacidad){
  nodo_hash_t** nodo_hash = calloc(1, (sizeof(nodo_hash_t)*capacidad));
  if(!nodo_hash)
    return NULL;

  return nodo_hash;
}

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial){
  if(capacidad_inicial < 3)
    capacidad_inicial = 3;
  
  hash_t* hash = calloc(1, sizeof(hash_t));
  if(!hash)
    return NULL;

  hash->capacidad_tabla = capacidad_inicial;
  hash->destructor = destruir_elemento;
  hash->tabla_hash = nodo_hash_crear(capacidad_inicial);
  if(!hash->tabla_hash)
    return NULL;

  return hash;
}

nodo_hash_t* nodo_hash_insertar(const char* clave, void* elemento){
  nodo_hash_t* auxiliar = calloc(1, sizeof(nodo_hash_t));
  if(!auxiliar)
    return NULL;
  auxiliar->clave = clave;
  auxiliar->valor = elemento;
  return auxiliar;
}


int hash_insertar(hash_t* hash, const char* clave, void* elemento){
  if(!hash || !clave)
    return ERROR;
  if(excede_factor_carga(hash->capacidad_tabla, hash->cant_ocupadas)){
    printf("%zu\n", hash->cant_ocupadas);
  } else {
    size_t posicion = funcion_hash(clave, hash->capacidad_tabla);
    hash->tabla_hash[posicion] = nodo_hash_insertar(clave, elemento);
    if(!hash->tabla_hash[posicion])
      return ERROR;
    hash->cant_ocupadas++;
  }
  return VALIDO;
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
  if(hash->destructor){
  }
  for(int i = 0; i < hash->capacidad_tabla; i++)
      free(hash->tabla_hash[i]);
  free(hash->tabla_hash);
  free(hash);
}

size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
  return 0;
}

