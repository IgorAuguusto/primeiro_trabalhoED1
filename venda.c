#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "vendedor.h"
#include "cliente.h"
#include "venda.h"
#include "produto.h"

void gerarNotaFiscal(unsigned long,unsigned long,float);
void registroItemNotaFiscal(unsigned long ,unsigned int, float );

struct TCarrinho{
    unsigned long idProduto;
    unsigned int quantidadeVendida;
    float valorVenda;
};

int validarVendedor(FILE *a,int posicao, char *password){
    TVendedor vendedor;
    fseek(a,posicao*sizeof(TVendedor),SEEK_SET);
    fread(&vendedor,sizeof(TVendedor),1,a);
    if(strcmp(password,vendedor.password) == 0)
        return 1;
    else
        return -1;
}

int pesquisaIdProdCarrinho(TCarrinho *carrinho, unsigned long id,int tam){
    for(int posicao = 0; posicao < tam; posicao++){
        if(carrinho[posicao].idProduto == id){
            return posicao;
        }
    }
    return -1;
}

void removerProduto(TCarrinho *carrinho,int posicaoIdProduto, int tamanhoCarrinho){
    if(posicaoIdProduto != tamanhoCarrinho){
        carrinho[posicaoIdProduto].idProduto = carrinho[tamanhoCarrinho-1].idProduto;
        carrinho[posicaoIdProduto].quantidadeVendida = carrinho[tamanhoCarrinho-1].quantidadeVendida;
        carrinho[posicaoIdProduto].valorVenda = carrinho[tamanhoCarrinho-1].valorVenda;
    }
}

float valorTotalCarrinho(TCarrinho *carrinho,int tamanhoCarrinho){
    int i;
    float valorTotal=0;
    for(i=0;i<tamanhoCarrinho;i++){
        valorTotal+=carrinho[i].valorVenda;
    }
    return valorTotal;
}

void mostrarCarrinho(TCarrinho *carrinho, int tamanho){
        printf("*==================================================*\n");
        printf("|_____________ CARRINHO DE COMPRAS ________________|\n");
        if(tamanho > 0){
            for(int i = 0; i < tamanho; i++){
                printf("\n\t\tID do produto: %lu",carrinho[i].idProduto);
                printf("\n\t\tQuantidade vendida: %u",carrinho[i].quantidadeVendida);
                printf("\n\t\tValor da venda: R$%.2f",carrinho[i].valorVenda);
                printf("\n*=================================================*\n");
            }
        }
        else{
            printf("\n\t\tNao ha itens no carinho");
            printf("\n*=================================================*\n");
        }
}

