#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorios.h"
#include "notaFiscal.h"
#include "notaCompra.h"
#include "vendedor.h"

void menuRegistro(){
    int opcao;
    do{
        system("cls || clear");
        printf("\n================ MENU RELATORIOS ===================\n");
        printf("\n1- Dados Nota Fiscal \n2- Dados Compras\n3- Compra cliente periodo ou dia\n4- Venda vendedor dia");
        printf("\n5- Venda vendedor Mes\n6- Vendedor com Mais venda no Mes\n7- Vendedor com mais venda no periodo\n8- Historico de Preco Produto\n9- sair\n");
        printf("Selecione a opcao desejada: ");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                system("cls || clear");
                dadosRegistroNotaFiscal();
                break;
            case 2:
                system("cls || clear");
                dadosCompra();
                break;
            case 3:
                system("cls || clear");
                comprasClienteDatas();
                break;
            case 4:
                system("cls || clear");
                vendaVendedorDia();
                break;
            case 5:
                system("cls || clear");
                vendaVendedorMes();
                break;
            case 6:
                system("cls || clear");
                maiorVendaVendedorMes();
                break;
            case 7:
                system("cls || clear");
                maiorVendaVendedorPeriodo();
                break;
            case 8:
                system("cls || clear");
                historicoVendaProduto();
                break;
        }
    }while(opcao!=9);
    system("cls || clear");
}

void dadosRegistroNotaFiscal(){
    int sair;
    unsigned long idNotaFiscal;
    do{
            listarNotaFiscal();
            printf("\nForneca o id da Nota Fiscal: ");
            scanf("%lu",&idNotaFiscal);
            system("cls || clear");
            if(consultaIdNotaFiscal(idNotaFiscal) == 1){
                consultaIdNotaFiscal(idNotaFiscal);
                consultaItemsNotaFiscal(idNotaFiscal);
                printf("\n");
                pressioneEnter();
            }
            else
                printf("\nID fornecido invalido");
        printf("\nDeseja abandonar a Consulta?\n1-Sim 2-Nao: ");
        scanf("%d",&sair);
    }while(sair!=1);
    system("cls || clear");
}

void dadosCompra(){
    int sair;
    unsigned long idCompra;
    do{
            listarNotaCompra();
            printf("\nForneca o id da Nota: ");
            scanf("%lu",&idCompra);
            system("cls || clear");
            if(consultarIdNotaCompra(idCompra)== 1){
                consultarIdNotaCompra(idCompra);
                consultarItemNotaCompra(idCompra);
                printf("\n");
                pressioneEnter();
            }
            else
                printf("\nID fornecido invalido");
        printf("\nDeseja abandonar a Consulta?\n1-Sim 2-Nao: ");
        scanf("%d", &sair);
    }while(sair!=1);
    system("cls || clear");
}

//c) Compras efetuadas por um cliente em uma data espec�fica, bem como em um intervalo de
//datas. Mostrar os dados da nota junto com os produtos pertencentes a ela

void comprasClienteDatas(){
    FILE *arquivo_cliente;
    unsigned long idCliente;
    char data[11],dataAux[11];
    int sair,opcao;
    NotaFiscal notaFiscal;

    arquivo_cliente = fopen("cliente.dat", "rb");

    if (arquivo_cliente == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }

    do{
        listagemCliente();
        printf("\nForneca o id do cliente: ");
        scanf("%lu",&idCliente);
        if(pesquisaIdCliente(arquivo_cliente,idCliente) == -1){
            printf("\nCliente Invalido\n");
           pressioneEnter();
            continue;
        }
        printf("\n1- Consultar data especifica\n2- Intervalo de datas");
        printf("\nSelecione a opcao desejada: ");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                printf("\nDigite a data da compra (utilize o seguinte formato dd/mm/aaaa): ");
                setbuf(stdin,NULL);
                gets(data);
                if(consultaCompraDataCliente(data,idCliente)==0){
                    printf("\nData Invalida!!");
                   pressioneEnter();
                    break;
                }
                else
                    system("cls || clear");
                    consultaCompraDataCliente(data,idCliente);
                    printf("\n");
                   pressioneEnter();
                    break;
            case 2:
                printf("\nDigite a data de inicio da consulta (utilize o seguinte formato dd/mm/aaaa): ");
                setbuf(stdin,NULL);
                gets(data);
                printf("\nDigite a data de termino da consulta (utilize o seguinte formato dd/mm/aaaa): ");
                setbuf(stdin,NULL);
                gets(dataAux);
                system("cls || clear");
                if(consultaCompraDataClientePeriodo(data,dataAux,idCliente) == 0){
                    printf("\nDatas invalidas ou cliente sem compras no periodo!!\n");
                   pressioneEnter();
                    break;
                }
                else
                    consultaCompraDataClientePeriodo(data,dataAux,idCliente);
                    printf("\n");
                    pressioneEnter();
                    break;
        }
        printf("\nDeseja abandonar a Consulta?\n1-Sim 2-Nao: ");
        scanf("%d", &sair);
    }while(sair!=1);
    fclose(arquivo_cliente);
    system("cls || clear");
}

