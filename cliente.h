#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

typedef struct TCliente TCliente;
//Funcao que contem um menu para chamar outras funcoes
void menuCliente();
void cadastroCliente();
void listagemCliente();
void alterarCliente();
void consultaCliente();
int pesquisaIdCliente(FILE *,int);

#endif // CLIENTE_H_INCLUDED
