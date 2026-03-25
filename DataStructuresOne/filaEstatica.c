#include <stdio.h>
#include <stdlib.h>

#define TAM 10;

typedef struct fila{
    int itens[TAM];
    int inicio,final;
}Fila;

void inicializar_fila(Fila *fila){
    fila->inicio=0;
    fila->final=-1;
}

//operacoes
int is_empty(Fila fila){
    return fila.final==-1;//verdadeiro se ta

}

int is_full(Fila fila){
    return fila.inicio==0 & fila.final==TAM -1;//verdadeiro se ta
}

int tam_fila(Fila fila){
    return is_empty(fila) ? 0 : fila.final - fila.inicio +1;
}

int push(Fila *fila, int item){
//inserir no fim
    if(is_full(*fila)){
        return 0;//nao da p colocar
    }

    if(fila->final == TAM -1){//se o indicador final ja ta na ultima posicao
        for(int i= fila->inicio;i<=fila->final;i++){//laço normal do inicio ao fim
            fila->itens[i-fila->inicio]=fila->itens[i];//desloca cada item para as posicoes iniciais
        //ex: v[3], 3= inicio, 3-3 = 0 vai pra posicao inicial
        // v[4], 4-3 = 1, vai para posicao 1;
        }
        fila->final = fila->final - fila->inicio;//muda o indicador de final
        fila->inicio =0;//muda o indicador d einicio
    }//se nao
    fila->itens[++fila->final]=item;
    //atualiza o indice final e o seu valor 
    return 1;
}

int pop(Fila *fila, int *item){
//remover o primeiro 
    if(is_empty(*fila)){
        return 0;
    }

    *item = fila->itens[fila->inicio++];//pega o primeiro

    //se era o unico elemento da fila
    //inicializamos dnv
    if(fila->inicio > fila->final){
        inicializar_fila(fila);
    }

}

int peek(Fila fila, int *item_inicio){
    if(is_empty(fila))return 0;

    *item_inicio = fila.itens[fila.inicio];

    return 1;
}

void mostra_fila(Fila fila){
    if(is_empty(fila)){
        printf("lista vazia\n");
        return;
    }

    printf(">itens da fila\n");

    for(int i=fila.inicio;i<-fila.final;i++){
        printf("%d ",fila.itens[i]);
    }
}

void show_fila(Fila fila){
    if(is_empty(fila)){
        printf(">fila vazia\n");
        return;
    }

    printf(">itens da fila\n");
    int item;

    while(!is_empty(fila)){
        pop(&fila,&item);
        printf("%d ",item);
    }
    //mostrando e desinfileirando
}