void vendaVendedorDia(){
    FILE *arquivo_vendedor;
    unsigned long idVendedor;
    char data[11];
    int sair;
    arquivo_vendedor = fopen("vendedor.dat", "rb");

    if (arquivo_vendedor == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }

    do{
        listagemVendedor();
        printf("\nForneca o id do vendedor: ");
        scanf("%lu",&idVendedor);
        if(pesquisaIdVendedor(arquivo_vendedor,idVendedor) == -1){
            printf("\nVendedor Invalido\n");
            pressioneEnter();
            continue;
        }
        printf("\nDigite a data da venda (utilize o seguinte formato dd/mm/aaaa): ");
        setbuf(stdin,NULL);
        gets(data);
        if(consultaVendaDiaVendedor(data,idVendedor)==0){
            printf("\nVendendor nao tem vendas no dia selecionado\n");
            pressioneEnter();
            break;
        }
        else
            system("cls || clear");
            consultaVendaDiaVendedor(data,idVendedor);
            printf("\n");
            pressioneEnter();
            break;


        printf("\nDeseja abandonar a Consulta?\n1-Sim 2-Nao: ");
        scanf("%d", &sair);
    }while(sair!=1);
    fclose(arquivo_vendedor);
    system("cls || clear");
}

void vendaVendedorMes(){
    FILE *arquivo_vendedor;
    unsigned long idVendedor;
    char data[8],dataAux[11];
    int sair;
    arquivo_vendedor = fopen("vendedor.dat", "rb");
    if (arquivo_vendedor == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }

    do{
        listagemVendedor();
        printf("\nForneca o id do vendedor: ");
        scanf("%lu",&idVendedor);
        if(pesquisaIdVendedor(arquivo_vendedor,idVendedor) == -1){
            printf("\nVendedor Invalido\n");
            pressioneEnter();
            continue;
        }
        printf("\nDigite o mes e ano da venda (utilize o seguinte formato mm/aaaa): ");
        setbuf(stdin,NULL);
        gets(data);
        sprintf(dataAux,"01/%s",data);
        if(consultaVendedorMes(dataAux,dataAux,idVendedor) == 0){
            printf("\nVendendor nao tem vendas no mes selecionado\n");
            pressioneEnter();
            break;
        }
        else
            system("cls || clear");
            consultaVendedorMes(dataAux,dataAux,idVendedor);
            printf("\n");
            pressioneEnter();
            break;


        printf("\nDeseja abandonar a Consulta?\n1-Sim 2-Nao: ");
        scanf("%d", &sair);
    }while(sair!=1);
    fclose(arquivo_vendedor);
    system("cls || clear");
}


