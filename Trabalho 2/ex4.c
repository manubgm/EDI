//fila estatica circular
//impressora com cancelamento 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>  

typedef struct {
    char arquivo[20];
    int paginas;
} documento;

typedef struct {
    documento fila[100];
    int inicio;
    int fim;
    int qtd;
} Fila;

void inicializa(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
}

int isEmpty(Fila *f){
    return f->qtd == 0; 
}

int enfila(Fila *f, char *arquivo, int paginas){
    if(f->qtd == 100) return 0; 
    strcpy(f->fila[f->fim].arquivo, arquivo);
    f->fila[f->fim].paginas = paginas;

    f->fim = (f->fim + 1) % 100; 
    f->qtd++;
    
    return 1;
}

int desenfila(Fila *f, documento *saida){
    if(isEmpty(f)) return 0; 
    
    *saida = f->fila[f->inicio];

    f->inicio = (f->inicio + 1) % 100;
    f->qtd--;
    
    return 1;
}

void imprimirDocumento(Fila *f) {
    documento doc;
    
    if (desenfila(f, &doc) == 0) {
        printf("> Erro: Nao ha documentos na fila de impressao.\n");
        return;
    }
    
    printf("> Imprimindo '%s' (%d paginas)...\n", doc.arquivo, doc.paginas);
    for (int i = 1; i <= doc.paginas; i++) {
        printf("  Imprimindo pagina %d...\n", i);
        sleep(1); // delay pra imprimir cada pag
    }
    printf("> Impressao de '%s' concluida!\n", doc.arquivo);
}

void cancelarDocumento(Fila *f, char *nome_alvo) {
    Fila aux;
    inicializa(&aux);
    documento doc_atual;
    int cancelou = 0;

    //svazia a original
    while (!isEmpty(f)) {
        desenfila(f, &doc_atual);
        
        // se achei o arquivo não coloco na auxiliar
        if (strcmp(doc_atual.arquivo, nome_alvo) == 0) {
            cancelou = 1;
            printf("> Documento '%s' cancelado com sucesso.\n", nome_alvo);
        } else {
            enfila(&aux, doc_atual.arquivo, doc_atual.paginas);
        }
    }

    //devolve tudo da auxiliar para a fila original
    while (!isEmpty(&aux)) {
        desenfila(&aux, &doc_atual);
        enfila(f, doc_atual.arquivo, doc_atual.paginas);
    }

    if (!cancelou) {
        printf("> Erro: Documento '%s' nao encontrado na fila.\n", nome_alvo);
    }
}

void mostrarStatus(Fila *f) {
    if (isEmpty(f)) {
        printf("> A fila de impressao esta vazia.\n");
        return;
    }

    printf("> Trabalhos aguardando na fila:\n");
    int tamanho_atual = f->qtd;
    documento doc;

    for (int i = 0; i < tamanho_atual; i++) {
        desenfila(f, &doc);
        printf("  %d. %s (%d paginas)\n", i + 1, doc.arquivo, doc.paginas);
        enfila(f, doc.arquivo, doc.paginas);
    }
}

int main() {
    Fila impressora;
    inicializa(&impressora); 
    
    char comando[20];
    char nome_arquivo[20];
    int paginas;

    printf("==========================================\n");
    printf("     SIMULADOR DE IMPRESSORA              \n");
    printf("==========================================\n");
    printf("Comandos disponiveis:\n");
    printf(" - add <nome> <paginas>\n");
    printf(" - print\n");
    printf(" - cancel <nome>\n");
    printf(" - status\n");
    printf(" - sair\n");
    printf("------------------------------------------\n");

    while (1) { 
        printf("\n> Digite um comando: ");
        scanf("%s", comando); 

        if (strcmp(comando, "add") == 0) {
            scanf("%s %d", nome_arquivo, &paginas);
            
            if (enfila(&impressora, nome_arquivo, paginas)) {
                printf("> Trabalho '%s' (%d pags) adicionado a fila!\n", nome_arquivo, paginas);
            } else {
                printf("> Erro: Fila de impressao cheia!\n");
            }
        } 
        else if (strcmp(comando, "print") == 0) {
            imprimirDocumento(&impressora);
        } 
        else if (strcmp(comando, "cancel") == 0) {
            scanf("%s", nome_arquivo);
            cancelarDocumento(&impressora, nome_arquivo);
        } 
        else if (strcmp(comando, "status") == 0) {
            mostrarStatus(&impressora);
        } 
        else if (strcmp(comando, "sair") == 0) {
            printf("> Desligando a impressora...\n");
            break;
        } 
        else {
            printf("> Comando invalido! Tente add, print, cancel, status ou sair.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }

    return 0;
}