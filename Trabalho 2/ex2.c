//processador completo de expressões matemáticas
//o racicinio de usasr pilha vai ser por conta d
//da ordem de prioridade das operações
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct no {
    int valor;
    struct no *prox;
} No;

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

int isEmpty(No *topo){
    return topo==NULL;
}

int pop(No **topo){
    if(isEmpty(*topo)){
        printf("Pilha vazia\n");
        return -1;
    }
    No *aux = *topo;
    int valor_removido = aux->valor;
    *topo = aux->prox;//topo passa a sero elemento debaixo
    //remove o do topo
    free(aux);
    return valor_removido;
}

void push(No **topo,int valor){
    No *novo = (No*)malloc(sizeof(No));
    if(novo==NULL){
        printf("Erro ao alocar memoria\n");
        return;
    }
    novo->valor=valor;
    novo->prox = *topo;//o prox do novo aponta pro topo atual
    *topo = novo;//o topo agora é o novo

}


int verificaParenteses(char *expressao){
    No *pilha = NULL;//cria
    int ta_certo=1;

    for(int i=0; i<strlen(expressao);i++){
        char c =expressao[i];

        if(c=='('){
            push(&pilha,c);
        }else if(c==')'){
            if(isEmpty(pilha)){
                ta_certo=0;
                break;
            }else{
                pop(&pilha);
            }
        }
    }

        if(!isEmpty(pilha)){
            ta_certo=0;

            while(!isEmpty(pilha)){
                pop(&pilha);
            }
        }

    return ta_certo;
}

int prioridade(char operador){
    if (operador=='+'||operador=='-'){
        return 1;
    }else if(operador=='*'||operador=='/'){
        return 2;
    }

    return 0;
}

void infixaParaPosfixa(char *expressao,char *saida){
    No *pilha = NULL;
    int k=0;

    for(int i=0; i < strlen(expressao); i++){
        char c = expressao[i];

        if(c==' ')continue;

        if(isdigit(c)){
            saida[k++]=c;
        }else if(c=='('){
            push(&pilha,c);
        }else if(c==')'){
            while(!isEmpty(pilha)&&pilha->valor!='('){
                saida[k++]=pop(&pilha);
            }
            if(!isEmpty(pilha)&&pilha->valor=='('){
                pop(&pilha);
            }
        }else{
            while(!isEmpty(pilha) && prioridade(pilha->valor)>=prioridade(c)){
                saida[k++]=pop(&pilha);
            }
            push(&pilha,c);
        }
    }

    while(!isEmpty(pilha)){
        saida[k++]=pop(&pilha);
    }
    saida[k]='\0';
}


int main(){
    int opcao;
    char expressao[30];

    do{
        opcao=menu();
        switch(opcao){
            case 1: { 
            printf("> digite sua expressao:\n");
            int c;
            
            while ((c = getchar()) != '\n' && c != EOF);
            
            fgets(expressao, 30, stdin);
            expressao[strcspn(expressao, "\n")] = '\0';
            
           
            printf("[DEBUG] Expressao lida: '%s'\n", expressao);
            
            if(verificaParenteses(expressao)){
                char PosFixa[30];
                infixaParaPosfixa(expressao, PosFixa);
                printf("> expressao posfixa: %s\n", PosFixa);
                
            }else{
                printf("> expressao invalida\n");
            }
            break;
        } 
            case 2:
                printf(">desligando a calculadora\n");
                break;
            default:
                printf("!!opcao invalida!!\n");
                break;
        }

    }while(opcao!=2);
}

