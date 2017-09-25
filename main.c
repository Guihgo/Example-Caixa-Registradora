#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* structs */
typedef struct {
    int codigo;
    char descricao[150];
    double quantidade, preco;
} ItemEstoque;

typedef struct {
    ItemEstoque * itensEstoque;
    int nLinhas;
} EstoqueData;

/* Declarações de funções */
EstoqueData leEstoque();

/* Variaveis globais */
EstoqueData estoqueData;

int main() {
    estoqueData = leEstoque();
    printf("\n\n----Testando-----") ;
    for(int p=0; p<estoqueData.nLinhas; p++) {
        printf("\n->Linha[%d]", p);
        printf("\n   ->Codigo: %d", estoqueData.itensEstoque[p].codigo);
        printf("\n   ->Descricao: %s", estoqueData.itensEstoque[p].descricao);
    }
    
    
    return 0;
}

EstoqueData leEstoque() {
    char linha[1024];
    char *coluna;
    int i=0,j=0;
    
    FILE *fstream = fopen("estoque.csv","r");
    if(fstream == NULL) {
        printf("\n Erro ao abrir arquivo estoque.csv");
        EstoqueData estoqueData;
        return estoqueData;
    }
    
    //contando quantas linhas tem
    char ch;
    int nLinhas=0;
    while(!feof(fstream)) {
      ch = fgetc(fstream);
      if(ch == '\n')
      {
        nLinhas++;
      }
    }
    printf("nLinhas: %d", nLinhas);
    
    ItemEstoque itensEstoque[nLinhas]; //cria vetor que ira conter todos itens do estoque
    
    fseek(fstream, 0, SEEK_SET); //rebobina fstream
    
    //enquanto tiver uma linha pra ser lida
    while(fgets(linha,sizeof(linha),fstream)!=NULL) {
        //printf("\nLinha[%d]: %s", i, linha) ;
        
        j=0;
        coluna = strtok(linha,";"); //procura primeiro delimitador na linha e corta a linha até ele
        while(coluna!=NULL) //enquanto tiver delimitadores na linha
        {
            //printf("\nColuna[%d] : %s", j, coluna);
            
            switch(j) {
                case 0: //coluna codigo
                    itensEstoque[i].codigo = atoi(coluna);
                break;
                case 1: //coluna descricao
                    strcpy(itensEstoque[i].descricao, coluna);
                break;
                case 2: //coluna quantidade
                    itensEstoque[i].quantidade = atof(coluna);
                break;
                case 3: //coluna preço
                    itensEstoque[i].preco = atof(coluna);
                break;
                default:
                break;
            }
            
            j++;
            coluna = strtok(NULL,";"); //procura proximo delimitador e corta
        }
        ++i;
    }
    
    EstoqueData estoqueData = {itensEstoque, nLinhas};
    
    return estoqueData;
}
