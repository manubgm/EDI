#include <stdio.h>
#include <stdlib.h>

int main(){
    int *valor1, valor2=50;
    char *letra1, letra2= 'g';

    //valor1 é ponteiro
    valor1 = &valor2;
    //atribuicao valida pois
    // &obtem o endereço de memoria de v2 e 
    //guarda em v1

    //letra1 é ponteiro
    letra1 = &letra2;
    printf("conteudo da letra2: %c\n",letra2);
    printf("endereco da letra2 %p\n", &letra2);
    printf("conteudo de letra1:%p\n", letra1);
    printf("conteudo apontado por letra1: %c\n", *letra1);


    printf("conteudo da variavael valor2: %d \n",valor2);
    printf("endereco da variavel valor 2: %p\n", &valor2);
    printf("conteudo da variavel v1 %p\n", valor1);
    printf("conteudo apontado pela v1: %d\n",*valor1);
    return 0;
}