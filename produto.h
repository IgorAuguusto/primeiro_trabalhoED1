#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED

typedef struct{
    unsigned long id;
    char nome[100];
    unsigned int quantidadeEstoque;
    float precoUnitario;
}TProduto;
void cadastroProduto();
void listagemProduto(FILE *);
int pesquisaIdProduto(FILE *,int);
int pesquisaQuantidadeProduto(FILE *,int);
float valorProduto(FILE *,unsigned long);
void atualizaProdutoVenda (FILE *, unsigned long, unsigned int);
void atualizaProdutoCompra (FILE *, unsigned long, unsigned int);
void atualizaPrecoProduto(FILE * ,unsigned long, float);
void atualizaPrecoTodosProdutos(FILE * ,float );
#endif // PRODUTO_H_INCLUDED
