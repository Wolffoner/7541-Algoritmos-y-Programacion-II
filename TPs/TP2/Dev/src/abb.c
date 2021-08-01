#include "abb.h"
#include <stdio.h>

#define ERROR -1
#define VALIDO 0
#define COMPARADOR_BUSCADO 0 

/*
 * Pre: 
 * Post: Crea un nodo con sus hijos nulos.
 */
nodo_abb_t* nodo_abb_crear(){
    nodo_abb_t* nodo_nuevo = calloc(1, sizeof(nodo_abb_t));
    if(!nodo_nuevo)
        return NULL;
    nodo_nuevo->izquierda = NULL;
    nodo_nuevo->derecha = NULL;
    return nodo_nuevo;
}

/*
 * Pre: 
 * Post: se le asigna al nodo el valor del elemento.
 */
void nodo_abb_set_elemento(nodo_abb_t** nodo, void* elemento){
    if(!nodo)
        return;
    (*nodo)->elemento = elemento;
}

/*
 * Pre:
 * Post: destruye los nodos, sus hijos y libera la memoria.
 */
void nodo_abb_destruir(abb_liberar_elemento destructor, nodo_abb_t* nodo_actual ){
    if(!nodo_actual) 
        return;
    nodo_abb_destruir(destructor, nodo_actual->izquierda);
    nodo_abb_destruir(destructor, nodo_actual->derecha);
    if(destructor)
        destructor(nodo_actual->elemento);
    free(nodo_actual);
}
/*
 * Pre: 
 * Post: Retorna true si no tiene hijo izquierdo el nodo, si tiene hijo retorna false.
 */
bool nodo_sin_hijo_izquierdo(nodo_abb_t* nodo){
  if(!nodo)
    return false;
  return !nodo->izquierda;
}

/*
 * Pre: 
 * Post: Retorna true si no tiene hijo derecho el nodo, si tiene hijo derecho retorna false.
 */
bool nodo_sin_hijo_derecho(nodo_abb_t* nodo){
  if(!nodo)
    return false;
  return !nodo->derecha;
}

/*
 * Pre: 
 * Post: Retorna true si no tiene ni hijo derecho ni izquierdo, si tiene alguno o ambos retorna false.
 */
bool nodo_sin_hijos(nodo_abb_t* nodo){
  if(!nodo)
    return false;
  return nodo->izquierda == NULL && nodo->derecha == NULL;
}

/*
 * Pre: 
 * Post: Inserta el nodo en el arbol en el lugar indicado dependiendo del comparador escogido.
 */
int nodo_insertar_recursivamente(nodo_abb_t** nodo_raiz, nodo_abb_t* nodo, abb_comparador comparador){
    if(comparador(nodo->elemento, (*nodo_raiz)->elemento) <= COMPARADOR_BUSCADO){
        if((*nodo_raiz)->izquierda == NULL){
            (*nodo_raiz)->izquierda = nodo;
            return VALIDO;
        } else {
            return nodo_insertar_recursivamente(&(*nodo_raiz)->izquierda, nodo, comparador);
        }
    } else {
        if((*nodo_raiz)->derecha == NULL){
            (*nodo_raiz)->derecha = nodo;
            return VALIDO;
        } else {
            return nodo_insertar_recursivamente(&(*nodo_raiz)->derecha, nodo, comparador);
        }
    }
    return ERROR;
}

/*
 * Pre: 
 * Post: Retorna el predecesor inorden al nodo pasado por parametro.
 */
nodo_abb_t* nodo_predecesor_inorder(nodo_abb_t* nodo){
    if(!nodo || !nodo->izquierda)
        return NULL;
    nodo_abb_t* nodo_predecesor = nodo->izquierda;
    if(nodo_predecesor->derecha != NULL){
        nodo_abb_t* nodo_previo = NULL;
        while(nodo_predecesor->derecha != NULL){
           nodo_previo = nodo_predecesor;
           nodo_predecesor = nodo_predecesor->derecha;
        }
        nodo_previo->derecha = nodo_predecesor->izquierda;
        nodo_predecesor->izquierda = nodo->izquierda;
        nodo_predecesor->derecha = nodo->derecha;
    } else {
        nodo_predecesor->derecha = nodo->derecha;
    }
    return nodo_predecesor;
}

/*
 * Pre: 
 * Post: Reemplaza un nodo con otro dependiendo si no tiene ambos hijos, si no tiene el hijo derecho, o si no tiene el hijo izquierdo, en caso de tener ambos busca el predecesor inorden
 */
void nodo_reemplazar(nodo_abb_t** nodo){
    if(nodo_sin_hijos(*nodo)){
        *nodo = NULL;
    } else if(nodo_sin_hijo_derecho(*nodo)){
        *nodo = (*nodo)->izquierda;
    } else if(nodo_sin_hijo_izquierdo(*nodo)){
        *nodo = (*nodo)->derecha;
    } else {
        *nodo = nodo_predecesor_inorder(*nodo);
    }
}

