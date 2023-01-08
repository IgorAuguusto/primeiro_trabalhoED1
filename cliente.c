#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "funcoes.h"

struct TCliente{
    unsigned long id;
    char nome[100];
    char cpf[12];
    char email[50];
    char telefone[15];
};

int pesquisaClienteCPF(FILE *a, char *cpf){
    int posicao = 0;
    TCliente cliente;
    // posicionando no início do arquivo
    rewind(a);
    while (fread(&cliente, sizeof(TCliente), 1, a) == 1){
        if (strcmp(cliente.cpf, cpf) == 0)
            return posicao;
        else
            posicao++;
    }
    return -1;
}

int pesquisaPrefixoNomeCliente(FILE *a, char *prefixo){
    int posicao = 0;
    char *ponteiro;
    TCliente cliente;
    // posicionando no início do arquivo
    rewind(a);
    while (fread(&cliente, sizeof(TCliente), 1, a) == 1){
        // verificando se o nome possui a substring prefixo
        ponteiro = strstr(cliente.nome, prefixo);
        if (ponteiro)
            return posicao;
        else
            posicao++;
    }
    return -1;
}

int pesquisaIdCliente(FILE *a, int id){
    int posicao = 0;
    TCliente cliente;
    // posicionando no início do arquivo
    rewind(a);
    while (fread(&cliente, sizeof(TCliente), 1, a) == 1){
        if (cliente.id == id)
            return posicao;
        else
            posicao++;
    }
    return -1;
}

void menuCliente(){
    int opcao;
    do{
        printf("\n-----------------MANUTENCAO CLIENTES----------------\n");
        printf("\n1- Cadastro de Cliente\n2- Listagem de Cliente\n3- Consulta de Cliente \n4- Alteracaoo de Cliente\n5- Voltar ao menu principal\n");
        printf("Selecione a opcao Desejada: ");
        scanf("%d", &opcao);
        switch (opcao){
        case 1:
            system("cls || clear");
            cadastroCliente();
            break;
        case 2:
            system("cls || clear");
            listagemCliente();
            break;
        case 3:
            system("cls || clear");
            consultaCliente();
            break;
        case 4:
            system("cls || clear");
            alterarCliente();
            break;
        }
    } while (opcao != 5);
    system("cls || clear");
}

void cadastroCliente(){
    FILE *arquivo_cliente;
    TCliente cliente;
    int sair, gravado, pesquisa;
    arquivo_cliente = fopen("cliente.dat", "rb+");

    if (arquivo_cliente == NULL){
        arquivo_cliente = fopen("cliente.dat", "wb+");
        if (arquivo_cliente == NULL){
            printf("Erro na criacao do arquivo!\n");
            pressioneEnter();
            return;
        }
    }
    do{
        // Poosiciona no final do arquivo para nao sobreescrever os dados
        fseek(arquivo_cliente, 0, SEEK_END);
        if (ftell(arquivo_cliente) > 0){
            // divide o tamanho total do arquivo pelo tamanho da estrutura e soma 1 para ser o id
            cliente.id = (ftell(arquivo_cliente)) / sizeof(TCliente) + 1;
        }
        else
            cliente.id = 1;
        printf("\n================ CADASTRO CLIENTES ================\n");
        printf("Forneca o nome: ");
        setbuf(stdin, NULL);
        fgets(cliente.nome, 100, stdin);
        retiraEnter(cliente.nome);
        maiuscSemAcento(cliente.nome);

        printf("Forneca seu cpf: ");
        setbuf(stdin, NULL);
        gets(cliente.cpf);
        pesquisa = pesquisaClienteCPF(arquivo_cliente, cliente.cpf);
        // Verificando se o cpf consta no arquivo e se e valido
        while (validarCPF(cliente.cpf) != 1 || pesquisa != -1){
            if (pesquisa != -1)
                printf("\nCPF ja e registrado no sistema");
            else
                printf("\nCPF INVALIDO");
            printf("\nForneca um CPF valido: ");
            setbuf(stdin, NULL);
            gets(cliente.cpf);
            pesquisa = pesquisaClienteCPF(arquivo_cliente, cliente.cpf);
        }
        printf("Forneca seu E-mail: ");
        setbuf(stdin, NULL);
        fgets(cliente.email, 50, stdin);
        retiraEnter(cliente.email);
        maiuscSemAcento(cliente.email);

        printf("Forneca seu Telefone: ");
        setbuf(stdin, NULL);
        fgets(cliente.telefone, 15, stdin);
        maiuscSemAcento(cliente.telefone);

        gravado = fwrite(&cliente, sizeof(TCliente), 1, arquivo_cliente);

        if (gravado != 1){
            printf("Erro na escrita do cadastro do cliente!!");
            pressioneEnter();
            return;
        }

        printf("\nDeseja abandonar o Cadastro?\n1-Sim 2-Nao: ");
        scanf("%d", &sair);
    } while (sair != 1);
    fclose(arquivo_cliente);
}

