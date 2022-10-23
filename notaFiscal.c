#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "notaFiscal.h"
#include "funcoes.h"

struct ItemNotaFiscal{
    unsigned long id;
    unsigned long idNotaFiscal;
    unsigned long idProduto;
    float valorVenda;
    unsigned int quantidade;
};

void gerarNotaFiscal(unsigned long idCliente, unsigned long idVendedor, float valorTotal){
    FILE *arquivo_notaFiscal;
    NotaFiscal notaFiscal;
    int gravado,opcao;
    char data[11], dataAuxiliar[11];

    int dia,mes,ano;
    struct tm tempo;
    time_t meuTempo;

    arquivo_notaFiscal = fopen("notafiscal.dat", "rb+");

    if (arquivo_notaFiscal == NULL){
        arquivo_notaFiscal = fopen("notafiscal.dat", "wb+");
        if (arquivo_notaFiscal == NULL){
            printf("Erro na criacao do arquivo!\n");
            pressioneEnter();
            return;
        }
    }

    //Poosiciona no final do arquivo para nao sobreescrever os dados
    fseek(arquivo_notaFiscal,0,SEEK_END);
    if(ftell(arquivo_notaFiscal) > 0){
        //divide o tamanho total do arquivo pelo tamanho da estrutura e soma 1 para ser o id
        notaFiscal.id = (ftell(arquivo_notaFiscal))/sizeof(NotaFiscal) +1;
    }
    else
        notaFiscal.id = 1;

    time(&meuTempo);
    tempo = *localtime(&meuTempo);
    dia = tempo.tm_mday;
    mes = tempo.tm_mon + 1;
    ano = tempo.tm_year + 1900;

    printf("\nDeseja manter a data da compra %0.2d/%0.2d/%d ou deseja alterar?",dia,mes,ano);
    printf("\n\n1- Manter\n2- Alterar\n\nSelecione a opcao desejada: ");
    scanf("%d",&opcao);

    switch(opcao){
        case 1:
            sprintf(notaFiscal.dataCompra,"%0.2d/%0.2d/%d",dia,mes,ano);
            break;
        case 2:
            printf("\nDigite a data da compra (utilize as '/' barras): ");
            setbuf(stdin,NULL);
            gets(data);
            strcpy(dataAuxiliar,data);
            while(verificaData(dataAuxiliar)!= 1 || strlen(data) != 10){
                 if(strlen(data) != 10){
                    printf("\nUtilize o seguinte formato dd/mm/aaaa");
                }
                printf("\nData ou formato invalido!!\n\nDigite uma data valida: ");
                gets(data);
                strcpy(dataAuxiliar,data);
            }
            strcpy(notaFiscal.dataCompra,data);
            break;
    }

    notaFiscal.idCliente = idCliente;
    notaFiscal.idVendedor = idVendedor;
    notaFiscal.valorTotal = valorTotal;

    gravado = fwrite(&notaFiscal, sizeof(NotaFiscal), 1, arquivo_notaFiscal);

    if(gravado != 1){
        printf("Erro na geracao da Nota Fiscal!!");
        pressioneEnter();
        return;
    }

    fclose(arquivo_notaFiscal);
}

void listarNotaFiscal(){
    FILE *arquivo_notaFiscal;
    NotaFiscal notaFiscal;
    arquivo_notaFiscal = fopen("notafiscal.dat", "rb+");

    if (arquivo_notaFiscal == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }
    system("cls || clear");
    printf("\n================= NOTAS FISCAIS ====================");
    while(fread(&notaFiscal,sizeof(NotaFiscal),1,arquivo_notaFiscal) == 1){
        printf("\nID: %lu",notaFiscal.id);
        printf("\nID Cliente: %lu",notaFiscal.idCliente);
        printf("\nID Vendedor: %lu",notaFiscal.idVendedor);
        printf("\nData compra: %s",notaFiscal.dataCompra);
        printf("\nValor Total: R$%.2f",notaFiscal.valorTotal);
        printf("\n====================================================");
    }
    fclose(arquivo_notaFiscal);
}

