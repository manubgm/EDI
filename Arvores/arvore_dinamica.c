#include <stdio.h>
#include <stdlib.h>

#define GRAU 3  // Define o grau máximo da árvore

// Estrutura do vértice da árvore
typedef struct vertice {
   char valor;               // Valor armazenado no vértice
   struct vertice *primeiro; // Ponteiro para o primeiro filho
   struct vertice *segundo;  // Ponteiro para o segundo filho
   struct vertice *terceiro; // Ponteiro para o terceiro filho
} *Arvore;

// Inicializa a árvore como vazia
void inicializar_arvore(Arvore *arvore) {
   *arvore = NULL;
}

// Limpa o buffer de entrada do teclado
void limpar_buffer() {
   int c;
   while ((c = getchar()) != '\n' && c != EOF);
}

// Cria um vértice com valor informado e ponteiros nulos
Arvore criar_vertice(char valor) {
   Arvore vertice = (Arvore) malloc(sizeof(struct vertice));

   vertice->valor = valor;        // Atribui o valor ao vértice
   
   vertice->primeiro = NULL;      // Inicializa ponteiros como NULL
   vertice->segundo = NULL;
   vertice->terceiro = NULL;

   return vertice;                // Retorna o vértice criado
}

// Cria os filhos de um vértice pai
void criar_filhos(Arvore pai, int qtd_filhos) {
   printf("\nLeitura dos filhos de: %c\n", pai->valor);

   for (int i = 1; i <= qtd_filhos; i++) {
      printf("Filho = ");
      char valor = getchar(); // Lê o valor do filho
      limpar_buffer();        // Limpa o buffer para próxima leitura
      
      Arvore filho = criar_vertice(valor); // chama a funcao que cria o vértice filho

      // Atribui o filho ao ponteiro correspondente
      switch (i) {
         case 1:
            pai->primeiro = filho;
            break;
         case 2:
            pai->segundo = filho;
            break;
         case 3:
            pai->terceiro = filho;
            break;
      }
   }
}

// Cria a árvore recursivamente a partir de um vértice pai
void criar_arvore(Arvore pai) {
   int qtd_filhos;

   printf("\n\nDigite o número de filhos do vértice %c (limite = %d): ", pai->valor, GRAU);
   scanf("%d", &qtd_filhos);
   limpar_buffer(); // Limpa buffer após scanf

   if (qtd_filhos <= 0) { // Se não houver filhos, retorna
      return;
   }

   if (qtd_filhos > GRAU) { // Garante que não ultrapasse o grau máximo
      qtd_filhos = GRAU;
   }

   criar_filhos(pai, qtd_filhos); // Cria os filhos do vértice

   // Chamada recursiva para cada filho existente
   if (pai->primeiro != NULL) {
      criar_arvore(pai->primeiro);
   }

   if (pai->segundo != NULL) {
      criar_arvore(pai->segundo);
   }

   if (pai->terceiro != NULL) {
      criar_arvore(pai->terceiro);
   }
}

// Lê a árvore a partir do valor da raiz
void ler_arvore(Arvore *arvore) {
   printf("Raiz = ");
   char valor = getchar(); // Lê valor da raiz
   limpar_buffer();

   Arvore raiz = criar_vertice(valor); // Cria vértice raiz

   *arvore = raiz; // Atribui ao ponteiro principal

   criar_arvore(*arvore); // Cria recursivamente o restante da árvore
}

// Exibe a árvore de forma hierárquica
void mostrar_arvore(Arvore arvore, int nivel) {
   if (arvore == NULL) { // Se o vértice não existir, retorna
      return;
   }

   printf(" ");

   // Imprime indentação de acordo com o nível do vértice
   for (int i = 0; i <= nivel * 2; i++) {
      printf("--");
   }

   printf(" %c\n", arvore->valor); // Mostra o valor do vértice

   nivel += 1; // Incrementa nível para os filhos

   // Exibe filhos recursivamente
   if (arvore->primeiro != NULL) {
      mostrar_arvore(arvore->primeiro, nivel);
   }

   if (arvore->segundo != NULL) {
      mostrar_arvore(arvore->segundo, nivel);
   }
   
   if (arvore->terceiro != NULL) {
      mostrar_arvore(arvore->terceiro, nivel);
   }
}

// Função principal
int main() {
   Arvore arvore;

   inicializar_arvore(&arvore); // Inicializa a árvore

   printf("Leitura dos vértices da árvore:\n");
   ler_arvore(&arvore);         // Lê a árvore do usuário

   printf("\n\nÁrvore criada:\n");
   mostrar_arvore(arvore, 0);   // Exibe a árvore

   return 0;
}