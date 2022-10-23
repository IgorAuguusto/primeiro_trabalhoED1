#ifndef FORNECEDOR_H_INCLUDED
#define FORNECEDOR_H_INCLUDED

typedef struct TFornecedor TFornecedor;
void menuFornecedor();
void cadastroFornecedor();
void listagemFornecedor();
void alterarFornecedor();
void consultaFornecedor();
int pesquisaIdFornecedor(FILE *,int);

#endif // FORNECEDOR_H_INCLUDED
