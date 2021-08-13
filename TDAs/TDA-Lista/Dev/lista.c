#include "lista.h"
#include <stdlib.h>

#define VALIDO 0
#define ERROR -1
#define INICIO_LISTA 0

/*
* Pre:
* Post: retorna un puntero con memoria reservado a un nodo_t
*/
nodo_t* nodo_crear(){
  nodo_t* nodo = calloc(1, sizeof(nodo_t));
  if(!nodo)
    return NULL;
  return nodo;
}

/*
* Pre:
* Post: Le asigna a un nodo el elemento que va a contener.
*/
nodo_t* nodo_set_elemento(nodo_t* nodo, void* elemento){
  if(!nodo)
    return NULL;
  nodo->elemento = elemento;
  nodo->siguiente = NULL;
  return nodo;
}

/*
* Pre:
* Post: Libera la memoria de todos los nodos de la lista.
*/
void nodo_destruir(nodo_t* nodo){
  if(!nodo)
    return;
  nodo_t* nodo_proximo = nodo->siguiente;
  free(nodo);
  nodo_destruir(nodo_proximo);
}

/*
* Pre:
* Post: Inicializa una Lista sin nodos agregados.
*/
lista_t* inicializar_lista_creada(lista_t* lista){
  lista->cantidad = 0;
  lista->nodo_fin = NULL;
  lista->nodo_inicio = NULL;
  return lista;
}

lista_t* lista_crear(){
  lista_t* lista_creada = calloc(1,sizeof(lista_t));
  if (!lista_creada)
      return NULL;
  lista_creada = inicializar_lista_creada(lista_creada);
  return lista_creada;
}

int lista_insertar(lista_t* lista, void* elemento){
  if(!lista)
    return ERROR;
  nodo_t* nodo_aux = nodo_crear();
  if(!nodo_aux)
    return ERROR;
  nodo_aux = nodo_set_elemento(nodo_aux, elemento);
  if(lista_vacia(lista)){
    lista->nodo_fin = nodo_aux;
    lista->nodo_inicio = nodo_aux;
  } else {
    lista->nodo_fin->siguiente = nodo_aux;
    lista->nodo_fin = nodo_aux;
  }
  lista->cantidad++;
  return VALIDO;
}

/*
* Pre: nodo_previo y nodo_proximo ya vienen verificados de distinto de nulos.
* Post: inserta un nodo a la posicion indicada de la lista y retorna PUDO_INSERTAR
*/
int nodo_insertar_en_posicion(nodo_t** nodo_previo, nodo_t* nodo_proximo, size_t posicion){
  if(posicion == 0){
    nodo_t* nodo_aux = *nodo_previo;
    *nodo_previo = nodo_proximo;
    (*nodo_previo)->siguiente = nodo_aux;
    return ERROR;
  }
  return nodo_insertar_en_posicion(&(*nodo_previo)->siguiente, nodo_proximo, (posicion-1));
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
  if(!lista)
    return ERROR;

  if(lista_vacia(lista) || posicion >= lista_elementos(lista)){
    lista_insertar(lista, elemento);
  } else {
    nodo_t* nodo = nodo_crear();
    if(!nodo)
      return ERROR;
    nodo = nodo_set_elemento(nodo, elemento);
    nodo_insertar_en_posicion(&lista->nodo_inicio, nodo, posicion);
    lista->cantidad++;
  }
  return VALIDO;
}

nodo_t* nodo_borrar(nodo_t* nodo, size_t cantidad_nodos){
  if(cantidad_nodos == 1){
    free(nodo->siguiente);
    nodo->siguiente = NULL;
    return nodo;
  } 
  return nodo_borrar(nodo->siguiente, (cantidad_nodos - 1)); 
}