void venda(){
    FILE *arquivo_vendedor, *arquivo_cliente, *arquivo_produto;
    int cont = 0,valida,sair,posicaoClienteID,posicaoIdProduto,i;
    int opcao,quantidade,quantidadeEstoque,remover =0 ,tamanhoCarrinho = 1;
    float valorTotal;
    unsigned long idCliente,idProduto,posicaoVendedor;
    char cpf[13],password[20];
    TCarrinho *carrinho;

    arquivo_cliente = fopen("cliente.dat", "rb+");
    arquivo_vendedor = fopen("vendedor.dat", "rb+");
    arquivo_produto = fopen("produto.dat", "rb+");

    if (arquivo_cliente == NULL || arquivo_vendedor == NULL || arquivo_produto == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }

    do{
        printf("\n================== LOGIN VENDEDOR ==================");
        printf("\nFornceca o cpf: ");
        setbuf(stdin,NULL);
        gets(cpf);
        posicaoVendedor = pesquisaVendedorCPF(arquivo_vendedor,cpf);
        if(posicaoVendedor == -1){
            printf("CPF imcompativel com o sistema!!");
            continue;
        }
        printf("Forneca a senha: ");
        setbuf(stdin,NULL);
        fgets(password,20,stdin);
        retiraEnter(password);
        maiuscSemAcento(password);
        valida = validarVendedor(arquivo_vendedor,posicaoVendedor,password);
        if(valida != 1){
            printf("Senha incorreta!!");
            continue;
        }
    }while(valida != 1);
    printf("================ LOGIN BEM SUCEDIDO ===============");
    do{
        do{
            printf("\nForneca o ID do cliente: ");
            scanf("%lu",&idCliente);
            posicaoClienteID = pesquisaIdCliente(arquivo_cliente,idCliente);
            if(posicaoClienteID == -1){
                printf("\nSem dados referente ao ID do cliente no sistema !!");
                continue;
            }
            //Alocando memoria para o carinho de compra
            carrinho = (TCarrinho *)malloc(sizeof(TCarrinho));
            if(carrinho == NULL){
                printf("Erro: sem memoria!!\n");
                return;
            }
        }while(posicaoClienteID == -1);
        system("cls || clear");
        do{
            listagemProduto(arquivo_produto);
            printf("\nForneca o id do produto a ser vendido: ");
            scanf("%lu",&idProduto);
            posicaoIdProduto = pesquisaIdProduto(arquivo_produto, idProduto);
            while(posicaoIdProduto == -1 || pesquisaIdProdCarrinho(carrinho,idProduto,tamanhoCarrinho) != -1){
                if(posicaoIdProduto == -1){
                    printf("\nProduto invalido!!");
                    printf("\nForneca o id do produto a ser vendido: ");
                    scanf("%lu",&idProduto);
                }
                else{
                    printf("\nProduto ja consta no carrinho!!");
                    printf("\nForneca o id do produto a ser vendido: ");
                    scanf("%lu",&idProduto);
                }
                posicaoIdProduto = pesquisaIdProduto(arquivo_produto, idProduto);
            }
            quantidadeEstoque = pesquisaQuantidadeProduto(arquivo_produto,idProduto);
            if(quantidadeEstoque > 0){
                    printf("\nUnidades em estoque do Produto: %d", quantidadeEstoque);
                    printf("\nForneca quantas unidades do produto sera vendido: ");
                    scanf("%d",&quantidade);
                while(quantidade > quantidadeEstoque){
                    printf("\nUnidades em estoque do Produto: %d", quantidadeEstoque);
                    printf("\nForneca quantas unidades do produto sera vendido: ");
                    scanf("%d",&quantidade);
                    if(quantidade > quantidadeEstoque){
                        printf("\nQuantidade solicitada maior que o estoque!!\n");
                        continue;
                    }
                }
            }
            else{
                printf("\nProduto nao se encontra no estoque!!\n");
                pressioneEnter();
                continue;
            }
            carrinho[cont].idProduto = idProduto;
            carrinho[cont].quantidadeVendida = quantidade;
            carrinho[cont].valorVenda = valorProduto(arquivo_produto,idProduto)*carrinho[cont].quantidadeVendida;
            pressioneEnter();
            system("cls || clear");
            do{
                if(tamanhoCarrinho == 0)
                    tamanhoCarrinho = 1;
                printf("\n1- Colocar mais produtos no carrinho\n2- Confirmar a venda");
                printf("\n3- Cancelar um produto\n4- Alterar quantidade de um produto\n5- Visualizar carrinho\nSelecione a opcao desejada: ");
                scanf("%d",&opcao);
                system("cls || clear");
                switch(opcao){
                    case 1:
                        cont++;
                        tamanhoCarrinho++;
                        //verificando se ja ouve remocao de algum produto, para não alocar mais memoria e sim usar a do produto que foi removido
                        if(remover == 0)
                            carrinho = (TCarrinho*)realloc(carrinho,tamanhoCarrinho*sizeof(TCarrinho));
                        else
                            remover--;
                        break;
                    case 2:

                        valorTotal = valorTotalCarrinho(carrinho,tamanhoCarrinho);
                        gerarNotaFiscal(idCliente,posicaoVendedor+1,valorTotal);
                        for(i=0;i<tamanhoCarrinho;i++){
                            atualizaProdutoVenda (arquivo_produto,carrinho[i].idProduto,carrinho[i].quantidadeVendida);
                            registroItemNotaFiscal(carrinho[i].idProduto,carrinho[i].quantidadeVendida,carrinho[i].valorVenda);
                        }
                        break;
                    case 3:
                        mostrarCarrinho(carrinho, tamanhoCarrinho);
                        printf("\nDigite o ID do produto a ser removido: ");
                        scanf("%lu",&idProduto);
                        posicaoIdProduto = pesquisaIdProdCarrinho(carrinho,idProduto,tamanhoCarrinho);
                        while(posicaoIdProduto == -1){
                            printf("\nProduto nao cosnta no carrinho!!");
                            printf("\nDigite o ID do produto a ser removido: ");
                            scanf("%lu",&idProduto);
                            posicaoIdProduto = pesquisaIdProdCarrinho(carrinho,idProduto,tamanhoCarrinho);
                        }
                        removerProduto(carrinho,posicaoIdProduto,tamanhoCarrinho-1);
                        remover++;
                        cont--;
                        tamanhoCarrinho--;
                        continue;

                    case 4:
                        mostrarCarrinho(carrinho, cont);
                        printf("\nDigite o ID do produto a ser alterado a quantidade: ");
                        scanf("%lu",&idProduto);
                        posicaoIdProduto = pesquisaIdProdCarrinho(carrinho,idProduto,tamanhoCarrinho);
                        if(posicaoIdProduto != -1){
                            quantidadeEstoque = pesquisaQuantidadeProduto(arquivo_produto,idProduto);
                            printf("Unidades em estoque do Produto: %d\n", quantidadeEstoque);
                            printf("Digite a quantidade nova: ");
                            scanf("%d",&quantidade);
                            while(quantidade > quantidadeEstoque){
                                printf("Unidades em estoque do Produto: %d\n", quantidadeEstoque);
                                printf("Forneca quantas unidades do produto: \n");
                                scanf("%d",&quantidade);
                                if(quantidade > quantidadeEstoque){
                                    printf("\nQuantidade solicitada maior que o estoque!!\n");
                                    continue;
                                }
                            }
                            carrinho[posicaoIdProduto].quantidadeVendida = quantidade;
                            printf("\nQuantidade alterada com sucesso!!\n");
                           pressioneEnter();
                        }
                        else{
                            printf("\nID de produto nao encontrado!!\n");
                            pressioneEnter();
                        }
                        break;

                    case 5:
                        mostrarCarrinho(carrinho, tamanhoCarrinho);
                        continue;
                }
                }while(opcao != 2 && opcao !=1 );

        }while(opcao == 1);
         //liberando carinho
         free(carrinho);

        printf("\nDeseja abandonar a venda?\n1-Sim 2-Nao: ");
        scanf("%d", &sair);
    } while (sair != 1);
    system("cls || clear");
    fclose(arquivo_produto);
    fclose(arquivo_vendedor);
    fclose(arquivo_cliente);
    
}
