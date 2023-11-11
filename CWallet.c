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

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_CLIENTES 100
#define MAX_NOME 50
#define MAX_CPF 12

float total_emprestado = 0;

struct cliente
{
    char nome[MAX_NOME + 1];
    int idade;
    char cpf[MAX_CPF + 1];
    int conta;
    int numero_conta;
    float saldo;
    char status;
};

typedef struct cliente cliente;

cliente clientes[MAX_CLIENTES];
int num_clientes = 0;

void cabecalho()
{
    for (int i = 0; i < 40; i++)
    {
        printf("-");
    }
    printf("\n");
}

void fazerEmprestimo()
{

    int numero_conta;

    printf("Digite o número da conta\n");
    scanf("%i", &numero_conta);

    int indice_cliente = -1;

    for (int i = 0; i < num_clientes; i++)
    {
        if (clientes[i].numero_conta == numero_conta)
        {
            indice_cliente = i;
            break;
        }
    }
      if (indice_cliente == -1) {
        printf("Conta nao encontrada.\n");
        return;
    }


    float valor_emprestimo;
    
    printf("Informe o valor desejado para o emprestimo: ");
    scanf("%f", &valor_emprestimo);

    if (valor_emprestimo > 2 * clientes[indice_cliente].saldo)
    {
        printf("Valor maior que o seu limite. Informe um novo valor.\n");
        return;
    }

    float soma_saldo = 0;

    for (int i = 0; i < num_clientes; i++)
    {
        soma_saldo += clientes[i].saldo;
    }

    float limite_emprestimo = 0.2 * soma_saldo;

    if (valor_emprestimo > limite_emprestimo)
    {
        printf("Valor maior que o crédito disponível\n");
        return;
    }

    printf("Emprestimo efetuado!\n");

    clientes[indice_cliente].saldo += valor_emprestimo;

    total_emprestado += valor_emprestimo;
}

void fecharConta()
{

    int numero_conta;

    printf("Digite o número da conta\n");
    scanf("%i", &numero_conta);

    int indice_cliente = -1;

    for (int i = 0; i < num_clientes; i++)
    {
        if (clientes[i].numero_conta == numero_conta)
        {
            indice_cliente = i;
            break;
        }
    }
    if (indice_cliente == -1)
    {
        printf("conta não encontrada");
    }
    if (clientes[indice_cliente].saldo == 0.0)
    {
        clientes[indice_cliente].status = 'F';
        printf("Conta fechada com sucesso!\n");
    }
    else
    {
        printf("É necessário esvaziar a conta antes de fecha-la\n");
    }
}

void fazerSaque()
{
    int numero_conta;
    float valor;

    printf("Digite o número da conta: ");
    scanf("%d", &numero_conta);

    int indice_cliente = -1;

    for (int i = 0; i < num_clientes; i++)
    {
        if (clientes[i].numero_conta == numero_conta)
        {
            indice_cliente = i;
            break;
        }
    }

    if (indice_cliente == -1)
    {
        cabecalho();
        printf("ATENÇÂO!! Conta não encontrada! \n");
        return;
    }

    cabecalho();
    printf("Digite o valor a ser sacado: ");
    scanf("%f", &valor);

    if (valor <= 0)
    {
        cabecalho();
        printf("ATENÇÃO!! O valor do saque deve ser positivo!\n");
        return;
    }

    if (clientes[indice_cliente].saldo < valor)
    {
        printf("ATENÇÃO!! Não foi possível realizar o saque, saldo insuficiente...\n");
        return;
    }

    clientes[indice_cliente].saldo -= valor;

    printf("Saque realizado com sucesso! Saldo atual: %.2f\n", clientes[indice_cliente].saldo);
}

