//aprovitar as fucnoes de fila do 4
#include <stdio.h>
#include <string.h>

#define MAX 100
typedef struct {
    char vetor[MAX][10]; 
    int inicio;
    int fim;
    int qtd;
} Fila;

void inicializa(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
}

int isEmpty(Fila *f) {
    return f->qtd == 0;
}

int enfila(Fila *f, char *placa) {
    if (f->qtd == MAX) return 0;
    
    strcpy(f->vetor[f->fim], placa);
    f->fim = (f->fim + 1) % MAX;
    f->qtd++;
    return 1;
}

int desenfila(Fila *f, char *saida) {
    if (isEmpty(f)) return 0; 
    
    strcpy(saida, f->vetor[f->inicio]);
    f->inicio = (f->inicio + 1) % MAX;
    f->qtd--;
    return 1;
}

// ai agr raciocinio do 5
void imprimirFila(Fila *f, char *nomeDirecao) {
    printf("Fila %s: ", nomeDirecao);
    if (isEmpty(f)) {
        printf("[Vazia]\n");
        return;
    }
    
    int tamanho = f->qtd;
    char placa_temp[10];
    
    for (int i = 0; i < tamanho; i++) {
        desenfila(f, placa_temp);
        printf("[%s] ", placa_temp);
        enfila(f, placa_temp); //para o fim
    }
    printf("\n");
}

void abrirSemaforo(Fila *f, int quantidade, char *nomeDirecao) {
    printf("> Semaforo %s ABERTO. Liberando ate %d carros...\n", nomeDirecao, quantidade);
    
    char placa_removida[10];
    int carros_passaram = 0;
    
    //desenfileirar 
    for (int i = 0; i < quantidade; i++) {
        if (desenfila(f, placa_removida)) {
            printf("  - Carro %s atravessou o cruzamento.\n", placa_removida);
            carros_passaram++;
        } else {
            // s a fila esvaziar antes de quantidad o laço para
            break; 
        }
    }
    
    if (carros_passaram == 0) {
        printf("  (Nenhum carro aguardando nesta direcao)\n");
    }
}

int main() {
    Fila ns, lo;
    inicializa(&ns); 
    inicializa(&lo); 
    
    char comando[20], direcao[5], placa[10];
    int n;

    printf("==========================================\n");
    printf("   SIMULADOR DE CRUZAMENTO (2 FILAS)      \n");
    printf("==========================================\n");
    printf("Comandos:\n");
    printf("- chega NS <placa>  | chega LO <placa>\n");
    printf("- abrir NS <n>      | abrir LO <n>\n");
    printf("- status\n");
    printf("- sair\n");
    printf("------------------------------------------\n");

    while (1) {
        printf("\n> Comando: ");
        scanf("%s", comando);

        if (strcmp(comando, "chega") == 0) {
            scanf("%s %s", direcao, placa); 
            
            if (strcmp(direcao, "NS") == 0) {
                enfila(&ns, placa);
                printf("> Carro %s entrou na fila Norte-Sul.\n", placa);
            } else if (strcmp(direcao, "LO") == 0) {
                enfila(&lo, placa);
                printf("> Carro %s entrou na fila Leste-Oeste.\n", placa);
            } else {
                printf("> Direcao invalida!\n");
            }
        } 
        else if (strcmp(comando, "abrir") == 0) {
            scanf("%s %d", direcao, &n); 
            
            if (strcmp(direcao, "NS") == 0) {
                abrirSemaforo(&ns, n, "Norte-Sul");
            } else if (strcmp(direcao, "LO") == 0) {
                abrirSemaforo(&lo, n, "Leste-Oeste");
            } else {
                printf("> Direcao invalida!\n");
            }
        } 
        else if (strcmp(comando, "status") == 0) {
            printf("\n--- STATUS DO CRUZAMENTO ---\n");
            imprimirFila(&ns, "NS"); 
            imprimirFila(&lo, "LO");
            printf("----------------------------\n");
        } 
        else if (strcmp(comando, "sair") == 0) {
            printf("> Encerrando simulador...\n");
            break;
        } 
        else {
            printf("> Comando invalidl.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }

    return 0;
}