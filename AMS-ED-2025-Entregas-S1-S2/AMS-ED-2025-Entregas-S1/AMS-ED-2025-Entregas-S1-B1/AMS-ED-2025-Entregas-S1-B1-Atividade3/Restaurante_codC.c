/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: Atividade B1-3                          */
/*             Objetivo: Programa de Restaurante                                    */
/*                                                                                  */
/*                                  Autor: Milena Miwa Sawada                       */
/*                                                                   Data:23/03/2025*/
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct Comanda
{
    int NumeroPedido;
    char NomeCliente[100];
    char DescricaoPrato[100];
    int Quantidade;
    char StatusPedido[50];
    struct Comanda *prox;
} Comanda;
 
Comanda *criarLista()
{
    return NULL;
}
 
Comanda *inserirpedido(Comanda *lista, int NumeroPedido, const char *NomeCliente, const char *DescricaoPrato, int Quantidade, const char *StatusPedido)
{
    Comanda *novo = (Comanda *)malloc(sizeof(Comanda));
    if (!novo)
    {
        printf("Erro ao alocar memória.\n");
        return lista;
    }
 
    novo->NumeroPedido = NumeroPedido;
    strcpy(novo->NomeCliente, NomeCliente);
    strcpy(novo->DescricaoPrato, DescricaoPrato);
    novo->Quantidade = Quantidade;
 
    if (strcmp(StatusPedido, "1") == 0)
    {
        strcpy(novo->StatusPedido, "Pendente");
    }
    else if (strcmp(StatusPedido, "2") == 0)
    {
        strcpy(novo->StatusPedido, "Em preparo");
    }
    else if (strcmp(StatusPedido, "3") == 0)
    {
        strcpy(novo->StatusPedido, "Pronto");
    }
    else if (strcmp(StatusPedido, "4") == 0)
    {
        strcpy(novo->StatusPedido, "Entregue");
    }
    else
    {
        strcpy(novo->StatusPedido, "Desconhecido");
    }
 
    novo->prox = lista;
    return novo;
}
 
Comanda *obterpedido(Comanda *lista, int NumeroPedido)
{
    Comanda *atual = lista;
    while (atual != NULL)
    {
        if (atual->NumeroPedido == NumeroPedido)
        {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}
 
void alterarStatus(Comanda *lista, int NumeroPedido, const char *StatusNovo)
{
    Comanda *atual = lista;
    while (atual != NULL)
    {
        if (atual->NumeroPedido == NumeroPedido)
        {
            if (strcmp(StatusNovo, "1") == 0)
            {
                strcpy(atual->StatusPedido, "Pendente");
            }
            else if (strcmp(StatusNovo, "2") == 0)
            {
                strcpy(atual->StatusPedido, "Em preparo");
            }
            else if (strcmp(StatusNovo, "3") == 0)
            {
                strcpy(atual->StatusPedido, "Pronto");
            }
            else if (strcmp(StatusNovo, "4") == 0)
            {
                strcpy(atual->StatusPedido, "Entregue");
            }
            else
            {
                printf("Status inválido.\n");
            }
            return;
        }
        atual = atual->prox;
    }
}
 
Comanda *deletarpedido(Comanda *lista, int NumeroPedido)
{
    Comanda *atual = lista;
    Comanda *anterior = NULL;
 
    while (atual != NULL)
    {
        if (atual->NumeroPedido == NumeroPedido)
        {
            if (anterior == NULL)
            {
                lista = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }
            free(atual);
            return lista;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Pedido não encontrado.\n");
    return lista;
}
 
void liberarlista(Comanda *lista)
{
    Comanda *atual = lista;
    Comanda *proximo;
 
    while (atual != NULL)
    {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}
 
int main()
{
    Comanda *lista = criarLista();
 
    int numPed;
    char nome_cliente[100];
    char desc_prato[100];
    int qtde;
    char status[10];
    int opcao = 6;
 
    while (opcao != 0)
    {
        printf("\nRESTAURANTE:\n\n");
        printf("1 - Inserir pedido\n");
        printf("2 - Alterar status do pedido\n");
        printf("3 - Deletar pedido\n");
        printf("4 - Obter pedido\n");
        printf("0 - Sair\n");
        printf("\nDigite uma opção: ");
        scanf("%d", &opcao);
 
        switch (opcao)
        {
        case 1:
            printf("\nInserir Pedido\n\n");
            printf("Número do pedido: ");
            scanf("%d", &numPed);
            printf("Nome do cliente: ");
            scanf("%s[^\n]", nome_cliente);
            getchar();
            printf("Descrição do prato: ");
            scanf("%s[^\n]", desc_prato);
            getchar();
            printf("Quantidade de pratos: ");
            scanf("%d", &qtde);
            printf("Status do pedido (1- Pendente, 2- Em preparo, 3- Pronto, 4- Entregue): ");
            scanf("%s[^\n]", status);
            getchar();
            lista = inserirpedido(lista, numPed, nome_cliente, desc_prato, qtde, status);
            printf("\nPedido registrado com sucesso!\n");
            break;
        case 2:
            printf("\nAlterar Status do Pedido\n\n");
            printf("Digite o número do pedido: ");
            scanf("%d", &numPed);
            printf("Novo status: ");
            scanf("%s", status);
            alterarStatus(lista, numPed, status);
            printf("\nStatus atualizado com sucesso!\n");
            break;
        case 3:
            printf("\nDeletar Pedido\n\n");
            printf("Digite o número do pedido: ");
            scanf("%d", &numPed);
            lista = deletarpedido(lista, numPed);
            printf("\nDeletado com sucesso!\n");
            break;
        case 4:
            printf("\nObter Pedido\n\n");
            printf("Digite o número do pedido: ");
            scanf("%d", &numPed);
            Comanda *pedido = obterpedido(lista, numPed);
            if (pedido)
            {
                printf("Pedido #%d\n", pedido->NumeroPedido);
                printf("Cliente: %s\n", pedido->NomeCliente);
                printf("Descrição: %s\n", pedido->DescricaoPrato);
                printf("Quantidade: %d\n", pedido->Quantidade);
                printf("Status: %s\n", pedido->StatusPedido);
            }
            else
            {
                printf("\nPedido não encontrado.\n");
            }
            break;
        case 0:
            printf("\nSaindo...\n");
            liberarlista(lista);
            break;
        default:
            printf("Opção inválida!\n");
        }
    }
 
    return 0;
}
