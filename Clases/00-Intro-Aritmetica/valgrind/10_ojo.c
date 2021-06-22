#include <stdio.h>
#include <stdlib.h>

int main(){

  int *p1,*p2,*p3,*p4,*p5;

  p1=malloc(10);
  p2=malloc(10);
  p3=malloc(10);
  p4=malloc(10);
  p5=malloc(10);

  p1[0]=p2[0]=p3[0]=p4[0]=p5[0];

  free(p1);
  free(p2);
  free(p3);
  free(p4);
  free(p5);
  
  return 0;
}
