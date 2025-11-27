#include <stdio.h>
#include <string.h>
#include "estadias.h"
#include "clientes.h"
#include "quartos.h"
#include "utils.h"

int gerarCodigoEstadia(){
    FILE *f = fopen("estadias.dat", "rb");
    if(!f) return 1;

    Estadia e;
    int ultimo = 0;

    while(fread(&e, sizeof(Estadia), 1, f)){
        ultimo = e.codigo;
    }

    fclose(f);
    return ultimo + 1;
}

/*
    Verifica se um quarto está livre no período desejado.
    Retorna 1 = disponível, 0 = ocupado
*/
int quartoDisponivel(int numero, Data entrada, Data saida){
    FILE *f = fopen("estadias.dat", "rb");
    if(!f) return 1;

    Estadia e;
    int eIni = dataParaDias(entrada);
    int eFim = dataParaDias(saida);

    while(fread(&e, sizeof(Estadia), 1, f)){
        if(e.numQuarto == numero && e.ativa == 'S'){
            int sIni = dataParaDias(e.entrada);
            int sFim = dataParaDias(e.saida);

            // se houver sobreposição de períodos
            if(!(eFim <= sIni || eIni >= sFim)){
                fclose(f);
                return 0;
            }
        }
    }

    fclose(f);
    return 1;
}

/*
    Procura um quarto que:
    - suporte a quantidade de hóspedes
    - esteja disponível no período
*/
int encontrarQuarto(int qtd, Data entrada, Data saida){
    FILE *f = fopen("quartos.dat", "rb");
    if(!f){
        printf("Nao ha quartos cadastrados.\n");
        return -1;
    }

    Quarto q;

    while(fread(&q, sizeof(Quarto), 1, f)){
        if(q.capacidade >= qtd && q.status == 'D'){
            if(quartoDisponivel(q.numero, entrada, saida)){
                fclose(f);
                return q.numero;
            }
        }
    }

    fclose(f);
    return -1;
}

/*
    cadastrarEstadia()
*/
void cadastrarEstadia(){
    Estadia e;
    Cliente c;

    e.codigo = gerarCodigoEstadia();

    int codCliente, qtdHosp;
    printf("Codigo do cliente: ");
    scanf("%d", &codCliente);

    if(!buscarCliente(codCliente, &c)){
        printf("Cliente nao encontrado!\n");
        return;
    }

    printf("Quantidade de hospedes: ");
    scanf("%d", &qtdHosp);

    printf("Data de entrada (dia mes ano): ");
    scanf("%d %d %d", &e.entrada.dia, &e.entrada.mes, &e.entrada.ano);

    printf("Data de saida (dia mes ano): ");
    scanf("%d %d %d", &e.saida.dia, &e.saida.mes, &e.saida.ano);

    int numeroQuarto = encontrarQuarto(qtdHosp, e.entrada, e.saida);

    if(numeroQuarto == -1){
        printf("Nao ha quarto disponivel!\n");
        return;
    }

    e.numQuarto = numeroQuarto;
    e.codCliente = codCliente;
    e.diarias = calculaDiarias(e.entrada, e.saida);
    e.ativa = 'S';

    FILE *f = fopen("estadias.dat", "ab");
    fwrite(&e, sizeof(Estadia), 1, f);
    fclose(f);

    atualizarStatus(numeroQuarto, 'O');

    printf("Estadia cadastrada!\n");
    printf("Quarto reservado: %d\n", numeroQuarto);
    printf("Diarias: %d\n", e.diarias);
}

/*
    finalizarEstadia()
*/
void finalizarEstadia(){
    int cod;
    printf("Codigo da estadia: ");
    scanf("%d", &cod);

    FILE *f = fopen("estadias.dat", "r+b");
    if(!f){
        printf("Nao ha estadias cadastradas.\n");
        return;
    }

    Estadia e;
    int encontrado = 0;

    while(fread(&e, sizeof(Estadia), 1, f)){
        if(e.codigo == cod && e.ativa == 'S'){
            encontrado = 1;

            // pega valor da diária do quarto
            Quarto q;
            if(!buscarQuarto(e.numQuarto, &q)){
                printf("Erro ao buscar quarto.\n");
                fclose(f);
                return;
            }

            float total = q.valor * e.diarias;
            printf("Valor total a pagar: R$ %.2f\n", total);

            e.ativa = 'N';

            // regravar posição
            fseek(f, -sizeof(Estadia), SEEK_CUR);
            fwrite(&e, sizeof(Estadia), 1, f);

            fclose(f);
            atualizarStatus(e.numQuarto, 'D');

            printf("Estadia finalizada e quarto liberado.\n");
            return;
        }
    }

    fclose(f);

    if(!encontrado){
        printf("Estadia nao encontrada ou ja finalizada.\n");
    }
}

/*
    Mostrar todas as estadias de um cliente
*/
void estadiasPorCliente(){
    int opcao, cod;
    char nome[50];
    Cliente c;

    printf("Pesquisar cliente por: 1-Codigo 2-Nome: ");
    scanf("%d", &opcao);
    getchar();

    if(opcao == 1){
        printf("Codigo: ");
        scanf("%d", &cod);

        if(!buscarCliente(cod, &c)){
            printf("Cliente nao encontrado.\n");
            return;
        }

    } else {
        FILE *fc = fopen("clientes.dat", "rb");
        if(!fc){
            printf("Nao ha clientes cadastrados.\n");
            return;
        }

        printf("Nome: ");
        fgets(nome, 50, stdin);

        int achou = 0;
        while(fread(&c, sizeof(Cliente), 1, fc)){
            if(strstr(c.nome, nome)){
                cod = c.codigo;
                achou = 1;
                break;
            }
        }
        fclose(fc);

        if(!achou){
            printf("Cliente nao encontrado.\n");
            return;
        }
    }

    printf("\n--- ESTADIAS DO CLIENTE %s ---\n", c.nome);

    FILE *fe = fopen("estadias.dat", "rb");
    if(!fe){
        printf("Nenhuma estadia cadastrada.\n");
        return;
    }

    Estadia e;
    int tem = 0;

    while(fread(&e, sizeof(Estadia), 1, fe)){
        if(e.codCliente == cod){
            printf("\nEstadia: %d\n", e.codigo);
            printf("Quarto: %d\n", e.numQuarto);
            printf("Entrada: %02d/%02d/%04d\n", e.entrada.dia, e.entrada.mes, e.entrada.ano);
            printf("Saida: %02d/%02d/%04d\n", e.saida.dia, e.saida.mes, e.saida.ano);
            printf("Diarias: %d\n", e.diarias);
            printf("Ativa: %s\n", e.ativa == 'S' ? "Sim" : "Nao");
            printf("--------------------------\n");
            tem = 1;
        }
    }

    fclose(fe);

    if(!tem) printf("Nenhuma estadia encontrada para este cliente.\n");
}

/*
    Pontos de fidelidade
*/
void pontosFidelidade(){
    int cod;
    printf("Codigo do cliente: ");
    scanf("%d", &cod);

    FILE *fe = fopen("estadias.dat", "rb");
    if(!fe){
        printf("Nao ha estadias cadastradas.\n");
        return;
    }

    Estadia e;
    int totalDiarias = 0;

    while(fread(&e, sizeof(Estadia), 1, fe)){
        if(e.codCliente == cod){
            totalDiarias += e.diarias;
        }
    }

    fclose(fe);

    printf("Pontos de fidelidade: %d\n", totalDiarias * 10);
}
