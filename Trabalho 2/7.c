//treinar filas dinamicas agr
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//criamos etiquetas 
typedef enum { REDE, SOFTWARE, HARDWARE } TipoChamado;

//criamos as structs para cada setor
typedef struct {
    char setor[30];
    int ramal;
} ReqRede;

typedef struct {
    char usuario[30];
    char programa[30];
} ReqSoftware;

typedef struct {
    char patrimonio[30];
    char defeito[50];
} ReqHardware;

//  union tem o tamanho da maior struct 
// mas so guardar uma delas por vez
typedef union {
    ReqRede rede;
    ReqSoftware software;
    ReqHardware hardware;
} DadosChamado;

//o completo q vai ser chamdo
typedef struct {
    TipoChamado tipo;     //etiqueta
    DadosChamado dados;   //conteudo da union
} Chamado;

//no dinamico
typedef struct no {
    Chamado info;
    struct no *prox;
} No;

typedef struct {
    No *inicio;
    No *fim;
    int qtd; 
} FilaDinamica;

//basicos de fila dinamica
void inicializa(FilaDinamica *f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->qtd = 0;
}

int isEmpty(FilaDinamica *f) {
    return f->inicio == NULL;
}

int enfila(FilaDinamica *f, Chamado c) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) return 0; 
    
    novo->info = c;
    novo->prox = NULL; 
    
    if (isEmpty(f)) {
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }
    
    f->fim = novo; 
    f->qtd++;
    return 1;
}

int desenfila(FilaDinamica *f, Chamado *saida) {
    if (isEmpty(f)) return 0; // Fila vazia
    
    No *aux = f->inicio;
    *saida = aux->info; 
    f->inicio = f->inicio->prox; 
    
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    
    free(aux); 
    f->qtd--;
    return 1;
}
void atenderChamado(FilaDinamica *f) {
    Chamado c;
    
    if (desenfila(f, &c)) {
        printf("> Atendendo chamado de ");
        switch (c.tipo) {
            case REDE:
                printf("REDE: setor %s, ramal = %d\n", c.dados.rede.setor, c.dados.rede.ramal);
                break;
            case SOFTWARE:
                printf("SOFTWARE: usuario %s, programa=%s\n", c.dados.software.usuario, c.dados.software.programa);
                break;
            case HARDWARE:
                printf("HARDWARE: patrimonio=%s, defeito=%s\n", c.dados.hardware.patrimonio, c.dados.hardware.defeito);
                break;
        }
    } else {
        printf("> Nenhum chamado na fila de atendimento.\n");
    }
}

void mostrarStatus(FilaDinamica *f) {
    if (isEmpty(f)) {
        printf("> Fila atual: vazia.\n");
        return;
    }
    
    int tamanho = f->qtd;
    Chamado c;
    
    printf("> Fila atual:\n");
    for (int i = 0; i < tamanho; i++) {
        desenfila(f, &c);
        
        printf("  %d. ", i + 1);
        switch (c.tipo) {
            case REDE:
                printf("REDE: setor %s, ramal=%d\n", c.dados.rede.setor, c.dados.rede.ramal);
                break;
            case SOFTWARE:
                printf("SOFTWARE: usuario %s, programa=%s\n", c.dados.software.usuario, c.dados.software.programa);
                break;
            case HARDWARE:
                printf("HARDWARE: patrimonio=%s, defeito=%s\n", c.dados.hardware.patrimonio, c.dados.hardware.defeito);
                break;
        }
        
        enfila(f, c); //p fim ne
    }
}

int main() {
    FilaDinamica central;
    inicializa(&central);
    
    char comando[20], tipo_str[20];
    Chamado novo_chamado;

    printf("==========================================\n");
    printf("   CENTRAL DE ATENDIMENTO (UNION)         \n");
    printf("==========================================\n");
    printf("Comandos disponiveis:\n");
    printf(" - add rede <setor> <ramal>\n");
    printf(" - add software <usuario> <programa>\n");
    printf(" - add hardware <patrimonio> <defeito>\n");
    printf(" - atender\n");
    printf(" - status\n");
    printf(" - sair\n");
    printf("------------------------------------------\n");
    
    while(1) {
        printf("\n> Comando: ");
        scanf("%s", comando); 

        if (strcmp(comando, "add") == 0) {
            scanf("%s", tipo_str); 
            
            if (strcmp(tipo_str, "rede") == 0) {
                novo_chamado.tipo = REDE;
                scanf("%s %d", novo_chamado.dados.rede.setor, &novo_chamado.dados.rede.ramal);
                
                enfila(&central, novo_chamado);
                printf("> Chamado de REDE adicionado com sucesso.\n");
                
            } else if (strcmp(tipo_str, "software") == 0) {
                novo_chamado.tipo = SOFTWARE;
                scanf("%s %s", novo_chamado.dados.software.usuario, novo_chamado.dados.software.programa);
                
                enfila(&central, novo_chamado);
                printf("> Chamado de SOFTWARE adicionado com sucesso.\n");
                
            } else if (strcmp(tipo_str, "hardware") == 0) {
                novo_chamado.tipo = HARDWARE;
                scanf("%s %s", novo_chamado.dados.hardware.patrimonio, novo_chamado.dados.hardware.defeito);
                
                enfila(&central, novo_chamado);
                printf("> Chamado de HARDWARE adicionado com sucesso.\n");
                
            } else {
                printf("> Erro: Tipo de chamado '%s' desconhecido.\n", tipo_str);
            }
        } 
        else if (strcmp(comando, "atender") == 0) {
            atenderChamado(&central);
        } 
        else if (strcmp(comando, "status") == 0) {
            mostrarStatus(&central);
        } 
        else if (strcmp(comando, "sair") == 0) {
            printf("> Encerrando o sistema de atendimento...\n");
            break;
        } 
        else {
            printf("> Comando invalido!\n");
            int c; 
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    
    return 0;
}