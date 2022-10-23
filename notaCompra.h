#ifndef NOTACOMPRA_H_INCLUDED
#define NOTACOMPRA_H_INCLUDED

typedef struct NotaCompra NotaCompra;
typedef struct ItemNotaCompra ItemNotaCompra;
void gerarNotaCompra(unsigned long, float);
void registroItemNotaCompra(unsigned long, unsigned int, float);
int consultarIdNotaCompra(unsigned long id);
void consultarItemNotaCompra(unsigned long id);
void listarNotaCompra();

#endif // NOTACOMPRA_H_INCLUDED
