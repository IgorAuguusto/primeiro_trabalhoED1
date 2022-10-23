#include <stdio.h>
#include <stdlib.h> //EXIT_SUCCESS
#include <string.h>
#include "cliente.h"
#include "vendedor.h"
#include "produto.h"
#include "venda.h"
#include "notaFiscal.h"
#include "compra.h"
#include "notaCompra.h"
#include "registroPreco.h"
#include "relatorios.h"


int menuGeral(){
    int opcao;
    do{
        printf("\n*************** SISTEMA FARMACEUTICO ***************\n");
        printf("****************** LOUCO DE PEDRAS *****************\n");
        printf("\n1- Manutencao Clientes\n2- Manutencao Vendedores\n3- Manutencao Fornecedores\n4- Cadastro Produto\n5- Efetuar uma venda\
               \n6- Realizar uma Compra\n7- Alterar valor Produto\n8- Consultar Relatorios\n9- sair\n");
        printf("Selecione a opcao Desejada: ");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                system("cls || clear");
                menuCliente();
                break;
            case 2:
                system("cls || clear");
                menuVendedor();
                break;
            case 3:
                system("cls || clear");
                menuFornecedor();
                 break;
            case 4:
                system("cls || clear");
                cadastroProduto();
                 break;
            case 5:
                system("cls || clear");
                venda();
                break;
            case 6:
                system("cls || clear");
                compra();
                break;
            case 7:
                system("cls || clear");
                atualizaPreco();
                break;
            case 8:
                system("cls || clear");
                menuRegistro();
                break;
            case 9:
                break;
        }
    }while(opcao!=9);
    return EXIT_SUCCESS;
}

void retiraEnter(char *s){
  int tamanho = strlen(s);
  if (s[tamanho - 1] == '\n')
    s[tamanho - 1] = '\0';
}

void maiuscSemAcento(char *s){
    int i = 0;

    while(s[i] != '\0'){
        if((int)s[i] == -75 || (int)s[i] == -57 || (int)s[i] == -74 || (int)s[i] == -73 || (int)s[i] == -96 || (int)s[i] == -58 || (int)s[i] == -125 || (int)s[i] == -123){
            s[i] = 'A';
        }
        else if ((int)s[i] == -112 || (int)s[i] == -46 || (int)s[i] == -44 || (int)s[i] == -126 || (int)s[i] == -120 || (int)s[i] == -118) {
            s[i] = 'E';
        }
        else if((int)s[i] == -42 || (int)s[i] == -41 || (int)s[i] == -34 || (int)s[i] == -95 || (int)s[i] == -116 || (int)s[i] == -115){
            s[i] = 'I';
        }
        else if((int)s[i] == -32 || (int)s[i] == -27 || (int)s[i] == -30 || (int)s[i] == -29 || (int)s[i] == -94 || (int)s[i] == -28 || (int)s[i] == -109 || (int)s[i] == -107){
            s[i] = 'O';
        }
        else if((int)s[i] == -23 || (int)s[i] == -22 || (int)s[i] == -21 || (int)s[i] == -93 || (int)s[i] == -106 || (int)s[i] == -105){
            s[i] = 'U';
        }
        else{
            s[i] = toupper(s[i]);
        }
        i++;
    }
}

int validarCPF(char *cpf){
    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cpf) != 11)
        return 0;
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0))
        return 0; ///se o CPF tiver todos os números iguais ele é inválido.
    else
    {
        ///digito 1---------------------------------------------------
        for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--) ///multiplica os números de 10 a 2 e soma os resultados dentro de digito1
            digito1 += (cpf[i]-48) * j;
        digito1 %= 11;
        if(digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if((cpf[9]-48) != digito1)
            return 0; ///se o digito 1 não for o mesmo que o da validação CPF é inválido
        else
        ///digito 2--------------------------------------------------
        {
            for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--) ///multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                    digito2 += (cpf[i]-48) * j;
        digito2 %= 11;
        if(digito2 < 2)
            digito2 = 0;
        else
            digito2 = 11 - digito2;
        if((cpf[10]-48) != digito2)
            return 0; ///se o digito 2 não for o mesmo que o da validação CPF é inválido
        }
    }
    return 1;
}
int verificarNumerosIguais(int *campo,int numero,int i,int tam){//verificar se todos os numeros do vetor CNPJ sao iguais, e caso for, retorna erro
    int igual;

    igual = 0;
    for(i = 0;i<tam;i++){
        if(campo[i] == numero)
            igual++;
    }
    if(igual == tam)
        return 1;

    return -1;
}

 int validarCNPJ(char *cnpj) {
    int i = 0,cnpjint[14],somador=0,resultado1,resultado2,digito1,digito2,*pesos,tam;


    for(i=0;i<14;i++){
        cnpjint[i] = cnpj[i] - 48;
    }

    tam = sizeof(cnpjint) / sizeof(int);

    if(verificarNumerosIguais(cnpjint,0,i,tam)==1)
        return 0;

    if(verificarNumerosIguais(cnpjint,1,i,tam)==1)
        return 0;

    if(verificarNumerosIguais(cnpjint,2,i,tam)==1)
        return 0;

    if(verificarNumerosIguais(cnpjint,3,i,tam)==1)
        return 0;

    if(verificarNumerosIguais(cnpjint,4,i,tam)==1)
        return 0;

    if(verificarNumerosIguais(cnpjint,5,i,tam)==1)
        return 0;

    if(verificarNumerosIguais(cnpjint,6,i,tam)==1)
        return 0;

    if(verificarNumerosIguais(cnpjint,7,i,tam)==1)
        return 0;

    if(verificarNumerosIguais(cnpjint,8,i,tam)==1)
        return 0;

    if(verificarNumerosIguais(cnpjint,9,i,tam)==1)
        return 0;

    pesos = (int*)malloc(12*sizeof(int));

    for(i=0;i<12;i++){
        if(i<4){
            pesos[i] = 5-i;
        }
        else{
            pesos[i] = 13-i;
        }
    }

    for(i=0;i<12;i++){
        somador += cnpjint[i] * pesos[i];
    }
    resultado1 = somador%11;

    if(resultado1 < 2){
        digito1 = 0;
    }
    else{
        digito1 = 11 - resultado1;
    }
    pesos = (int*)realloc(pesos,13*sizeof(int));
    somador = 0;

    for(i=0;i<13;i++){
        if(i<5){
            pesos[i] = 6-i;
        }
        else{
            pesos[i] = 14-i;
        }
    }

    for(i=0;i<13;i++){
        somador += cnpjint[i] * pesos[i];
    }
    resultado2 = somador%11;

    if(resultado2 < 2){
        digito2 = 0;
    }
    else{
        digito2 = 11 - resultado2;
    }

    free(pesos);
    if(cnpjint[12]==digito1 && cnpjint[13] == digito2){
        return 1;
    }

    return 0;
}

