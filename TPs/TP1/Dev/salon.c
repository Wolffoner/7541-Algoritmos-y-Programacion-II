#include "salon.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#define SEPARADOR ';'
#define VACIO ""

//COLORS
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
 
 /*
 * Pre:
 * Post: Retorna un entrenador_t* con sus respectivos datos o retorna NULL si str_div es NULL
 */
entrenador_t* set_entrenador(char** str_div){
    int i = 0;
    entrenador_t* entrenador_aux;
    entrenador_aux = calloc(1, sizeof(entrenador_t));
    if(!entrenador_aux){
        free(entrenador_aux);
        return NULL;
    }
    if(str_div == NULL){
        return NULL;
    }
    strcpy(entrenador_aux->nombre, str_div[i]);
    i++;
    entrenador_aux->victorias = atoi(str_div[i]);

    return entrenador_aux;
}
 
 /*
 * Pre:
 * Post: Retorna un pokemon_t* con sus respectivos datos o Retorna NULL si str_div es NULL.
 */
pokemon_t* set_pokemon(char** str_div){
    int i = 0;
    pokemon_t* pokemon_aux;
    pokemon_aux = calloc(1, sizeof(entrenador_t));
    if(!pokemon_aux){
        free(pokemon_aux);
        return NULL;
    }
    if(str_div == NULL){
        return NULL;
    }
    strcpy(pokemon_aux->nombre, str_div[i]);
    i++;
    pokemon_aux->nivel = atoi(str_div[i]);
    i++;
    pokemon_aux->defensa = atoi(str_div[i]);
    i++;
    pokemon_aux->fuerza = atoi(str_div[i]);
    i++;
    pokemon_aux->inteligencia = atoi(str_div[i]);
    i++;
    pokemon_aux->velocidad = atoi(str_div[i]);
    return pokemon_aux;
}

salon_t* salon_leer_archivo(const char* nombre_archivo){
    FILE *file;
    char* str = NULL;
    char** str_div = NULL;
    int cantidad_entrenadores = 0;
    int posicion_actual = 0;
    file = fopen(nombre_archivo, "r");
    if(!file){
        return NULL;
    }
    salon_t* salon;
    salon = (salon_t*)calloc(1, sizeof(salon_t));
    if(!salon){
        free(salon);
        return NULL;
    }
    entrenador_t* entrenador = NULL;
    pokemon_t* pokemon = NULL;

    str = fgets_alloc(file);
    while( str != NULL){
        str_div = split(str, SEPARADOR);
        if(vtrlen(str_div) == 2){
            entrenador = set_entrenador(str_div);
            salon->entrenadores = vtradd(salon->entrenadores, entrenador);
            posicion_actual = cantidad_entrenadores;
            cantidad_entrenadores++;
        } else {
            pokemon = set_pokemon(str_div);
            salon->entrenadores[posicion_actual]->equipo = vtradd(salon->entrenadores[posicion_actual]->equipo, pokemon);
        }
        free(str);
        vtrfree(str_div);
        str = fgets_alloc(file);
    }
    fclosen(file);
    return salon; 
}

int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo){
    FILE* file;
    int i = 0;
    int j = 0;
    file = fopen(nombre_archivo, "w");
    if(!file){
        return -1;
    }
    if(!salon){
        return -1;
    }

    while(salon->entrenadores[i] != NULL){
        fprintf(file, "%s;%i\n", salon->entrenadores[i]->nombre, salon->entrenadores[i]->victorias);
        if(salon->entrenadores[i]->equipo != NULL){
            while(salon->entrenadores[i]->equipo[j] != NULL){
                fprintf(file, "%s;%i;%i;%i;%i;%i\n", 
                    salon->entrenadores[i]->equipo[j]->nombre, 
                    salon->entrenadores[i]->equipo[j]->nivel,
                    salon->entrenadores[i]->equipo[j]->defensa,
                    salon->entrenadores[i]->equipo[j]->fuerza,
                    salon->entrenadores[i]->equipo[j]->inteligencia,
                    salon->entrenadores[i]->equipo[j]->velocidad
                );
                j++;
            }
        j = 0;
        }
    i++;
    }
    fclosen(file);
    return i;
}

/*
*   Pre:
*   Post: ordena el salon->entrenadores de menor a mayor.
*/
void ordena_salon(salon_t* salon ){
    entrenador_t* aux;
    for(int i = 0; i < vtrlen(salon->entrenadores); i++){
        for(int j = 0; j < vtrlen(salon->entrenadores)-1; j++){
            if(salon->entrenadores[j]->victorias > salon->entrenadores[j+1]->victorias){
                aux = salon->entrenadores[j];
                salon->entrenadores[j] = salon->entrenadores[j+1];
                salon->entrenadores[j+1] = aux;
            }
        }
    }
}

salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador){
    if(!salon){
        return NULL;
    }
    if(!entrenador){
        return NULL;
    } 
    salon->entrenadores = vtradd(salon->entrenadores, entrenador);
    ordena_salon(salon);
    return salon;
}

entrenador_t** salon_obtener_entrenadores_mas_ganadores(salon_t* salon, int cantidad_minima_victorias){
    entrenador_t** podio_entrenadores = NULL;
    int i = 0;
    while (salon->entrenadores[i] != NULL){
        if(salon->entrenadores[i]->victorias >= cantidad_minima_victorias){
            podio_entrenadores = vtradd(podio_entrenadores, salon->entrenadores[i]);
        }
        i++;
    }
    return podio_entrenadores;
}

void salon_mostrar_entrenador(entrenador_t* entrenador){
    printf(YEL"Entrenador: " RESET RED "%s" RESET YEL" - Victorias:" RESET RED" %i\n" RESET, entrenador->nombre, entrenador->victorias);
    int i = 0;
    if(entrenador->equipo != NULL){
        while(entrenador->equipo[i] != NULL ){
            printf(YEL " Pokemon: " RESET GRN "%s\n" RESET, entrenador->equipo[i]->nombre);
            printf("  - Nivel: " CYN "%i\n" RESET, entrenador->equipo[i]->nivel);
            printf("  - Fuerza: " CYN "%i\n" RESET, entrenador->equipo[i]->fuerza);
            printf("  - Defensa: " CYN "%i\n" RESET, entrenador->equipo[i]->defensa);
            printf("  - Inteligencia: " CYN "%i\n" RESET, entrenador->equipo[i]->inteligencia);
            printf("  - Velocidad: " CYN "%i\n" RESET, entrenador->equipo[i]->velocidad);
            i++;
        }
    }
}

void salon_destruir(salon_t* salon){
    int i = 0;
    while(salon->entrenadores[i] != NULL){
        vtrfree(salon->entrenadores[i]->equipo);
        free(salon->entrenadores[i]);
        i++;
    }
    free(salon->entrenadores);
    free(salon);
}
