#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "salon.h"
#include "util.h"

#define PATH_ORIGINAL "salon_original.sal"
#define PATH_MODIFICADO "salon_modificado.sal"

#define ASCII_INTRO "intro.txt"

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
*   Pre: 
*   Post: Retorna un entrenador_t* con sus datos inicializados.
*/
entrenador_t* inicializa_entrenador(entrenador_t* entrenador, char* nombre, int victorias){
    entrenador_t* entrenador_aux;
    entrenador_aux = calloc(1, sizeof(entrenador_t));
    if(!entrenador_aux){
        free(entrenador_aux);
        return NULL;
    }
    entrenador = entrenador_aux;
    strcpy(entrenador->nombre, nombre);
    entrenador->victorias = victorias;
    entrenador->equipo = NULL;
    return entrenador;
}

/*
*   Pre: 
*   Post: Imprime en consola todos los entrenadores que esten dentro del vector entrenadores_ganadores.
*/
void imprimir_entrenadores_ganadores(entrenador_t** entrenadores_ganadores){
    for(int i = 0; i < (int)vtrlen(entrenadores_ganadores); i++){
        salon_mostrar_entrenador(entrenadores_ganadores[i]);
    }
}

/*
*   Pre: 
*   Post: Imprime en consola lo que esta dentro del archvio ASCII_INTRO
*/
void imprimir_intro(){
    FILE* file;
    char* str;
    file = fopen(ASCII_INTRO, "r");
    if(!file){
        return;
    }
    str = fgets_alloc(file);
    while(str != NULL){
        printf(MAG "%s" RESET, str);
        free(str);
        str = fgets_alloc(file);
    }
    free(str);
    printf("\n");
    fclose(file);
}

int main(){
    entrenador_t** entrenadores_ganadores;        
    entrenador_t* entrenador1 = NULL;
    entrenador_t* entrenador2 = NULL;
    salon_t* salon = salon_leer_archivo(PATH_ORIGINAL);
    if(!salon){
        printf("Error al Iniciar salon\n");
        return 1;
    }
    imprimir_intro();
    entrenadores_ganadores = salon_obtener_entrenadores_mas_ganadores(salon, 3);
    printf(MAG "\nEntrenadores con mas de 3 ligas ganadas\n\n" RESET);
    imprimir_entrenadores_ganadores(entrenadores_ganadores);
    free(entrenadores_ganadores);

    entrenador1 = inicializa_entrenador(entrenador1, "Pandolfo", 5);
    entrenador2 = inicializa_entrenador(entrenador2, "Julia", 7);
    salon = salon_agregar_entrenador(salon, entrenador1);
    salon = salon_agregar_entrenador(salon, entrenador2);
    entrenadores_ganadores = salon_obtener_entrenadores_mas_ganadores(salon, 5);
    printf(MAG "\nEntrenadores con mas de 5 ligas ganadas\n\n" RESET);
    imprimir_entrenadores_ganadores(entrenadores_ganadores);
    free(entrenadores_ganadores);

    salon_guardar_archivo(salon, PATH_MODIFICADO);
    salon_destruir(salon);
    return 0;
}