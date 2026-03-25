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

void imprimirLista(Lista *lista){
    if(lista->inicio==NULL){
        printf("lista vazia\n");
        return;
    }
    No *atual = lista->inicio;
    while(atual!=NULL){
        printf("%d ",atual->valor);
        
        atual= atual->prox;
    }
    printf("\n");
}


int tamLista(Lista *lista){
    int count=0;

    No *atual = lista->inicio;
    while(atual!=NULL){
        atual=atual->prox;
        count++;
    }

    return count;
}



int main(){
    Lista lista;
    lista.inicio=NULL;

    int num;
    int op,valor;
    do{
        printf("1. inserir no inicio\n");
        printf("2.inserir no final\n");
        printf("3. imprimir\n");
        printf("4. sair\n");
        printf("5. contar tamanho\n");
        scanf("%d",&op);
        switch(op){
            case 1:
                printf("1. qual numero deseja inserir?");
                scanf("%d",&valor);
                inserirInicio(&lista,valor);
                break;
            case 2:
                printf("2. qual numero deseja inserir?");
                scanf("%d",&valor);
                inserirFinal(&lista,valor);
                break;
            case 3:
                printf("3. imprimindo");
                imprimirLista(&lista);
                break;
            case 4:
                printf("saindo\n");
                break;
            case 5:
                num =tamLista(&lista);
                printf("5. a lista tem %d de tamanho\n",num);
            default:
                printf("opcao invalida\n");
                
                
        }

    }while(op!=4);
}