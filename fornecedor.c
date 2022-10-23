#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fornecedor.h"
#include "funcoes.h"

struct TFornecedor{
    unsigned long id;
    char cnpj[15];
    char nome[100];
    char email[50];
    char telefone[15];
};


int pesquisaNomeFornecedor(FILE *a,char *nome){
    TFornecedor fornecedor;
    int posicao=0;
    //posicionando no início do arquivo
    rewind(a);
    while(fread(&fornecedor,sizeof(TFornecedor),1,a)==1){
        if(strcmp(fornecedor.nome,nome) == 0)
          return posicao;
        else
            posicao++;
    }
    return -1;
}

int pesquisaFornecedorCNPJ(FILE *a,char *cnpj){
    int posicao=0;
    TFornecedor fornecedor;
    //posicionando no início do arquivo
    rewind(a);
    while(fread(&fornecedor,sizeof(TFornecedor),1,a)==1){
        if(strcmp(fornecedor.cnpj,cnpj) == 0)
          return posicao;
        else
           posicao++;
    }
    return -1;
}

int pesquisaIdFornecedor(FILE *a,int id){
    int posicao=0;
    TFornecedor fornecedor;
    //posicionando no início do arquivo
    rewind(a);
    while(fread(&fornecedor,sizeof(TFornecedor),1,a)==1){
        if(fornecedor.id == id)
          return posicao;
        else
           posicao++;
    }
    return -1;
}

int pesquisaPrefixoNomeFornecedor(FILE *a,char *prefixo){
    int posicao=0;
    char *ponteiro;
    TFornecedor fornecedor;
    //posicionando no início do arquivo
    rewind(a);
    while(fread(&fornecedor,sizeof(TFornecedor),1,a)==1){
        //verificando se o nome possui a substring prefixo
        ponteiro = strstr(fornecedor.nome, prefixo);
        if(ponteiro)
             return posicao;
        else
            posicao++;
    }
    return -1;
}

void menuFornecedor(){
    int opcao;
    do{
        printf("\n--------------MANUTENCAO FORNECEDORES---------------\n");
        printf("\n1- Cadastro de fornecedor\n2- Listagem fornecedores\n3- Consulta fornecedor \n4- Alteracaoo fornecedores\n5- Voltar ao menu principal\n");
        printf("Selecione a opcao Desejada: ");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                system("cls || clear");
                cadastroFornecedor();
                break;
            case 2:
                system("cls || clear");
                listagemFornecedor();
                break;
            case 3:
                system("cls || clear");
                consultaFornecedor();
                break;
            case 4:
                system("cls || clear");
                alterarFornecedor();
                break;
        }
    }while(opcao!=5);
    system("cls || clear");
}

void cadastroFornecedor(){
    FILE *arquivo_fornecedor;
    TFornecedor fornecedor;
    int sair,gravado,pesquisa;
    arquivo_fornecedor = fopen("fornecedor.dat", "rb+");

    if (arquivo_fornecedor == NULL){
        arquivo_fornecedor = fopen("fornecedor.dat", "wb+");
        if (arquivo_fornecedor == NULL){
            printf("Erro na criacao do arquivo!\n");
            pressioneEnter();
            return;
        }
    }
    do{

        fseek(arquivo_fornecedor,0,SEEK_END);
        if(ftell(arquivo_fornecedor) > 0){
            //divide o tamanho total do arquivo pelo tamanho da estrutura e soma 1 para ser o id
            fornecedor.id = (ftell(arquivo_fornecedor))/sizeof(TFornecedor) +1;
        }
        else
            fornecedor.id = 1;

        printf("\n=============== CADASTRO FORNECEDORES ==============\n");
        printf("Forneca seu CNPJ: ");
        setbuf(stdin,NULL);
        gets(fornecedor.cnpj);
        pesquisa = pesquisaFornecedorCNPJ(arquivo_fornecedor, fornecedor.cnpj);
        while(validarCNPJ(fornecedor.cnpj) != 1 || pesquisa != -1){
            if(pesquisa != -1)
                printf("\nCNPJ ja e registrado no sistema");
            else
                printf("\nCNPJ INVALIDO");
            printf("\nForneca um CNPJ valido: ");
            setbuf(stdin,NULL);
            gets(fornecedor.cnpj);
            pesquisa = pesquisaFornecedorCNPJ(arquivo_fornecedor, fornecedor.cnpj);
        }

        printf("Forneca o nome: ");
        setbuf(stdin,NULL);
        fgets(fornecedor.nome,100,stdin);
        retiraEnter(fornecedor.nome);
        maiuscSemAcento(fornecedor.nome);
        while(pesquisaNomeFornecedor(arquivo_fornecedor,fornecedor.nome) != -1){
            printf("\nNome ja registrado no sistema!!\nForneca um nome valido: ");
            setbuf(stdin, NULL);
            fgets(fornecedor.nome, 100, stdin);
            retiraEnter(fornecedor.nome);
            maiuscSemAcento(fornecedor.nome);

        }

        printf("Forneca seu E-mail: ");
        setbuf(stdin, NULL);
        fgets(fornecedor.email, 50, stdin);
        retiraEnter(fornecedor.email);
        maiuscSemAcento(fornecedor.email);

        printf("Forneca seu Telefone: ");
        setbuf(stdin, NULL);
        fgets(fornecedor.telefone, 15, stdin);
        retiraEnter(fornecedor.telefone);
        maiuscSemAcento(fornecedor.telefone);

        gravado = fwrite(&fornecedor, sizeof(TFornecedor), 1, arquivo_fornecedor);

        if(gravado != 1){
            printf("Erro na escrita do cadastro do Fornecedor!!");
           pressioneEnter();
            return;
        }

        printf("\nDeseja abandonar o Cadastro?\n1-Sim 2-Nao: ");
        scanf("%d", &sair);
    } while (sair != 1);
    fclose(arquivo_fornecedor);
}

