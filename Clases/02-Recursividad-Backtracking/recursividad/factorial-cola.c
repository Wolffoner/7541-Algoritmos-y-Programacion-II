#include <stdio.h>

unsigned factorial_rec(unsigned n, unsigned parcial){
    if(n==0)
        return parcial;
    return factorial_rec(n-1, parcial*n);
}

unsigned factorial(unsigned n){
    return factorial_rec(n,1);
}

int main(){
    unsigned resultado=0;
    unsigned n=10;
    resultado = factorial(n);
    printf("%u! = %u\n", n, resultado);
    return 0;
}
