#include "pa2m.h"

void dado_el_uno_y_el_dos_cuando_los_sumo_obtengo_el_3(){
    // test case
    // Preparar -----DADO
    
    int i = 1;
    int j = 2;
    int w;

    // Actuar ----> CUANDO
    
    w=i+j;

    // Verificar ---->ENTONCES
    pa2m_afirmar(w==3,"la suma de 1 + 2 es 3");
    
}

void pruebas_enteros(){
    // test suit 
   pa2m_nuevo_grupo("Pruebas de numeros enteros ");
    
    dado_el_uno_y_el_dos_cuando_los_sumo_obtengo_el_3();

 }


void pruebas_varias(){
    pa2m_nuevo_grupo(" mas Pruebas de numeros enteros ");
    
    dado_el_uno_y_el_dos_cuando_los_sumo_obtengo_el_3();
 

}


int  main (){

     pruebas_enteros();
     pruebas_varias();
     return pa2m_mostrar_reporte();
}