void listagemFornecedor(){
    FILE *arquivo_fornecedor;
    TFornecedor fornecedor;
    arquivo_fornecedor = fopen("fornecedor.dat", "rb");

    if (arquivo_fornecedor == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }
    system("cls || clear");
    fseek(arquivo_fornecedor,0,SEEK_END);
    if(ftell(arquivo_fornecedor) > 0){
        rewind(arquivo_fornecedor);
        printf("\n============== LISTAGEM FORNECEDORES ===============");
        while(fread(&fornecedor,sizeof(TFornecedor),1,arquivo_fornecedor) == 1){
            printf("\nID: %lu",fornecedor.id);
            printf("\nCNPJ: %s",fornecedor.cnpj);
            printf("\nNome: %s",fornecedor.nome);
            printf("\nEmail: %s",fornecedor.email);
            printf("\nTelefone: %s",fornecedor.telefone);
            printf("\n====================================================");
        }
    }
    else
        printf("\nSem dados de Fornecedores cadastrados");
    printf("\n");
    fclose(arquivo_fornecedor);
    pressioneEnter();

}

void consultaFornecedor(){
    FILE *arquivo_fornecedor;
    TFornecedor fornecedor;
    int consulta,posicao,sair;
    unsigned long id;
    char cnpj[16],prefixo[100];
    arquivo_fornecedor = fopen("fornecedor.dat", "rb");

    if (arquivo_fornecedor == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }
    do{
        printf("\n1- Para consulta por ID \n2- Para consulta por CNPJ \n3- Para consulta por nome\n");
        printf("Selecione a opcao Desejada: ");
        scanf("%d",&consulta);
        switch(consulta){
            case 1:
                printf("Forneca o ID que desaja consultar: ");
                scanf("%lu",&id);
                posicao = pesquisaIdFornecedor(arquivo_fornecedor, id);
                break;
            case 2:
                printf("Forneca o CNPJ que deseja consultar: ");
                setbuf(stdin,NULL);
                fgets(cnpj,16,stdin);
                retiraEnter(cnpj);
                posicao = pesquisaFornecedorCNPJ(arquivo_fornecedor, cnpj);
                break;
            case 3:
                printf("Forneca o nome: ");
                setbuf(stdin,NULL);
                fgets(prefixo,100,stdin);
                retiraEnter(prefixo);
                maiuscSemAcento(prefixo);
                posicao = pesquisaPrefixoNomeFornecedor(arquivo_fornecedor, prefixo);

        }
        system("cls || clear");
        if(ftell(arquivo_fornecedor) > 0 && posicao != -1){
                fseek(arquivo_fornecedor,posicao*sizeof(TFornecedor),SEEK_SET);
                fread(&fornecedor,sizeof(TFornecedor),1,arquivo_fornecedor);
                printf("\n=============== CONSULTA FORNECEDORES ===============");
                printf("\nID: %lu",fornecedor.id);
                printf("\nCNPJ: %s",fornecedor.cnpj);
                printf("\nNome: %s",fornecedor.nome);
                printf("\nEmail: %s",fornecedor.email);
                printf("\nTelefone: %s",fornecedor.telefone);
                printf("\n=====================================================");
        }
        else{
            printf("\nDados do fornecedor inexistente");
            printf("\n");
        }
        printf("\nDeseja abandonar a consulta?\n1-Sim 2-Nao: ");
        scanf("%d",&sair);

    }while(sair!=1);
    fclose(arquivo_fornecedor);
    pressioneEnter();
}

