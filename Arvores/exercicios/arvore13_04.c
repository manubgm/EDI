#include <stdio.h>
#include <stdlib.h>

int GRAU;  

typedef struct vertice{
    char item;
    struct vertice *filho_esquerdo;
    struct vertice *irmao_direito;
}*Arvore;

void incializar_arvore(Arvore *arvore){
    *arvore=NULL;
}

//pra ler os char
void limpar_buffer(){
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}

Arvore criar_vertice(char item){
    Arvore vertice = (Arvore) malloc(sizeof(struct vertice));

    vertice->item = item;//atribui

    vertice->filho_esquerdo = NULL;
    vertice->irmao_direito = NULL;

    return vertice;
}

void criar_filhos(Arvore pai, int qtd_filhos){
    printf("> leitura dos filhos de >%c<\n", pai->item);

    for(int i=1;i<=qtd_filhos;i++){
        printf(">filho #%d de %c\n",i,pai->item);
        char ifilho = getchar();
        limpar_buffer();

        Arvore filho = criar_vertice(ifilho);

        switch(i){
            case 1:
                pai->filho_esquerdo = filho;
                break;
            case 2:
                pai->irmao_direito = filho;
                break;
        }
    }
}

void criar_arvore(Arvore raiz){
    int qtd_filhos;
    printf("Digite a quantidade de filhos para o vértice %c: ", raiz->item);
    scanf("%d",&qtd_filhos);
    limpar_buffer();

    if(qtd_filhos<=0){
        return;
    }

    if(qtd_filhos > GRAU){
        qtd_filhos = GRAU;
    }

    //chama a funcao que real vai ler os vertices filhos
    criar_filhos(raiz,qtd_filhos);

    //chama a criar_arvores dnv para cada filho
    if(raiz->filho_esquerdo != NULL){
        criar_arvore(raiz->filho_esquerdo);
    }
    if(raiz->irmao_direito != NULL){
        criar_arvore(raiz->irmao_direito);
    }

}

void mostrar_arvore(Arvore arvore){
    if(arvore==NULL){
        return;
    }


}

char find_menor(Arvore raiz, char menor_atual){
    if(raiz==NULL){
        printf("Árvore vazia ou fim da árvore alcançado.\n");
        return menor_atual; // Retorna o menor encontrado até agora
    }

    if(raiz->item < menor_atual){
        menor_atual = raiz->item;
    }

    char menor_esquerdo = find_menor(raiz->filho_esquerdo, menor_atual);
    char menor_direito = find_menor(raiz->irmao_direito, menor_atual);

    //compara os dois e retorna o menor
    return (menor_esquerdo < menor_direito) ? menor_esquerdo : menor_direito;
}

int main(){
    Arvore arvore;
    incializar_arvore(&arvore);

    printf("Digite o grau da árvore (máximo de filhos por vértice): ");
    scanf("%d", &GRAU);
    limpar_buffer(); 

    printf("Digite o valor da raiz: ");
    char valor = getchar();
    limpar_buffer();

    arvore = criar_vertice(valor);

    criar_arvore(arvore);

    printf("\n\nÁrvore criada com sucesso!\n");

    printf("Menor valor na árvore: %c\n", find_menor(arvore, arvore->item));
    



    return 0;
}


