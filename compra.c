#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fornecedor.h"
#include "notaCompra.h"
#include "produto.h"
#include "compra.h"
#include "funcoes.h"


struct TCarrinhoCompra{
    unsigned long idProduto;
    unsigned int quantidade;
    float valorUnitario;
};

float valorProduto(FILE *,unsigned long);

int pesquisaIdProdCarrinhoCompra(TCarrinhoCompra *carrinhoCompra, unsigned long id,int tam){
    for(int posicao = 0; posicao < tam; posicao++){
        if(carrinhoCompra[posicao].idProduto == id){
            return posicao;
        }
    }
    return -1;
}

void removerProdutoCarrinhoCompra(TCarrinhoCompra *carrinhoCompra,int posicaoIdProduto, int tamanhoCarrinho){
    if(posicaoIdProduto != tamanhoCarrinho){
        carrinhoCompra[posicaoIdProduto].idProduto = carrinhoCompra[tamanhoCarrinho-1].idProduto;
        carrinhoCompra[posicaoIdProduto].quantidade = carrinhoCompra[tamanhoCarrinho-1].quantidade;
        carrinhoCompra[posicaoIdProduto].valorUnitario = carrinhoCompra[tamanhoCarrinho-1].valorUnitario;
    }
}

float valorTotalCarrinhoCompra(TCarrinhoCompra *carrinhoCompra,int tamanhoCarrinho){
    int i;
    float valorTotal=0;
    for(i=0;i<tamanhoCarrinho;i++){
        valorTotal+=carrinhoCompra[i].valorUnitario;
    }
    return valorTotal;
}

void mostrarCarrinhoCompra(TCarrinhoCompra *carrinhoCompra, int tamanho){
        printf("*==================================================*\n");
        printf("|_____________ CARRINHO DE COMPRAS ________________|\n");
        if(tamanho > 0){
            for(int i = 0; i < tamanho; i++){
                printf("\n\t\tID do produto: %lu",carrinhoCompra[i].idProduto);
                printf("\n\t\tQuantidade comprada: %u",carrinhoCompra[i].quantidade);
                printf("\n\t\tValor do Produto: R$%.2f",carrinhoCompra[i].valorUnitario);
                printf("\n*=================================================*\n");
            }
        }
        else{
            printf("\n\t\tNao ha itens no carinho");
            printf("\n*=================================================*\n");
        }
}

