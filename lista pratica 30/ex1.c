//Simulação de Manobrista em Estacionamento
//implementação com fila
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

typedef struct no{
    char placa[10];
    struct no *prox;
}No;

//informar quantos carros foram retirados para permitir a saida
//OS CARROS ENTRAM E SAEM PELO MESMO PORTAO = PILHA 


int is_empty(No *topo){
    return(topo==NULL);//1 p vazia
}

//insere no topo
int push(No **topo, char *p){
    No *novo = (No*)malloc(sizeof(No));
    if(novo==NULL)return 0;

    strcpy(novo->placa,p);
    novo->prox=*topo;
    *topo=novo;
    return 1;
}

//remove do topo
int pop(No **topo,char *placa_dest){
    if(is_empty(*topo))return 0;

    No *aux = *topo;
    strcpy(placa_dest, aux->placa); // "Devolve" a placa para quem chamou a função
    *topo = aux->prox;          // Move o topo para baixo
    free(aux);                  // Deleta o nó da memória
    return 1;


    //se tiver carro antes tem q puxar a fila aux
    //fazer outra funcao saindo
    //tirar e consertar o restante

}

void saindo(No **estacionamento,No **auxiliar, char *alvo){
    char placa_temp[10];
    int count=0;

    //buscando o alvo
    while(!is_empty(*estacionamento)&&strcmp((*estacionamento)->placa,alvo)!=0){
        pop(estacionamento,placa_temp);//tiro do estacionamento
        push(auxiliar,placa_temp);//colocar na aux pra nao perder
        count++;//conta p mopstrar 
    }

    //remove com pop
    if(!is_empty(*estacionamento)){
        pop(estacionamento,placa_temp);
        printf("carro escolhido: %s saindo.\n >manobras: %d \n",alvo,count);
    }else{
        printf("carro %s nao encontrado",alvo);
    }

    //devolver da auxiliar pro estacionamento
    while(!is_empty(*auxiliar)){
        pop(auxiliar, placa_temp);
        push(estacionamento,placa_temp);
    }
}

int menu(){
    printf("Bem vindo ao Estacionamento\n");
    printf("1. Entrar com carro\n");
    printf("2. Sair com carro (selecione o carro)\n");
    printf("3. Status do estacionamento (ordem atual dos carros)\n");
    printf("4. Sair");;
    printf(">escolha opcao:\n");
    int opcao;
    scanf("%d",&opcao);
    return opcao;
}

int main() {
    // 1. Inicialização das Pilhas
    No *estacionamento = NULL;
    No *auxiliar = NULL;
    int op;
    char nome[20]; // Aumentado para 20 para evitar estouro de memória com espaços

    do {
        op = menu();

        // Isso remove o '\n' que sobraria para o próximo fgets
        while (getchar() != '\n'); 

        switch (op) {
            case 1:
                printf("\n> Opcao 1: Entrada de Veiculo\n");
                printf("Digite a placa (ex: ABC 1234): ");
                fgets(nome, 20, stdin);
                //remove o \n
                nome[strcspn(nome, "\n")] = '\0';

                if (push(&estacionamento, nome)) {
                    printf(">> Carro [%s] estacionado com sucesso!\n", nome);
                } else {
                    printf(">> Erro: Falha de memoria ao estacionar.\n");
                }
                break;

            case 2:
                printf("\n> Opcao 2: Saida de Veiculo\n");
                if (is_empty(estacionamento)) {
                    printf(">> O estacionamento ja esta vazio!\n");
                } else {
                    printf("Digite a placa do carro para sair: ");
                    fgets(nome, 20, stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    // Chama a função de manobra passando as duas pilhas
                    saindo(&estacionamento, &auxiliar, nome);
                }
                break;

            case 3:
                printf("\n--- Status do Estacionamento (Saida -> Fundo) ---\n");
                if (is_empty(estacionamento)) {
                    printf("Nenhum carro estacionado.\n");
                } else {
                    char temp[20];
                    int vagas_ocupadas = 0;

                    //desempilhar para mostrar
                    while (!is_empty(estacionamento)) {
                        printf("[%d] Placa: %s\n", vagas_ocupadas + 1, estacionamento->placa);
                        pop(&estacionamento, temp);
                        push(&auxiliar, temp);
                        vagas_ocupadas++;
                    }
                    printf("Total de vagas ocupadas: %d\n", vagas_ocupadas);

                    // Rempilhar dnv pra voltar pro estacionamento
                    while (!is_empty(auxiliar)) {
                        pop(&auxiliar, temp);
                        push(&estacionamento, temp);
                    }
                }
                break;

            case 4:
                printf("\n>> Encerrando sistema de manobrista...\n");
                break;

            default:
                printf("\n!! Opcao invalida. Tente novamente !!\n");
                break;
        }

    } while (op != 4);

    return 0;
}