void maiorVendaVendedorMes(){
    FILE *arquivo_vendedor, *arquivo_notaFiscal;;
    TVendedor vendedor, vendedorMaisVenda;
    char data[8],dataMes[11],dataAux[11],dataAux2[11];
    int sair;
    float maior, soma;
    NotaFiscal notaFiscal;

    arquivo_notaFiscal = fopen("notafiscal.dat", "rb+");
    arquivo_vendedor = fopen("vendedor.dat", "rb");

    if (arquivo_vendedor == NULL || arquivo_notaFiscal == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }
    do{
        system("cls || clear");
        fseek(arquivo_vendedor,0,SEEK_END);
        printf("\nDigite o mes e ano da venda (utilize o seguinte formato mm/aaaa): ");
        setbuf(stdin,NULL);
        gets(data);
        sprintf(dataMes,"01/%s",data);
        maior = 0;
        vendedorMaisVenda.id = -1;

        if(ftell(arquivo_vendedor) > 0){
            rewind(arquivo_vendedor);
            while(fread(&vendedor,sizeof(TVendedor),1,arquivo_vendedor) == 1){
                soma = 0;
                rewind(arquivo_notaFiscal);
                while(fread(&notaFiscal,sizeof(NotaFiscal),1,arquivo_notaFiscal) == 1){
                    strcpy(dataAux, dataMes);
                    strcpy(dataAux2, notaFiscal.dataCompra);
                    if((notaFiscal.idVendedor == vendedor.id) && (intervaloData(dataAux2,dataAux,dataAux,0) == 1)){
                        soma+= notaFiscal.valorTotal;
                    }
                }
                if(maior < soma){
                    maior = soma;
                    vendedorMaisVenda = vendedor;
                }
            }
            if(vendedorMaisVenda.id != -1){
                printf("\n============ VENDEDOR MAIS VENDA MES ===============");
                printf("\nID: %lu",vendedorMaisVenda.id);
                printf("\nNome: %s",vendedorMaisVenda.nome);
                printf("\nCPF: %s",vendedorMaisVenda.cpf);
                printf("\nEmail: %s",vendedorMaisVenda.email);
                printf("\nTelefone: %s",vendedorMaisVenda.telefone);
                printf("\nTotal Vendido R$: %.2f",maior);
                printf("\n====================================================");

            }
            else
                printf("\Nao houve vendas no mes");

        }
        else
            printf("\nSem dados cadastrados");
        printf("\nDeseja abandonar a Consulta?\n1-Sim 2-Nao: ");
        scanf("%d", &sair);
    }while(sair!=1);
    printf("\n");
    fclose(arquivo_vendedor);
    fclose(arquivo_notaFiscal);
    pressioneEnter();
    system("cls || clear");

}

void maiorVendaVendedorPeriodo(){
    FILE *arquivo_vendedor, *arquivo_notaFiscal;;
    TVendedor vendedor, vendedorMaisVenda;
    char dataInicio[11],dataFinal[11],dataAuxInicio[11],dataAuxFim[11],dataAux[11];
    int sair;
    float maior, soma;
    NotaFiscal notaFiscal;

    arquivo_notaFiscal = fopen("notafiscal.dat", "rb+");
    arquivo_vendedor = fopen("vendedor.dat", "rb");

    if (arquivo_vendedor == NULL || arquivo_notaFiscal == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }
    do{
        system("cls || clear");
        fseek(arquivo_vendedor,0,SEEK_END);
        printf("\nDigite a data Inicial da pesquisa (utilize o seguinte formato dd/mm/aaaa): ");
        setbuf(stdin,NULL);
        gets(dataInicio);
        printf("\nDigite a data Final da pesquisa (utilize o seguinte formato dd/mm/aaaa): ");
        setbuf(stdin,NULL);
        gets(dataFinal);
        maior = 0;
        vendedorMaisVenda.id = -1;

        if(ftell(arquivo_vendedor) > 0){
            rewind(arquivo_vendedor);
            while(fread(&vendedor,sizeof(TVendedor),1,arquivo_vendedor) == 1){
                soma = 0;
                rewind(arquivo_notaFiscal);
                while(fread(&notaFiscal,sizeof(NotaFiscal),1,arquivo_notaFiscal) == 1){
                    strcpy(dataAuxInicio, dataInicio);
                    strcpy(dataAux, notaFiscal.dataCompra);
                    strcpy(dataAuxFim, dataFinal);
                    if((notaFiscal.idVendedor == vendedor.id) && (intervaloData(dataAux,dataAuxInicio,dataAuxFim,1) == 1)){
                        soma+= notaFiscal.valorTotal;
                    }
                }
                if(maior < soma){
                    maior = soma;
                    vendedorMaisVenda = vendedor;
                }
            }
            if(vendedorMaisVenda.id != -1){
                printf("\n======== VENDEDOR MAIS VENDA NO PERIODO ============");
                printf("\nID: %lu",vendedorMaisVenda.id);
                printf("\nNome: %s",vendedorMaisVenda.nome);
                printf("\nCPF: %s",vendedorMaisVenda.cpf);
                printf("\nEmail: %s",vendedorMaisVenda.email);
                printf("\nTelefone: %s",vendedorMaisVenda.telefone);
                printf("\nTotal Vendido R$: %.2f",maior);
                printf("\n====================================================");

            }
            else
                printf("\Nao houve vendas no mes");

        }
        else
            printf("\nSem dados cadastrados");
        printf("\nDeseja abandonar a Consulta?\n1-Sim 2-Nao: ");
        scanf("%d", &sair);
    }while(sair!=1);
    printf("\n");
    fclose(arquivo_vendedor);
    fclose(arquivo_notaFiscal);
    pressioneEnter();
    system("cls || clear");

}
