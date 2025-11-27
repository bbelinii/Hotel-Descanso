#ifndef ESTADIAS_H
#define ESTADIAS_H

#include "utils.h"

typedef struct {
    int codigo;
    Data entrada;
    Data saida;
    int diarias;
    int codCliente;
    int numQuarto;
    char ativa;
} Estadia;

void cadastrarEstadia();
void finalizarEstadia();
void estadiasPorCliente();
void pontosFidelidade();

#endif
