#include "utils.h"

int dataParaDias(Data d){
    return d.ano * 365 + d.mes * 30 + d.dia;
}

int calculaDiarias(Data e, Data s){
    int dif = dataParaDias(s) - dataParaDias(e);
    if(dif <= 0) return 1;
    return dif;
}
