#include "agenda.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

char* duplicar_string(const char* texto){
    char* duplicado = malloc(strlen(texto)+1);
    if(!duplicado)
        return NULL;

    strcpy(duplicado, texto);

    return duplicado;
}

agenda_t* agenda_crear(const char* nombre){
    agenda_t* agenda;
    agenda = calloc(1, sizeof(agenda_t));

    if(agenda==NULL)
        return NULL;

    agenda->nombre = duplicar_string(nombre);

    if(agenda->nombre == NULL){
        free(agenda);
        return NULL;
    }

    return agenda;
}

agenda_t* agenda_agregar_contacto(agenda_t* agenda, const char* nombre, int telefono){
    if(!agenda || !nombre || !*nombre || !telefono)
        return NULL;

    char* nombre_duplicado = duplicar_string(nombre);
    if(!nombre_duplicado)
        return NULL;

    void* aux = realloc(agenda->entradas, sizeof(item_agenda_t)*(size_t)(agenda->cantidad_entradas+1));
    if(!aux){
        free(nombre_duplicado);
        return NULL;
    }

    agenda->entradas = aux;

    agenda->cantidad_entradas += 1;

    item_agenda_t* item = agenda->entradas+(agenda->cantidad_entradas-1);

    item->nombre = nombre_duplicado;
    item->numero = telefono;

    return agenda;
}

void agenda_mostrar_si(agenda_t* agenda, bool (*criterio)(item_agenda_t*)){
 if(!agenda)
        return;

    for(int i = 0 ; i<agenda->cantidad_entradas;i++){

        if(criterio(agenda->entradas+i))
            printf("Nombre: %s, Numero: %i\n", agenda->entradas[i].nombre, agenda->entradas[i].numero);
    }
}

void agenda_destruir(agenda_t* agenda){
    if(!agenda)
        return ;

    free(agenda->nombre);

    for(int i = 0 ; i<agenda->cantidad_entradas;i++)
        free(agenda->entradas[i].nombre);

    free(agenda->entradas);
    free(agenda);
}
