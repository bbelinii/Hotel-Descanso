#include <stdio.h>
#include "clientes.h"
#include "funcionarios.h"
#include "quartos.h"
#include "estadias.h"

int main(){
    int op;

    do{
        printf("\n=== HOTEL DESCANSO GARANTIDO ===\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Cadastrar funcionario\n");
        printf("3 - Cadastrar quarto\n");
        printf("4 - Cadastrar estadia\n");
        printf("5 - Baixar estadia\n");
        printf("6 - Pesquisar cliente\n");
        printf("7 - Pesquisar funcionario\n");
        printf("8 - Mostrar estadias de cliente\n");
        printf("9 - Pontos de fidelidade\n");
        printf("0 - Sair\nOpcao: ");

        scanf("%d", &op);

        switch(op){
            case 1: cadastrarCliente(); break;
            case 2: cadastrarFuncionario(); break;
            case 3: cadastrarQuarto(); break;
            case 4: cadastrarEstadia(); break;
            case 5: finalizarEstadia(); break;
            case 6: pesquisarCliente(); break;
            case 7: pesquisarFuncionario(); break;
            case 8: estadiasPorCliente(); break;
            case 9: pontosFidelidade(); break;
        }

    } while(op != 0);

    return 0;
}
