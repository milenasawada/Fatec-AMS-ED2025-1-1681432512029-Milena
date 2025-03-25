/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: Atividade B3-2                          */
/*             Objetivo: Programa de Restaurante                                    */
/*                                                                                  */
/*                                  Autor: Milena Miwa Sawada                       */
/*                                                                   Data:23/03/2025*/
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum { PENDENTE, EM_PREPARO, PRONTO, ENTREGUE } StatusPedido;


typedef struct Restaurante {
    int num_pedido;
    char nome[30];
    char descricao[100];
    int qtde;
    StatusPedido status;
    struct Restaurante *prox;
} Restaurante;


Restaurante* criarLista() {
    return NULL;
}


Restaurante* inserirRestaurante(Restaurante* lista, int num_pedido, char nome[], char descricao[], int qtde, StatusPedido status) {
    Restaurante* novoRestaurante = (Restaurante*) malloc(sizeof(Restaurante));
    if (!novoRestaurante) {
        printf("Erro ao alocar memória!\n");
        return lista;
    }
    novoRestaurante->num_pedido = num_pedido;
    strcpy(novoRestaurante->nome, nome);
    strcpy(novoRestaurante->descricao, descricao);
    novoRestaurante->qtde = qtde;
    novoRestaurante->status = status;
    novoRestaurante->prox = lista; 
    return novoRestaurante;
}


void atualizarStatus(Restaurante* lista, int num_pedido, StatusPedido novo_status) {
    Restaurante* atual = lista;
    while (atual) {
        if (atual->num_pedido == num_pedido) {
            atual->status = novo_status;
            printf("Status do pedido #%d atualizado com sucesso!\n", num_pedido);
            return;
        }
        atual = atual->prox;
    }
    printf("Pedido não encontrado!\n");
}


void exibirPedidos(Restaurante* lista) {
    Restaurante* atual = lista;
    if (!atual) {
        printf("Nenhum pedido encontrado.\n");
        return;
    }
    printf("\nLista de Pedidos:\n");
    while (atual) {
        printf("Pedido #%d | Cliente: %s | Prato: %s | Quantidade: %d | Status: %d\n",
               atual->num_pedido, atual->nome, atual->descricao, atual->qtde, atual->status);
        atual = atual->prox;
    }
}


Restaurante* deletarPedido(Restaurante* lista, int num_pedido) {
    Restaurante* atual = lista;
    Restaurante* anterior = NULL;

    while (atual) {
        if (atual->num_pedido == num_pedido) {
            if (anterior) {
                anterior->prox = atual->prox; 
            } else {
                lista = atual->prox; 
            }
            free(atual);
            printf("Pedido #%d removido com sucesso!\n", num_pedido);
            return lista;
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Pedido não encontrado!\n");
    return lista;
}


void liberarLista(Restaurante* lista) {
    Restaurante* atual = lista;
    while (atual) {
        Restaurante* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    printf("Memória liberada com sucesso!\n");
}


int main() {
    Restaurante* lista = criarLista();
    int opcao, num_pedido, qtde, status;
    char nome[30], descricao[100];

    do {
        printf("\nMenu:\n");
        printf("1. Inserir Pedido\n");
        printf("2. Atualizar Status do Pedido\n");
        printf("3. Exibir Pedidos\n");
        printf("4. Excluir Pedido\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                printf("Número do Pedido: ");
                scanf("%d", &num_pedido);
                getchar();
                
                printf("Nome do Cliente: ");
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Descrição do Prato: ");
                fgets(descricao, 100, stdin);
                descricao[strcspn(descricao, "\n")] = '\0';

                printf("Quantidade: ");
                scanf("%d", &qtde);
                getchar();

                lista = inserirRestaurante(lista, num_pedido, nome, descricao, qtde, PENDENTE);
                printf("\nPedido inserido com sucesso!\n");
                break;

            case 2:
                printf("Número do Pedido a atualizar: ");
                scanf("%d", &num_pedido);
                getchar();

                printf("Novo Status (0 = Pendente, 1 = Em Preparo, 2 = Pronto, 3 = Entregue): ");
                scanf("%d", &status);
                getchar();

                if (status >= PENDENTE && status <= ENTREGUE) {
                    atualizarStatus(lista, num_pedido, (StatusPedido)status);
                } else {
                    printf("Status inválido!\n");
                }
                break;

            case 3:
                exibirPedidos(lista);
                break;

            case 4:
                printf("Número do Pedido a excluir: ");
                scanf("%d", &num_pedido);
                getchar();
                lista = deletarPedido(lista, num_pedido);
                break;

            case 5:
                liberarLista(lista);
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);

    return 0;
}
