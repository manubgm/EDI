#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define MAX 100
//ainda com a circular 
typedef struct {
    char nome[20];
    int tempo;
    int prioridade;
} Tarefa;

typedef struct {
    Tarefa vetor[MAX];
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

int enfila(Fila *f, Tarefa t) {
    if (f->qtd == MAX) return 0;
    f->vetor[f->fim] = t;
    f->fim = (f->fim + 1) % MAX;
    f->qtd++;
    return 1;
}

int desenfila(Fila *f, Tarefa *saida) {
    if (isEmpty(f)) return 0;
    *saida = f->vetor[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->qtd--;
    return 1;
}

//raciocinio do 5 aq
void imprimirFilaPrioridade(Fila *f, char *nomeFila) {
    if (isEmpty(f)) return; 
    
    int tamanho = f->qtd;
    Tarefa t;
    printf("  [%s]: ", nomeFila);
    
    for (int i = 0; i < tamanho; i++) {
        desenfila(f, &t);
        printf("%s(%ds) ", t.nome, t.tempo);
        enfila(f, t); //devolve para a fila
    }
    printf("\n");
}

void processarTarefa(Fila *alta, Fila *media, Fila *baixa) {
    Fila *fila_alvo = NULL;
    Tarefa t;
    if (!isEmpty(alta)) {
        fila_alvo = alta;
    } else if (!isEmpty(media)) {
        fila_alvo = media;
    } else if (!isEmpty(baixa)) {
        fila_alvo = baixa;
    } else {
        printf("> Nenhuma tarefa pendente para processamento.\n");
        return;
    }

    desenfila(fila_alvo, &t);
    int tempo_execucao = (t.tempo > 2) ? 2 : t.tempo;
    
    printf("> Executando '%s' por %ds...\n", t.nome, tempo_execucao);
    sleep(tempo_execucao); // delay pro processamento
    
    t.tempo -= tempo_execucao;

    if (t.tempo > 0) {
        printf("  (Tarefa pausada. Restam %ds - Retornando para a fila)\n", t.tempo);
        enfila(fila_alvo, t); // volta para o fim da mesma fila de prioridade
    } else {
        printf("  (Tarefa '%s' CONCLUIDA e removida da fila!)\n", t.nome);
    }
}
int main() {
    Fila alta, media, baixa;
    inicializa(&alta);
    inicializa(&media);
    inicializa(&baixa);
    
    char comando[20];
    Tarefa nova_t;

    printf("==========================================\n");
    printf("    PROCESSADOR COM PRIORIDADE \n");
    printf("==========================================\n");
    printf("Comandos disponiveis:\n");
    printf(" - add <nome> <tempo> <prioridade (3,2,1)>\n");
    printf(" - processar\n");
    printf(" - status\n");
    printf(" - sair\n");
    printf("------------------------------------------\n");
    
    while (1) {
        printf("\n> Comando: ");
        scanf("%s", comando);

        if (strcmp(comando, "add") == 0) {
            scanf("%s %d %d", nova_t.nome, &nova_t.tempo, &nova_t.prioridade);
            
            if (nova_t.prioridade == 3) {
                enfila(&alta, nova_t);
                printf("> '%s' adicionada a fila ALTA.\n", nova_t.nome);
            } else if (nova_t.prioridade == 2) {
                enfila(&media, nova_t);
                printf("> '%s' adicionada a fila MEDIA.\n", nova_t.nome);
            } else if (nova_t.prioridade == 1) {
                enfila(&baixa, nova_t);
                printf("> '%s' adicionada a fila BAIXA.\n", nova_t.nome);
            } else {
                printf("> Erro: Prioridade deve ser 3, 2 ou 1.\n");
            }
        } 
        else if (strcmp(comando, "processar") == 0) {
            processarTarefa(&alta, &media, &baixa);
        } 
        else if (strcmp(comando, "status") == 0) {
            printf("\n--- STATUS DAS FILAS ---\n");
            if (isEmpty(&alta) && isEmpty(&media) && isEmpty(&baixa)) {
                printf("  Todas as filas estao vazias.\n");
            } else {
                imprimirFilaPrioridade(&alta, "ALTA");
                imprimirFilaPrioridade(&media, "MEDIA");
                imprimirFilaPrioridade(&baixa, "BAIXA");
            }
            printf("------------------------\n");
        } 
        else if (strcmp(comando, "sair") == 0) {
            printf("> Encerrando sistema...\n");
            break;
        } 
        else {
            printf("> Comando invalido. Use: add, processar, status, sair.\n");
            int c; while ((c = getchar()) != '\n' && c != EOF);
        }
    }

    return 0;
}