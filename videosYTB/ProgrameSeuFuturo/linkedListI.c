#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *prox;
}No;

typedef struct{
    int tam_lista;
    No *inicio;
}Lista;//cabeca

void inserirInicio(Lista *lista,int valor){
/*  1. cria no
    2. linka o proximo*/
    No *novo = (No*)malloc(sizeof(No));//ponteiro de uma regiao alocada
    novo->valor = valor;//equivalente a (*novo).valor = novo
    novo->prox = lista->inicio;
    lista->inicio=novo;
    lista->tam_lista++;
}

void inserirFinal(Lista *lista, int valor){
    No *novo = (No*)malloc(sizeof(No));
    No *no;
    //cria o novo no apontando pro null
    novo->valor=valor;
    novo->prox = NULL;

    //precisa linkar o novo na lista
    if(lista->inicio==NULL){//novo é o primeiro no
        lista->inicio=novo;
        //lista->tam_lista++;
    }else{//mais de um no na lista
        no = lista->inicio;
        while(no->prox!=NULL)no=no->prox;
        no->prox = novo;
        //lista->tam_lista++;
    }
    lista->tam_lista++;

}

void remover(Lista *lista, int valor){
    No *inicio = lista->inicio;//nao posso perder a referencia para o inicio
    No *noARemover = NULL;//ponteiro auxiliar
    if(lista->inicio!=NULL&&lista->inicio->valor==valor){
        noARemover = lista->inicio;//nao posso perder a referencia para o inicio
        lista->inicio=noARemover->prox;//alterar o inicio
        
    }else{//tenho que percorrer minha lista para achar 
        while(inicio!=NULL&&inicio->prox !=NULL &&inicio->prox->valor!=valor){
            inicio=inicio->prox;
        }
        if(inicio!=NULL&&inicio->prox!=NULL){
            noARemover = inicio->prox;
            inicio->prox = noARemover->prox;
        }
        

    }

    if(noARemover){//pq se for o primeiro o null vai ser ignorado e vai continuar com tamnho 0
        free(noARemover);
        lista->tam_lista--;
    }

}

void imprime(Lista *lista){
    No *inicio = lista->inicio;
    while(inicio!=NULL){
        printf("%d ",inicio->valor);
        inicio= inicio->prox;
    }
    printf("\n");

}
int main(){
    Lista lista;
    lista.inicio= NULL;
    lista.tam_lista=0;
    int op,valor;

    do{
        printf("1. inserir no inicio\n");
        printf("2. imprimir\n");
        printf("3. sair\n");
        printf("4. inserir no final\n");
        printf("5. remover \n");
        scanf("%d",&op);
        switch(op){
            case 1: 
                printf("digite o valor inserido\n");
                scanf("%d",&valor);
                inserirInicio(&lista, valor);
                break;
            case 2:
                imprime(&lista);
                break;
            case 3:
                printf("fim\n");
                break;
            case 4:
                printf("digite o valor inserido\n");
                scanf("%d",&valor);
                inserirFinal(&lista,valor);
                break;
            case 5:
                printf("digite o valor a ser removido\n");
                scanf("%d",&valor);
                remover(&lista, valor);
                break;
            default:
                printf(">opcao invalida\n");
                break;
        }
    }while(op!=3);

    return 0;
}