void fazerDeposito()
{
    int numero_conta;
    float valor;

    printf("Digite o número da conta: ");
    scanf("%d", &numero_conta);

    int indice_cliente = -1;

    for (int i = 0; i < num_clientes; i++)
    {
        if (clientes[i].numero_conta == numero_conta)
        {
            indice_cliente = i;
            break;
        }
    }

    if (indice_cliente == -1)
    {
        cabecalho();
        printf("ATENÇÂO!! Conta não encontrada! \n");
        return;
    }

    cabecalho();
    printf("Digite o valor a ser depositado: ");
    scanf("%f", &valor);

    if (valor <= 0)
    {
        cabecalho();
        printf("ATENÇÃO!! O valor do depósito deve ser positivo! \n");
        return;
    }

    clientes[indice_cliente].saldo += valor;

    printf("Depósito realizado com sucesso! Saldo atual: %.2f\n", clientes[indice_cliente].saldo);
}

void inserirCliente()
{
    if (num_clientes >= MAX_CLIENTES)
    {
        printf("Número máximo de clientes atingido.\n");
        return;
    }

    cliente novoCliente;

    printf("Digite o nome completo (max %i caracteres): ", MAX_NOME);
    scanf(" %50[^\n]", novoCliente.nome);

    printf("Digite a idade: ");
    scanf("%i", &(novoCliente.idade));
    getchar();

    if (novoCliente.idade < 18)
    {
        printf("ATENÇÃO! Cliente precisa ser maior de idade!\n");
        return;
    }

    printf("Digite o CPF: ");
    scanf("%11[^\n]", novoCliente.cpf);

    for (int i = 0; i < num_clientes; i++)
    {
        if (strcmp(clientes[i].cpf, novoCliente.cpf) == 0)
        {
            printf("ATENÇÃO! Cliente ja cadastrado!\n");
            return;
        }
    }

    cabecalho();
    printf("1 - Conta Corrente\n");
    printf("2 - Conta Poupanca\n");
    cabecalho();
    printf("Escolha o tipo da Conta: ");
    scanf("%d", &novoCliente.conta);

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
        printf("ERRO!! Tipo de conta invalida!\n");
        return;
    }

    novoCliente.numero_conta = rand() % 1000000;
    novoCliente.status = 'A';
    novoCliente.saldo = 0.0;

    clientes[num_clientes] = novoCliente;
    num_clientes++;

    printf("Conta criada! Número da conta: %i\n", novoCliente.numero_conta);
}

void listarClientes()
{
    if (num_clientes == 0)
    {
        printf("Nenhum cliente cadastrado! \n");
        return;
    }

    printf("Lista de Clientes:\n");
    printf("| %-4s | %-20s | %-5s | %-12s | %-15s | %-7s | %-6s | %-6s |\n",
           "Num", "Nome", "Idade", "CPF", "Tipo de Conta", "Status", "Saldo", "Nº Conta");
    printf("|------|----------------------|-------|--------------|-----------------|---------|--------|--------|\n");

    for (int i = 0; i < num_clientes; i++)
    {
        printf("| %-4d | %-20s | %-5d | %-12s | %-15s | %-7c | %-6.2f | %-6d |\n",
               i + 1, clientes[i].nome, clientes[i].idade, clientes[i].cpf,
               clientes[i].conta == 1 ? "Conta Corrente" : "Conta Poupança ",
               clientes[i].status, clientes[i].saldo, clientes[i].numero_conta);
    }
}

int menu()
{
    while (1)
    {
        cabecalho();
        printf("       SEJA BEM VINDO AO C-WALLET\n");
        cabecalho();

        printf("1 | Abrir Conta\n");
        printf("2 | Listar Clientes\n");
        printf("3 | Fazer Depósito\n");
        printf("4 | Fazer Saque\n");
        printf("5 | Fechar Conta\n");
        printf("6 | Fazer Empréstimo\n");
        printf("0 | Sair\n");

        printf("Digite uma opção: ");

        int opcao;
        scanf("%i", &opcao);

        switch (opcao)
        {
        case 1:
            inserirCliente();
            break;
        case 2:
            listarClientes();
            break;
        case 3:
            fazerDeposito();
            break;
        case 4:
            fazerSaque();
            break;
        case 5:
            fecharConta();
            break;
        case 6:
            fazerEmprestimo();
            break;
        case 0:
            return 0;

        default:
            printf("opcao invalida, tente novamente\n");
            break;
        }
    }
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    menu();

    return 0;
}