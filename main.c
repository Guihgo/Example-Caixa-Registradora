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
EstoqueData * leEstoque();
double existeEstoque(int codigo);
//float Soma(int codigo, int quantidade);
//float troco(float total, float vrecebe);

/* Variaveis globais */
EstoqueData estoqueData;

/* ---------------------------------------------------*/
/* ---------------------------------------------------*/
/* ---------------------------------------------------*/

int main() {
    // estoqueData = leEstoque();
    estoqueData = (*leEstoque());
    
    // printf("\nestoqueData - main(): %d ", estoqueData);
    // printf("\n&estoqueData - main(): %d ", &estoqueData);
    // printf("\n*estoqueData - main(): %d ", *estoqueData);
    
    printf("\n\n----Testandooo-----") ;
    for(int p=0; p<estoqueData.nLinhas; p++) {
        printf("\n->Linha[%d]", p);
        printf("\n   ->Codigo: %d", estoqueData.itensEstoque[p].codigo);
        printf("\n   ->Descricao: %s", estoqueData.itensEstoque[p].descricao);
    }
 
    /*
    
    int b,a;
    
    float total=0;
    
    while( b!=0 ){
    
        printf("1 - Novo Produto\n0 - Finalizar");
        scanf("%d", a);
    
        switch(a){
         
        case 0:
        float vrecebe,troco;
            printf("Valor total = %f", total);
            printf("Valor Recebido:");
                scanf("%f", &vrecebe).
                troco = troco(total,vrecebe);
                printf("\nValor do Troco: %f",troco);
            break;
            
        case 1:
            int op;
            printf("1 - Digitar ou 2 - Escanear");
                scanf("%d", &op);
               
            if(op == 1){
                int codigo, quantidade;
                
                printf("Codigo do Produto:");
                scanf("%d", &codigo);
                printf("Quantidade");
                scanf("%d", &quantidade)
                    
                    total = total + Soma(codigo,quantidade);
                
            }
         break;
      
        
            
        }
     

    }
    */
    
    
    // FILE *fstream = fopen("teste.csv","w");
    // if(fstream == NULL) {
    //     printf("\n Erro ao abrir arquivo teste.csv");
    //     return -1;
    // }
    
    // fputs("Testeeeee...\n", fstream);
    
    // fclose(fstream);
    
    return 0;
}


/* ---------------------------------------------------*/
/* ---------------------------------------------------*/
/* ---------------------------------------------------*/

/* Função que verifica se certo codigo existe no estoque e retorna seu preço*/
double existeEstoque(int codigo) {
    return 0;
}


EstoqueData * leEstoque() {
    char buffer[1024];
    char *coluna, *linha;
    int i=0,j=0;
    
    FILE *fstream = fopen("estoque.csv","r");
    if(fstream == NULL) {
        printf("\n Erro ao abrir arquivo estoque.csv");
        return NULL;
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
    //printf("nLinhas: %d", nLinhas);
    
    ItemEstoque * itensEstoque = calloc(nLinhas, sizeof(ItemEstoque));
    
    if(!itensEstoque) {
        printf("\n Banco de dados muito grande para a máquina");
        return NULL;
    }
    
    //fseek(fstream, 0, SEEK_SET); //rebobina fstream
    rewind(fstream); //rebobina fstream
    
    //enquanto tiver uma linha pra ser lida
    while((linha = fgets(buffer,sizeof(buffer),fstream))!=NULL) {
        //printf("\nLinha[%d]: %s", i, linha) ;
        
        j=0; //contador de coluna
        
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
        i++;
    }
    fclose(fstream);
    
    EstoqueData estoqueData = {itensEstoque, nLinhas};
    EstoqueData * pEstoqueData = &estoqueData;
    // printf("\n&estoqueData - leEstoque(): %d ", &estoqueData);
    return pEstoqueData;
}

/*
EstoqueData leEstoque() {
    char buffer[1024];
    char *coluna, *linha;
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
    
    ItemEstoque itensEstoque[nLinhas+2]; //cria vetor que ira conter todos itens do estoque
    
    //fseek(fstream, 0, SEEK_SET); //rebobina fstream
    rewind(fstream); //rebobina fstream
    
    //enquanto tiver uma linha pra ser lida
    while((linha = fgets(buffer,sizeof(buffer),fstream))!=NULL) {
        //printf("\nLinha[%d]: %s", i, linha) ;
        
        j=0; //contador de coluna
        
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
                    printf("%s",itensEstoque[i].descricao);
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
        i++;
    }
    
    EstoqueData estoqueData = {itensEstoque, nLinhas};
    fclose(fstream);
    
    printf("\n\n----Testando 0-----") ;
    for(int p=0; p<estoqueData.nLinhas; p++) {
        printf("\n->Linha[%d]", p);
        printf("\n   ->Codigo: %d", estoqueData.itensEstoque[p].codigo);
        printf("\n   ->Descricao: %s", estoqueData.itensEstoque[p].descricao);
    }
    
    return estoqueData;
}
*/

/*
float Soma(int codigo, int quantidade){
    float soma = 0;
    
    for(int p=0; p<estoqueData.nLinhas; p++){
        if(codigo == ItemEstoque.itensEstoque[p].codigo){
            soma = soma + ItemEstoque.itensEstoque[p].preco * quantidade;
        }
        return soma;
    }
    
}

float troco(float total,float vrecebe){
    float valor;
    
    if(vrecebe < total){
        printf("Faltando dinheiro");
    }
        else{
            valor = vrecebe - total;
        }
    return valor;
}

*/
