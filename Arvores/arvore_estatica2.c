#include <stdio.h>

#define GRAU 3
#define MAX 30

typedef struct vertice {
   char valor;
   int qtd_filhos;
} Vertice;

typedef Vertice Arvore[MAX];


void inicializar_arvore(Arvore arvore){
   for(int i = 0; i < MAX; i++){
      arvore[i].valor = '-';
      arvore[i].qtd_filhos = 0;
   }
}

void limpar_buffer() {
   int c;
   while ((c = getchar()) != '\n' && c != EOF);
}

void ler_arvore(Arvore arvore){
   int indice_pai = 0; // índice do vértice atual (pai)

   printf("Raiz: ");
   arvore[indice_pai].valor = getchar(); // lê a raiz da árvore
   limpar_buffer();

   int indice_filho = 1;
   
   // percorre o vetor enquanto houver espaço e vértices pais válidos
   while(indice_filho < MAX && indice_pai < MAX) {
      
      // se o vértice atual não existe, passa para o próximo
      if (arvore[indice_pai].valor == '-') {
         indice_pai++;
         continue;
      }

      // solicita a quantidade de filhos do vértice atual
      printf("\n\nDigite o número de filhos do vértice %c (Limite = %d): ", arvore[indice_pai].valor, GRAU);
      scanf("%d", &arvore[indice_pai].qtd_filhos);
      limpar_buffer();

      // se não houver filhos, apenas pula o espaço reservado
      if (arvore[indice_pai].qtd_filhos <= 0) {
         indice_pai++;         // próximo vértice pai
         continue;
      }

      // garante que não ultrapasse o grau máximo da árvore
      if (arvore[indice_pai].qtd_filhos > GRAU) {
         arvore[indice_pai].qtd_filhos = GRAU;
      }

      printf("\nLeitura dos filhos de: %c\n", arvore[indice_pai].valor);

      for(int i = 0; i < arvore[indice_pai].qtd_filhos; i++){

         // evita ultrapassar o limite do vetor
         if (indice_filho >= MAX) {
            arvore[indice_pai].qtd_filhos = i;
            break;
         }
         
         printf("Filho = ");
         arvore[indice_filho++].valor = getchar(); // armazena o filho e avança para o próximo
         limpar_buffer(); // limpa o buffer
      }

      // passa para o próximo vértice pai
      indice_pai++;
   }
}


void mostrar_arvore(Arvore arvore){
   // verifica se a árvore está vazia
   if (arvore[0].valor == '-') {
      printf("\n\n\aArvore vazia...");
      return;
   }

   int indice_pai = 0; // índice do vértice atual
   int indice_filho = 1; // índice dos filhos no vetor

   printf("Raiz: %c",arvore[indice_pai].valor); // imprime a raiz

   // percorre os vértices da árvore
   while (indice_pai < MAX && arvore[indice_pai].valor != '-') {
      printf("\nFilhos de %c: ", arvore[indice_pai].valor);
      
      if (arvore[indice_pai].qtd_filhos == 0) {
         printf("sem filhos");
         indice_pai++;
         continue;
      }

      for (int i = 0; i < arvore[indice_pai].qtd_filhos; i++) {
         printf("\t%c",arvore[indice_filho++].valor); // imprime o filho e avança para o próximo
      }

      indice_pai++;
   }
}

void mostrar_vetor(Arvore arvore){
   for (int i = 0; i < MAX; i++) {
      printf("Arvore[%2d] = %c (%d)\n", i, arvore[i].valor, arvore[i].qtd_filhos);
   }
}


int main(){
	Arvore arvore;

   inicializar_arvore(arvore);

   printf("Leitura dos vértices da árvore:\n");
   ler_arvore(arvore);

   printf("\n\nÁrvore criada:\n");
   mostrar_arvore(arvore);

   printf("\n\nVetor que armazena a árvore:\n");
   mostrar_vetor(arvore);

   return 0;
}