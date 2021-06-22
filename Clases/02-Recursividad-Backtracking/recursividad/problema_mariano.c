#include <stdlib.h>
#include <stdio.h>

int sumar_n(int n){
    int suma = 0;
    for(int i=0;i<=n;i++)
        suma+=i;

    return suma;
}

int sumar_n_rec(int n){
    if(n<=0)
        return 0;
    return n+sumar_n_rec(n-1);
}

int main(int argc, char *argv[]) {

    int n = strtol(argv[1], NULL, 0);

    int suma1 = sumar_n(n);
    int suma2 = sumar_n_rec(n);

    printf("Suma1: %i\n", suma1);
    printf("Suma2: %i\n", suma2);

    return 0;
}
