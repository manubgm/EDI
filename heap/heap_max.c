#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int v[MAX];
    int tamanho;
} Heap;

void inicializar(Heap *h) {
    h->tamanho = 0;
}

// Retorna o índice do pai de um nó i [cite: 988]
int pai(int i) {
    return (i - 1) / 2;
}

// Troca dois valores de lugar no vetor
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ============================================================================
// A MAGIA DO HEAP: SUBIR (Up-Heapify / Shift-Up)
// ============================================================================
// É aqui que ocorrem as comparações que você perguntou! 
void subir(Heap *h, int i) {
    // Enquanto o nó não for a raiz (i > 0) 
    // E o valor do filho for MAIOR que o valor do pai (para Heap-Máximo) 
    while (i > 0 && h->v[i] > h->v[pai(i)]) {
        // Troca o filho com o pai
        trocar(&h->v[i], &h->v[pai(i)]);
        
        // O ponteiro de busca sobe para a posição do pai
        i = pai(i);
    }
}

// INSERÇÃO NO HEAP [cite: 1085-1087, 1094]
int inserir(Heap *h, int valor) {
    if (h->tamanho == MAX) {
        printf("Erro: Heap cheio!\n");
        return 0;
    }

    // 1. Insere o novo elemento na primeira posição livre do vetor (última folha) [cite: 1086, 1087]
    h->v[h->tamanho] = valor;
    
    // 2. Faz o elemento "subir" até o seu lugar correto para restaurar a ordem 
    subir(h, h->tamanho);
    
    // 3. Incrementa o tamanho
    h->tamanho++;
    
    return 1;
}

// Função para imprimir a representação em vetor
void imprimirVetor(Heap *h) {
    printf("Vetor do Heap: [ ");
    for (int i = 0; i < h->tamanho; i++) {
        printf("%d ", h->v[i]);
    }
    printf("]\n");
}

int main() {
    Heap h;
    inicializar(&h);

    // Inserindo os valores do exemplo da aula: 30, 75, 80, 60 [cite: 1102]
    inserir(&h, 30);
    inserir(&h, 75);
    inserir(&h, 80);
    inserir(&h, 60);

    imprimirVetor(&h); // O 80 obrigatoriamente estará no índice 0 (Raiz) [cite: 1033]

    return 0;
}