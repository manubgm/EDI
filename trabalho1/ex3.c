#include <stdio.h>
#include <stdlib.h>>

typedef struct no{
    int valor;
    struct no *prox;
}No;

void insiraOrdenado(No **topo, int v){
    No *novo = (No*) malloc(sizeof(No));

    if(novo==NULL)return;
    
    novo->valor=v;
    
    if(*topo==NULL||(*topo)->valor>=v){
        //se alista for vazia ou o valor v ser o menor
        novo->prox= *topo;
        *topo=novo;
        //insere no inicio
    }else{
        No *atual = *topo;//ponteiro aux atual
            while(atual->prox !=NULL && atual->prox->valor <v){
                atual = atual->prox;    
            }
        novo->prox = atual->prox;
        atual->prox=novo;

    }
}

void imprime(No *topo){
printf(">lista:\n");

    No *atual = topo;

    while(atual != NULL){
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }

}

void removerMenores(No **topo, int k){

    // remover do início
    while(*topo != NULL && (*topo)->valor < k){
        No *temp = *topo;
        *topo = (*topo)->prox;
        free(temp);
    }

    // remover do restante da lista
    No *atual = *topo;

    while(atual != NULL && atual->prox != NULL){

        if(atual->prox->valor < k){
            No *temp = atual->prox;
            atual->prox = temp->prox;
            free(temp);
        }
        else{
            atual = atual->prox;
        }
    }
}

int menu(){
    printf(">menu<\n");
    printf("1. inserir numero na lista\n");
    printf("2. remover numeros menores que k\n");
    printf("3. imprimir lista\n");
    printf("4. sair\n");
    int resp;
    scanf("%d",&resp);
    return resp;
}

int main(){
No *topo = NULL; 
    int opcao = menu(); 
    do{

        switch(opcao){

            case 1:{
                int v;
                printf("digite um numero:\n");
                scanf("%d",&v);

                insiraOrdenado(&topo,v);
                break;
            }

            case 2:{
                int k;
                printf("remover menores que:\n");
                scanf("%d",&k);

                removerMenores(&topo,k);
                break;
            }

            case 3:
                imprime(topo);
                break;
        }

        opcao = menu();

    }while(opcao != 4);

    printf("saindo...\n");

    return 0;    
}