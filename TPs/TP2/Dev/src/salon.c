#include "salon.h"

struct _salon_t{
    //???
};

salon_t* salon_leer_archivo(const char* nombre_archivo){
    return NULL;
}

int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo){
    return -1;
}

salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador){
    return NULL;
}


lista_t* salon_filtrar_entrenadores(salon_t* salon , bool (*f)(entrenador_t*, void*), void* extra){
    return NULL;
}

char* salon_ejecutar_comando(salon_t* salon, const char* comando){
    return NULL;
}

void salon_destruir(salon_t* salon){

}