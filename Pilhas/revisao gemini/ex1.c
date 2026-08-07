#include <stdio.h>

#define MAX 10

typedef struct{
    int itens[MAX];
    int topo;
}PilhaE;

void inicia(PilhaE *p){
    p->topo= -1;
}

int push(PilhaE *p,int item){
    if(p->topo==(MAX-1)){
        printf("pilha cheia\n");
            return 0;
        }
    p->topo=p->itens[++p->topo];
    printf("item %d empilhado\n",item);
}

int main(){
    PilhaE p;
    inicia(&p);

    push(&p,32);
}