void listagemCliente(){
    FILE *arquivo_cliente;
    TCliente cliente;
    arquivo_cliente = fopen("cliente.dat", "rb");

    if (arquivo_cliente == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }

    fseek(arquivo_cliente, 0, SEEK_END);
    if (ftell(arquivo_cliente) > 0){
        rewind(arquivo_cliente);
        printf("\n================= LISTAGEM CLIENTES ================");
        while (fread(&cliente, sizeof(TCliente), 1, arquivo_cliente) == 1){
            printf("\nID: %lu", cliente.id);
            printf("\nNome: %s", cliente.nome);
            printf("\nCPF: %s", cliente.cpf);
            printf("\nEmail: %s", cliente.email);
            printf("\nTelefone: %s", cliente.telefone);
            printf("\n====================================================");
        }
    }
    else
        printf("\nSem dados de Clientes cadastrados");
    printf("\n");
    fclose(arquivo_cliente);
    pressioneEnter();
}

void consultaCliente(){
    FILE *arquivo_cliente;
    TCliente cliente;
    int consulta, posicao, sair;
    unsigned long id;
    char cpf[13], prefixo[100];
    arquivo_cliente = fopen("cliente.dat", "rb");

    if (arquivo_cliente == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }
    do{
        printf("\n1- Para consulta por ID \n2- Para consulta por CPF \n3- Para consulta por prefixo do nome\n");
        printf("Selecione a opcao Desejada: ");
        scanf("%d", &consulta);
        switch (consulta){
        case 1:
            printf("Forneca o ID que desaja consultar: ");
            scanf("%lu", &id);
            posicao = pesquisaIdCliente(arquivo_cliente, id);
            break;
        case 2:
            printf("Forneca o CPF do usuario que deseja consultar: ");
            setbuf(stdin, NULL);
            fgets(cpf, 13, stdin);
            retiraEnter(cpf);
            posicao = pesquisaClienteCPF(arquivo_cliente, cpf);
            break;
        case 3:
            printf("Forneca o nome que deseja consultar: ");
            setbuf(stdin, NULL);
            fgets(prefixo, 100, stdin);
            retiraEnter(prefixo);
            maiuscSemAcento(prefixo);
            posicao = pesquisaPrefixoNomeCliente(arquivo_cliente, prefixo);
            break;
        }
        if (ftell(arquivo_cliente) > 0 && posicao != -1){
            fseek(arquivo_cliente, posicao * sizeof(TCliente), SEEK_SET);
            fread(&cliente, sizeof(TCliente), 1, arquivo_cliente);
            printf("\n================== CONSULTA CLIENTE =================");
            printf("\nID: %lu", cliente.id);
            printf("\nNome: %s", cliente.nome);
            printf("\nCPF: %s", cliente.cpf);
            printf("\nEmail: %s", cliente.email);
            printf("\nTelefone: %s", cliente.telefone);
            printf("\n=====================================================");
        }
        else
            printf("\nDados do cliente inexistente");
        printf("\n\nDeseja abandonar a consulta?\n1-Sim 2-Nao: ");
        scanf("%d", &sair);

    } while (sair != 1);
    fclose(arquivo_cliente);
    pressioneEnter();
}

