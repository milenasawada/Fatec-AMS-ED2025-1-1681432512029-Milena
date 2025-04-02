/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: Atividade B1-5                          */
/*          Objetivo: Programa de Restaurante - transformando lista ligada em pilha */
/*                                                                                  */
/*                                  Autoras: Isabella Monsalles Barbosa             */
/*                                           Milena Miwa Sawada                     */
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
} Comanda;
 
typedef struct Pilha {
    Comanda *dados; 
    int topo;       
    int capacidade; 
} Pilha;
 
Pilha* criarPilha(int capacidade) {
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    pilha->capacidade = capacidade;
    pilha->topo = -1;
    pilha->dados = (Comanda *)malloc(capacidade * sizeof(Comanda));
    return pilha;
}
 
int pilhaCheia(Pilha *pilha) {
    return pilha->topo == pilha->capacidade - 1;
}
 
int pilhaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}
 
void push(Pilha *pilha, Comanda pedido) {
    if (pilhaCheia(pilha)) {
        printf("Pilha cheia! Não é possível inserir mais pedidos.\n");
        return;
    }
    pilha->dados[++pilha->topo] = pedido;
    printf("\nPedido inserido na pilha!\n");
}
 
Comanda pop(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        printf("Pilha vazia! Não há pedidos para remover.\n");
        Comanda vazio = {0};  
        return vazio;
    }
    return pilha->dados[pilha->topo--];
}
 
Comanda topo(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        printf("Pilha vazia! Não há pedidos no topo.\n");
        Comanda vazio = {0};  
        return vazio;
    }
    return pilha->dados[pilha->topo];
}
 
void alterarStatus(Pilha *pilha, int NumeroPedido, const char *StatusNovo) {
    for (int i = 0; i <= pilha->topo; i++) {
        if (pilha->dados[i].NumeroPedido == NumeroPedido) {
            strcpy(pilha->dados[i].StatusPedido, StatusNovo);
            printf("\nStatus do pedido #%d alterado para: %s\n", NumeroPedido, StatusNovo);
            return;
        }
    }
    printf("\nPedido não encontrado na pilha.\n");
}
 
void imprimirPedido(Comanda pedido) {
    printf("Pedido #%d\n", pedido.NumeroPedido);
    printf("Cliente: %s\n", pedido.NomeCliente);
    printf("Descrição: %s\n", pedido.DescricaoPrato);
    printf("Quantidade: %d\n", pedido.Quantidade);
    printf("Status: %s\n", pedido.StatusPedido);
}
 
void liberarPilha(Pilha *pilha) {
    free(pilha->dados);
    free(pilha);
}
 
int main() {
    Pilha *pilha = criarPilha(10); 
 
    int numPed;
    char nome_cliente[100];
    char desc_prato[100];
    int qtde;
    char status[10];
    int opcao = 6;
 
    while (opcao != 0) {
        printf("\nRESTAURANTE:\n\n");
        printf("1 - Inserir pedido\n");
        printf("2 - Alterar status do pedido\n");
        printf("3 - Remover pedido (desfazer)\n");
        printf("4 - Obter pedido do topo\n");
        printf("0 - Sair\n");
        printf("\nDigite uma opção: ");
        scanf("%d", &opcao);
 
        switch (opcao) {
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
 
            Comanda novoPedido = {numPed, "", "", qtde, ""};
            strcpy(novoPedido.NomeCliente, nome_cliente);
            strcpy(novoPedido.DescricaoPrato, desc_prato);
            if (strcmp(status, "1") == 0) {
                strcpy(novoPedido.StatusPedido, "Pendente");
            } else if (strcmp(status, "2") == 0) {
                strcpy(novoPedido.StatusPedido, "Em preparo");
            } else if (strcmp(status, "3") == 0) {
                strcpy(novoPedido.StatusPedido, "Pronto");
            } else if (strcmp(status, "4") == 0) {
                strcpy(novoPedido.StatusPedido, "Entregue");
            } else {
                strcpy(novoPedido.StatusPedido, "Desconhecido");
            }
 
            push(pilha, novoPedido);
            break;
        case 2:
            printf("\nAlterar Status do Pedido\n\n");
            printf("Digite o número do pedido: ");
            scanf("%d", &numPed);
            printf("Novo status (1- Pendente, 2- Em preparo, 3- Pronto, 4- Entregue): ");
            scanf("%s", status);
            alterarStatus(pilha, numPed, status);
            break;
        case 3:
            printf("\nRemover Pedido (desfazer)\n\n");
            Comanda pedidoRemovido = pop(pilha);
            if (pedidoRemovido.NumeroPedido != 0) { 
                printf("Pedido #%d removido da pilha.\n", pedidoRemovido.NumeroPedido);
            }
            break;
        case 4:
            printf("\nObter Pedido do Topo\n\n");
            Comanda pedidoTopo = topo(pilha);
            if (pedidoTopo.NumeroPedido != 0) {
                imprimirPedido(pedidoTopo);
            }
            break;
        case 0:
            printf("\nSaindo...\n");
            liberarPilha(pilha);
            break;
        default:
            printf("Opção inválida!\n");
        }
    }
 
    return 0;
}
