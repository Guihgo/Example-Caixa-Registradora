#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* structs */
typedef struct {
    int codigo;
    double quantidade;
} Carrinho;

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
int existeEstoque(int codigo,double quantidade);
double soma(int codigo, double quantidade);
//float troco(float total, float vrecebe);

/* Declaracoes de metodos */
void criaNovaCompra();

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
    
    // printf("\n\n----Testandooo-----");
    // for(int p=0; p<estoqueData.nLinhas; p++) {
    //     printf("\n->Linha[%d]", p);
    //     printf("\n   ->Codigo: %d", estoqueData.itensEstoque[p].codigo);
    //     printf("\n   ->Descricao: %s", estoqueData.itensEstoque[p].descricao);
    // }
 
    int a = 0;
    while(a!=1) {
        printf("\nEscolha uma opcao:");
        printf("\n0 - Novo Compra\n1 - Finalizar");
        scanf("%d", &a);
        
        switch(a){
            case 0:
                criaNovaCompra();
            break;
            
            case 1: //faz nada
            break;
            
            default:
                printf("\nEssa opcao nao existe!\nTente novamente");
            break;
        }
    }
    return 0;
}


/* ---------------------------------------------------*/
/* ---------------------------------------------------*/
/* ---------------------------------------------------*/

/* Função que verifica se certo codigo existe no estoque */
int existeEstoque(int codigo, double quantidade) {
    int flagExiste = 0;
    for(int a=0; a<estoqueData.nLinhas; a++){
        if(codigo == estoqueData.itensEstoque[a].codigo && quantidade <= estoqueData.itensEstoque[a].quantidade){
            flagExiste = 1;
        }
    }
    return flagExiste;
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


double soma(int codigo, double quantidade){
    double soma;
    
    for(int p=0; p<estoqueData.nLinhas; p++){
        if(codigo == estoqueData.itensEstoque[p].codigo){
            soma = estoqueData.itensEstoque[p].preco * quantidade;
        }
        return soma;
    }
}

/*
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


void criaNovaCompra() {
    int a = 0;
    int nItens = 0;

    Carrinho * listaProdutos = malloc(sizeof(Carrinho));
    
    
    while(a!=1){
        printf("\n0 - Novo Produto\n1 - Finalizar");
        scanf("%d", &a);
        switch(a){
            
            case 0:{
                
                int b;
                printf("\n0 - Digitar codigo\n1 - Escanear QRcode");
                scanf("%d", &b);
                
                if(b==0){
                    int codigo;
                    double quantidade;
                    printf("\nCodigo do Produto:");
                    scanf("%d", &codigo);
                    
                    printf("\nQuantidade:");
                    scanf("%lf", &quantidade);
                        
                    //verifica se existe o codigo no estoque e verificar se a quantidade é menor ou igual à existente no estoque;
                    if(existeEstoque(codigo, quantidade) == 1){
                        nItens++;
                        listaProdutos = realloc(listaProdutos, (sizeof(Carrinho)*(nItens+1)));
                        //add produto no carrinho
                        listaProdutos[nItens].codigo = codigo; 
                        listaProdutos[nItens].quantidade = quantidade;
                    } else {
                        printf("\n[Erro] - Codigo nao existe ou quantidade nao existe em estoque");
                    }
                }
                
                if(b==1){
                    //deixa pra depois que td estiver pronto...
                }
                break;
            }
            
            case 1: {
                //checkout();//total, troco, saida estoque;
                break; 
            }
                
        }
    }
    
    free(listaProdutos);
}