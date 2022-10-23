#ifndef VENDEDOR_H_INCLUDED
#define VENDEDOR_H_INCLUDED

typedef struct{
    unsigned long id;
    char nome[100];
    char cpf[12];
    char email[50];
    char telefone[15];
    char password[20];
}TVendedor;

//Funcao que contem um menu para chamar o resto das funcoes
void menuVendedor();
void cadastroVendedor();
void listagemVendedor();
void alterarVendedor();
void consultaVendedor();
int pesquisaVendedorCPF(FILE *,char *);

#endif // VENDEDOR_H_INCLUDED