int consultaIdNotaFiscal(unsigned long id){
    FILE *arquivo_notaFiscal;
    NotaFiscal notaFiscal;
    arquivo_notaFiscal = fopen("notafiscal.dat", "rb+");

    if (arquivo_notaFiscal == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return 0;
    }
    system("cls || clear");
    rewind(arquivo_notaFiscal);
    while(fread(&notaFiscal,sizeof(NotaFiscal),1,arquivo_notaFiscal) == 1){
        if(notaFiscal.id == id){
            printf("\n================= NOTA FISCAL ======================");
            printf("\nID: %lu",notaFiscal.id);
            printf("\nID Cliente: %lu",notaFiscal.idCliente);
            printf("\nID Vendedor: %lu",notaFiscal.idVendedor);
            printf("\nData compra: %s",notaFiscal.dataCompra);
            printf("\nValor Total: R$%.2f",notaFiscal.valorTotal);
            printf("\n====================================================");
            fclose(arquivo_notaFiscal);
            return 1;
        }
    }
    fclose(arquivo_notaFiscal);
    return 0;


}


void registroItemNotaFiscal(unsigned long idProduto, unsigned int quantidadeVendida, float valorVenda){
    FILE *arquivo_itemNotaFiscal, *arquivo_notaFiscal;
    ItemNotaFiscal itemNota;
    NotaFiscal NotaFiscal;
    int gravado;



    arquivo_itemNotaFiscal = fopen("itemnotafiscal.dat", "rb+");
    arquivo_notaFiscal = fopen("notafiscal.dat", "rb+");

    if(arquivo_notaFiscal == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }
    else if (arquivo_itemNotaFiscal == NULL){
        arquivo_itemNotaFiscal = fopen("itemnotafiscal.dat", "wb+");
        if (arquivo_itemNotaFiscal == NULL){
            printf("Erro na criacao do arquivo!\n");
            pressioneEnter();
            return;
        }
    }
    fseek(arquivo_itemNotaFiscal,0,SEEK_END);
    if(ftell(arquivo_itemNotaFiscal) > 0){
        //divide o tamanho total do arquivo pelo tamanho da estrutura e soma 1 para ser o id
       itemNota.id = (ftell(arquivo_itemNotaFiscal))/sizeof(ItemNotaFiscal) +1;
    }
    else
         itemNota.id =1;

    //Poosiciona no final do arquivo para nao sobreescrever os dados
    fseek(arquivo_notaFiscal,0,SEEK_END);
    if(ftell(arquivo_notaFiscal) > 0){
        //divide o tamanho total do arquivo pelo tamanho da estrutura e soma 1 para ser o id
        itemNota.idNotaFiscal = (ftell(arquivo_notaFiscal))/sizeof(NotaFiscal);
    }
    else
        itemNota.idNotaFiscal = 1;
    itemNota.idProduto = idProduto;
    itemNota.quantidade = quantidadeVendida;
    itemNota.valorVenda = valorVenda;

    gravado = fwrite(&itemNota, sizeof(ItemNotaFiscal), 1, arquivo_itemNotaFiscal);

    if(gravado != 1){
        printf("Erro na geracao da Nota Fiscal!!");
        pressioneEnter();
        return;
    }
    fclose(arquivo_itemNotaFiscal);
    fclose(arquivo_notaFiscal);
}

void consultaItemsNotaFiscal(unsigned long id){
    FILE *arquivo_itemNotaFiscal;
    ItemNotaFiscal itemNota;

    arquivo_itemNotaFiscal = fopen("itemnotafiscal.dat", "rb+");

    if (arquivo_itemNotaFiscal == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }
    printf("\n=============== ITEM NOTA FISCAL ===================");
    while(fread(&itemNota,sizeof(ItemNotaFiscal),1,arquivo_itemNotaFiscal) == 1){
        if(id == itemNota.idNotaFiscal){
            printf("\nID: %lu",itemNota.id);
            printf("\nID Nota Fiscal: %lu",itemNota.idNotaFiscal);
            printf("\nID Produto: %lu",itemNota.idProduto);
            printf("\nQuantidae: %u",itemNota.quantidade);
            printf("\nValor Venda: R$%.2f",itemNota.valorVenda);
            printf("\n====================================================");
        }
    }
    fclose(arquivo_itemNotaFiscal);
}

 int consultaCompraDataCliente(char *data,unsigned int idCliente){
    FILE *arquivo_notaFiscal;
    NotaFiscal notaFiscal;
    int cont = 0;
    arquivo_notaFiscal = fopen("notafiscal.dat", "rb+");

    if (arquivo_notaFiscal == NULL){
            printf("Erro na abertura do arquivo!\n");
           pressioneEnter();
            return cont;
    }
    system("cls || clear");
    printf("\n================= NOTAS FISCAIS ====================");
    while(fread(&notaFiscal,sizeof(NotaFiscal),1,arquivo_notaFiscal) == 1){
        if(notaFiscal.idCliente == idCliente && strcmp(notaFiscal.dataCompra,data) == 0){
            printf("\nID: %lu",notaFiscal.id);
            printf("\nID Cliente: %lu",notaFiscal.idCliente);
            printf("\nID Vendedor: %lu",notaFiscal.idVendedor);
            printf("\nData compra: %s",notaFiscal.dataCompra);
            printf("\nValor Total: R$%.2f",notaFiscal.valorTotal);
            printf("\n====================================================");
            consultaItemsNotaFiscal(notaFiscal.id);
            cont++;

        }
    }
    fclose(arquivo_notaFiscal);
    return cont;
}

