#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

#define FACTOR_CARGA 0.75
#define ERROR -1
#define VALIDO 0
#define CAPACIDAD_MIN 3

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

const nodo_hash_t* NODO_VACIO = (nodo_hash_t*)"VACIO";
/*  
 * Genera una posicion indicada donde iria este elemento dentro de la tabla de hash,
 * Se le pasa por parametro la cave, y la capacidad de la tabla.
 * Retorna la posicion indicada.
*/
size_t funcion_hash(const char* clave, size_t capacidad_tabla){
  size_t auxiliar = 0;
  for(int i = 0; i < strlen(clave); i++)
    auxiliar += clave[i];
  
  return (size_t)(auxiliar%capacidad_tabla);
}

/*
 * Verifica si la tabla de hash excede el factor de carga,
 * Se le pasa por parametros la capacidad de la tabla y la cantidad de celdas ocupadas.
 * Retorna true si excedio el factor de carga y false en caso contrario.
*/
bool excede_factor_carga(size_t capacidad_tabla, size_t cant_ocupadas){
  double resultado = (double)cant_ocupadas/capacidad_tabla;
  return cant_ocupadas !=0 && resultado >= FACTOR_CARGA;
}

/*
 *  Reserva memoria para la tabla de hash,
 *  se le pasa por parametro la capacidad que tendra la tabla,
 *  retorna el puntero a la tabla vacia creada.
*/
nodo_hash_t** tabla_hash_crear(size_t capacidad){
  nodo_hash_t** tabla_hash = calloc(1, (sizeof(nodo_hash_t*)*capacidad));
  if(!tabla_hash)
    return NULL;

  return tabla_hash;
}

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial){
  if(capacidad_inicial < CAPACIDAD_MIN)
    capacidad_inicial = CAPACIDAD_MIN;
  
  hash_t* hash = calloc(1, sizeof(hash_t));
  if(!hash)
    return NULL;

  hash->capacidad_tabla = capacidad_inicial;
  hash->destructor = destruir_elemento;
  hash->cant_ocupadas = 0;
  hash->tabla_hash = tabla_hash_crear(capacidad_inicial);
  if(!hash->tabla_hash){
    free(hash);
    return NULL;
  }
  return hash;
}

/*
 * Crea un nodo_hash_t para insertar a la tabla de hash,
 * se le pasa por parametros la clave y el elemento,
 * retorna el nodo_hash_t creado con los valores pasados por parametros.
*/
nodo_hash_t* nodo_hash_crear(const char* clave, void* elemento){
  nodo_hash_t* auxiliar = calloc(1, sizeof(nodo_hash_t));
  if(!auxiliar)
    return NULL;
  char* clave_aux = calloc(1, sizeof(strlen(clave)+1));
  if(!clave_aux){
    free(auxiliar);
    return NULL;
  }
  strcpy(clave_aux, clave);
  auxiliar->clave = clave_aux;
  auxiliar->valor = elemento;
  return auxiliar;
}

void modifica_posicion(size_t* posicion, size_t posicion_final){
  if(*posicion == posicion_final){
    *posicion = *posicion + 1;
  } else {
    *posicion = 0;
  }
}
/*
 * Inserta un nodo dentro de la tabla de hash,
 * Se pasan por parametros la tabla de hash, la cantidad de celdas ocupadas, la capacidad de la tabla, la clave y el elemento,
 * Retorna VALIDO si logra insertarlo o en caso contrario retorna ERROR.
 */
int nodo_hash_insertar(hash_t* hash, const char* clave, void* elemento){
  if(!hash->tabla_hash || !hash){
    return ERROR;
  }
  void* auxiliar = hash_obtener(hash, clave);
  size_t posicion = funcion_hash(clave, hash->capacidad_tabla);
  size_t posicion_final = hash->capacidad_tabla-1;
  if(auxiliar){
    while(hash->tabla_hash[posicion]){
      if(hash->tabla_hash[posicion] != NODO_VACIO){
        if(strcmp(hash->tabla_hash[posicion]->clave, clave) == 0){
          if(hash->destructor)
            hash->destructor(hash->tabla_hash[posicion]->valor);
          hash->tabla_hash[posicion]->valor = elemento;
          return VALIDO;
        } else {
          modifica_posicion(&posicion, posicion_final);
        }
      } else{
        modifica_posicion(&posicion, posicion_final);
      }
    }
  } else {
    nodo_hash_t* nodo = nodo_hash_crear(clave, elemento);
      if(!nodo)
        return ERROR;

    if(!hash->tabla_hash[posicion] || hash->tabla_hash[posicion] == NODO_VACIO){
      hash->tabla_hash[posicion] = nodo;
      hash->cant_ocupadas++;
      return VALIDO;
    } else {
      while(hash->tabla_hash[posicion]){
        modifica_posicion(&posicion, posicion_final);
      }
      hash->tabla_hash[posicion] = nodo;
      hash->cant_ocupadas++;
      return VALIDO;
    }
  }
  return ERROR;
}

/*
 * Reemplaza la tabla de hash con otra tabla auxiliar y libera la anterior.
 * Se le pasa por parametro la tabla y la tabla_auxiliar.
 */
