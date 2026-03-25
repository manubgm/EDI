#include <stdio.h>
#include <stdlib.h>
#define TAM 10;

typedef struct fila{
    int inicio,final;
    int itens[TAM];
    int tam_atual;
}Fila;

void inicia(Fila *fila){
    fila->inicio=fila->final=-1;//inicia em uma posicao inexistente
    fila->tam_atual=0;
}

int is_full(Fila fila){
    return (fila.final+1)% TAM == fila.inicio;//se verdadeiro
}

int tam_fila(Fila fila){
    return fila.tam_atual;
}

int push(Fila *fila, int item){
    //nao precisamos fazer deslocamentos na  fila circular
    //temos que observar qnd colcoar um item se a ultima posicao esta ocupada
    if(is_full(*fila)){
        return 0;
    }
    
    //como incializamos inicio=final=-1 (inexistente) temos que atualizar o inicio
    if(fila->inicio==-1){
        fila->inicio=0;
    }
    //também atualizamos o final
    fila->final = (fila->final +1)%TAM;

    fila->itens[fila->final]=item;//adiciona o item no final
    fila->tam_atual++; //incrementando o tamanho atual da fila
    return 1;
}

int pop(Fila *fila, int *item){
    if(is_empty(*fila))return 0;

    *item = fila->itens[fila->inicio];

    //fila com um elemento
    if(fila->inicio == fila->final){
        inicia(fila);
    }else{//com mais 
        fila->inicio = (fila->inicio +1)%TAM;//calculo do circular
        fila->tam_atual--;//decrementa tamanho
    }
    return 1;

}

void show(Fila fila){
    if(is_empty(fila)){
        printf(">fila vazia\n");
        return;
    }
    printf(">itens da fila circular\n");

    int i=fila.inicio;

    //final fica de fora
    while(i!=fila.final){
        printf("%d ",fila.itens[i]);
        i= (i+1)%TAM;//isso acontece pq o inicio pode ser > final por ser circular
    }
    //mostra final
    printf("%d\n",fila.itens[fila.final]);
}