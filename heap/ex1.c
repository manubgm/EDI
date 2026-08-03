#include <stdio.h>

#define MAX 30

typedef struct heap {
    int elemento[MAX];
    int qtd;
} Heap;

void inicializar_heap(Heap *heap) {
    heap->qtd = 0;
}

int cheio(Heap heap) {
    return heap.qtd == MAX;
}

int vazio(Heap heap) {
    return heap.qtd == 0;
}

int insere(Heap *heap, int valor) { 
    if (cheio(*heap)) return 0;

    // 1. Guarda a POSIÇÃO livre antes de incrementar a quantidade
    int pos = heap->qtd; 
    
    // 2. Coloca o VALOR na POSIÇÃO
    heap->elemento[pos] = valor;
    //atualiza a qtd
    heap->qtd++;

    // 3. Calcula o PAI usando a POSIÇÃO
    int pai = (pos - 1) / 2;

    // 4. Sobe se a POSIÇÃO atual tiver valor MENOR que o PAI
    while (pos > 0 && heap->elemento[pos] < heap->elemento[pai]) {
        // Troca os valores no vetor
        int aux = heap->elemento[pai];
        heap->elemento[pai] = heap->elemento[pos];
        heap->elemento[pos] = aux;

        // Atualiza a POSIÇÃO para continuar subindo
        pos = pai;
        pai = (pos - 1) / 2;
    }
    return 1;
}

int main() {
    Heap heap;
    inicializar_heap(&heap);
    int num;

    printf("Digite 10 numeros para inserir no Heap Min:\n");
    for (int n = 0; n < 10; n++) {
        scanf("%d", &num);
        if (insere(&heap, num)) { 
            printf("Valor %d inserido no heap!\n", num);
        } else {
            printf("Heap cheio!\n");
        }
    }

    printf("\n> Conteudo do Heap Min <\n");
    for (int i = 0; i < heap.qtd; i++) {
        printf("Heap[%d] = %d\n", i, heap.elemento[i]);
    }

    return 0;
}