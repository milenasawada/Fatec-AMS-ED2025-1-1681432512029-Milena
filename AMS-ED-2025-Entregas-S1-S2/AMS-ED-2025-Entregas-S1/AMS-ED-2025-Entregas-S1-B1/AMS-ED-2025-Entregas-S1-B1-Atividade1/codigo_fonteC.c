#include <stdio.h>
#include <string.h> 

int main()
{
    float valor_prod, porcentagem_desc, desc, valor_final; 
    float *ptr_valor_prod = &valor_prod;
    float *ptr_porcentagem_desc = &porcentagem_desc;
    float *ptr_desc = &desc; 
    float *ptr_valor_final = &valor_final;
    char resp[4]; 
    
    printf("Insira o valor do produto: ");
    scanf("%f", ptr_valor_prod);
    
    printf("Deseja adicionar um desconto (Sim/Não)? ");
    scanf("%s", resp); 
    
    
    if (strcmp(resp, "Sim") == 0 || strcmp(resp, "sim") == 0) {
        printf("Digite a porcentagem do desconto: ");
        scanf("%f", ptr_porcentagem_desc);
        
        *ptr_desc = *ptr_valor_prod * (*ptr_porcentagem_desc / 100);
        *ptr_valor_final = *ptr_valor_prod - *ptr_desc;
    } else {
        *ptr_desc = 0;
        *ptr_valor_final = *ptr_valor_prod;
    }
    
    printf("O valor do produto é R$: %.2f\n", *ptr_valor_prod);
    printf("O valor do desconto é R$: %.2f\n", *ptr_desc);
    printf("O valor final do produto é R$: %.2f\n", *ptr_valor_final);
    
    return 0;
}