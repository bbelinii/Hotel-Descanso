#include <stdio.h>
#include <string.h>
#include "clientes.h"

int gerarCodigoCliente(){
    FILE *f = fopen("clientes.dat", "rb");
    if(!f) return 1;
    Cliente c;
    int ultimo = 0;
    while(fread(&c, sizeof(Cliente), 1, f)){
        ultimo = c.codigo;
    }
    fclose(f);
    return ultimo + 1;
}

void cadastrarCliente(){
    Cliente c;
    c.codigo = gerarCodigoCliente();

    printf("Codigo: %d\n", c.codigo);
    fflush(stdin);
    printf("Nome: ");
    fgets(c.nome, 50, stdin);
    printf("Endereco: ");
    fgets(c.endereco, 80, stdin);
    printf("Telefone: ");
    fgets(c.telefone, 20, stdin);

    FILE *f = fopen("clientes.dat", "ab");
    fwrite(&c, sizeof(Cliente), 1, f);
    fclose(f);

    printf("Cliente cadastrado!\n");
}

int buscarCliente(int codigo, Cliente *c){
    FILE *f = fopen("clientes.dat", "rb");
    if(!f) return 0;

    while(fread(c, sizeof(Cliente), 1, f)){
        if(c->codigo == codigo){
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void pesquisarCliente(){
    FILE *f = fopen("clientes.dat", "rb");
    if(!f){
        printf("Nao ha clientes cadastrados.\n");
        return;
    }

    int opcao, cod;
    Cliente c;
    char nome[50];

    printf("Pesquisar por: 1-Codigo 2-Nome: ");
    scanf("%d", &opcao);
    getchar();

    if(opcao == 1){
        printf("Codigo: ");
        scanf("%d", &cod);

        while(fread(&c, sizeof(Cliente), 1, f)){
            if(c.codigo == cod){
                printf("\nCodigo: %d\nNome: %sEndereco: %sTelefone: %s\n",
                    c.codigo, c.nome, c.endereco, c.telefone);
                fclose(f);
                return;
            }
        }
        printf("Nao encontrado.\n");

    } else {
        printf("Digite parte do nome: ");
        fgets(nome, 50, stdin);

        int achou = 0;
        while(fread(&c, sizeof(Cliente), 1, f)){
            if(strstr(c.nome, nome)){
                printf("\nCodigo: %d\nNome: %sEndereco: %sTelefone: %s\n",
                    c.codigo, c.nome, c.endereco, c.telefone);
                achou = 1;
            }
        }
        if(!achou) printf("Nao encontrado.\n");
    }

    fclose(f);
}
