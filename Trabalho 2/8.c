#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. ESTRUTURAS ESPECÍFICAS DAS TAREFAS
typedef struct {
    char pasta[50];
    int tamanho;
} TarefaBackup;

typedef struct {
    char destinatario[50];
    char assunto[50];
} TarefaEmail;

typedef struct {
    char nome[50];
    int paginas;
} TarefaRelatorio;

// 2. A "ETIQUETA" E O PONTEIRO GENÉRICO
typedef enum { BACKUP, EMAIL, RELATORIO } TipoTarefa;

// O nó agora guarda a etiqueta e o ponteiro void*
typedef struct {
    TipoTarefa tipo; // Identificador [cite: 230]
    void *dados;     // Ponteiro genérico para a struct correspondente [cite: 231]
} ElementoFila;

// 3. O TAD DA FILA DINÂMICA
typedef struct no {
    ElementoFila info;
    struct no *prox;
} No;

typedef struct {
    No *inicio;
    No *fim;
    int qtd;
} FilaDinamica;

void inicializa(FilaDinamica *f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->qtd = 0;
}

int isEmpty(FilaDinamica *f) {
    return f->inicio == NULL;
}

// enfila e desenfila são IDÊNTICOS ao exercício 7
int enfila(FilaDinamica *f, ElementoFila e) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) return 0;
    
    novo->info = e;
    novo->prox = NULL;
    
    if (isEmpty(f)) f->inicio = novo;
    else f->fim->prox = novo;
    
    f->fim = novo;
    f->qtd++;
    return 1;
}

int desenfila(FilaDinamica *f, ElementoFila *saida) {
    if (isEmpty(f)) return 0;
    
    No *aux = f->inicio;
    *saida = aux->info;
    
    f->inicio = f->inicio->prox;
    if (f->inicio == NULL) f->fim = NULL;
    
    free(aux); // Libera o "caixote" da fila, mas NÃO libera o void* ainda!
    f->qtd--;
    return 1;
}

// 4. REGRAS DE NEGÓCIO

void executarTarefa(FilaDinamica *f) {
    ElementoFila e;
    
    if (desenfila(f, &e)) { // Remove do início [cite: 240]
        printf("> Executando ");
        
        // Descobre o que o void* está apontando e faz o "Cast" (conversão)
        switch (e.tipo) {
            case BACKUP: {
                // Dizemos ao C que aquele void* na verdade é um TarefaBackup*
                TarefaBackup *b = (TarefaBackup*) e.dados;
                printf("BACKUP: pasta %s, tamanho %d GB\n", b->pasta, b->tamanho);
                break;
            }
            case EMAIL: {
                TarefaEmail *em = (TarefaEmail*) e.dados;
                printf("EMAIL: destinatario=%s, assunto=%s\n", em->destinatario, em->assunto);
                break;
            }
            case RELATORIO: {
                TarefaRelatorio *r = (TarefaRelatorio*) e.dados;
                printf("RELATORIO: nome %s, paginas=%d\n", r->nome, r->paginas);
                break;
            }
        }
        
        // REGRA OBRIGATÓRIA DO PROFESSOR: Liberar a memória apontada pelo void* 
        free(e.dados); 
        
    } else {
        printf("> Nenhuma tarefa pendente para execucao.\n");
    }
}

void mostrarStatus(FilaDinamica *f) {
    if (isEmpty(f)) {
        printf("> Fila atual: vazia.\n");
        return;
    }
    
    int tamanho = f->qtd;
    ElementoFila e;
    
    printf("> Fila atual:\n");
    for (int i = 0; i < tamanho; i++) {
        desenfila(f, &e);
        
        printf("  %d. ", i + 1);
        switch (e.tipo) {
            case BACKUP: {
                TarefaBackup *b = (TarefaBackup*) e.dados;
                printf("BACKUP: pasta %s, tamanho=%d GB\n", b->pasta, b->tamanho);
                break;
            }
            case EMAIL: {
                TarefaEmail *em = (TarefaEmail*) e.dados;
                printf("EMAIL: destinatario=%s, assunto=%s\n", em->destinatario, em->assunto);
                break;
            }
            case RELATORIO: {
                TarefaRelatorio *r = (TarefaRelatorio*) e.dados;
                printf("RELATORIO: nome %s, paginas=%d\n", r->nome, r->paginas);
                break;
            }
        }
        
        // AQUI NÃO TEM FREE! Porque a tarefa não foi executada, ela volta pra fila
        enfila(f, e); 
    }
}

// 5. O MAIN
int main() {
    FilaDinamica agenda;
    inicializa(&agenda);
    
    char comando[20], tipo_str[20];
    ElementoFila nova_tarefa;

    printf("==========================================\n");
    printf("     AGENDADOR DE TAREFAS (VOID*)         \n");
    printf("==========================================\n");
    printf("Comandos:\n");
    printf(" - add backup <pasta> <tamanho>\n");
    printf(" - add email <destinatario> <assunto>\n");
    printf(" - add relatorio <nome> <paginas>\n");
    printf(" - executar\n");
    printf(" - status\n");
    printf(" - sair\n");
    printf("------------------------------------------\n");

    while (1) {
        printf("\n> Comando: ");
        scanf("%s", comando);

        if (strcmp(comando, "add") == 0) {
            scanf("%s", tipo_str);
            
            if (strcmp(tipo_str, "backup") == 0) {
                // 1. Aloca dinamicamente a struct específica (MUITO IMPORTANTE!)
                TarefaBackup *b = (TarefaBackup*) malloc(sizeof(TarefaBackup));
                
                // 2. Lê os dados direto para o ponteiro alocado
                scanf("%s %d", b->pasta, &b->tamanho);
                
                // 3. Configura o elemento da fila com a etiqueta e o ponteiro void*
                nova_tarefa.tipo = BACKUP;
                nova_tarefa.dados = (void*) b;
                
                enfila(&agenda, nova_tarefa);
                printf("> Tarefa de BACKUP enfileirada.\n");
                
            } else if (strcmp(tipo_str, "email") == 0) {
                TarefaEmail *em = (TarefaEmail*) malloc(sizeof(TarefaEmail));
                scanf("%s %s", em->destinatario, em->assunto);
                
                nova_tarefa.tipo = EMAIL;
                nova_tarefa.dados = (void*) em;
                
                enfila(&agenda, nova_tarefa);
                printf("> Tarefa de EMAIL enfileirada.\n");
                
            } else if (strcmp(tipo_str, "relatorio") == 0) {
                TarefaRelatorio *r = (TarefaRelatorio*) malloc(sizeof(TarefaRelatorio));
                scanf("%s %d", r->nome, &r->paginas);
                
                nova_tarefa.tipo = RELATORIO;
                nova_tarefa.dados = (void*) r;
                
                enfila(&agenda, nova_tarefa);
                printf("> Tarefa de RELATORIO enfileirada.\n");
                
            } else {
                printf("> Erro: Tipo '%s' desconhecido.\n", tipo_str);
            }
        } 
        else if (strcmp(comando, "executar") == 0) {
            executarTarefa(&agenda);
        } 
        else if (strcmp(comando, "status") == 0) {
            mostrarStatus(&agenda);
        } 
        else if (strcmp(comando, "sair") == 0) {
            printf("> Desligando o agendador...\n");
            break;
        } 
        else {
            printf("> Comando invalido!\n");
            int c; while ((c = getchar()) != '\n' && c != EOF);
        }
    }

    return 0;
}