#include <stdlib.h>
#include <stdio.h>


void mostrar_palabra(const char* palabra){
    if(*palabra != 0){
        printf("%c", *palabra);
        mostrar_palabra(palabra+1);
    }
}

void mostrar_palabra_invertida(const char* palabra){
    if(*palabra != 0){
        mostrar_palabra_invertida(palabra+1);
        printf("%c", *palabra);
    }
}

int main(int argc, char *argv[]) {

    char* palabra = argv[1]?argv[1]:"Algo2Mendez";

    mostrar_palabra(palabra);
    printf("\n");
    mostrar_palabra_invertida(palabra);
    printf("\n");
    
    return 0;
}
