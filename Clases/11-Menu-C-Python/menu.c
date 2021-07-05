#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"


/*
 * ? - Muestra la ayuda
 * I - Incrementa un contador
 * P - Muestra el contador
 * D - Decrementa el contador
 * Q - Salir del programa
 * R - Resetear el contador
 * nose - mostrar el menu de coso
 **/

typedef struct{
    const char* nombre;
    const char* documentacion;
    bool (*ejecutar)(const char*, void*);
}Comando;

typedef struct{
    const char* nombre_menu;
    const char* ayuda;
    hash_t* comandos;
}Menu;

typedef struct{
    int contador;
    bool finalizado;

    Menu* menu_activo;
}Juego;

char* leer_linea(char* buffer, size_t tam){
    char* respuesta = fgets(buffer, tam, stdin);
    if(respuesta)
        respuesta[strlen(respuesta)-1] = 0;

    return respuesta;
}

Comando* comando_crear(const char* nombre, const char* doc, bool (*ejecutar)(const char*, void*)){
    Comando* comando = calloc(1, sizeof(Comando));
    comando->nombre = nombre;
    comando->documentacion = doc;
    comando->ejecutar = ejecutar;
    return comando;
}

Menu* menu_crear(){
    Menu* menu = calloc(1, sizeof(Menu));
    menu->comandos = hash_crear(10);
    return menu;
}

void agregar_comando(Menu* menu, const char* nombre, const char* doc, bool (*ejecutar)(const char*, void*)){
    Comando *comando = comando_crear(nombre, doc, ejecutar);
    hash_insertar(menu->comandos, nombre, comando);
}

void menu_ejecutar(Menu* menu, void* contexto){
    char buffer[512];
    buffer[0] = 0;
    Juego* juego = contexto;

    while(!juego->finalizado){
        printf("> ");
        char* linea  = leer_linea(buffer, 512);

        if(linea){
            Comando *comando = hash_buscar(menu->comandos, linea);
            if(comando){
                comando->ejecutar(linea, contexto);
            }
            else{
                printf("No sé como hacer eso");
            }
        }
        printf("\n");
    }
}

bool incrementar_contador(const char* linea, void* contexto){
    Juego* juego = contexto;
    juego->contador++;
    printf("Se incrementó el contador");
}

bool decrementar_contador(const char* linea, void* contexto){
    Juego* juego = contexto;
    juego->contador--;
    printf("Se decrementó el contador");
    return false;
}

bool imprimir_contador(const char* linea, void* contexto){
    Juego* juego = contexto;
    printf("El contador vale %i", juego->contador);
    return false;
}

bool resetear_contador(const char* linea, void* contexto){
    Juego* juego = contexto;
    juego->contador = 0;
    printf("Reseteo el contador");
    return false;
}


bool salir(const char* linea, void* contexto){
    Juego* juego = contexto;
    juego->finalizado=true;
    printf("Saliendo...");
    return false;
}


bool mostrar_comando(const char* nombre, void* cmd, void* aux){
    Comando* c=cmd;
    printf("%s \t%s\n", c->nombre, c->documentacion);
    return false;
}

bool mostrar_ayuda(const char* linea, void* contexto){
    Juego* juego = contexto;
    Menu* menu = juego->menu_activo;

    printf("Los comandos disponibles son: \n\n");

    hash_con_cada_elemento(menu->comandos, mostrar_comando, NULL);

    return false;
}


int main(int argc, char *argv[]) {
    Menu *menu = menu_crear();
    Juego juego = {0, false, menu};

    agregar_comando(menu, "I", "Incrementar contador", incrementar_contador);
    agregar_comando(menu, "D", "Decrementar contador", decrementar_contador);
    agregar_comando(menu, "P", "Imprimir contador",    imprimir_contador);
    agregar_comando(menu, "R", "Resetear el contador", resetear_contador);
    agregar_comando(menu, "Q", "Salir del juego",      salir);
    agregar_comando(menu, "?", "Muestra la ayuda",     mostrar_ayuda);

    menu_ejecutar(menu, &juego);

    return 0;
}
