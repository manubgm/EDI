#include <stdio.h>
#include <stdlib.h>

// Estrutura de um vértice usando filho esquerdo e irmão direito
typedef struct vertice {
   char valor;                     // Valor armazenado no vértice
   struct vertice *filho_esquerdo; // Ponteiro para o primeiro filho
   struct vertice *irmao_direito;  // Ponteiro para o próximo irmão
} *Vertice;

// Estrutura da árvore, contendo a raiz, grau máximo e profundidade
typedef struct arvore {
   Vertice raiz;     // Ponteiro para o vértice raiz
   int grau;         // Grau máximo da árvore
   int profundidade; // Profundidade da árvore
} Arvore;

// Inicializa a árvore
void inicializar_arvore(Arvore *arvore) {
   arvore->raiz = NULL;      // Raiz começa vazia
   arvore->grau = 0;         // Grau inicial 0
   arvore->profundidade = -1; // Profundidade inicial -1
}

// Limpa o buffer do teclado
void limpar_buffer() {
   int c;
   while ((c = getchar()) != '\n' && c != EOF);
}

// Cria um vértice com valor informado
Vertice criar_vertice(char valor) {
   Vertice vertice = (Vertice) malloc(sizeof(struct vertice));

   vertice->valor = valor;              // Atribui valor ao vértice
   vertice->filho_esquerdo = NULL;      // Inicializa ponteiros como NULL
   vertice->irmao_direito = NULL;

   return vertice;                      // Retorna vértice criado
}

// Cria os filhos de um vértice pai
void criar_filhos(Vertice pai, int qtd_filhos) {
   printf("\nLeitura dos filhos de: %c\n", pai->valor);

   // Cria o primeiro filho
   printf("Filho = ");
   char valor = getchar(); // Lê valor do filho
   limpar_buffer();        // Limpa buffer
   pai->filho_esquerdo = criar_vertice(valor);

   Vertice filho_atual = pai->filho_esquerdo;

   // Cria os demais filhos e conecta via irmão_direito
   for (int i = 2; i <= qtd_filhos; i++) {
      printf("Filho = ");
      valor = getchar();
      limpar_buffer();

      Vertice novo_filho = criar_vertice(valor);

      filho_atual->irmao_direito = novo_filho; // conecta como irmão
      filho_atual = filho_atual->irmao_direito; // atualiza para último filho
   }
}

// Cria árvore recursivamente a partir de um vértice pai
void criar_arvore(Arvore *arvore, Vertice pai) {
   int qtd_filhos;

   printf("\n\nDigite o número de filhos do vértice %c: ", pai->valor);
   scanf("%d", &qtd_filhos);
   limpar_buffer();

   if (qtd_filhos <= 0) { // Se não houver filhos, retorna
      return;
   }

   // Atualiza grau máximo da árvore se necessário
   if (qtd_filhos > arvore->grau) {
      arvore->grau = qtd_filhos;
   }

   arvore->profundidade++; // Incrementa profundidade ao criar nível

   criar_filhos(pai, qtd_filhos); // Cria filhos do vértice

   // Chamada recursiva para cada filho
   Vertice filho = pai->filho_esquerdo;
   while (filho != NULL) {
      criar_arvore(arvore, filho);
      filho = filho->irmao_direito; // avança para próximo irmão
   }
}

// Lê a árvore a partir do valor da raiz
void ler_arvore(Arvore *arvore) {
   printf("Raiz = ");
   char valor = getchar(); // Lê valor da raiz
   limpar_buffer();

   Vertice raiz = criar_vertice(valor); // Cria vértice raiz
   arvore->raiz = raiz;

   criar_arvore(arvore, arvore->raiz); // Cria recursivamente os filhos
}

// Mostra árvore hierarquicamente
void mostrar_arvore(Vertice raiz, int nivel) {
   if (raiz == NULL) {
      return;
   }

   printf(" ");

   // Imprime indentação de acordo com nível
   for (int i = 0; i <= nivel * 2; i++) {
      printf("--");
   }

   printf(" %c\n", raiz->valor);

   // Percorre os filhos
   Vertice filho = raiz->filho_esquerdo;
   nivel += 1;

   while (filho != NULL) {
      mostrar_arvore(filho, nivel); // Recursivamente mostra cada filho
      filho = filho->irmao_direito; // Avança para próximo irmão
   }
}

// Percurso pré-ordem (processa nó antes dos filhos)
void percorrer_preordem(Vertice raiz) {
   if (raiz == NULL) {
      return;
   }

   printf("%c ", raiz->valor);

   percorrer_preordem(raiz->filho_esquerdo);
   percorrer_preordem(raiz->irmao_direito);
}

// Percurso pós-ordem (processa nó após os filhos)
void percorrer_posordem(Vertice raiz) {
   if (raiz == NULL) {
      return;
   }

   percorrer_posordem(raiz->filho_esquerdo);
   printf("%c ", raiz->valor);
   percorrer_posordem(raiz->irmao_direito);
}

// Calcula potência (base^exp)
int pot(int base, int exp) {
   int res = 1;
   for (int i = 0; i < exp; i++) {
      res *= base;
   }
   return res;
}

// Percurso por nível usando fila temporária
void percorrer_nivel(Arvore arvore, Vertice raiz) {
   if (raiz == NULL) {
      return;
   }

   Vertice vertice_atual = raiz;

   // Calcula tamanho máximo da fila baseado em grau e profundidade
   int tam_fila = (pot(arvore.grau, arvore.profundidade + 1) - 1) / (arvore.grau - 1);
   Vertice *fila_filhos = malloc(sizeof(Vertice) * tam_fila);
   int final_fila = -1;

   // Processa todos os irmãos do nível atual
   while (vertice_atual != NULL) {
      printf("%c ", vertice_atual->valor);

      // Adiciona primeiro filho à fila, se existir
      if (vertice_atual->filho_esquerdo != NULL) {
         fila_filhos[++final_fila] = vertice_atual->filho_esquerdo;
      }

      vertice_atual = vertice_atual->irmao_direito;
   }

   // Chamada recursiva para os filhos armazenados na fila
   for (int i = 0; i <= final_fila; i++) {
      percorrer_nivel(arvore, fila_filhos[i]);
   }

   free(fila_filhos); // Libera memória da fila
}

// Função principal
int main() {
   Arvore arvore;

   inicializar_arvore(&arvore); // Inicializa árvore

   printf("Leitura dos vértices da árvore:\n");
   ler_arvore(&arvore); // Lê árvore do usuário

   printf("\n\nÁrvore criada:\n");
   mostrar_arvore(arvore.raiz, 0); // Mostra árvore hierarquicamente
   printf("Grau: %d\n", arvore.grau);
   printf("Profundidade: %d\n", arvore.profundidade);

   printf("Percurso em pré-ordem: ");
   percorrer_preordem(arvore.raiz); // Pré-ordem

   printf("\nPercurso em pós-ordem: ");
   percorrer_posordem(arvore.raiz); // Pós-ordem

   printf("\nPercurso por nível: ");
   percorrer_nivel(arvore, arvore.raiz); // Por nível

   return 0;
}