/*
 * Pre:
 * Post: Verifica si  2 nodos son iguales.
 */
bool nodos_iguales(nodo_abb_t* nodo, nodo_abb_t* otro_nodo){
    return nodo == otro_nodo;
}

/*
 * Pre:
 * Post: acomoda los punteros para que queden apuntando correctamente.
 */
void acomoda_punteros_padres(abb_t* arbol, nodo_abb_t* nodo_encontrado, nodo_abb_t** nodo_previo, nodo_abb_t* nodo){
    if(nodos_iguales(arbol->nodo_raiz, nodo_encontrado)){
        arbol->nodo_raiz = nodo;
    } else if(nodos_iguales((*nodo_previo)->derecha, nodo_encontrado)){
        (*nodo_previo)->derecha = nodo;
    } else if(nodos_iguales((*nodo_previo)->izquierda, nodo_encontrado)){
        (*nodo_previo)->izquierda = nodo;
    }
}
/*
 * Pre:
 * Post: Borra un elemento del arbol retorna VALIDO si pudo hacer el borrado y ERROR en caso contrario.
 */
int nodo_abb_borrar(abb_t* arbol, nodo_abb_t* nodo, nodo_abb_t** nodo_previo, void* elemento){
    if(!nodo || arbol_vacio(arbol))
        return ERROR;
    if(arbol->comparador(elemento, nodo->elemento) == COMPARADOR_BUSCADO){
        nodo_abb_t* nodo_encontrado = nodo;
        nodo_reemplazar(&nodo);
        acomoda_punteros_padres(arbol, nodo_encontrado, nodo_previo, nodo);
        nodo_encontrado->derecha = NULL;
        nodo_encontrado->izquierda = NULL;
        nodo_abb_destruir(arbol->destructor, nodo_encontrado);
        return VALIDO;
    } else if(arbol->comparador(elemento, nodo->elemento) < COMPARADOR_BUSCADO){
        *nodo_previo = nodo;
        return nodo_abb_borrar(arbol, nodo->izquierda, nodo_previo, elemento);
    } else if(arbol->comparador(elemento, nodo->elemento) > COMPARADOR_BUSCADO){
        *nodo_previo = nodo;
        return nodo_abb_borrar(arbol, nodo->derecha, nodo_previo, elemento);
    }
    return ERROR;
}

/*
 * Pre:
 * Post: Busca un elemento si lo encuentra devuelve el elemento, si no devuelve Nulo.
 */
nodo_abb_t* nodo_buscar(nodo_abb_t* nodo, abb_comparador comparador, void* elemento){
    if(!nodo)
        return NULL;
    if(comparador(elemento, nodo->elemento) == COMPARADOR_BUSCADO){
        return nodo->elemento;
    } else if(comparador(elemento, nodo->elemento) < COMPARADOR_BUSCADO){
        return nodo_buscar(nodo->izquierda, comparador, elemento);
    } else if (comparador(elemento, nodo->elemento) > COMPARADOR_BUSCADO){
        return nodo_buscar(nodo->derecha, comparador, elemento);
    }
    return NULL;
}

/*
 * Pre:
 * Post: agrega un elemento al vector.
 */
void agregar_elem_vector(void** array, void* elemento, size_t* posicion){
    *(&array[*posicion]) = elemento;
    (*posicion)++;
}

/*
 * Pre:
 * Post: Recorre los nodos en orden.
 */
void nodo_recorrer_inorden(nodo_abb_t* nodo, void** array, size_t tamanio, size_t* posicion){
    if(!nodo || !array || *posicion >= tamanio){
        return;
    }
    nodo_recorrer_inorden(nodo->izquierda, array, tamanio, posicion);
    if(*posicion < tamanio){
        agregar_elem_vector(array, nodo->elemento, posicion);
    }
    nodo_recorrer_inorden(nodo->derecha, array, tamanio, posicion);
}

/*
 * Pre:
 * Post: Recorre los nodos en preorden.
 */
void nodo_recorrer_preorden(nodo_abb_t* nodo, void** array, size_t tamanio, size_t* posicion){
    if(!nodo || !array || *posicion >= tamanio){
        return;
    }
    if(*posicion < tamanio){
        agregar_elem_vector(array, nodo->elemento, posicion);
    }
    nodo_recorrer_preorden(nodo->izquierda, array, tamanio, posicion);
    nodo_recorrer_preorden(nodo->derecha, array, tamanio, posicion);
}

/*
 * Pre:
 * Post: Recorre los nodos en postorden.
 */
void nodo_recorrer_postorden(nodo_abb_t* nodo, void** array, size_t tamanio, size_t* posicion){
    if(!nodo || !array || *posicion >= tamanio){
        return;
    }
    nodo_recorrer_postorden(nodo->izquierda, array, tamanio, posicion);
    nodo_recorrer_postorden(nodo->derecha, array, tamanio, posicion);
    if(*posicion < tamanio){
        agregar_elem_vector(array, nodo->elemento, posicion);
    }
}

