#include <stdio.h>

unsigned factorial(unsigned n){
    if(n==0)
        return 1;
    return n*factorial(n-1);
}

int main(){
    unsigned resultado=0;
    unsigned n=10;
    resultado = factorial(n);
    printf("%u! = %u\n", n, resultado);
    return 0;
}
