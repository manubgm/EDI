//processador completo de expressões matemáticas
//o racicinio de usasr pilha vai ser por conta d
//da ordem de prioridade das operações
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct no {
    char carac;
    struct no *prox;
    int eh_parentese;
} No;//se eu ler carac por carac e ir colocando em pilhas 

int menu(){
    printf("\n==========================================\n");
    printf("   BEM-VINDO A CALCULADORA DE EXPRESSOES  \n");
    printf("==========================================\n");
    printf("1. Calcular nova expressao (Infixa)\n");
    printf("2. Sair\n");
    printf("------------------------------------------\n");
    printf("Escolha uma opcao: ");
    int op;
    scanf("%d",&op);
    return op;
}

int pop(){

}

void push(){

}



int main(){
    int opcao;
    char expressao[30];

    do{
        opcao=menu();
        switch(opcao){
            case 1:
                printf(">digite sua expressao:\n");
                fgets(expressao,30,stdin);
                break;
            case 2:
                printf(">desligando a calculadora\n");
                break;
            default:
                printf("!!opcao invalida!!\n");
                break;
        }

    }while(opcao!=0);
}

