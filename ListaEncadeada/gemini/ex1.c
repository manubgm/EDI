/*Escreva a declaração 
de uma struct para uma lista encadeada que guarde
um número inteiro. Use typedef para que o apelido
da estrutura seja No. 
Além disso, declare no seu código uma variável 
que represente uma lista chamada minhaLista 
inicialmente vazia.*/
#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *prox;
}No;
int main(){
    No *minhaLista=NULL;
    return 0;
}