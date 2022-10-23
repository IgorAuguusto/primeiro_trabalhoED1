#ifndef NOTAFISCAL_H_INCLUDED
#define NOTAFISCAL_H_INCLUDED

typedef struct{
    unsigned long id;
    unsigned long idCliente;
    unsigned long idVendedor;
    char dataCompra[11];
    float valorTotal;
}NotaFiscal;
typedef struct ItemNotaFiscal ItemNotaFiscal;
void gerarNotaFiscal(unsigned long, unsigned long, float);
void registroItemNotaFiscal(unsigned long ,unsigned int, float );
void listarItemNotaFiscal();
void consultaItemsNotaFiscal(unsigned long);
int consultaIdNotaFiscal(unsigned long);
void listarNotaFiscal();
int consultaVendaDiaVendedor(char *,unsigned int);
void consultaVendaMesVendedor(char *, unsigned long);
int consultaVendedorMes(char *,char *,unsigned long);
#endif // NOTAFISCAL_H_INCLUDED
