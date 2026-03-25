/*função que insere no final*/
#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *prox;
}No;

typedef struct{
    struct no *inicio;
}Lista;

void inserirFinal(Lista *lista, int valor){
    No *novo = (No*)malloc(sizeof(No));//1
    novo->valor = valor; //1
    novo->prox = NULL;//2
    if(lista->inicio==NULL){//3
        lista->inicio=novo;
    }else{
    No *atual = lista->inicio;//4
    while(atual->prox!=NULL){
        atual=atual->prox;
    }
    
    atual->prox=novo;
    }

}