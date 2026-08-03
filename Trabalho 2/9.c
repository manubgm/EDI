#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Para a função sleep()

// 1. A CARGA DO DEQUE
typedef struct {
    char nome[30];
    int tempo;
} Tarefa;

// 2. A ESTRUTURA DO DEQUE DINÂMICO
typedef struct no {
    Tarefa info;
    struct no *prox;
} No;

typedef struct {
    No *inicio;
    No *fim;
    int qtd;
} Deque;

void inicializa(Deque *d) {
    d->inicio = NULL;
    d->fim = NULL;
    d->qtd = 0;
}

int isEmpty(Deque *d) {
    return d->inicio == NULL;
}

// COMPORTAMENTO DE FILA (Adiciona no fim)
int insereFim(Deque *d, Tarefa t) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) return 0;
    
    novo->info = t;
    novo->prox = NULL;
    
    if (isEmpty(d)) d->inicio = novo;
    else d->fim->prox = novo;
    
    d->fim = novo;
    d->qtd++;
    return 1;
}

// COMPORTAMENTO DE PILHA (Adiciona no início) - Usado para o histórico e o UNDO
int insereInicio(Deque *d, Tarefa t) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) return 0;
    
    novo->info = t;
    novo->prox = d->inicio; // O novo aponta para quem era o início antigo
    
    d->inicio = novo;       // O início passa a ser o novo
    if (d->fim == NULL) {
        d->fim = novo;      // Se estava vazio, ele também é o fim
    }
    
    d->qtd++;
    return 1;
}

// COMPORTAMENTO COMPARTILHADO (Remove do início) - Usado pela Pilha e pela Fila
int removeInicio(Deque *d, Tarefa *saida) {
    if (isEmpty(d)) return 0;
    
    No *aux = d->inicio;
    *saida = aux->info;
    
    d->inicio = d->inicio->prox;
    if (d->inicio == NULL) d->fim = NULL; // Regra de ouro
    
    free(aux);
    d->qtd--;
    return 1;
}

// 3. REGRAS DE NEGÓCIO

void executarTarefa(Deque *aguardando, Deque *historico) {
    Tarefa t;
    
    // Tira do início da Fila (FIFO)
    if (removeInicio(aguardando, &t)) {
        printf("> Executando: %s\n", t.nome);
        sleep(t.tempo); // Simula o processamento
        printf("  (concluida)\n");
        
        // Coloca no início do Histórico (LIFO)
        insereInicio(historico, t);
    } else {
        printf("> Fila de tarefas aguardando esta vazia.\n");
    }
}

void desfazerTarefa(Deque *aguardando, Deque *historico) {
    Tarefa t;
    
    // Tira do início do Histórico (Desempilha o mais recente)
    if (removeInicio(historico, &t)) {
        // Coloca de volta no INÍCIO da Fila de espera
        insereInicio(aguardando, t);
        printf("> Tarefa \"%s\" retornou para a fila.\n", t.nome);
    } else {
        printf("> Nenhuma tarefa no historico para desfazer.\n");
    }
}

void mostrarStatus(Deque *aguardando, Deque *historico) {
    Tarefa t;
    printf("\n--- STATUS DO PROCESSADOR ---\n");
    
    // Mostrando tarefas aguardando (girando a fila com insereFim)
    printf("1. Aguardando execucao:\n");
    if (isEmpty(aguardando)) printf("   [Vazio]\n");
    for (int i = 0; i < aguardando->qtd; i++) {
        removeInicio(aguardando, &t);
        printf("   - %s (%ds)\n", t.nome, t.tempo);
        insereFim(aguardando, t); // Devolve para trás
    }
    
    // Mostrando o histórico (girando a pilha com insereFim, mantendo a ordem correta no final)
    printf("\n2. Historico de concluidas (mais recentes primeiro):\n");
    if (isEmpty(historico)) printf("   [Vazio]\n");
    for (int i = 0; i < historico->qtd; i++) {
        removeInicio(historico, &t);
        printf("   - %s (%ds)\n", t.nome, t.tempo);
        insereFim(historico, t); 
    }
    printf("-----------------------------\n");
}

// 4. O MAIN E LEITURA DE COMANDOS
int main() {
    Deque fila_aguardando, pilha_historico;
    inicializa(&fila_aguardando);
    inicializa(&pilha_historico);
    
    char comando[20];
    Tarefa nova_t;

    printf("==========================================\n");
    printf("   PROCESSADOR DE TAREFAS COM DEQUE       \n");
    printf("==========================================\n");
    printf("Comandos:\n");
    printf(" - add <nome> <tempo>\n");
    printf(" - run\n");
    printf(" - undo\n");
    printf(" - status\n");
    printf(" - sair\n");
    printf("------------------------------------------\n");

    while (1) {
        printf("\n> Comando: ");
        scanf("%s", comando);

        if (strcmp(comando, "add") == 0) {
            scanf("%s %d", nova_t.nome, &nova_t.tempo);
            insereFim(&fila_aguardando, nova_t);
            printf("> Tarefa '%s' adicionada a fila.\n", nova_t.nome);
        } 
        else if (strcmp(comando, "run") == 0) {
            executarTarefa(&fila_aguardando, &pilha_historico);
        } 
        else if (strcmp(comando, "undo") == 0) {
            desfazerTarefa(&fila_aguardando, &pilha_historico);
        } 
        else if (strcmp(comando, "status") == 0) {
            mostrarStatus(&fila_aguardando, &pilha_historico);
        } 
        else if (strcmp(comando, "sair") == 0) {
            printf("> Encerrando simulador...\n");
            break;
        } 
        else {
            printf("> Comando invalido!\n");
            int c; while ((c = getchar()) != '\n' && c != EOF);
        }
    }

    return 0;
}