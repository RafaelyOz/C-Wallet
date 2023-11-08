#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

#define MAX_CLIENTES 100
#define MAX_NOME 50
#define MAX_CPF 12

struct cliente
{
    char nome[MAX_NOME + 1];
    int idade;
    char cpf[MAX_CPF + 1];
    char conta;
    int numero_conta;
    float saldo;
    char status;
};

typedef struct cliente cliente;

cliente clientes[MAX_CLIENTES];
int num_clientes = 0;

void inserirCliente()
{
    if (num_clientes >= MAX_CLIENTES)
    {
        printf("Número máximo de clientes atingido.\n");
        return;
    }

    cliente novoCliente;

    printf("Informe o nome completo (max %i caracteres):\n", MAX_NOME);
    scanf(" %50[^\n]s", &novoCliente.nome);

    printf("Informe a idade\n");
    scanf("%i", &(novoCliente.idade));
    getchar();
     if (novoCliente.idade < 18)
    {
        printf("cliente precisa ser maior de idade\n");
        return;
    }

    printf("informe o CPF\n");
    scanf("%12[^\n]", novoCliente.cpf);

    for (int i = 0; i < num_clientes; i++)
    {
        if (strcmp(clientes[i].cpf, novoCliente.cpf) == 0)
        {
            printf("Cliente ja cadastrado\n");
            return;
        }
    }

    clientes[num_clientes] = novoCliente;
    num_clientes++;

    printf("Escolha o tipo da Conta:\n");
    printf("1 - Conta Corrente\n");
    printf("2 - Conta Poupanca\n");
    scanf("%i", &novoCliente.conta);

    if (novoCliente.conta == 1)
    {
        novoCliente.conta = 1;
    }
    else if (novoCliente.conta == 2)
    {
        novoCliente.conta = 2;
    }
    else
    {
        printf("tipo de conta invalida\n");
        return;
    }

    novoCliente.numero_conta = num_clientes;
    novoCliente.status = 'A';
    novoCliente.saldo = 0.0;

    printf("Conta criada! numero da conta %i\n", novoCliente.numero_conta);
}

int main()
{

    while (1)
    {

        printf("\n Menu Principal: \n");
        printf("1 - Abrir Conta\n");
        printf("2 - Listar Clientes\n");
        printf("3 - Fazer Deposito\n");
        printf("4 - Fazer Saque\n");
        printf("5 - Fechar Conta\n");
        printf("6 - Fazer Emprestimo\n");
        printf("0 - Sair\n");

        int opcao;
        scanf("%i", &opcao);

        switch (opcao)
        {
        case 1:
            inserirCliente();

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        case 0:
            return 0;

        default:
            printf("opcao invalida, tente novamente\n");
            break;
        }
    }

    return 0;
}