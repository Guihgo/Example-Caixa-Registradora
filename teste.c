#include <stdio.h>

int main() {
    int a = 69;
    int *p = &a;
    int **pp = &p;
    printf("\nEnd A : %d", &a);
    printf("\n%d", p); //mostra o endereço q p esta apontado
    printf("\n%d", &p); //endereço de p
    printf("\n%d", *p); //valor
    printf("\n%d", pp);
    printf("\n%d", &pp);
    printf("\n%d", **pp);
    return 0;
}