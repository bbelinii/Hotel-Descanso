#ifndef QUARTOS_H
#define QUARTOS_H

typedef struct {
    int numero;
    int capacidade;
    float valor;
    char status; // D = livre, O = ocupado
} Quarto;

void cadastrarQuarto();
int buscarQuarto(int numero, Quarto *q);
void atualizarStatus(int numero, char st);

#endif
