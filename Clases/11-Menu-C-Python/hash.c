#include "hash.h"


hash_t* hash_crear(size_t capacidad_inicial){
    hash_t* hash = calloc(1, sizeof(hash_t));

    if(!hash)
        return NULL;

    hash->tamanio_tabla = capacidad_inicial;
    hash->tabla = calloc(capacidad_inicial, sizeof(par_t*));

    if(!hash->tabla){
        free(hash);
        return NULL;
    }

    return hash;
}

void hash_destruir(hash_t* h){}

size_t magia(const char* k){
    size_t valor = 0;

    while(*k){
        valor += *k;
        k++;
    }

    return valor;
}

size_t funcion_hash(const char* k){
    return magia(k);
}

#include <string.h>

par_t* par_crear(const char* k, void* v){
    par_t* par = malloc(sizeof(par_t));
    if(!par)
        return NULL;

    par->clave = strdup(k);
    par->valor = v;

    if(!par->clave){
        free(par);
        return NULL;
    }

    return par;
}

#include <stdio.h>


bool rehashear(hash_t* h){
    hash_t hash_aux = *h;

    h->tabla = calloc(h->tamanio_tabla*2, sizeof(par_t*));
    h->tamanio_tabla *= 2;
    h->cantidad = 0;

    //itero hash_aux e inserto en h
    //itero hash_aux y traspaso los pares

}

bool hash_insertar(hash_t* h, const char* k, void* v){
    size_t hash = funcion_hash(k);
    size_t posicion = hash % h->tamanio_tabla;

    //rehashear en algun momento

    if(!h->tabla[posicion]){
        par_t* par = par_crear(k, v);
        if(!par)
            return false;
        h->tabla[posicion] = par;
        return true;
    }

    par_t* actual = h->tabla[posicion];
    while(actual && strcmp(actual->clave, k) != 0)
        actual = actual->siguiente;

    if(actual){

        actual->valor = v;
        return true;
    }

    par_t* par = par_crear(k, v);
    if(!par)
        return false;

    par->siguiente = h->tabla[posicion];
    h->tabla[posicion] = par;
    return true;
}

void* hash_buscar(hash_t* h, const char* k){
    size_t hash = funcion_hash(k);
    size_t posicion = hash % h->tamanio_tabla;

    par_t* actual = h->tabla[posicion];
    while(actual && strcmp(actual->clave, k) != 0)
        actual = actual->siguiente;

    if(!actual)
        return NULL;

    return actual->valor;
}

bool hash_eliminar(hash_t* h, const char* k){
    size_t hash = funcion_hash(k);
    size_t posicion = hash % h->tamanio_tabla;

    par_t* anterior = NULL;
    par_t* actual = h->tabla[posicion];

    while(actual && strcmp(actual->clave, k) != 0){
        anterior = actual;
        actual = actual->siguiente;
    }

    if(!actual)
        return false;

    if(anterior){
        anterior->siguiente = actual->siguiente;
        free((char*)actual->clave);
        free(actual);
        return true;
    }

    par_t* primero = h->tabla[posicion];
    h->tabla[posicion] = primero->siguiente;

    free((char*)primero->clave);
    free(primero);
    return true;
}


int hash_con_cada_elemento(hash_t* h, bool (*f)(const char*,void*,void*), void* aux){
    for(size_t i=0;i<h->tamanio_tabla;i++){
        if(h->tabla[i]){
            f(h->tabla[i]->clave, h->tabla[i]->valor, aux);
        }

    }
}