void compra(){
    FILE *arquivo_fornecedor, *arquivo_produto;
    int cont = 0,sair,posicaoIdProduto,posicaoFornecedor,i;
    int opcao,quantidade,remover =0 ,tamanhoCarrinho = 1;
    unsigned long idFornecedor,idProduto;
    float valorTotal;
    TCarrinhoCompra *carrinhoCompra;

    arquivo_fornecedor = fopen("fornecedor.dat", "rb+");
    arquivo_produto = fopen("produto.dat", "rb+");

    if (arquivo_fornecedor == NULL || arquivo_produto == NULL){
            printf("Erro na abertura do arquivo!\n");
            pressioneEnter();
            return;
    }

    do{
        do{
            printf("\n===================== COMPRA ======================");
            printf("\nFornceca o ID do fornecedor: ");
            scanf("%lu",&idFornecedor);
            posicaoFornecedor = pesquisaIdFornecedor(arquivo_fornecedor,idFornecedor);
            if(posicaoFornecedor == -1){
                printf("\nFornedor Invalido!!");
            }
        }while(posicaoFornecedor == -1);
        carrinhoCompra = (TCarrinhoCompra *)malloc(sizeof(TCarrinhoCompra));
        do{
            listagemProduto(arquivo_produto);
            printf("\nForneca o id do produto a ser Comprado: ");
            scanf("%lu",&idProduto);
            posicaoIdProduto = pesquisaIdProduto(arquivo_produto, idProduto);
            while(posicaoIdProduto == -1|| pesquisaIdProdCarrinhoCompra(carrinhoCompra,idProduto,tamanhoCarrinho) != -1){
                if(posicaoIdProduto == -1){
                    printf("\nProduto invalido!!");
                    printf("\nForneca o id do produto a ser Comprado: ");
                    scanf("%lu",&idProduto);
                }
                else{
                    printf("\nProduto ja consta no carrinho!!");
                    printf("\nForneca o id do produto a ser Comprado: ");
                    scanf("%lu",&idProduto);
                }
                posicaoIdProduto = pesquisaIdProduto(arquivo_produto, idProduto);
            }
            printf("\nForneca quantas unidades do produto sera comprado: ");
            scanf("%d",&quantidade);
            while(quantidade <= 0){
                printf("\nQuantidade solicitada invalida!!\n");
                printf("\nForneca quantas unidades do produto sera comprado: ");
                scanf("%d",&quantidade);
                continue;

            }

            carrinhoCompra[cont].idProduto = idProduto;
            carrinhoCompra[cont].quantidade = quantidade;
            carrinhoCompra[cont].valorUnitario = valorProduto(arquivo_produto,idProduto);
            pressioneEnter();
            system("cls || clear");
            do{
                if(tamanhoCarrinho == 0)
                    tamanhoCarrinho = 1;
                printf("\n1- Colocar mais produtos no carrinho\n2- Confirmar a compra");
                printf("\n3- Cancelar um produto\n4- Alterar quantidade de um produto\n5- Visualizar carrinho\nSelecione a opcao desejada: ");
                scanf("%d",&opcao);
                system("cls || clear");
                switch(opcao){
                    case 1:
                        cont++;
                        tamanhoCarrinho++;
                        //verificando se ja ouve remocao de algum produto, para não alocar mais memoria e sim usar a do produto que foi removido
                        if(remover == 0)
                            carrinhoCompra = (TCarrinhoCompra*)realloc(carrinhoCompra,tamanhoCarrinho*sizeof(TCarrinhoCompra));
                        else
                            remover--;
                        break;
                    case 2:
                        valorTotal = valorTotalCarrinhoCompra(carrinhoCompra,tamanhoCarrinho);
                        gerarNotaCompra(idFornecedor,valorTotal);
                        for(i=0;i<tamanhoCarrinho;i++){
                            atualizaProdutoCompra (arquivo_produto,carrinhoCompra[i].idProduto,carrinhoCompra[i].quantidade);
                            registroItemNotaCompra(carrinhoCompra[i].idProduto,carrinhoCompra[i].quantidade,carrinhoCompra[i].valorUnitario);
                        }
                        break;
                    case 3:
                        mostrarCarrinhoCompra(carrinhoCompra, tamanhoCarrinho);
                        printf("\nDigite o ID do produto a ser removido: ");
                        scanf("%lu",&idProduto);
                        posicaoIdProduto = pesquisaIdProdCarrinhoCompra(carrinhoCompra,idProduto,tamanhoCarrinho);
                        while(!posicaoIdProduto){
                            printf("\nProduto nao cosnta no carrinho!!");
                            printf("\nDigite o ID do produto a ser removido: ");
                            scanf("%lu",&idProduto);
                            posicaoIdProduto = pesquisaIdProdCarrinhoCompra(carrinhoCompra,idProduto,tamanhoCarrinho);
                        }
                        removerProdutoCarrinhoCompra(carrinhoCompra,posicaoIdProduto,tamanhoCarrinho-1);
                        remover++;
                        cont--;
                        tamanhoCarrinho--;
                        continue;

                    case 4:
                        mostrarCarrinhoCompra(carrinhoCompra, cont);
                        printf("\nDigite o ID do produto a ser alterado a quantidade: ");
                        scanf("%lu",&idProduto);
                        posicaoIdProduto = pesquisaIdProdCarrinhoCompra(carrinhoCompra,idProduto,tamanhoCarrinho);
                        if(posicaoIdProduto != -1){
                            printf("Digite a quantidade nova: ");
                            scanf("%d",&quantidade);
                            while(quantidade < 0){
                                printf("Quantidade invalida!!");
                                printf("Forneca quantas unidades do produto: \n");
                                scanf("%d",&quantidade);
                                continue;
                                }
                            carrinhoCompra[posicaoIdProduto].quantidade = quantidade;
                            printf("\nQuantidade alterada com sucesso!!\n");
                            pressioneEnter();
                        }
                        else{
                            printf("\nID de produto nao encontrado!!\n");
                            pressioneEnter();
                        }
                        break;
                    case 5:
                        mostrarCarrinhoCompra(carrinhoCompra, tamanhoCarrinho);
                        continue;
                }
                }while(opcao != 2 && opcao !=1 );
        }while(opcao == 1);
        //liberando carinho
        free(carrinhoCompra);
        printf("\nDeseja abandonar a compra?\n1-Sim 2-Nao: ");
        scanf("%d", &sair);
    } while (sair != 1);
    system("cls || clear");
    fclose(arquivo_produto);
    fclose(arquivo_fornecedor);
}
