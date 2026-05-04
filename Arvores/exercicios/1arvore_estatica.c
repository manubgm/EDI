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

//certo
void mostrar_vetor(Arvore arvore){
   for (int i = 0; i < MAX; i++) {
      printf("Arvore[%2d] = %c (%d)\n", i, arvore[i].valor, arvore[i].qtd_filhos);
   }
}


void soma_elementos(Arvore arvore) {
   int soma = 0;
   for (int i = 0; i < MAX; i++) {
      if (arvore[i].valor != '-') {
         soma += arvore[i].valor; // soma o valor do vértice
      }
   }
   printf("> soma dos elementos da arvore: %d\n", soma);
}

//certo
void profundidade_arvore(Arvore arvore) {
   //inicio de tudo
    int profundidade = 0;
   int indice_pai = 0; 
   int indice_filho = 1; 

   while (indice_pai < MAX && arvore[indice_pai].valor != '-') {
      if (arvore[indice_pai].qtd_filhos > 0) {
         profundidade++; // incrementa a profundidade para cada nível de filhos
      }
      indice_pai++;
   }
   printf("> profundidade da arvore: %d\n", profundidade);
}

//certo
void qtd_nos(Arvore arvore) {
   int qtd_nos = 0;
   for (int i = 0; i < MAX; i++) {
      if (arvore[i].valor != '-') {
         qtd_nos++; // conta o número de vértices
      }
   }
   printf("> quantidade de nós da arvore: %d\n", qtd_nos);
}

//certo
void qtd_um_filho(Arvore arvore) {
   int qtd_um_filho = 0;
   for (int i = 0; i < MAX; i++) {
      if (arvore[i].valor != '-' && arvore[i].qtd_filhos == 1) {
         qtd_um_filho++; // conta o número de vértices com exatamente um filho
      }
   }
   printf("> quantidade de nós com exatamente um filho: %d\n", qtd_um_filho);
}

void descobrir_parentesco(Arvore arvore, char valor) {
   int indice_pai = 0; 
   int indice_filho = 1; 
   char pai = '-';

   while (indice_pai < MAX && arvore[indice_pai].valor != '-') {
      for (int i = 0; i < arvore[indice_pai].qtd_filhos; i++) {
         if (arvore[indice_filho + i].valor == valor) {
            pai = arvore[indice_pai].valor; // encontra o pai do vértice
            break;
         }
      }
      if (pai != '-') {
         break; // se o pai foi encontrado, sai do loop
      }
      indice_pai++;
      indice_filho += arvore[indice_pai].qtd_filhos; // avança para os filhos do próximo vértice pai
   }

   if (pai != '-') {
      printf("> o pai de %c é: %c\n", valor, pai);
   } else {
      printf("> o vértice %c não foi encontrado na árvore.\n", valor);
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

   printf("> menor item da arvore: %c\n", arvore[MAX-1].valor);

   printf("> maior item da arvore: %c\n", arvore[0].valor);

   soma_elementos(arvore);
profundidade_arvore(arvore);
    qtd_nos(arvore);
    qtd_um_filho(arvore);
    char valor;
    printf("\nDigite um valor para descobrir seu parentesco: ");    
    scanf("%c", &valor);
    

   return 0;
}