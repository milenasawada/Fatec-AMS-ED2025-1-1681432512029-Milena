/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: Atividade B1-2                          */
/*             Objetivo: Programa de  seleção para RESIDÊNCIA MÉDICA                */
/*                                                                                  */
/*                                  Autor: Milena Miwa Sawada                       */
/*                                                                   Data:11/03/2025*/
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS 50


typedef struct {
    char nome[100];
    float notas_PE[4];  
    float notas_AC[5];  
    float notas_PP[10]; 
    float notas_EB[3];  
    float nota_final;
} Candidato;


float calcular_nota(float *notas, int tamanho) {
    float maior = notas[0], menor = notas[0], soma = 0.0;
    int i, indice_maior = 0, indice_menor = 0;

    for (i = 1; i < tamanho; i++) {
        if (notas[i] > maior) {
            maior = notas[i];
            indice_maior = i;
        }
        if (notas[i] < menor) {
            menor = notas[i];
            indice_menor = i;
        }
    }
    
    for (i = 0; i < tamanho; i++) {
        if (i != indice_maior && i != indice_menor) {
            soma += notas[i];
        }
    }

    return soma;
}


int comparar(const void *a, const void *b) {
    Candidato *c1 = (Candidato *)a;
    Candidato *c2 = (Candidato *)b;
    return (c2->nota_final > c1->nota_final) - (c2->nota_final < c1->nota_final);
}

int main() {
    Candidato *candidatos;
    int num_candidatos = 0, i, j;

    printf("Quantos candidatos deseja inserir? (Máx. 50): ");
    scanf("%d", &num_candidatos);
    if (num_candidatos > MAX_CANDIDATOS || num_candidatos < 1) {
        printf("Número inválido!\n");
        return 1;
    }

    candidatos = (Candidato *)malloc(num_candidatos * sizeof(Candidato));
    if (candidatos == NULL) {
        printf("Erro de alocação de memória!\n");
        return 1;
    }

    for (i = 0; i < num_candidatos; i++) {
        printf("\nCandidato %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", candidatos[i].nome);

        printf("Digite as 4 notas da Prova Escrita (PE): ");
        for (j = 0; j < 4; j++) scanf("%f", &candidatos[i].notas_PE[j]);

        printf("Digite as 5 notas da Análise Curricular (AC): ");
        for (j = 0; j < 5; j++) scanf("%f", &candidatos[i].notas_AC[j]);

        printf("Digite as 10 notas da Prova Prática (PP): ");
        for (j = 0; j < 10; j++) scanf("%f", &candidatos[i].notas_PP[j]);

        printf("Digite as 3 notas da Entrevista em Banca (EB): ");
        for (j = 0; j < 3; j++) scanf("%f", &candidatos[i].notas_EB[j]);

        float PE = calcular_nota(candidatos[i].notas_PE, 4);
        float AC = calcular_nota(candidatos[i].notas_AC, 5);
        float PP = calcular_nota(candidatos[i].notas_PP, 10);
        float EB = calcular_nota(candidatos[i].notas_EB, 3);

        candidatos[i].nota_final = (PE * 0.3) + (AC * 0.1) + (PP * 0.4) + (EB * 0.2);
    }

    qsort(candidatos, num_candidatos, sizeof(Candidato), comparar);

    printf("\n--- Classificação dos 5 Melhores Candidatos ---\n");
    for (i = 0; i < (num_candidatos < 5 ? num_candidatos : 5); i++) {
        printf("%dº Lugar: %s - Nota Final: %.2f\n", i + 1, candidatos[i].nome, candidatos[i].nota_final);
    }

    free(candidatos);

    return 0;
}
