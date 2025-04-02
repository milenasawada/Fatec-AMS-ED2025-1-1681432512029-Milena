/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: Atividade B1-4                          */
/*             Objetivo:    Manipulação de Pilha - Implementando HP12c              */
/*                                                                                  */
/*                                  Autor: Milena Miwa Sawada                       */
/*                                                                   Data:30/03/2025*/
/*----------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 4

typedef struct {
    double itens[MAX];
    int topo;
} Pilha;


Pilha* criar_pilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = -1;
    return p;
}


int vazia(Pilha* p) {
    return p->topo == -1;
}


int cheia(Pilha* p) {
    return p->topo == MAX - 1;
}

void push(Pilha* p, double valor) {
    if (cheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->itens[++p->topo] = valor;
}

double pop(Pilha* p) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        return 0;
    }
    return p->itens[p->topo--];
}

double top(Pilha* p) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        return 0;
    }
    return p->itens[p->topo];
}

double calcular_RPN(char* expressao) {
    Pilha* p = criar_pilha();
    char* token = strtok(expressao, " ");

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(p, atof(token));
        } else {
            double b = pop(p);
            double a = pop(p);
            double resultado;

            switch (token[0]) {
                case '+': resultado = a + b; break;
                case '-': resultado = a - b; break;
                case '*': resultado = a * b; break;
                case '/':
                    if (b == 0) {
                        printf("Não é possível dividir po zero!\n");
                        free(p);
                        return 0;
                    }
                    resultado = a / b;
                    break;
                default:
                    printf("Operador inválido: %s\n", token);
                    free(p);
                    return 0;
            }
            push(p, resultado);
        }
        token = strtok(NULL, " ");
    }
    double resultado_final = pop(p);
    free(p);
    return resultado_final;
}

int main() {
    char expressao[MAX];
    printf("Digite a expressão RPN: ");
    fgets(expressao, sizeof(expressao), stdin);
    expressao[strcspn(expressao, "\n")] = 0;
    double resultado = calcular_RPN(expressao);
    printf("Resultado: %.2f\n", resultado);
    return 0;
}