void alterarCliente(){
    FILE *arquivo_cliente;
    TCliente cliente;
    int consulta, posicao, sair, pesquisa;
    unsigned long id;
    char cpf[13], prefixo[100];
    arquivo_cliente = fopen("cliente.dat", "rb+");

    if (arquivo_cliente == NULL){
        printf("Erro na abertura do arquivo!\n");
        pressioneEnter();
        return;
    }
    do{
        printf("\n1- Para alterar por ID \n2- Para alterar por CPF \n3- Para alterar por  nome\n");
        printf("Selecione a opcao Desejada: ");
        scanf("%d", &consulta);
        switch (consulta){
        case 1:
            printf("Forneca o ID que desaja alterar: ");
            scanf("%lu", &id);
            posicao = pesquisaIdCliente(arquivo_cliente, id);
            break;
        case 2:
            printf("Forneca o CPF do usuario que deseja alterar: ");
            setbuf(stdin, NULL);
            fgets(cpf, 13, stdin);
            retiraEnter(cpf);
            posicao = pesquisaClienteCPF(arquivo_cliente, cpf);
            break;
        case 3:
            printf("Forneca o nome: ");
            setbuf(stdin, NULL);
            fgets(prefixo, 100, stdin);
            retiraEnter(prefixo);
            maiuscSemAcento(prefixo);
            posicao = pesquisaPrefixoNomeCliente(arquivo_cliente, prefixo);
        }
        if (ftell(arquivo_cliente) > 0 && posicao != -1){

            printf("\n================ ALTERACAO CLIENTE =================\n");
            printf("Forneca o nome: ");
            setbuf(stdin, NULL);
            fgets(cliente.nome, 100, stdin);
            retiraEnter(cliente.nome);
            maiuscSemAcento(cliente.nome);

            printf("Forneca seu cpf: ");
            setbuf(stdin, NULL);
            gets(cliente.cpf);
            pesquisa = pesquisaClienteCPF(arquivo_cliente, cliente.cpf);
            while (validarCPF(cliente.cpf) != 1 || pesquisa != -1){
                if (pesquisa == posicao)
                    break;
                else if (pesquisa != -1)
                    printf("\nCPF ja e registrado no sistema");
                else
                    printf("\nCPF INVALIDO");
                printf("\nForneca um CPF valido: ");
                setbuf(stdin, NULL);
                gets(cliente.cpf);
                pesquisa = pesquisaClienteCPF(arquivo_cliente, cliente.cpf);
            }
            printf("Forneca seu E-mail: ");
            setbuf(stdin, NULL);
            fgets(cliente.email, 50, stdin);
            retiraEnter(cliente.email);
            maiuscSemAcento(cliente.email);

            printf("Forneca seu Telefone: ");
            setbuf(stdin, NULL);
            fgets(cliente.telefone, 15, stdin);
            retiraEnter(cliente.telefone);
            maiuscSemAcento(cliente.telefone);

            fseek(arquivo_cliente, posicao * sizeof(TCliente), SEEK_SET);
            cliente.id = (ftell(arquivo_cliente)) / sizeof(TCliente) + 1;
            fwrite(&cliente, sizeof(TCliente), 1, arquivo_cliente);
            printf("\n=====================================================");
        }
        else
            printf("\nSem dados de Clientes cadastrados");
        printf("\nDeseja sair da alteracao?\n1-Sim 2-Nao: ");
        scanf("%d", &sair);

    } while (sair != 1);
    printf("\n");
    fclose(arquivo_cliente);
    pressioneEnter();
}
