#include <stdio.h>
#include <stdlib.h>

//EXERCICIO: qnd tiver um impar coloca o triplo dele após
//fila original: 2 3 4 5 6 
//fila esperada: 2 3 9 4 5 15 6
#define TAM 10;
typedef struct fila{
    int valor[TAM];
    int inicio,final;
}Fila;

void incia(Fila *fila){
    fila->inicio=0;
    fila->final=-1;
}

int is_empty(Fila fila){
    return fila.final==-1;
}

int is_full(Fila fila){
    return fila.final==TAM-1 && fila.inicio==0;
}

int push(Fila *fila, int item){
    if(is_full(*fila))return 0;

    if(fila->final==TAM-1){
        for(int i = fila->inicio;i<=fila->final;i++){
            fila->valor[i-fila->inicio]=fila->valor[i];
        }
        fila->final = fila->final - fila->inicio;
        fila->inicio=0;
    }
    fila->valor[++fila->final]=item;
    return 1;
}

void triplo_impar(Fila *fila, int *item){
    if(is_empty(*fila)||is_full(*fila))return 0;//nao da pra fazer se ta vazia ou cheia

    




}