#include <stdio.h>

typedef struct no{
    int valor;
    struct no *prox;
}No;

int is_Empty(No *topo){
    return topo==NULL;
}

void push(No **topo,int valor){
    No *novo = (No*)malloc(sizeof(No));
    
    if(novo==NULL)return;

    novo->valor=valor;
    novo->prox=*topo;
    *topo=novo;
}