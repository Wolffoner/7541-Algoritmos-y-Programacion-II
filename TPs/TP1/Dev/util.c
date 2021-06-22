#include "util.h"
#include <stdlib.h>

#include <string.h>
#define FIN_STRING '\0'
#define VACIO ""

const size_t TAMANIO_STRING = 512;

size_t vtrlen(void* ptr){
    void** ptr_aux = (void**)ptr;
    size_t i = 0;
    if(ptr_aux != NULL){
        while(ptr_aux[i] != NULL){
            i++;
        }
    }
    return i;
}

void* vtradd(void* ptr, void* item){
    void** ptr_vtr = (void**)ptr;
    void** ptr_aux = NULL;
    size_t i = vtrlen(ptr_vtr);
    ptr_aux = (void**)realloc(ptr_vtr, ((sizeof(void*)*(i+2))));
        if(!ptr_aux){
            free(ptr_aux);
            return NULL;
        }
    ptr_vtr = ptr_aux;
    ptr_vtr[i] = item;
    i++;
    ptr_vtr[i] = NULL;
    return ptr_vtr;
}

void vtrfree(void* ptr){
    if(!ptr){
        return;
    }
    int i = 0;
    void** ptr_aux = (void**)ptr;
    while(ptr_aux[i] != NULL){
        free(ptr_aux[i]);
        i++;
    }
    free(ptr);
}

char* get_string(const char* str, int i, char separador, char* str_div){
    char* str_aux = NULL;
    size_t j = 0;
    if(str_div != NULL){
        j = strlen(str_div);
    }
    if(str[i] != separador){
        str_aux = (char*)realloc(str_div, (sizeof(char)*(j+2)));
        if(!str_aux){
            free(str_aux);
            return NULL;
        }
        str_div = str_aux;
        str_div[j] = str[i];
        j++;
        str_div[j] = FIN_STRING;
    }
    return str_div;
}

char** split(const char* str, char separador){
    char** vector_str = NULL;
    char* str_div = NULL;
    int i = 0;
    if(str == NULL || strcmp(str, VACIO) == 0){
        return NULL;
    }
    while(str[i] != FIN_STRING){
        str_div =  get_string(str, i, separador, str_div);
        if(str[i] == separador){
            if(str_div == NULL){
                str_div = VACIO;
            }
            vector_str = (char**)vtradd(vector_str, str_div);
            str_div = NULL;
        }
        i++;
    }
    if(str_div == NULL){
        str_div = VACIO;
    }
    vector_str = (char**)vtradd(vector_str, str_div);
    
    return vector_str;
}

char* fgets_alloc(FILE* archivo){
    if(!archivo){
        return NULL;
    }
    char* str = NULL;
    size_t bytes_leidos = 0;
    size_t contador = 1;
    str = malloc(TAMANIO_STRING);
    if(!str){
        free(str);
        return NULL;
    }
    while(fgets(str+bytes_leidos, (int)(TAMANIO_STRING), archivo)){
    size_t leido = strlen(str+bytes_leidos);
        if(leido > 0 && *(str+bytes_leidos+leido-1) == '\n'){
            *(str+bytes_leidos+leido-1) = 0;
            return str;
        } else {
            contador++;
            char* str_aux = realloc(str, TAMANIO_STRING*(contador+1));
            if(!str_aux){
                free(str);
                return NULL;
            }
            str = str_aux;
        }
    bytes_leidos += leido;
    }
    if(bytes_leidos == 0){
        free(str);
        return NULL;
    }
    return str;
}

void fclosen(FILE* archivo){
    if(!archivo){
        fclose(archivo);
    }
}
