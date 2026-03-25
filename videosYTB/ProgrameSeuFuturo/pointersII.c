#include <stdio.h>
#include <stdlib.h>

void imprimirVetor(int *v, int tam){
    //*v indica que vou receber um ponteiro 
    //de int , que vai ser o nome do vetor
    for(int i=0;i<tam;i++){
        printf("%d ",*(v + i));
    }
}

void imprimirLetras(char *v, int tam){
    //*v indica que vou receber um ponteiro de vetor de char
    for(int i=0;i<tam;i++){
        printf("%c ",*(v+i));
    }
}

void preencheInt(int *v,int tam){
    for(int i=0;i<tam;i++){
        printf("digite um valor int: ");
        //scanf("%d",&v[i]);
        scanf("%d", v+i);//dessa forma como ja recebemos o ponteiro v ja é endereço
    }
}

int main(){
    int vet[10]={0,1,2,3,4,5,6,7,8,9};
    char letras[3]={'a','b','c'};

    preencheInt(vet, 10);//vet é passada por referencia 
    imprimirVetor(vet, 10);//vet é passsada por referencia
    printf("\n");
    imprimirLetras(letras, 3);
    return 0;
}