int lista_borrar(lista_t* lista){
  if(lista_vacia(lista) || !lista){
    return ERROR;
  }
  if(lista->cantidad == 1){
    free(lista->nodo_inicio);
    lista->nodo_inicio = NULL;
    lista->nodo_fin = NULL;
  } else {
    nodo_t* nodo_aux = nodo_borrar(lista->nodo_inicio, (lista->cantidad - 1));
    if(!nodo_aux)
      return ERROR;
    lista->nodo_fin = nodo_aux;
  }
  lista->cantidad--;
  return VALIDO;
}

/*
* Pre: nodo_previo y nodo_proximo ya vienen verificados de distinto de nulos.
* Post: borra un nodo en la posicion indicada de la lista y retorna PUDO_BORRAR.
*/
int nodo_borrar_en_posicion(nodo_t** nodo_previo, nodo_t* nodo_proximo, size_t posicion){
  if(posicion == 1){
    (*nodo_previo)->siguiente = nodo_proximo->siguiente;
    free(nodo_proximo);
    return ERROR;
  }
  return nodo_borrar_en_posicion(&(*nodo_previo)->siguiente, nodo_proximo->siguiente, (posicion-1));
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
  if(lista_vacia(lista) || !lista)
    return ERROR;

  if(posicion >= (lista_elementos(lista) - 1)){
    return lista_borrar(lista);
  } else if(posicion == 0){
    nodo_t* nodo_aux = lista->nodo_inicio->siguiente;
    free(lista->nodo_inicio);
    lista->nodo_inicio = nodo_aux;
    lista->cantidad--;
  } else {
    nodo_borrar_en_posicion(&lista->nodo_inicio, lista->nodo_inicio->siguiente, posicion);
    lista->cantidad--;
  }
  return VALIDO;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
  if(lista_vacia(lista) || posicion >= lista_elementos(lista))
    return NULL;
  nodo_t* nodo = lista->nodo_inicio;
  for(int i = 0; i < posicion; i++)
    nodo = nodo->siguiente;
  return nodo->elemento;
}

void* lista_ultimo(lista_t* lista){
  if(lista_vacia(lista) || !lista)
    return NULL;
  return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t* lista){
  return (!lista || (lista->cantidad == 0));
}

size_t lista_elementos(lista_t* lista){
  if(!lista)
    return 0;
  return lista->cantidad;
}

int lista_apilar(lista_t* lista, void* elemento){
  return lista_insertar(lista, elemento);
}

int lista_desapilar(lista_t* lista){
  return lista_borrar(lista);
}

void* lista_tope(lista_t* lista){
  return lista_ultimo(lista);
}

int lista_encolar(lista_t* lista, void* elemento){
  return lista_insertar(lista, elemento);
}

int lista_desencolar(lista_t* lista){
  return lista_borrar_de_posicion(lista, INICIO_LISTA);
}

void* lista_primero(lista_t* lista){
  if(lista_vacia(lista) || !lista)
    return NULL;
  return lista->nodo_inicio->elemento;
}

void lista_destruir(lista_t* lista){
  if(!lista_vacia(lista) || !lista)
    nodo_destruir(lista->nodo_inicio);
  free(lista);
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
  if(!lista)
    return NULL;
  lista_iterador_t* iterador_nuevo = calloc(1, sizeof(lista_iterador_t));
  if(!iterador_nuevo)
    return NULL;

  iterador_nuevo->lista = lista;
  iterador_nuevo->corriente = lista->nodo_inicio;
  return iterador_nuevo;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
    return iterador && iterador->corriente;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){
  if(!lista_iterador_tiene_siguiente(iterador))
    return false;

  iterador->corriente = iterador->corriente->siguiente;
  return lista_iterador_tiene_siguiente(iterador);
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
  if(!iterador || !iterador->corriente)
    return NULL;

  return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador){
  if(iterador)
    free(iterador);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
  size_t cantidad = 0;
  if(!lista)
    return cantidad;

  if(!lista_vacia(lista) && funcion){
    nodo_t* nodo = lista->nodo_inicio;
    while(nodo && funcion(nodo->elemento, contexto)){
      nodo = nodo->siguiente;
      cantidad++;
    }
  }
  return cantidad;
}
