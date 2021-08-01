#include "pa2mm.h"
#include "src/salon.h"


void salon_leer_archivo_inexistente_devuelve_null(){
    salon_t* salon = NULL;

    pa2m_afirmar((salon = salon_leer_archivo("archivos_prueba/asdasdasdasdasdasdasd.asd")) == NULL, "Leer un archivo inexistente devuelve un salon nulo.");
}

void salon_leer_archivo_carga_correctamente_un_archivo_con_1e_y_1p(){
  salon_t* salon = NULL;
  salon = salon_leer_archivo("./src/archivos/salon_1e_1p.txt");
  pa2m_afirmar(salon != NULL, "Puedo leer un archivo con 1 entrenador y 1 pokemon.");
  salon_destruir(salon);
}

void salon_leer_archivo_carga_correctamente_un_archivo_con_2e_y_2p(){
    salon_t* salon = NULL;
    salon = salon_leer_archivo("./src/archivos/salon_2e_2p.txt");
    pa2m_afirmar(salon != NULL, "Puedo leer un archivo con 2 entrenadores y 2 pokemon cada uno.");
    salon_destruir(salon);
}

int main(){
    pa2m_nuevo_grupo("Pruebas Salon");
    pa2m_nuevo_grupo("Salon Leer Archivo");
    salon_leer_archivo_inexistente_devuelve_null();
    salon_leer_archivo_carga_correctamente_un_archivo_con_1e_y_1p();
    salon_leer_archivo_carga_correctamente_un_archivo_con_2e_y_2p();
    return pa2m_mostrar_reporte();
}
