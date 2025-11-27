#ifndef CLIENTES_H
#define CLIENTES_H

typedef struct {
    int codigo;
    char nome[50];
    char endereco[80];
    char telefone[20];
} Cliente;

void cadastrarCliente();
int buscarCliente(int codigo, Cliente *c);
void pesquisarCliente();

#endif
