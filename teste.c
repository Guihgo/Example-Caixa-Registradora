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
    
    FILE *fstream = fopen("estoqueReplica.csv","w");
    if(fstream == NULL) {
        printf("\n Erro ao abrir arquivo estoqueReplica.csv");
        return -1;
    }
    int a = 65;
    char t[20] = "comida";
    double b = 12;
    fprintf(fstream, "%d;%s\n", a,t);
    fprintf(fstream, "%d;%s;%.2lf\n", a,t,b);
    fclose(fstream);
    
    return 0;
}