#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "notaCompra.h"
#include "funcoes.h"

struct NotaCompra{
    unsigned long id;
    unsigned long idFornecedor;
    char dataCompra[11];
    float valorTotal;
};

struct ItemNotaCompra{
    unsigned long id;
    unsigned long idProduto;
    unsigned long idNotaCompra;
    unsigned int quantidade;
    float valorUnitario;
};


void gerarNotaCompra(unsigned long idFornecedor, float valorTotal){
    FILE *arquivo_notaCompra;
    NotaCompra notaCompra;
    int gravado,opcao;
    char data[11], dataAuxiliar[11];

    int dia,mes,ano;
    struct tm tempo;
    time_t meuTempo;

    arquivo_notaCompra = fopen("notacompra.dat", "rb+");

    if (arquivo_notaCompra == NULL){
        arquivo_notaCompra = fopen("notacompra.dat", "wb+");
        if (arquivo_notaCompra == NULL){
            printf("Erro na criacao do arquivo!\n");
           pressioneEnter();
            return;
        }
    }

    //Poosiciona no final do arquivo para nao sobreescrever os dados
    fseek(arquivo_notaCompra,0,SEEK_END);
    if(ftell(arquivo_notaCompra) > 0){
        //divide o tamanho total do arquivo pelo tamanho da estrutura e soma 1 para ser o id
        notaCompra.id = (ftell(arquivo_notaCompra))/sizeof(NotaCompra) +1;
    }
    else
        notaCompra.id = 1;

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
            sprintf(notaCompra.dataCompra,"%d0.2/%0.2d/%d",dia,mes,ano);
            break;
        case 2:
            printf("\nDigite a data da compra (utilize as '/' barras): ");
            setbuf(stdin,NULL);
            gets(data);
            strcpy(dataAuxiliar,data);
            while(verificaData(dataAuxiliar)!= 1 || strlen(data) != 10){
                 if(strlen(data) != 10){
                    printf("\nUtilize o seguinte formato xx/xx/xxxx");
                }
                printf("\nData ou formato invalido!!\n\nDigite uma data valida: ");
                gets(data);
                strcpy(dataAuxiliar,data);
            }
            strcpy(notaCompra.dataCompra,data);
            break;
    }

    notaCompra.idFornecedor = idFornecedor;
    notaCompra.valorTotal = valorTotal;


    gravado = fwrite(&notaCompra, sizeof(NotaCompra), 1, arquivo_notaCompra);

    if(gravado != 1){
        printf("Erro na geracao da Nota da Compra!!");
       pressioneEnter();
        return;
    }
    fclose(arquivo_notaCompra);
}

void listarNotaCompra(){
    FILE *arquivo_notaCompra;
    NotaCompra notaCompra;
    arquivo_notaCompra = fopen("notacompra.dat", "rb+");

    if (arquivo_notaCompra == NULL){
            printf("Erro na abertura do arquivo!\n");
           pressioneEnter();
            return;
    }
    system("cls || clear");
    printf("\n================= NOTAS COMPRA ====================");
    while(fread(&notaCompra,sizeof(NotaCompra),1,arquivo_notaCompra) == 1){
        printf("\nID: %lu",notaCompra.id);
        printf("\nID Fornecedor: %lu",notaCompra.idFornecedor);
        printf("\nData compra: %s",notaCompra.dataCompra);
        printf("\nValor Total: R$%.2f",notaCompra.valorTotal);
        printf("\n====================================================");
    }
    fclose(arquivo_notaCompra);
}


void registroItemNotaCompra(unsigned long idProduto,unsigned int quantidade,float valorUnitario){
    FILE *arquivo_itemNotaCompra, *arquivo_notaCompra;
    ItemNotaCompra itemCompra;
    int gravado;

    arquivo_itemNotaCompra = fopen("itemnotacompra.dat","rb+");
    arquivo_notaCompra = fopen("notacompra.dat","rb+");

    if(arquivo_notaCompra == NULL){
         printf("Erro na abertura do arquivo!\n");
           pressioneEnter();
            return;
    }
    else if (arquivo_itemNotaCompra == NULL){
        arquivo_itemNotaCompra = fopen("itemnotacompra.dat", "wb+");
        if (arquivo_itemNotaCompra == NULL){
            printf("Erro na criacao do arquivo!\n");
           pressioneEnter();
            return;
        }
    }
    fseek(arquivo_itemNotaCompra,0,SEEK_END);
    if(ftell(arquivo_itemNotaCompra) > 0){
        //divide o tamanho total do arquivo pelo tamanho da estrutura e soma 1 para ser o id
       itemCompra.id = (ftell(arquivo_itemNotaCompra))/sizeof(ItemNotaCompra) +1;
    }
    else
        itemCompra.id = 1;

    //Poosiciona no final do arquivo para nao sobreescrever os dados
    fseek(arquivo_notaCompra,0,SEEK_END);
    if(ftell(arquivo_notaCompra) > 0){
        //divide o tamanho total do arquivo pelo tamanho da estrutura e soma 1 para ser o id
        itemCompra.idNotaCompra = (ftell(arquivo_notaCompra))/sizeof(NotaCompra);
    }
    else
        itemCompra.idNotaCompra = 1;
    itemCompra.idProduto = idProduto;
    itemCompra.quantidade = quantidade;
    itemCompra.valorUnitario = valorUnitario;

    gravado = fwrite(&itemCompra, sizeof(ItemNotaCompra), 1, arquivo_itemNotaCompra);

    if(gravado != 1){
        printf("Erro na geracao da Nota Fiscal!!");
        pressioneEnter();
        return;
    }
    fclose(arquivo_itemNotaCompra);
    fclose(arquivo_notaCompra);
}

int consultarIdNotaCompra(unsigned long id){
    FILE *arquivo_notaCompra;
    NotaCompra notaCompra;
    arquivo_notaCompra = fopen("notacompra.dat", "rb+");

    if (arquivo_notaCompra == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return 0;
    }
    system("cls || clear");
    printf("\n=================== NOTA COMPRA ====================");
    while(fread(&notaCompra,sizeof(NotaCompra),1,arquivo_notaCompra) == 1){
        if(notaCompra.id == id){
            printf("\nID: %lu",notaCompra.id);
            printf("\nID Fornecedor: %lu",notaCompra.idFornecedor);
            printf("\nData compra: %s",notaCompra.dataCompra);
            printf("\nValor Total: R$%.2f",notaCompra.valorTotal);
            printf("\n====================================================");
            fclose(arquivo_notaCompra);
            return 1;
        }
    }
    fclose(arquivo_notaCompra);
    return 0;
}

void consultarItemNotaCompra(unsigned long id){
    FILE *arquivo_itemNotaCompra;
    ItemNotaCompra itemCompra;

    arquivo_itemNotaCompra = fopen("itemnotacompra.dat", "rb+");

    if (arquivo_itemNotaCompra == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }
    printf("\n=============== ITEM NOTA COMPRA ===================");
    while(fread(&itemCompra,sizeof(ItemNotaCompra),1,arquivo_itemNotaCompra) == 1){
        if(id == itemCompra.idNotaCompra){
            printf("\nID: %lu",itemCompra.id);
            printf("\nID Produto: %lu",itemCompra.idProduto);
            printf("\nID Nota Compra: %lu",itemCompra.idNotaCompra);
            printf("\nQuantidae: %u",itemCompra.quantidade);
            printf("\nValor Unitario: R$%.2f",itemCompra.valorUnitario);
            printf("\n====================================================");
    }
    }
    fclose(arquivo_itemNotaCompra);
}