/*
 * Pre:
 * Post: nodo debe seguir iterando si funcion es false, si no, no sigue iterando.
 */
bool nodo_sigue_iterando(void* elemento, bool (*funcion)(void*,void*), void* extra, size_t* cant_iterados){
    (*cant_iterados)++;
    return !funcion(elemento, extra);
}


/*
 * Pre:
 * Post: nodo itera elementos segun si su recorrido ABB_RECORRER_PREORDEN, ABB_RECORRER_INORDEN o ABB_RECORRER_POSTORDEN.
 */
size_t nodo_iterar_elementos(bool* seguir_iterando, size_t* cant_iterados, nodo_abb_t* nodo, int recorrido, bool (*funcion)(void*, void*), void* extra){
    if(!nodo && !(*seguir_iterando))
      return *cant_iterados;

    if(nodo && *seguir_iterando) {
      if (recorrido == ABB_RECORRER_PREORDEN && *seguir_iterando)
        *seguir_iterando = nodo_sigue_iterando(nodo->elemento, funcion, extra, cant_iterados);

      nodo_iterar_elementos(seguir_iterando, cant_iterados, nodo->izquierda, recorrido, funcion, extra);
      if (recorrido == ABB_RECORRER_INORDEN && *seguir_iterando)
        *seguir_iterando = nodo_sigue_iterando(nodo->elemento, funcion, extra, cant_iterados);

      nodo_iterar_elementos(seguir_iterando, cant_iterados, nodo->derecha, recorrido, funcion, extra);
      if (recorrido == ABB_RECORRER_POSTORDEN && *seguir_iterando)
        *seguir_iterando = nodo_sigue_iterando(nodo->elemento, funcion, extra, cant_iterados);
    }
    return *cant_iterados;
}

/* abb.h */

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
    if(!comparador)
        return NULL;
    abb_t* arbol = calloc(1, sizeof(abb_t));
    if(!arbol)
        return NULL;
    arbol->comparador = comparador;
    arbol->destructor = destructor;
    return arbol;
}

int arbol_insertar(abb_t* arbol, void* elemento){
    if(!arbol)
        return ERROR;
    nodo_abb_t* nodo = nodo_abb_crear();
    if(!nodo)
        return ERROR;
    nodo_abb_set_elemento(&nodo, elemento);
    if(arbol_vacio(arbol)){
        arbol->nodo_raiz = nodo;
    } else {
        return nodo_insertar_recursivamente(&arbol->nodo_raiz, nodo, arbol->comparador);
    }
    return VALIDO;
}

int arbol_borrar(abb_t* arbol, void* elemento){
    if(arbol_vacio(arbol)){
        return ERROR;
    }
    nodo_abb_t* nodo_previo = NULL;
    nodo_abb_borrar(arbol, arbol->nodo_raiz, &nodo_previo, elemento);
    return VALIDO;
} 

void* arbol_buscar(abb_t* arbol, void* elemento){
    if(arbol_vacio(arbol)){
        return NULL;
    }
    nodo_abb_t* nodo_buscado = nodo_buscar(arbol->nodo_raiz, arbol->comparador, elemento);
    return nodo_buscado;
}

void* arbol_raiz(abb_t* arbol){
    if(arbol_vacio(arbol))
        return NULL;
    return arbol->nodo_raiz->elemento;
}

bool arbol_vacio(abb_t* arbol){
    return !arbol || !arbol->nodo_raiz;
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
    size_t cant_elementos = 0;
    if(arbol_vacio(arbol))
        return cant_elementos;
    nodo_recorrer_inorden(arbol->nodo_raiz, array, tamanio_array, &cant_elementos);
    return cant_elementos;
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
    size_t cant_elementos = 0;
    if(arbol_vacio(arbol))
         return cant_elementos;
    nodo_recorrer_preorden(arbol->nodo_raiz, array, tamanio_array, &cant_elementos);
    return cant_elementos;
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
    size_t cant_elementos = 0;
    if(arbol_vacio(arbol))
         return cant_elementos;
    nodo_recorrer_postorden(arbol->nodo_raiz, array, tamanio_array, &cant_elementos);
    return cant_elementos;
}

void arbol_destruir(abb_t* arbol){
    if(arbol){
        nodo_abb_destruir(arbol->destructor, arbol->nodo_raiz);
        free(arbol);
    }
}

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
  if(arbol_vacio(arbol) || !funcion)
      return 0;
  bool seguir_iterando = true;
  size_t cant_iterados = 0;
  return nodo_iterar_elementos(&seguir_iterando, &cant_iterados, arbol->nodo_raiz, recorrido, funcion, extra);
}
