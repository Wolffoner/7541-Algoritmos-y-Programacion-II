#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CLAVE 4

char* clave_secreta="BABA";

bool probar_clave(char* clave_candidata){
  printf("Probando clave %s.... \n", clave_candidata);
  return (strcmp(clave_candidata, clave_secreta)==0);
}


int main(){

  char clave_candidata[5];
  memset(clave_candidata, 0, 5);
  
  if(adivinar_clave(clave_candidata))
    printf("La clave es: %s\n", clave_candidata);
  else printf("No pude adivinar la clave D:\n");

  return 0;
}
