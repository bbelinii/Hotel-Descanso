#ifndef UTILS_H
#define UTILS_H

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

int dataParaDias(Data d);
int calculaDiarias(Data e, Data s);

#endif
