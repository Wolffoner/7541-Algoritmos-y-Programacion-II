#ifndef HASH_H_
#define HASH_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct par{
    const char* clave;
    void* valor;
    struct par *siguiente;
}par_t;

typedef struct {
    size_t cantidad;

    //vector de algo
    size_t tamanio_tabla;
    par_t** tabla;
}hash_t;


hash_t* hash_crear(size_t capacidad_inicial);

void hash_destruir(hash_t*);

bool hash_insertar(hash_t* , const char*, void*);

void* hash_buscar(hash_t*, const char*);

bool hash_eliminar(hash_t*, const char* );

int hash_con_cada_elemento(hash_t*, bool (*)(const char*,void*,void*), void*);

#endif // HASH_H_
