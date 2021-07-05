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

nodo_hash_t** tabla_hash_crear(size_t capacidad){
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
  hash->tabla_hash = tabla_hash_crear(capacidad_inicial);
  if(!hash->tabla_hash)
    return NULL;

  return hash;
}

nodo_hash_t* nodo_hash_crear(const char* clave, void* elemento){
  nodo_hash_t* auxiliar = calloc(1, sizeof(nodo_hash_t));
  if(!auxiliar)
    return NULL;
  auxiliar->clave = clave;
  auxiliar->valor = elemento;
  return auxiliar;
}

int nodo_hash_insertar(nodo_hash_t** tabla_hash, size_t capacidad, const char* clave, void* elemento){
  size_t posicion = funcion_hash(clave, capacidad);
  if(tabla_hash[posicion] && tabla_hash[posicion]->clave == clave){
    tabla_hash[posicion]->valor = elemento;
    return VALIDO;
  }
  nodo_hash_t* nodo = nodo_hash_crear(clave, elemento);
  if(!nodo)
    return ERROR;

  if(!tabla_hash[posicion]){
    tabla_hash[posicion] = nodo;
  }else{
    while(tabla_hash[posicion])
      if(posicion == capacidad-1){
        posicion = 0;
      } else {
        posicion++;
      }
    tabla_hash[posicion] = nodo;
  }
  return VALIDO;
}

void reemplazar_tabla(nodo_hash_t*** tabla, nodo_hash_t** tabla_cambiar){
  nodo_hash_t** tabla_liberar = *tabla;
  *tabla = tabla_cambiar;
  free(tabla_liberar);
}

bool rehash_tabla(hash_t* hash){
  nodo_hash_t** tabla_auxiliar = tabla_hash_crear(hash->capacidad_tabla*2);
  if(!tabla_auxiliar)
    return false;

  for(int i = 0; i < hash->capacidad_tabla; i++){
    if(hash->tabla_hash[i]){
      nodo_hash_insertar(tabla_auxiliar,hash->capacidad_tabla*2, hash->tabla_hash[i]->clave, hash->tabla_hash[i]->valor);
      free(hash->tabla_hash[i]);
    }
  }
  hash->capacidad_tabla = hash->capacidad_tabla*2;
  reemplazar_tabla(&hash->tabla_hash, tabla_auxiliar);
  return true;
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento){
  if(!hash || !clave)
    return ERROR;
  if(excede_factor_carga(hash->capacidad_tabla, hash->cant_ocupadas)){
    bool rehasheo = rehash_tabla(hash);
    if(!rehasheo)
      return ERROR;
  }
  if(nodo_hash_insertar(hash->tabla_hash, hash->capacidad_tabla, clave, elemento) == VALIDO){
    hash->cant_ocupadas++;
    return VALIDO;
  }
  return ERROR;
}

int hash_quitar(hash_t* hash, const char* clave){
  if(!hash || !clave)
    return ERROR;
  size_t posicion = funcion_hash(clave, hash->capacidad_tabla);
  size_t posicion_proxima = posicion + 1;
  if(posicion == hash->capacidad_tabla-1){
    posicion_proxima = 0;
  }
  if(!hash->tabla_hash[posicion_proxima]){
    if(hash->destructor){
    }
    free(hash->tabla_hash[posicion]);
    hash->tabla_hash[posicion] = NULL;
    return VALIDO;
  } else {
    
  }
  return ERROR;
}

void* hash_obtener(hash_t* hash, const char* clave){
  if(!hash || !clave)
    return NULL;
  size_t posicion = funcion_hash(clave, hash->capacidad_tabla);
  if(hash->tabla_hash[posicion] && hash->tabla_hash[posicion]->clave == clave){
    return hash->tabla_hash[posicion]->valor;
  }else{
    while(hash->tabla_hash[posicion] && hash->tabla_hash[posicion]->clave != clave){
      if(posicion == (hash->capacidad_tabla-1)){
        posicion = 0;
      } else {
        posicion++;
      }
    }
    if(!hash->tabla_hash[posicion]){
      return NULL;
    }else{
      return hash->tabla_hash[posicion]->valor;
    }
  }
}

size_t hash_cantidad(hash_t* hash){
  if(!hash)
    return 0;
  return hash->cant_ocupadas;
}

bool hash_contiene(hash_t* hash, const char* clave){
  if(!hash || !clave)
    return false;
  void* elemento = hash_obtener(hash, clave);
  if(!elemento)
    return false;
  return true;
}

void hash_destruir(hash_t* hash){
  if(hash->destructor){
  }
  for(int i = 0; i < hash->capacidad_tabla; i++){
    if(hash->tabla_hash[i] != NULL){
      free(hash->tabla_hash[i]);
    }
  }
  free(hash->tabla_hash);
  free(hash);
}

size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
  return 0;
}

