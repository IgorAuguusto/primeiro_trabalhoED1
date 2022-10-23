#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendedor.h"
#include "funcoes.h"

int pesquisaVendedorCPF(FILE *a,char *cpf){
    int posicao=0;
    TVendedor vendedor;
    //posicionando no início do arquivo
    rewind(a);
    while(fread(&vendedor,sizeof(TVendedor),1,a)==1){
        if(strcmp(vendedor.cpf,cpf) == 0)
          return posicao;
        else
           posicao++;
    }
    return -1;
}

int validarEmailVendedor(FILE *a,char *email){
    TVendedor vendedor;
    int posicao=0;
    //posicionando no início do arquivo
    rewind(a);
    while(fread(&vendedor,sizeof(TVendedor),1,a)==1){
        if(strcmp(vendedor.email,email) == 0)
          return posicao;
        else
            posicao++;
    }
    return -1;
}

int pesquisaPrefixoNomeVendedor(FILE *a,char *prefixo){
    int posicao=0;
    char *ponteiro;
    TVendedor vendedor;
    //posicionando no início do arquivo
    rewind(a);
    while(fread(&vendedor,sizeof(TVendedor),1,a)==1){
        //verificando se o nome possui a substring prefixo
        ponteiro = strstr(vendedor.nome, prefixo);
        if(ponteiro)
             return posicao;
        else
            posicao++;
    }
    return -1;
}

int pesquisaIdVendedor(FILE *a,int id){
    int posicao=0;
    TVendedor vendedor;
    //posicionando no início do arquivo
    rewind(a);
    while(fread(&vendedor,sizeof(TVendedor),1,a)==1){
        if(vendedor.id == id)
          return posicao;
        else
           posicao++;
    }
    return -1;
}

void menuVendedor(){
    int opcao;
    do{
        printf("\n----------------MANUTENCAO VENDEDORES---------------\n");
        printf("\n1- Cadastro de Vendedor\n2- Listagem de Vendedor\n3- Consulta de Vendedor\n4- Alteracaoo de Vendedor\n5- Voltar ao menu principal\n");
        printf("Selecione a opcao Desejada: ");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                system("cls || clear");
                cadastroVendedor();
                break;
            case 2:
                system("cls || clear");
                listagemVendedor();
                break;
            case 3:
                system("cls || clear");
                consultaVendedor();
                break;
            case 4:
                system("cls || clear");
                alterarVendedor();
                break;
        }
    }while(opcao!=5);
    system("cls || clear");
}

void cadastroVendedor(){
    FILE *arquivo_vendedor;
    TVendedor vendedor;
    int sair,gravado,pesquisa;
    arquivo_vendedor = fopen("vendedor.dat", "rb+");

    if (arquivo_vendedor == NULL){
        arquivo_vendedor = fopen("vendedor.dat", "wb+");
        if (arquivo_vendedor == NULL){
            printf("Erro na criacao do arquivo!\n");
            pressioneEnter();
            return;
        }
    }
    do{

        fseek(arquivo_vendedor,0,SEEK_END);
        if(ftell(arquivo_vendedor) > 0){
            //divide o tamanho total do arquivo pelo tamanho da estrutura e soma 1 para ser o id
            vendedor.id = (ftell(arquivo_vendedor))/sizeof(TVendedor) +1;
        }
        else
            vendedor.id = 1;
        printf("\n================ CADASTRO VENDEDORES ===============\n");
        printf("Forneca o nome: ");
        setbuf(stdin, NULL);
        fgets(vendedor.nome, 100, stdin);
        retiraEnter(vendedor.nome);
        maiuscSemAcento(vendedor.nome);


        printf("Forneca seu cpf: ");
        setbuf(stdin, NULL);
        gets(vendedor.cpf);
        pesquisa = pesquisaVendedorCPF(arquivo_vendedor, vendedor.cpf);
        while(validarCPF(vendedor.cpf) != 1 || pesquisa != -1){
            if(pesquisa != -1)
                printf("\nCPF ja registrado no sistema!!");
            else
                printf("\nCPF INVALIDO");
            printf("\nForneca um CPF valido: ");
            setbuf(stdin, NULL);
            gets(vendedor.cpf);
            pesquisa = pesquisaVendedorCPF(arquivo_vendedor, vendedor.cpf);
        }
        printf("Forneca seu E-mail: ");
        setbuf(stdin, NULL);
        fgets(vendedor.email, 50, stdin);
        retiraEnter(vendedor.email);
        maiuscSemAcento(vendedor.email);
        while(validarEmailVendedor(arquivo_vendedor,vendedor.email) != -1){
            printf("\nEmail ja registrado no sistema!!\nForneca um E-mail valido: ");
            setbuf(stdin, NULL);
            fgets(vendedor.email, 50, stdin);
            retiraEnter(vendedor.email);
            maiuscSemAcento(vendedor.email);

        }

        printf("Forneca seu Telefone: ");
        setbuf(stdin, NULL);
        fgets(vendedor.telefone, 15, stdin);
        retiraEnter(vendedor.telefone);
        maiuscSemAcento(vendedor.telefone);

        printf("Crie uma senha: ");
        setbuf(stdin, NULL);
        fgets(vendedor.password, 20, stdin);
        retiraEnter(vendedor.password);
        maiuscSemAcento(vendedor.password);

        gravado = fwrite(&vendedor, sizeof(TVendedor), 1, arquivo_vendedor);

        if(gravado != 1){
            printf("Erro na escrita do cadastro do cliente!!");
            pressioneEnter();
            return;
        }

        printf("\nDeseja abandonar o Cadastro?\n1-Sim 2-Nao: ");
        scanf("%d", &sair);
    } while (sair != 1);
    fclose(arquivo_vendedor);
}