void alterarFornecedor(){
    FILE *arquivo_fornecedor;
    TFornecedor fornecedor;
    int consulta,posicao,sair,pesquisa;
    unsigned long id;
    char cnpj[16],prefixo[100];
    arquivo_fornecedor = fopen("fornecedor.dat", "rb+");

    if (arquivo_fornecedor == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }
    do{
        printf("\n1- Para alterar por ID \n2- Para alterar por CNPJ \n3- Para alterar por nome\n");
        printf("Selecione a opcao Desejada: ");
        scanf("%d",&consulta);
        switch(consulta){
            case 1:
                printf("Forneca o ID que desaja alterar: ");
                scanf("%lu",&id);
                posicao = pesquisaIdFornecedor(arquivo_fornecedor, id);
                break;
            case 2:
                printf("Fornca o CNPJ do usuario que deseja alterar: ");
                setbuf(stdin,NULL);
                fgets(cnpj,16,stdin);
                retiraEnter(cnpj);
                posicao = pesquisaFornecedorCNPJ(arquivo_fornecedor, cnpj);
                break;
            case 3:
                printf("Forneca o nome: ");
                setbuf(stdin,NULL);
                fgets(prefixo,100,stdin);
                retiraEnter(prefixo);
                maiuscSemAcento(prefixo);
                posicao = pesquisaPrefixoNomeFornecedor(arquivo_fornecedor, prefixo);

        }
        if(ftell(arquivo_fornecedor) > 0  && posicao != -1){
            printf("\n============== ALTERACAO FORNECEDOR ================\n");
            printf("Forneca seu CNPJ:");
            setbuf(stdin, NULL);
            gets(fornecedor.cnpj);
            pesquisa = pesquisaFornecedorCNPJ(arquivo_fornecedor,fornecedor.cnpj);
            while(validarCNPJ(fornecedor.cnpj) != 1 ||pesquisa != -1){
                if(pesquisa == posicao)
                    break;
                else if(pesquisa != -1)
                    printf("\nCNPJ ja e registrado no sistema");
                else
                    printf("\nCNPJ INVALIDO");
                printf("\nForneca um CNPJ valido: ");
                setbuf(stdin, NULL);
                gets(fornecedor.cnpj);
                pesquisa = pesquisaFornecedorCNPJ(arquivo_fornecedor,fornecedor.cnpj);
            }

            printf("Forneca o nome:");
            setbuf(stdin, NULL);
            fgets(fornecedor.nome,100,stdin);
            retiraEnter(fornecedor.nome);
            maiuscSemAcento(fornecedor.nome);

            pesquisa = pesquisaNomeFornecedor(arquivo_fornecedor, fornecedor.nome);
            while(pesquisa != -1 && pesquisa != posicao){
                if(pesquisa != -1)
                    printf("\nNome ja registrado no sistema");
                printf("\nForneca um nome valido: ");
                setbuf(stdin, NULL);
                fgets(fornecedor.nome,100,stdin);
                retiraEnter(fornecedor.nome);
                maiuscSemAcento(fornecedor.nome);
                pesquisa = pesquisaNomeFornecedor(arquivo_fornecedor, fornecedor.nome);
            }

            printf("Forneca seu E-mail: ");
            setbuf(stdin, NULL);
            fgets(fornecedor.email, 50, stdin);
            retiraEnter(fornecedor.email);
            maiuscSemAcento(fornecedor.email);

            printf("Forneca seu Telefone: ");
            setbuf(stdin, NULL);
            fgets(fornecedor.telefone, 15, stdin);
            retiraEnter(fornecedor.telefone);
            maiuscSemAcento(fornecedor.telefone);

            fseek(arquivo_fornecedor,posicao*sizeof(TFornecedor),SEEK_SET);
            fornecedor.id = (ftell(arquivo_fornecedor))/sizeof(TFornecedor) +1;
            fwrite(&fornecedor, sizeof(TFornecedor),1,arquivo_fornecedor);
            printf("\n=====================================================");
        }
        else
            printf("\nSem dados do Fornecedor cadastrados");
        printf("\nDeseja sair da alteracao?\n1-Sim 2-Nao: ");
        scanf("%d",&sair);


    }while(sair!=1);
    printf("\n");
    fclose(arquivo_fornecedor);
    pressioneEnter();
}
