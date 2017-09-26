#include <stdio.h>

int main() {
    // int a = 69;
    // int *p = &a;
    // int **pp = &p;
    // printf("\nEnd A : %d", &a);
    // printf("\n%d", p); //mostra o endereço q p esta apontado
    // printf("\n%d", &p); //endereço de p
    // printf("\n%d", *p); //valor
    // printf("\n%d", pp);
    // printf("\n%d", &pp);
    // printf("\n%d", **pp);
    
    int * a = malloc(sizeof(int));
    a = realloc(a,1);
    a[0] = 69;
    a[1] = 45;
    a[2] = 89;
    a[3] = 22;
    a[60] = 69;
    printf("\na : %d", a[60]);
    
    return 0;
}