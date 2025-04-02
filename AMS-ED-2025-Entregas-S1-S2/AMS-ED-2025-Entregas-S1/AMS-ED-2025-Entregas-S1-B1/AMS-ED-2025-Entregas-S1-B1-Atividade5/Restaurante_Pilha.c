/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: Atividade B1-5                          */
/*          Objetivo: Programa de Restaurante - transformando lista ligada em pilha */
/*                                                                                  */
/*                                  Autor: Milena Miwa Sawada                       */
/*                                                                   Data:01/04/2025*/
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Comanda {
    int NumeroPedido;
    char NomeCliente[100];
    char DescricaoPrato[100];
    int Quantidade;
    char StatusPedido[50];
    struct Comanda *prox;
} Comanda;

typedef struct Pilha {
    Comanda *topo;
} Pilha;

Pilha *criarPilha() {
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

void push(Pilha *p, int NumeroPedido, const char *NomeCliente, const char *DescricaoPrato, int Quantidade, const char *StatusPedido) {
    Comanda *novo = (Comanda *)malloc(sizeof(Comanda));
    if (!novo) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    novo->NumeroPedido = NumeroPedido;
    strcpy(novo->NomeCliente, NomeCliente);
    strcpy(novo->DescricaoPrato, DescricaoPrato);
    novo->Quantidade = Quantidade;
    strcpy(novo->StatusPedido, StatusPedido);
    novo->prox = p->topo;
    p->topo = novo;
}

void pop(Pilha *p) {
    if (p->topo == NULL) {
        printf("A pilha está vazia!\n");
        return;
    }
    Comanda *removido = p->topo;
    p->topo = p->topo->prox;
    free(removido);
}

void peek(Pilha *p) {
    if (p->topo == NULL) {
        printf("A pilha está vazia!\n");
        return;
    }
    printf("Pedido #%d\n", p->topo->NumeroPedido);
    printf("Cliente: %s\n", p->topo->NomeCliente);
    printf("Descrição: %s\n", p->topo->DescricaoPrato);
    printf("Quantidade: %d\n", p->topo->Quantidade);
    printf("Status: %s\n", p->topo->StatusPedido);
}

void liberarPilha(Pilha *p) {
    while (p->topo != NULL) {
        pop(p);
    }
    free(p);
}

int main() {
    Pilha *pedidos = criarPilha();
    int opcao, numPed, qtde;
    char nome_cliente[100], desc_prato[100], status[50];

    do {
        printf("\nRESTAURANTE:\n");
        printf("1 - Inserir pedido\n");
        printf("2 - Visualizar topo\n");
        printf("3 - Remover pedido\n");
        printf("0 - Sair\n");
        printf("Digite uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Número do pedido: ");
                scanf("%d", &numPed);
                printf("Nome do cliente: ");
                scanf("%s", nome_cliente);
                printf("Descrição do prato: ");
                scanf("%s", desc_prato);
                printf("Quantidade: ");
                scanf("%d", &qtde);
                printf("Status (Pendente, Em preparo, Pronto, Entregue): ");
                scanf("%s", status);
                push(pedidos, numPed, nome_cliente, desc_prato, qtde, status);
                printf("Pedido registrado com sucesso!\n");
                break;
            case 2:
                printf("Último pedido registrado:\n");
                peek(pedidos);
                break;
            case 3:
                pop(pedidos);
                printf("Último pedido removido!\n");
                break;
            case 0:
                printf("Saindo...\n");
                liberarPilha(pedidos);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
