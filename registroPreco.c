#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "produto.h"
#include "registroPreco.h"

struct HistoricoPreco{
    unsigned long idProduto;
    char dataAlteracao[11];
    float valor;
};


void atualizaPreco(){
    FILE *arquivo_historicoPreco, *arquivo_produto;
    HistoricoPreco historicoPreco;
    TProduto produto;
    int sair,opcao,posicao;
    unsigned long idProduto;
    float porcentagem;

    int dia,mes,ano;
    struct tm tempo;
    time_t meuTempo;

   arquivo_produto = fopen("produto.dat", "rb+");
   arquivo_historicoPreco = fopen("historicopreco.dat", "rb+");

    if (arquivo_historicoPreco == NULL){
        arquivo_historicoPreco = fopen("historicopreco.dat", "wb+");
        if (arquivo_historicoPreco == NULL){
            printf("Erro na criacao do arquivo!\n");
            pressioneEnter();
            return;
        }
    }
    if(arquivo_produto == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }
    //Poosiciona no final do arquivo para nao sobreescrever os dados
    fseek(arquivo_historicoPreco,0,SEEK_END);
    do{
       system("cls || clear");
       printf("\n1- Alterar preco poduto\n2- Alterar precos de todos os produtos\n3- Ver Produtos\n");
       printf("Selecione a opcao desejada: ");
       scanf("%d",&opcao);
       switch(opcao){
        case 1:
            system("cls || clear");
            listagemProduto(arquivo_produto);
            printf("\nForneca o id do produto a ser alterado o preco: ");
            scanf("%lu",&idProduto);
            while(pesquisaIdProduto(arquivo_produto, idProduto) == -1){
                printf("\nProduto invalido!!");
                printf("\nForneca o id do produto a ser alterado o preco: ");
                scanf("%lu",&idProduto);
            }
            printf("\nQuantos %% deseja alterar no valor desse produto?\n\nPorcentagem: ");
            scanf("%f",&porcentagem);
            atualizaPrecoProduto(arquivo_produto,idProduto,porcentagem);
            historicoPreco.idProduto = idProduto;
            historicoPreco.valor = valorProduto(arquivo_produto,idProduto);
            time(&meuTempo);
            tempo = *localtime(&meuTempo);
            dia = tempo.tm_mday;
            mes = tempo.tm_mon + 1;
            ano = tempo.tm_year + 1900;
            sprintf(historicoPreco.dataAlteracao,"%d/%d/%d",dia,mes,ano);

            fwrite(&historicoPreco,sizeof(HistoricoPreco),1,arquivo_historicoPreco);
            break;
        case 2:
            system("cls || clear");
            printf("\nQuantos %% deseja alterar no valor desse produto?\n\nPorcentagem: ");
            scanf("%f",&porcentagem);
            rewind(arquivo_produto);
                    while(fread(&produto,sizeof(TProduto),1,arquivo_produto)==1){
                        produto.precoUnitario = porcentagem/100 * (produto.precoUnitario) + produto.precoUnitario;
                        historicoPreco.idProduto = produto.id;
                        historicoPreco.valor = produto.precoUnitario;
                        time(&meuTempo);
                        tempo = *localtime(&meuTempo);
                        dia = tempo.tm_mday;
                        mes = tempo.tm_mon + 1;
                        ano = tempo.tm_year + 1900;
                        sprintf(historicoPreco.dataAlteracao,"%d/%d/%d",dia,mes,ano);
                        fwrite(&historicoPreco,sizeof(HistoricoPreco),1,arquivo_historicoPreco);

                        posicao = pesquisaIdProduto(arquivo_produto,produto.id);
                        fseek(arquivo_produto,posicao*sizeof(TProduto),SEEK_SET);
                        fwrite(&produto,sizeof(TProduto),1,arquivo_produto);
                        fseek(arquivo_produto,(posicao+1)*sizeof(TProduto),SEEK_SET);
                    }
            break;
        case 3:
            listagemProduto(arquivo_produto);
            break;

        }
        printf("\nDeseja abandonar a alteracao?\n1-Sim 2-Nao: ");
        scanf("%d", &sair);
    }while(sair!=1);
    system("cls || clear");
    fclose(arquivo_produto);
    fclose(arquivo_historicoPreco);

}

void historicoVendaProduto(){
    FILE *arquivo_historicoPreco, *arquivo_produto;
    HistoricoPreco preco;
    unsigned long idProduto;
    arquivo_produto = fopen("produto.dat", "rb");
    arquivo_historicoPreco = fopen("historicopreco.dat", "rb");

    if (arquivo_historicoPreco == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }

    fseek(arquivo_historicoPreco,0,SEEK_END);
    if(ftell(arquivo_historicoPreco) > 0){
        listagemProduto(arquivo_produto);
        printf("\nForncca o id do produto a ser consultado: ");
        scanf("%lu",&idProduto);
        while(pesquisaIdProduto(arquivo_produto, idProduto) == -1){
            printf("\nID Invalido");
            printf("\nForncca o id do produto a ser consultado: ");
            scanf("%lu",&idProduto);
        }

        rewind(arquivo_historicoPreco);
        system("cls || clear");
        printf("\n======== LISTAGEM HISTORICO PRECO PRODUTO ==========");
        while(fread(&preco,sizeof(HistoricoPreco),1,arquivo_historicoPreco) == 1){
            if(preco.idProduto == idProduto){
                printf("\nID Produto: %lu",preco.idProduto);
                printf("\nData de Alteracao: %s",preco.dataAlteracao);
                printf("\nValor: %.2f",preco.valor);
                printf("\n====================================================");
            }
        }
        printf("\n");
        pressioneEnter();
    }
    else
        printf("\nSem dados sobre alteracao de preco do produto\n");
    fclose(arquivo_historicoPreco);
    fclose(arquivo_produto);
}
