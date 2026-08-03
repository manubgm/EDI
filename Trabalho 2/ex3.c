#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    char pasta[50];
    struct no *prox;
}No;

int isEmpty(No *topo){
   return topo==NULL;
}

int menu(){
    printf("|==========================================|\n");
    printf("|   BEM-VINDO AO SIMPLIFICADOR DE CAMINHOS  |\n");
    printf("|==========================================|\n");   
    printf("| 1. Simplificar caminho                    |\n");
    printf("| 2. Sair                                   |\n");  
    printf("|==========================================|\n");
    printf("Escolha uma opcao: ");
    int op;
    scanf("%d",&op);
    return op;
}

void push(No **topo, char pasta[]){
    No *novo = (No*)malloc(sizeof(No));
    if(novo==NULL){
        printf("erro de alocação");
        return;
    }
    strcpy(novo->pasta,pasta);
    novo->prox = *topo;
    *topo = novo;
}

int pop(No **topo, char pasta[]){
    if(isEmpty(*topo)){
      return 0;
    }

    No *aux = *topo;
    char saida[50];
    strcpy(saida,aux->pasta);
    *topo = aux->prox;
    free(aux);
    strcpy(pasta,saida);
    return 1;
}

int simplificaCaminho(char caminho[],char pasta[]){
    No *pilha = NULL;
    int erro=0;

    pasta[0]='\0';

    char *token = strtok(caminho,"/");

    while(token!=NULL){
        if(strcmp(token,".")==0){
         //ignora
        }else if(strcmp(token,"..")==0){
            char lixo[50];
            if(pop(&pilha,lixo)==0){
                erro=1;
                break;
            }
        }else{
            push(&pilha,token);
        }
        token = strtok(NULL,"/");
    }
    if(erro){
        strcpy(pasta,"Caminho invalido");
        return 0;
    }

    No *pilha_aux = NULL;
    while(!isEmpty(pilha)){
        char temp[50];
        if(pop(&pilha,temp)==0){
            break;
        }
        push(&pilha_aux,temp);
    }
    pasta[0]='\0';
    while(!isEmpty(pilha_aux)){
        char temp[50];
        if(pop(&pilha_aux,temp)==0){
            break;
        }
        strcat(pasta,"/");
        strcat(pasta,temp);
    }
    if(pasta[0]=='\0'){
        strcpy(pasta,"/");
    }
    return 1;

}

//uma pilha principal
/*c<-topo
projects
docs
user
home<-base*/

//sai do topo da principal pra base da aux

//uma pilha aux
/*
home<-topo
user
docs
projects
c-<base*/
int main(){
    int opcao = menu();
    switch(opcao){
        case 1:{ 
            char caminho[100];
            printf("Digite o caminho: ");
            scanf("%s",caminho);
            char pasta[50];
            simplificaCaminho(caminho,pasta);
            printf("Caminho simplificado: %s\n",pasta);
            break;
        }
        case 2:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
    }
}