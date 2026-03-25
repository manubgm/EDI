#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TAM 100  

typedef struct {
    int senhas[MAX_TAM]; 
    int ultimo;         // aponta pra ultima posição livre(vazia ou naao)
} ListaEstatica;

void criaLista(ListaEstatica *l){
    l->ultimo=0;//aponta pra 0, ou seja, a primeira posicao do vetor
}

int verifica(ListaEstatica *l, int senha){
    for(int i=0;i<l->ultimo;i++){
        if(l->senhas[i]==senha)return i; //retorna a posicao se achou
    }
    return -1;
}

void inserirOrdenado(ListaEstatica *l, int senha){
    if(l->ultimo >= MAX_TAM){ 
        printf("acabou o espaço na memoria declarada\n");
        return;
    }

    if(verifica(l,senha)!=-1)return;
    
    int i=l->ultimo-1;//começa na direita(maior)

    while(i>=0&&l->senhas[i]>senha){
        l->senhas[i+1]=l->senhas[i];//move p direita
        i--;
    }
    //isere no "buraco"
    l->senhas[i+1]=senha;
    l->ultimo++;

}

void removerMenor(ListaEstatica *l){
    if(l->ultimo==0){
        printf("lista vazia\n");
        return;
    }

    for(int i=0;i<l->ultimo-1;i++){
        l->senhas[i]=l->senhas[i+1];//pula uma posicao
    }
    l->ultimo--;
}

int menu(){
    printf(">escolha uma opcao<\n");
    printf("1. criar lista\n");
    printf("2. inserir numeros aleatorios no vetor\n");
    printf("3. mostrar vetor\n");
    printf("4. remover menor algarismo\n");
    printf("5. sair\n");
    int resp;
    scanf("%d",&resp);
    return resp;
}

void printarVetor(ListaEstatica l){
printf("> mostrando vetor completo:\n");
    for(int i=0;i<10;i++){
        printf("v[%d]= %d\n",i,l.senhas[i]);
    }   
}

int main() {
    srand(time(NULL));
    ListaEstatica minhaLista;
    int opcao=menu();

    while(opcao!=5){

        switch(opcao){
            case 1:
                criaLista(&minhaLista);
                
                break;
            case 2:
                printf("> gerando 10 senhas aleatorias:\n");
                for(int i=0;i<10;i++){
                    int novaSenha = rand()%500;
                    inserirOrdenado(&minhaLista,novaSenha);
                }
                
                printf(">finalizado\n");
                break;
            case 3:
                printarVetor(minhaLista);
                
                break;
            case 4:
                removerMenor(&minhaLista);
                
                break;
            }
            opcao=menu();
    }

    printf(">saindo\n");
    return 0;
}