void reemplazar_tabla(nodo_hash_t*** tabla, nodo_hash_t** tabla_auxiliar){
  nodo_hash_t** tabla_liberar = *tabla;
  *tabla = tabla_auxiliar;
  free(tabla_liberar);
}

/*
 * Le hace un rehash a la tabla, crea otro tabla con el doble de capacidad y la reemplaza.
 * se le pasa por parametro el hash
 * retorna true si pudo completa el rehash o en caso contrario retorna false.
 */
bool rehash_tabla(hash_t* hash){
  nodo_hash_t** tabla_hash = hash->tabla_hash;
  nodo_hash_t** tabla_auxiliar = tabla_hash_crear((hash->capacidad_tabla)*2);
  reemplazar_tabla(&hash->tabla_hash, tabla_auxiliar);
  hash->capacidad_tabla = (hash->capacidad_tabla)*2;
  hash->cant_ocupadas = 0;
  if(!tabla_auxiliar)
    return false;
  for(int i = 0; i < hash->capacidad_tabla; i++){
    if(hash->tabla_hash[i] && hash->tabla_hash[i] != NODO_VACIO){
      nodo_hash_insertar(hash, tabla_hash[i]->clave, tabla_hash[i]->valor);
      free(tabla_hash[i]->clave);
      free(tabla_hash[i]);
    }
  }
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
  return nodo_hash_insertar(hash, clave, elemento);
}

/*
 * Modifica la posicion proxima si posicion esta en su posicion final, la posicion proxima pasa a ser 0,
 * si no es asi la posicion proxima pasa a ser posicion + 1,
 * Se le pasa por parametros la posicion final, posicion actual, y posicion proxima.
 */
size_t modifica_posicion_proxima(size_t posicion_final, size_t posicion){
  size_t posicion_proxima = 0;
  if(posicion == posicion_final){
    posicion_proxima = 0;
  } else {
    posicion_proxima++;
  }
  return posicion_proxima;
}

int hash_quitar(hash_t* hash, const char* clave){
  if(!hash || !hash->tabla_hash)
    return ERROR;
  size_t posicion = funcion_hash(clave, hash->capacidad_tabla);
  size_t posicion_final = hash->capacidad_tabla-1;
  nodo_hash_t* nodo_borrar = NULL;
  while(hash->tabla_hash[posicion] && !nodo_borrar){
    if(hash->tabla_hash[posicion] == NODO_VACIO){
      if(posicion == posicion_final){
        posicion = 0;
      } else {
        posicion++;
      }
    } else if(hash->tabla_hash[posicion] != NODO_VACIO && hash->tabla_hash[posicion]){
      if(strcmp(hash->tabla_hash[posicion]->clave, clave) != 0){
        if(posicion == posicion_final){
          posicion = 0;
        } else {
          posicion++;
        }
      } else {
        nodo_borrar = hash->tabla_hash[posicion];
      }
    }
  }
  if(!nodo_borrar)
    return ERROR;

  if(hash->destructor)
      hash->destructor(nodo_borrar->valor);
  free(nodo_borrar->clave);
  free(nodo_borrar);
  hash->tabla_hash[posicion] = (nodo_hash_t*)NODO_VACIO;
  hash->cant_ocupadas--;
  return VALIDO;
 }

void* hash_obtener(hash_t* hash, const char* clave){
  if(!hash || !hash->tabla_hash)
    return NULL;
  size_t posicion = funcion_hash(clave, hash->capacidad_tabla);
  size_t posicion_final = hash->capacidad_tabla-1;
  while(hash->tabla_hash[posicion]){
    if(hash->tabla_hash[posicion] == NODO_VACIO){
      if(posicion == posicion_final){
        posicion = 0;
      } else {
        posicion++;
      }
    } else if(hash->tabla_hash[posicion] && hash->tabla_hash[posicion] != NODO_VACIO){
      if(strcmp(hash->tabla_hash[posicion]->clave, clave) == 0){
        return hash->tabla_hash[posicion]->valor;
      } else {
        if(posicion == (hash->capacidad_tabla-1)){
          posicion = 0;
        } else {
          posicion++;
        } 
      } 
    }
  }
  return NULL;
}

size_t hash_cantidad(hash_t* hash){
  if(!hash)
    return 0;
  printf("%zu", hash->cant_ocupadas);
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
  if(!hash)
    return;
  for(size_t i = 0; i < hash->capacidad_tabla; i++){
    if(hash->tabla_hash[i] && hash->tabla_hash[i] != NODO_VACIO){
      if(hash->destructor){
        hash->destructor(hash->tabla_hash[i]->valor);
      }
      free(hash->tabla_hash[i]->clave);
      free(hash->tabla_hash[i]);
    }
  }
  free(hash->tabla_hash);
  free(hash);
}

size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
  size_t contador = 0;
  if(!hash)
    return contador;

  size_t i = 0;
  bool seguir = true;
  while(i < hash->capacidad_tabla && seguir){
    if(hash->tabla_hash[i] && hash->tabla_hash[i] != NODO_VACIO){
      seguir = !funcion(hash, hash->tabla_hash[i]->clave, aux);
      contador++;
    }
    i++;
  }
  return contador;
}

