#include <stdio.h>
#include "quartos.h"

void cadastrarQuarto(){
    Quarto q;

    printf("Numero do quarto: ");
    scanf("%d", &q.numero);

    printf("Capacidade: ");
    scanf("%d", &q.capacidade);

    printf("Valor diaria: ");
    scanf("%f", &q.valor);

    q.status = 'D';

    FILE *f = fopen("quartos.dat", "ab");
    fwrite(&q, sizeof(Quarto), 1, f);
    fclose(f);

    printf("Quarto cadastrado!\n");
}

int buscarQuarto(int numero, Quarto *q){
    FILE *f = fopen("quartos.dat", "rb");
    if(!f) return 0;

    while(fread(q, sizeof(Quarto), 1, f)){
        if(q->numero == numero){
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void atualizarStatus(int numero, char st){
    FILE *f = fopen("quartos.dat", "r+b");
    Quarto q;

    while(fread(&q, sizeof(Quarto), 1, f)){
        if(q.numero == numero){
            q.status = st;
            fseek(f, -sizeof(Quarto), SEEK_CUR);
            fwrite(&q, sizeof(Quarto), 1, f);
            break;
        }
    }
    fclose(f);
}