void listagemVendedor(){
    FILE *arquivo_vendedor;
    TVendedor vendedor;
    arquivo_vendedor = fopen("vendedor.dat", "rb");

    if (arquivo_vendedor == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }
    system("cls || clear");
    fseek(arquivo_vendedor,0,SEEK_END);
    if(ftell(arquivo_vendedor) > 0){
        rewind(arquivo_vendedor);
        printf("\n============== LISTAGEM VENDEDORES =================");
        while(fread(&vendedor,sizeof(TVendedor),1,arquivo_vendedor) == 1){
            printf("\nID: %lu",vendedor.id);
            printf("\nNome: %s",vendedor.nome);
            printf("\nCPF: %s",vendedor.cpf);
            printf("\nEmail: %s",vendedor.email);
            printf("\nTelefone: %s",vendedor.telefone);
            printf("\nSenha Vendedor: %s",vendedor.password);
            printf("\n====================================================");
        }
    }
    else
        printf("\nSem dados cadastrados");
    printf("\n");
    fclose(arquivo_vendedor);
    pressioneEnter();

}

void consultaVendedor(){
    FILE *arquivo_vendedor;
    TVendedor vendedor;
    int consulta,id,posicao,sair;
    char cpf[13],prefixo[100];
    arquivo_vendedor = fopen("vendedor.dat", "rb");

    if (arquivo_vendedor == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }
    do{
        printf("\n1- Para consulta por ID \n2- Para consulta por CPF \n3- Para consulta por prefixo do nome\n");
        printf("Selecione a opcao Desejada: ");
        scanf("%d",&consulta);
        switch(consulta){
            case 1:
                printf("Forneca o ID que desaja consultar: ");
                scanf("%d",&id);
                posicao = pesquisaIdVendedor(arquivo_vendedor, id);
                break;
            case 2:
                printf("Forneca o CPF que deseja consultar: ");
                setbuf(stdin, NULL);
                fgets(cpf,13,stdin);
                retiraEnter(cpf);
                posicao = pesquisaVendedorCPF(arquivo_vendedor, cpf);
                break;
            case 3:
                printf("Forneca o nome: ");
                setbuf(stdin, NULL);
                fgets(prefixo,100,stdin);
                retiraEnter(prefixo);
                maiuscSemAcento(prefixo);
                posicao = pesquisaPrefixoNomeVendedor(arquivo_vendedor, prefixo);

        }
        system("cls || clear");
        if(ftell(arquivo_vendedor) > 0 && posicao != -1){
                fseek(arquivo_vendedor,posicao*sizeof(TVendedor),SEEK_SET);
                fread(&vendedor,sizeof(TVendedor),1,arquivo_vendedor);
                printf("\n=============== CONSULTA VENDEDOR ==================");
                printf("\nID: %lu",vendedor.id);
                printf("\nNome: %s",vendedor.nome);
                printf("\nCPF: %s",vendedor.cpf);
                printf("\nEmail: %s",vendedor.email);
                printf("\nTelefone: %s",vendedor.telefone);
                printf("\nSenha: %s",vendedor.password);
                printf("\n====================================================");
        }
        else
            printf("\nDados do vendedor inexistente");
        printf("\nDeseja abandonar a consulta?\n1-Sim 2-Nao: ");
        scanf("%d",&sair);

    }while(sair!=1);
    fclose(arquivo_vendedor);
    pressioneEnter();
}

