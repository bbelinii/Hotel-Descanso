#include <stdio.h>
#include <string.h>
#include "funcionarios.h"

int gerarCodigoFuncionario(){
    FILE *f = fopen("funcionarios.dat", "rb");
    if(!f) return 1;
    Funcionario x;
    int ultimo = 0;
    while(fread(&x, sizeof(Funcionario), 1, f)){
        ultimo = x.codigo;
    }
    fclose(f);
    return ultimo + 1;
}

void cadastrarFuncionario(){
    Funcionario f;
    f.codigo = gerarCodigoFuncionario();

    printf("Codigo: %d\n", f.codigo);
    fflush(stdin);
    printf("Nome: ");
    fgets(f.nome, 50, stdin);
    printf("Telefone: ");
    fgets(f.telefone, 20, stdin);
    printf("Cargo: ");
    fgets(f.cargo, 30, stdin);
    printf("Salario: ");
    scanf("%f", &f.salario);

    FILE *arq = fopen("funcionarios.dat", "ab");
    fwrite(&f, sizeof(Funcionario), 1, arq);
    fclose(arq);

    printf("Funcionario cadastrado!\n");
}

void pesquisarFuncionario(){
    FILE *f = fopen("funcionarios.dat", "rb");
    if(!f){
        printf("Nao ha funcionarios.\n");
        return;
    }

    int opcao, cod;
    char nome[50];
    Funcionario x;

    printf("Pesquisar por: 1-Codigo 2-Nome: ");
    scanf("%d", &opcao);
    getchar();

    if(opcao == 1){
        printf("Codigo: ");
        scanf("%d", &cod);

        while(fread(&x, sizeof(Funcionario), 1, f)){
            if(x.codigo == cod){
                printf("Nome: %sTelefone: %sCargo: %sSalario: %.2f\n",
                    x.nome, x.telefone, x.cargo, x.salario);
                fclose(f);
                return;
            }
        }
        printf("Nao encontrado.\n");

    } else {
        printf("Nome: ");
        fgets(nome, 50, stdin);

        int achou = 0;
        while(fread(&x, sizeof(Funcionario), 1, f)){
            if(strstr(x.nome, nome)){
                printf("Codigo: %d\nNome: %sTelefone: %sCargo: %sSalario: %.2f\n",
                    x.codigo, x.nome, x.telefone, x.cargo, x.salario);
                achou = 1;
            }
        }
        if(!achou) printf("Nao encontrado.\n");
    }
    fclose(f);
}