int consultaVendaDiaVendedor(char *data,unsigned int idVendedor){
    FILE *arquivo_notaFiscal;
    NotaFiscal notaFiscal;
    int cont = 0;
    arquivo_notaFiscal = fopen("notafiscal.dat", "rb+");

    if (arquivo_notaFiscal == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return cont;
    }
    system("cls || clear");
    printf("\n================= VENDA VENDEDOR ====================");
    while(fread(&notaFiscal,sizeof(NotaFiscal),1,arquivo_notaFiscal) == 1){
        if(notaFiscal.idVendedor == idVendedor && strcmp(notaFiscal.dataCompra,data) == 0){
            printf("\nID: %lu",notaFiscal.id);
            printf("\nID Cliente: %lu",notaFiscal.idCliente);
            printf("\nID Vendedor: %lu",notaFiscal.idVendedor);
            printf("\nData compra: %s",notaFiscal.dataCompra);
            printf("\nValor Total: R$%.2f",notaFiscal.valorTotal);
            printf("\n====================================================");
            consultaItemsNotaFiscal(notaFiscal.id);
            cont++;

        }
    }
    fclose(arquivo_notaFiscal);
    return cont;
}

int consultaCompraDataClientePeriodo(char *dataInicio,char *dataFinal,unsigned long idCliente){
    FILE *arquivo_notaFiscal;
    NotaFiscal notaFiscal;
    char dataAux[11];
    int cont = 0;
    arquivo_notaFiscal = fopen("notafiscal.dat", "rb+");

    if (arquivo_notaFiscal == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return cont;
    }
    system("cls || clear");
    while(fread(&notaFiscal,sizeof(NotaFiscal),1,arquivo_notaFiscal) == 1){
        strcpy(dataAux, notaFiscal.dataCompra);
        if((notaFiscal.idCliente == idCliente) && (intervaloData(dataAux,dataInicio,dataFinal,1) == 1)){
            printf("\n================= NOTAS FISCAIS ====================");
            printf("\nID: %lu",notaFiscal.id);
            printf("\nID Cliente: %lu",notaFiscal.idCliente);
            printf("\nID Vendedor: %lu",notaFiscal.idVendedor);
            printf("\nData compra: %s",notaFiscal.dataCompra);
            printf("\nValor Total: R$%.2f",notaFiscal.valorTotal);
            printf("\n====================================================");
            consultaItemsNotaFiscal(notaFiscal.id);
            cont++;

        }
    }
    fclose(arquivo_notaFiscal);
    return cont;
}

int consultaVendedorMes(char *dataInicio,char *dataFinal,unsigned long idVendedor){
    FILE *arquivo_notaFiscal;
    NotaFiscal notaFiscal;
    char dataAux[11],dataAux2[11];
    int cont = 0;
    arquivo_notaFiscal = fopen("notafiscal.dat", "rb+");

    if (arquivo_notaFiscal == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return cont;
    }
    system("cls || clear");
    strcpy(dataAux, dataInicio);
    while(fread(&notaFiscal,sizeof(NotaFiscal),1,arquivo_notaFiscal) == 1){
        strcpy(dataAux, dataInicio);
        strcpy(dataAux2, notaFiscal.dataCompra);
        if((notaFiscal.idVendedor == idVendedor) && (intervaloData(dataAux2,dataAux,dataAux,0) == 1)){
            printf("\n================= NOTAS FISCAIS ====================");
            printf("\nID: %lu",notaFiscal.id);
            printf("\nID Cliente: %lu",notaFiscal.idCliente);
            printf("\nID Vendedor: %lu",notaFiscal.idVendedor);
            printf("\nData compra: %s",notaFiscal.dataCompra);
            printf("\nValor Total: R$%.2f",notaFiscal.valorTotal);
            printf("\n====================================================");
            consultaItemsNotaFiscal(notaFiscal.id);
            cont++;

        }
    }
    fclose(arquivo_notaFiscal);
    return cont;
}
