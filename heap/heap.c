#include <stdio.h>

#define MAX 30

typedef struct heap {
	int elementos[MAX];
	int qtd;
} Heap;


void inicializar_heap(Heap *heap) {
	heap->qtd = 0;
}

int esta_cheio(Heap heap) {
	return heap.qtd == MAX;
}

int esta_vazio(Heap heap) {
	return heap.qtd == 0;
}

void trocar(Heap *heap, int i, int j) {
	int temp = heap->elementos[i];
	heap->elementos[i] = heap->elementos[j];
	heap->elementos[j] = temp;
}

void subir(Heap *heap, int i) {
	// Troca elementos iterativamente
	int pai = (i - 1) / 2;

	while (i > 0 && heap->elementos[i] > heap->elementos[pai]) {
		trocar(heap, i, pai);
		i = pai;
		pai = (i - 1) / 2;
	}
}

int obter_maior_filho(Heap heap, int i, int *maior_filho) {
	int filho_esq = 2 * i + 1;
	int filho_dir = 2 * i + 2;

	// Não possui filhos
	if (filho_esq >= heap.qtd) {
		return 0;
	}

	// Possui apenas filho esquerdo
	if (filho_dir >= heap.qtd) {
		*maior_filho = filho_esq;
		return 1;
	}

	// Possui os dois filhos
	if (heap.elementos[filho_esq] >= heap.elementos[filho_dir]) {
		*maior_filho = filho_esq;
	} else {
		*maior_filho = filho_dir;
	}

	return 1;
}

void descer(Heap *heap, int i) {
	int maior_filho;
	
	while (obter_maior_filho(*heap, i, &maior_filho) && 
		   heap->elementos[maior_filho] > heap->elementos[i]) {
		trocar(heap, maior_filho, i);
		i = maior_filho;
	}
}

int inserir(Heap *heap, int elemento){
	if (esta_cheio(*heap)) {
		return 0;
	}

	// Coloca o novo elemento na posição mais a esquerda do último nível
	heap->elementos[heap->qtd] = elemento;

	// Incrementa a quantidade de elementos
	heap->qtd++;

	// Sobe o novo elemento na heap para restaurar a propriedade
	subir(heap, heap->qtd - 1);

	return 1;
}

int remover(Heap *heap, int *elemento_removido){
	if (esta_vazio(*heap)) {
		return 0;
	}

	// Guarda o elemento removido
	*elemento_removido = heap->elementos[0];

	// Coloca o elemento mais a direita no último nível como nova raiz
	heap->elementos[0] = heap->elementos[heap->qtd - 1];

	// Decrementa a quantidade de elementos
	heap->qtd--;

	// Desce a nova raiz no heap para restaurar a propriedade
	descer(heap, 0);

	return 1;
}

// Retorna a primeira ocorrência de um elemento
int encontrar_elemento(Heap heap, int elemento) {
	if (esta_vazio(heap)) {
		return -1;
	}

	for (int i = 0; i < heap.qtd; i++) {
		if (heap.elementos[i] == elemento) {
			return i;
		}
	}

	return -1;
}

// Lógica simples de alteração (altera primeira ocorrência)
int alterar(Heap *heap, int antigo_elemento, int novo_elemento){
	// Busca índice do elemento a ser alterado
	int i = encontrar_elemento(*heap, antigo_elemento);

	// Se não encontrar, retorna
	if (i == -1) {
		return 0;
	}

	// Troca o antigo elemento pelo novo elemento
	heap->elementos[i] = novo_elemento;

	int maior_filho;
	
	// Decide de sobe ou desce no heap
	if (i > 0 && heap->elementos[(i - 1) / 2] < heap->elementos[i]) {
		subir(heap, i);
	} else if (obter_maior_filho(*heap, i, &maior_filho) && 
			   heap->elementos[maior_filho] > heap->elementos[i]) {
		descer(heap, i);
	}

	return 1;
}

void ordenar_heapsort(int *vetor, int tam) {
	Heap heap;

	inicializar_heap(&heap);

	for (int i = 0; i < tam; i++) {
		inserir(&heap, vetor[i]);
	}

	int removido;
	int j = tam - 1;

	while (!esta_vazio(heap)) {
		remover(&heap, &removido);
		vetor[j] = removido; 
		j--;
	}
}


void mostrar_arvore(Heap heap, int pai, int nivel, char *rotulo) {
	if (pai >= heap.qtd) {
		return;
	}

	printf(" ");

	// Imprime indentação de acordo com o nível do vértice
	for (int i = 0; i <= nivel * 3; i++) {
		printf("--");
	}

	printf("%d (%s)\n", heap.elementos[pai], rotulo); // Mostra o valor do vértice

	nivel += 1; // Incrementa nível para os filhos

	// Exibe filhos recursivamente
	int filho_esq = 2 * pai + 1;
	int filho_dir = 2 * pai + 2;

	if (filho_esq < heap.qtd) {
		mostrar_arvore(heap, filho_esq, nivel, "esq");
	}

	if (filho_dir < heap.qtd) {
		mostrar_arvore(heap, filho_dir, nivel, "dir");
	}
}

void mostrar_vetor_heap(Heap heap) {
    for (int i = 0; i < heap.qtd; i++) {
        printf("Heap[%2d] = %d\n", i, heap.elementos[i]);
    }
}

void mostrar_elementos_vetor(int *vetor, int tam) {
    for (int i = 0; i < tam; i++) {
		printf("%d ", vetor[i]);
    }

	printf("\n");
}


int main() {
    Heap heap;

	inicializar_heap(&heap);

	
	// Inserção de elementos
	for (int i = 1; i <= 10; i++) {
		inserir(&heap, i);
		printf("Valor %d inserido no heap!\n", i);

		printf("Heap atualizada:\n");
		mostrar_arvore(heap, 0, 0, "raiz");
	}



	// Remoção de elementos
	int removido;
	remover(&heap, &removido);
	printf("Item removido: %d\n", removido);
	
	printf("Heap atualizada:\n");
	mostrar_arvore(heap, 0, 0, "raiz");


	remover(&heap, &removido);
	printf("Item removido: %d\n", removido);
	
	printf("Heap atualizada:\n");
	mostrar_arvore(heap, 0, 0, "raiz");


	// Alteração de elementos
	alterar(&heap, 1, 20);
	printf("Valor %d alterado para %d\n", 1, 20);
	
	printf("Heap atualizada:\n");
	mostrar_arvore(heap, 0, 0, "raiz");

	alterar(&heap, 5, 1);
	printf("Valor %d alterado para %d\n", 5, 1);

	printf("Heap atualizada:\n");
	mostrar_arvore(heap, 0, 0, "raiz");



	printf("\nÁrvore binária do heap: \n");
	mostrar_arvore(heap, 0, 0, "raiz");

	printf("\nVetor que armazena o heap: \n");
	mostrar_vetor_heap(heap);


	// Ordenação de um vetor
	int vetor[] = {10, 3, 50, 1, 5, 29, 6};
	int tam = sizeof(vetor) / sizeof(vetor[0]);

	printf("Vetor original: ");
	mostrar_elementos_vetor(vetor, tam);

	// Utiliza heapsort para ordernar
	ordenar_heapsort(vetor, tam);

	printf("Vetor ordenado: ");
	mostrar_elementos_vetor(vetor, tam);

    return 0;
}