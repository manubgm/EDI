#include <stdio.h>
#include <stdlib.h>

int main(){
    int vet[10]={0,1,2,3,4,5,6,7,8,9};
    //lembrando que os endereços dos itens de vetores sao consecutivos
    int i;

    printf("%p\t%p\n",vet,&vet[0]);
//o nome do vetor é o endereço inicial do vetor 
//logo, vet == &vet[o], ou seja, sao equivalentes

    for(int i=0;i<10;i++){
        //aritimetica de ponteiro
        //soma de um ponteiro + int, 
        //o endereço de meória vet + i sempre da o endereço de memoria da posicao i
        printf("%d ",*(vet+i));
        //equivalente a vet[i];
        //se fizer *vet+i sem parenteses vai somar i ao conteudo
        //printf("%d",*vet); imprime 0, que é o conteudo que esta na no endereço

    }
}