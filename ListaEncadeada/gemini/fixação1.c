#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *prox;
}No;

typedef struct{
    struct no *inicio;
}Lista;

int tamLista(Lista *lista){
    int count=0;

    No *atual = lista->inicio;
    while(atual!=NULL){
        atual=atual->prox;
        count++;
    }

    return count;
}

