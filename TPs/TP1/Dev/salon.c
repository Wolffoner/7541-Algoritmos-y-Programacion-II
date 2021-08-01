#include "salon.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#define SEPARADOR ';'

salon_t* salon_leer_archivo(const char* nombre_archivo){
    FILE* file;
    char* str = NULL;
    char** str_div = NULL;
    int cant_entrenadores = 0;
    int cant_pokemones = 0;
    int j = 0;
    int k = 0;
    file = fopen(nombre_archivo, "r");
    if(!file){
        return NULL;
    }
    salon_t* salon;
    salon = calloc(1,sizeof(salon_t));
    if(!salon){
        return NULL;
    }
    entrenador_t* entrenador;
    entrenador = calloc(1,sizeof(entrenador_t));
    if (!entrenador){
        return NULL;
    }
    pokemon_t* pokemon;
    pokemon = calloc(1, sizeof(pokemon_t));
    if(!pokemon){
        return NULL;
    }
    while(feof(file)){
        str = fgets_alloc(file);
        str_div = split(str, SEPARADOR);
        if(vtrlen(str_div) == 2){
            strcpy(entrenador->nombre, str_div[j]);
            j++;
            entrenador->victorias = (int)*str_div[j];
            salon->entrenadores[cant_entrenadores] = entrenador;
            cant_entrenadores++;
            j = 0;
        } else {
            strcpy(pokemon->nombre, str_div[k]);
            k++;
            pokemon->nivel = (int)*str_div[k];
            k++;
            pokemon->fuerza = (int)*str_div[k];
            k++;
            pokemon->inteligencia = (int)*str_div[k];
            k++;
            pokemon->velocidad = (int)*str_div[k];
            k++;
            pokemon->defensa = (int)*str_div[k];
            entrenador->equipo[cant_pokemones] = pokemon;
            cant_pokemones++;
            k = 0;
        }
    }
    return salon;
}

int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo){
    return -1;
}

salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador){
    return NULL;
}

entrenador_t** salon_obtener_entrenadores_mas_ganadores(salon_t* salon, int cantidad_minima_victorias){
    return NULL;
}

void salon_mostrar_entrenador(entrenador_t* entrenador){

}

void salon_destruir(salon_t* salon){

}
