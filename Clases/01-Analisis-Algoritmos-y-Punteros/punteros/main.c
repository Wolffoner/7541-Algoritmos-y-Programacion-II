#include "agenda.h"
#include <stdlib.h>

bool item_es_impar_y_empieza_con_v(const item_agenda_t* item){
    if(item->numero % 2 == 0)
        return false;

    if(item->nombre[0] != 'V')
        return false;

    return true;
}

int main(){
    agenda_t* agenda = agenda_crear("Lucas");

    //Hicimos algo

    agenda_agregar_contacto(agenda, "Lucas", 1234567);
    agenda_agregar_contacto(agenda, "Mariano", 444444);
    agenda_agregar_contacto(agenda, "Valen", 555555);
    agenda_agregar_contacto(agenda, "Gabriel", 786234);

    bool (*mi_funcion)(item_agenda_t*) = item_es_impar_y_empieza_con_v;

    agenda_mostrar_si(agenda, mi_funcion);

    agenda_destruir(agenda);
    return 0;
}
