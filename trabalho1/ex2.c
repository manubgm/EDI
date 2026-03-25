//editor de texto
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct no{
    char conteudo[100];
    struct no *prox;//ponteiro que armazena o endereço do proximo no
}No;//apelido do no

No *historico = NULL;

//logica geral
//toda funcao que faz alguma alteracao no texto
//antes, salva a versao atual do texto


//salvar historico é vital para a logica do desfazer
//pois so podera desfazer usando partes salavas do texto anterior
// o no atual é sempre o mais recente

void salvarHistorico(No **topo, char *textoAtual){
    No *novo = (No*) malloc(sizeof(No)); //salva

    if(novo ==NULL){
        printf("memoria insuficiente\n");
        exit(1);
    }

    strcpy(novo->conteudo,textoAtual);//copia o atual para o novo no

    novo->prox = *topo;//a primeira posicao guardada em topo
    //o ponteiro prox do atual passa a apontar pra ela

    *topo = novo;
    //agora que o novo nó ja esta conectado voce atualiza
    //o novo no é a cabefca/no atual

    printf("estado salvo no historico\n");
}

void desfazer(No **topo, char *textoAtual){
    if(*topo==NULL){
        printf("historico vazio nao da pra desfazer\n");
        return;
    }

    No *aux = *topo;//ponteiro auxiliar para o no q vai ser removido

    strcpy(textoAtual, aux->conteudo);
    //textoAtual recebe o que tava no historico

    *topo = aux->prox;
    //topo passa apontar pro endereço do anterior
    //ou seja, remove o no do inicio da lista

    free(aux);//libera a memoria d eauxexpl

    printf("operacao desfeita\n");
}

int main(){
char textoAtual[100] = "";
No *historico = NULL;
int opcao;
char letra;

do {
        printf("\n--------------------------\n");
        printf("TEXTO ATUAL: \"%s\"\n", textoAtual);
        printf("--------------------------\n");
        printf("1. Digitar caractere\n");
        printf("2. Apagar ultimo (Backspace)\n");
        printf("3. Desfazer (Undo)\n");
        printf("4. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1:
                printf("Digite o caractere: ");
                scanf("%c", &letra);
                getchar(); 
                
                // Salva o estado ANTES de mudar 
                salvarHistorico(&historico, textoAtual);
                
                // Adiciona no final da string
                int tam = strlen(textoAtual);
                if (tam < 99) {
                    textoAtual[tam] = letra;
                    textoAtual[tam + 1] = '\0'; // finaliza a string
                }
                break;

            case 2:
                if (strlen(textoAtual) > 0) {
                    // Salva o estado ANTES de apagar 
                    salvarHistorico(&historico, textoAtual);
                    
                    // Remove o ultimo caractere
                    textoAtual[strlen(textoAtual) - 1] = '\0';
                } else {
                    printf("Texto ja esta vazio!\n");
                }
                break;

            case 3:
                // Recupera a versão anterior e libera memória 
                desfazer(&historico, textoAtual);
                break;
        }
    } while(opcao != 4);

    return 0;

}
