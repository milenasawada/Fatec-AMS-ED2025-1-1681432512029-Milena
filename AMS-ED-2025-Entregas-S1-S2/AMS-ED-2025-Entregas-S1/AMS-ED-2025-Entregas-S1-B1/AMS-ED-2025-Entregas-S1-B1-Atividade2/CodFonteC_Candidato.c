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
#define MAX_NOME 100

typedef struct{
    char nome[MAX_NOME];
    float notas_PE[4];
    float notas_AC[5];
    float notas_PP[10];
    float notas_EB[3];
    float nota_final;
} Candidato;

void calcularNotaFinal (Candidato *candidato){
    
    float soma_PE = 0, soma_AC = 0, soma_PP = 0, soma_EB = 0;
    float minPE, maxPE, minAC, maxAC, minPP, maxPP, minEB, maxEB;
    
    minPE = maxPE = candidato->notas_PE[0];
    minAC = maxAC = candidato->notas_AC[0];
    minPP = maxPP = candidato->notas_PP[0];
    minEB = maxEB = candidato->notas_EB[0];
    
    for (int i = 0; i < 4; i++){
        if(candidato->notas_PE[i] < minPE) minPE = candidato->notas_PE[i];
        if(candidato->notas_PE[i] > maxPE) maxPE = candidato->notas_PE[i];
        soma_PE += candidato->notas_PE[i];
    }
    
    for (int i = 0; i < 5; i++){
        if(candidato->notas_AC[i] < minAC) minAC = candidato->notas_AC[i];
        if(candidato->notas_AC[i] > maxAC) maxAC = candidato->notas_AC[i];
        soma_AC += candidato->notas_AC[i];
    }
    
    for (int i = 0; i < 10; i++){
        if(candidato->notas_PP[i] < minPP) minPP = candidato->notas_PP[i];
        if(candidato->notas_PP[i] > maxPP) maxPP = candidato->notas_PP[i];
        soma_PP += candidato->notas_PP[i];
    }
    
    for (int i = 0; i < 3; i++){
        if(candidato->notas_EB[i] < minEB) minEB = candidato->notas_EB[i];
        if(candidato->notas_EB[i] > maxEB) maxEB = candidato->notas_EB[i];
        soma_EB += candidato->notas_EB[i];
    }
    
    soma_PE = soma_PE - minPE - maxPE;
    soma_AC = soma_AC - minAC - maxAC;
    soma_PP = soma_PP - minPP - maxPP;
    soma_EB = soma_EB - minEB - maxEB;
    
    candidato->nota_final = (soma_PE * 0.3) + (soma_AC * 0.1) + (soma_PP * 0.4) + (soma_EB * 0.2);
}

int main(){
    Candidato candidatos[MAX_CANDIDATOS];
    int num_candidatos = 0;
    
    while (num_candidatos < MAX_CANDIDATOS){
        
        printf("Digite o nome do candidato: ");
        scanf(" %[^\n]", candidatos[num_candidatos].nome);
        
        printf ("Digite as 4 notas da prova escrita (PE): ");
            for (int i = 0; i < 4; i++){
                scanf("%f", &candidatos[num_candidatos].notas_PE[i]);
            }
        
        printf ("Digite as 5 notas da Análise Curricular (AC): ");
            for (int i = 0; i < 5; i++){
                scanf("%f", &candidatos[num_candidatos].notas_AC[i]);
            }
        
        printf ("Digite as 10 notas da Prova Prática(PP): ");
            for (int i = 0; i < 10; i++){
                scanf("%f", &candidatos[num_candidatos].notas_PP[i]);
            }
        
        printf ("Digite as 3 notas da Entrevista em Banca Avaliadora(EB): ");
            for (int i = 0; i < 3; i++){
                scanf("%f", &candidatos[num_candidatos].notas_EB[i]);
            }
            
        calcularNotaFinal(&candidatos[num_candidatos]);
        num_candidatos++;
    }
    
    for (int i = 0; i < num_candidatos - 1; i++){
        for (int j = i + 1; j < num_candidatos; j++){
            if(candidatos[i].nota_final < candidatos[j].nota_final){
                Candidato temp = candidatos[i];
                candidatos[i] = candidatos[j];
                candidatos[j] = temp;
            }
        }
    }
    
    printf ("\n Classificação dos 5 melhores: \n");
    for (int i = 0; i < 5 && i < num_candidatos; i++){
        printf ("%d° lugar: %s - Nota Final: %2f\n", i + 1, candidatos[i].nome, candidatos[i].nota_final);
    }
    
    return 0;
}