int verificaData(char *data){
    int i;
    long int datas[3];
    const char delimitador[2] = "/";
    const char substring[3] = "//";

    for (i = 0; data[i] != '\0'; i++){
        if (data[i] != '/' && !isdigit(data[i])){
            return 0;
        }
    }
    if (strstr(data, substring) != NULL){
        return 0;
    }
    i = 0;
    char *token = strtok(data, delimitador);

    while (token != NULL){
        datas[i++] = strtol(token, NULL, 10);
        token = strtok(NULL, delimitador);
    }
    if(datas[1] < 1 || datas[1] > 12 || datas[0] < 1 || datas[0] > 31 || datas[2] < 1960 || datas[2] > 2040){
            return 0;   //caso o mes n estiver entre 1 e 12 ou se o dia n estiver entre 1 e 31 ou se a data for menor que 20/06/1960 e maior que 2040,retorna erro
    }
    else if((datas[2] == 1960 && datas[1] < 6) || (datas[2] == 1960 && datas[0] < 20)){
        return 1;
    }
    switch(datas[1]){
        case 4:;
        case 6:;
        case 9:;
        case 11:
            if(datas[0] < 1 || datas[0] > 30) //se o dia n estiver entre 0 ou 30 nos meses 4,6,9,11,volta erro
                return 0;
        break;
        case 2:
            if(((datas[2]%4 == 0)&&(datas[2]% 100 != 0)) || (datas[2]% 400 == 0)){ //verificando se  ano  e bissexto e se o dia entrado valido
                if(datas[0] < 1 || datas[0] > 29)                                     //caso seja ou n�o ano bissexto
                    return 0;
            }
            else{
                if(datas[0] < 1 || datas[0] > 28)
                    return 0;
            }
        break;
    }

    return 1;
}

int intervaloData(char *dataAtual,char *dataInicio, char *dataFinal, int comprararDia){
    char dataNumero[11];
    int dataInt, dataInicioInt, dataFinalInt;
    if((verificaData(dataAtual) == 1) && (verificaData(dataInicio) == 1) && (verificaData(dataFinal) == 1)){
        sprintf(dataNumero,"%c%c%c%c%c%c%c%c",dataAtual[6],dataAtual[7],dataAtual[8],dataAtual[9],dataAtual[3],dataAtual[4],dataAtual[0],dataAtual[1]);

        if(comprararDia == 0){
            dataNumero[6] = '\0';
        }
        dataInt = atoi(dataNumero);

        sprintf(dataNumero,"%c%c%c%c%c%c%c%c",dataInicio[6],dataInicio[7],dataInicio[8],dataInicio[9],dataInicio[3],dataInicio[4],dataInicio[0],dataInicio[1]);

         if(comprararDia == 0){
            dataNumero[6] = '\0';
        }
        dataInicioInt = atoi(dataNumero);

        sprintf(dataNumero,"%c%c%c%c%c%c%c%c",dataFinal[6],dataFinal[7],dataFinal[8],dataFinal[9],dataFinal[3],dataFinal[4],dataFinal[0],dataFinal[1]);

         if(comprararDia == 0){
            dataNumero[6] = '\0';
        }
        dataFinalInt = atoi(dataNumero);

        if((dataInt >= dataInicioInt) && (dataInt <= dataFinalInt)){
            return 1;
        }
    }
    return 0;
}
void pressioneEnter(){
    setbuf(stdin,NULL);
    printf("Pressione a tecla Enter para continuar. . .\n");
    getchar();
    setbuf(stdin,NULL);
}
