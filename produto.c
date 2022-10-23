#include <stdio.h>
#include <stdlib.h>
#include "produto.h"
#include "funcoes.h"

int pesquisaIdProduto(FILE *a,int id){
    int posicao=0;
    TProduto produto;
    //posicionando no início do arquivo
    rewind(a);
    while(fread(&produto,sizeof(TProduto),1,a)==1){
        if(produto.id == id)
          return posicao;
        else
           posicao++;
    }
    return -1;
}

int pesquisaQuantidadeProduto(FILE *a,int id){
    TProduto produto;
    //posicionando no início do arquivo
    rewind(a);
    while(fread(&produto,sizeof(TProduto),1,a)==1){
        if(produto.id == id)
          return produto.quantidadeEstoque;
    }
    return -1;
}

float valorProduto(FILE *a,unsigned long id){
    TProduto produto;
    //posicionando no início do arquivo
    rewind(a);
    while(fread(&produto,sizeof(TProduto),1,a)==1){
        if(produto.id == id)
          return produto.precoUnitario;
    }
    return -1;
}

void atualizaProdutoVenda (FILE *a, unsigned long id, unsigned int quantidade){
    int posicao;
    TProduto produto;

    posicao = pesquisaIdProduto(a,id);
    //posicionando o arquivo a onde sera feita a alteracao
    fseek(a,posicao*sizeof(TProduto)+sizeof(produto.id)+sizeof(produto.nome),SEEK_SET);
    fread(&produto.quantidadeEstoque,sizeof(produto.quantidadeEstoque),1,a);

    produto.quantidadeEstoque -= quantidade;

    fseek(a,posicao*sizeof(TProduto)+sizeof(produto.id)+sizeof(produto.nome),SEEK_SET);
    fwrite(&produto.quantidadeEstoque,sizeof(produto.quantidadeEstoque),1,a);

}

void atualizaPrecoProduto(FILE *a, unsigned long id,float porcentagem){
    int posicao;
    TProduto produto;

    posicao = pesquisaIdProduto(a,id);
    //posicionando o arquivo a onde sera feita a alteracao
    fseek(a,posicao*sizeof(TProduto)+sizeof(produto.id)+sizeof(produto.nome)+sizeof(produto.quantidadeEstoque),SEEK_SET);
    fread(&produto.precoUnitario,sizeof(produto.precoUnitario),1,a);

    produto.precoUnitario = porcentagem/100 * (produto.precoUnitario) + produto.precoUnitario;

    fseek(a,posicao*sizeof(TProduto)+sizeof(produto.id)+sizeof(produto.nome)+sizeof(produto.quantidadeEstoque),SEEK_SET);
    fwrite(&produto.precoUnitario,sizeof(produto.precoUnitario),1,a);

}

void atualizaProdutoCompra (FILE *a, unsigned long id, unsigned int quantidade){
    int posicao;
    TProduto produto;

    posicao = pesquisaIdProduto(a,id);
    //posicionando o arquivo a onde sera feita a alteracao
    fseek(a,posicao*sizeof(TProduto)+sizeof(produto.id)+sizeof(produto.nome),SEEK_SET);
    fread(&produto.quantidadeEstoque,sizeof(produto.quantidadeEstoque),1,a);

    produto.quantidadeEstoque += quantidade;

    fseek(a,posicao*sizeof(TProduto)+sizeof(produto.id)+sizeof(produto.nome),SEEK_SET);
    fwrite(&produto.quantidadeEstoque,sizeof(produto.quantidadeEstoque),1,a);

}



void cadastroProduto(){
    FILE *arquivo_produto;
    TProduto produto;
    int sair,gravado;
    arquivo_produto = fopen("produto.dat", "rb+");

    if (arquivo_produto == NULL){
        arquivo_produto = fopen("produto.dat", "wb+");
        if (arquivo_produto == NULL){
            printf("Erro na criacao do arquivo!\n");
            pressioneEnter();
            return;
        }
    }
    do{
        //Poosiciona no final do arquivo para nao sobreescrever os dados
        fseek(arquivo_produto,0,SEEK_END);
        if(ftell(arquivo_produto) > 0){
            //divide o tamanho total do arquivo pelo tamanho da estrutura e soma 1 para ser o id
            produto.id = (ftell(arquivo_produto))/sizeof(TProduto) +1;
        }
        else
            produto.id = 1;
        system("cls || clear");
        printf("\n================ CADASTRO PRODUTOS =================\n");
        printf("Forneca o nome do produto: ");
        setbuf(stdin, NULL);
        fgets(produto.nome, 100, stdin);
        retiraEnter(produto.nome);
        maiuscSemAcento(produto.nome);

        produto.quantidadeEstoque = 10;

        printf("Forneca o preco unitario do produto: ");
        scanf("%f",&produto.precoUnitario);

        gravado = fwrite(&produto, sizeof(TProduto), 1, arquivo_produto);

        if(gravado != 1){
            printf("Erro na escrita do cadastro do cliente!!");
            pressioneEnter();
            return;
        }
        printf("\n=========== DADOS DO PRODUTO CADASTRADO =============");
        printf("\nID: %lu",produto.id);
        printf("\nNome: %s",produto.nome);
        printf("\nQuantidade em estoque: %u",produto.quantidadeEstoque);
        printf("\nPreco unitario: R$%.2f",produto.precoUnitario);
        printf("\n====================================================\n");

        printf("\n\nDeseja abandonar o Cadastro?\n1-Sim 2-Nao: ");
        scanf("%d", &sair);
    } while (sair != 1);
    fclose(arquivo_produto);
}

void listagemProduto(FILE *arquivo_produto){
    TProduto produto;
    printf("\n============= PRODUTOS CADASTRADOS ================");
    rewind(arquivo_produto);
    while(fread(&produto,sizeof(TProduto),1,arquivo_produto) == 1) {
        printf("\nID: %lu",produto.id);
        printf("\nNome: %s",produto.nome);
        printf("\nQuantidade em estoque: %u",produto.quantidadeEstoque);
        printf("\nPreco unitario: R$%.2f",produto.precoUnitario);
        printf("\n===================================================");
    }
}

