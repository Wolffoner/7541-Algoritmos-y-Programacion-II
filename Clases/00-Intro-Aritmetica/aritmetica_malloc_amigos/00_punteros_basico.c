//¿Qué error hay en el código?
#include <stdlib.h>

int main(){
  char vector1[6];
  char* vector2 = malloc(6);

  if(vector2 == NULL)
    return -1;

  //Acceder al 7mo elemento
  vector1[6] = 1;

  vector2[6] = 1;
  *(vector2+6) = 1;

  free(vector2);

  return 0;
}
