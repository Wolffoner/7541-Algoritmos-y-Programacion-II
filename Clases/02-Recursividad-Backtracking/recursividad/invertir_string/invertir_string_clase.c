#include <stdio.h>

size_t strlen_iterativo(const char* string){
  size_t cantidad = 0;
  while(*(string+cantidad) != '\0')
    cantidad++;

  return cantidad;
}

size_t strlen_iterativo2(const char* string){
  size_t cantidad = 0;
  while(*string != 0){
    cantidad++;
    string++;
  }
  return cantidad;
}

size_t strlen_recursivo(const char* string){
  if(*string == 0)
    return 0;
  return 1+strlen_recursivo(string+1);
}

void mostrar_directo(const char* string){
  if(*string == 0)
    return ;

  printf("%c", *string);
  mostrar_directo(string+1);
}


void mostrar_invertido(const char* string){
  if(*string == 0)
    return ;

  mostrar_invertido(string+1);

  printf("%c", *string);
}




int main(int argc, char* argv[]){

  char* string ="\nœ€âŽƒã)€½ï½–â´Â(½ƒã€â";
  //char* string="1234";
  
  if(argc>=2)
    string = argv[1];

  //mostrar_directo(string);

  printf("\n");

  mostrar_invertido(string);

  printf("\n");

}
