/*Escreva uma função chamada inserirInicio que 
receba a nossa lista e um valor inteiro. 
Dentro dela, você deve:

Usar o malloc para criar um novo nó na memória. 

Atribuir o valor a esse novo nó. 

Fazer esse novo nó apontar para onde a lista
 apontava antes. 

Atualizar o início da lista para ser esse novo nó.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *prox;
}No;

typedef struct{
    struct no *inicio;
}Lista;


void inserirInicio(Lista *lista,int valor){//0. criei a função
    No *novo = (No*)malloc(sizeof(No));//1. criei novo no com malloc
    novo->valor=valor;//2. atribui o valor
    novo->prox=lista->inicio;//3.novo aponta para onde a lista apontava
    lista->inicio=novo;//4. atualizar o inicio da lista para o novo no
}