void alterarVendedor(){
    FILE *arquivo_vendedor;
    TVendedor vendedor;
    int consulta,posicao,sair,pesquisa;
    unsigned long id;
    char cpf[13],prefixo[100];
    arquivo_vendedor = fopen("vendedor.dat", "rb+");

    if (arquivo_vendedor == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }
    do{
        printf("\n1- Para alterar por ID \n2- Para alterar por CPF \n3- Para alterar por prefixo do nome\n");
        printf("Selecione a opcao Desejada: ");
        scanf("%d",&consulta);
        switch(consulta){
            case 1:
                printf("Forneca o ID que desaja alterar: ");
                scanf("%lu",&id);
                posicao = pesquisaIdVendedor(arquivo_vendedor, id);
                break;
            case 2:
                printf("Fornca o CPF do usuario que deseja alterar: ");
                setbuf(stdin, NULL);
                fgets(cpf,13,stdin);
                retiraEnter(cpf);
                posicao = pesquisaVendedorCPF(arquivo_vendedor, cpf);
                break;
            case 3:
                printf("Forneca o nome: ");
                setbuf(stdin, NULL);
                fgets(prefixo,100,stdin);
                retiraEnter(prefixo);
                maiuscSemAcento(prefixo);
                posicao = pesquisaPrefixoNomeVendedor(arquivo_vendedor, prefixo);

        }
        if(ftell(arquivo_vendedor) > 0  && posicao != -1){
            printf("\n================ ALTERACAO CLIENTE =================\n");
            printf("Forneca o nome: ");
            setbuf(stdin, NULL);
            fgets(vendedor.nome, 100, stdin);
            retiraEnter(vendedor.nome);
            maiuscSemAcento(vendedor.nome);


            printf("Forneca seu cpf: ");
            setbuf(stdin, NULL);
            gets(vendedor.cpf);
            pesquisa = pesquisaVendedorCPF(arquivo_vendedor, vendedor.cpf);
            while(validarCPF(vendedor.cpf) != 1 || pesquisa != -1){
                if(pesquisa == posicao)
                    break;
                else if(pesquisaVendedorCPF(arquivo_vendedor, vendedor.cpf) != -1)
                    printf("\nCPF ja e registrado no sistema");
                else
                    printf("\nCPF INVALIDO");
                printf("\nForneca um CPF valido: ");
                setbuf(stdin, NULL);
                gets(vendedor.cpf);
                pesquisa = pesquisaVendedorCPF(arquivo_vendedor, vendedor.cpf);
            }

            printf("Forneca seu E-mail: ");
            setbuf(stdin, NULL);
            fgets(vendedor.email, 50, stdin);
            retiraEnter(vendedor.email);
            maiuscSemAcento(vendedor.email);
            pesquisa = validarEmailVendedor(arquivo_vendedor, vendedor.email);
            while(pesquisa!= -1 && pesquisa != posicao){
                if(pesquisa != -1)
                    printf("\nEmail ja registrado no sistema");
                printf("\nForneca seu E-mail: ");
                setbuf(stdin, NULL);
                fgets(vendedor.email, 50, stdin);
                retiraEnter(vendedor.email);
                maiuscSemAcento(vendedor.email);
                pesquisa = validarEmailVendedor(arquivo_vendedor, vendedor.email);
            }

            printf("Forneca seu Telefone: ");
            setbuf(stdin, NULL);
            fgets(vendedor.telefone,15,stdin);
            retiraEnter(vendedor.telefone);
            maiuscSemAcento(vendedor.telefone);

            printf("Forneca uma nova senha: ");
            setbuf(stdin, NULL);
            fgets(vendedor.password,20,stdin);
            retiraEnter(vendedor.password);
            maiuscSemAcento(vendedor.password);

            fseek(arquivo_vendedor,posicao*sizeof(TVendedor),SEEK_SET);
            vendedor.id = (ftell(arquivo_vendedor))/sizeof(TVendedor) +1;
            fwrite(&vendedor, sizeof(TVendedor),1,arquivo_vendedor);
            printf("\n=====================================================");
        }
        else
            printf("\nDados do vendedor inexistente");
        printf("\nDeseja sair da alteracao?\n1-Sim 2-Nao: ");
        scanf("%d",&sair);


    }while(sair!=1);
    printf("\n");
    fclose(arquivo_vendedor);
    pressioneEnter();

}

