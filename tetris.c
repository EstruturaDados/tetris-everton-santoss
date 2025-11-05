#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5 // capacidade da fila

// Estrutura da peça
typedef struct {
    char tipo;
    int id;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca pecas[TAM];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// Protótipos
void inicializarFila(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
void enqueue(Fila *f, Peca p);
Peca dequeue(Fila *f);
void mostrarFila(Fila *f);
Peca gerarPeca(int id);

// Função principal
int main() {
    Fila fila;
    inicializarFila(&fila);
    srand(time(NULL));

    int opcao;
    int idAtual = 1;

    // Preenche a fila inicialmente com 5 peças
    for (int i = 0; i < TAM; i++) {
        enqueue(&fila, gerarPeca(idAtual++));
    }

    do {
        printf("\n==== FILA DE PECAS FUTURAS ====\n");
        mostrarFila(&fila);
        printf("\n1 - Jogar peca (remover da frente)");
        printf("\n0 - Sair");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                    Peca jogada = dequeue(&fila);
                    printf("\nVoce jogou a peca ID %d tipo %c!\n", jogada.id, jogada.tipo);
                    enqueue(&fila, gerarPeca(idAtual++)); // adiciona nova peça no final
                } else {
                    printf("\nFila vazia!\n");
                }
                break;
            case 0:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}

// Inicializa fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->quantidade == TAM;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

// Insere uma peça na fila
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\nFila cheia! Nao foi possivel adicionar a peca.\n");
        return;
    }
    f->pecas[f->fim] = p;
    f->fim = (f->fim + 1) % TAM;
    f->quantidade++;
}

// Remove uma peça da fila
Peca dequeue(Fila *f) {
    Peca removida = {'-', -1};
    if (filaVazia(f)) {
        printf("\nFila vazia!\n");
        return removida;
    }
    removida = f->pecas[f->inicio];
    f->inicio = (f->inicio + 1) % TAM;
    f->quantidade--;
    return removida;
}

// Mostra as peças na fila
void mostrarFila(Fila *f) {
    printf("\n[Fila de Pecas Futuras]\n");
    if (filaVazia(f)) {
        printf("(vazia)\n");
        return;
    }

    int i = f->inicio;
    for (int cont = 0; cont < f->quantidade; cont++) {
        printf("ID:%d Tipo:%c | ", f->pecas[i].id, f->pecas[i].tipo);
        i = (i + 1) % TAM;
    }
    printf("\n");
}

// Gera uma peça aleatória com tipo A-E
Peca gerarPeca(int id) {
    Peca nova;
    nova.tipo = 'A' + (rand() % 5); // tipos entre A e E
    nova.id = id;
    return nova;
}
