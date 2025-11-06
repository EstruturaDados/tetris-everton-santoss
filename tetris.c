#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// ===== Estrutura da peça =====
typedef struct {
    char tipo;
    int id;
} Peca;

// ===== Estrutura da Fila Circular =====
typedef struct {
    Peca pecas[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// ===== Estrutura da Pilha Linear =====
typedef struct {
    Peca pecas[TAM_PILHA];
    int topo;
} Pilha;

// ======== Protótipos ========
void inicializarFila(Fila *f);
void inicializarPilha(Pilha *pilha);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
int pilhaCheia(Pilha *pilha);
int pilhaVazia(Pilha *pilha);
void enqueue(Fila *f, Peca p);
Peca dequeue(Fila *f);
void push(Pilha *pilha, Peca pec);
Peca pop(Pilha *pilha);
void mostrarFila(Fila *f);
void mostrarPilha(Pilha *pilha);
Peca gerarPeca(int id);
void trocarFrenteComTopo(Fila *f, Pilha *pilha);
void trocarTresComTres(Fila *f, Pilha *pilha);

// ======== Função principal ========
int main() {
    Fila fila;
    Pilha pilha;
    int idAtual = 1;
    int opcao;

    inicializarFila(&fila);
    inicializarPilha(&pilha);
    srand(time(NULL));

    // Preenche a fila inicialmente
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(idAtual++));
    }

    do {
        printf("\n===== SISTEMA DE PECAS - NIVEL MESTRE =====\n");
        mostrarFila(&fila);
        mostrarPilha(&pilha);

        printf("\n1 - Jogar peca (remover da frente)");
        printf("\n2 - Enviar peca da fila para a reserva (pilha)");
        printf("\n3 - Usar peca da reserva (remover do topo)");
        printf("\n4 - Trocar peca da frente com topo da pilha");
        printf("\n5 - Trocar 3 primeiros da fila com as 3 da pilha");
        printf("\n0 - Sair");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                    Peca jogada = dequeue(&fila);
                    printf("\nVoce jogou a peca ID %d tipo %c!\n", jogada.id, jogada.tipo);
                    enqueue(&fila, gerarPeca(idAtual++)); // repõe a fila
                } else {
                    printf("\nFila vazia!\n");
                }
                break;

            case 2:
                if (!filaVazia(&fila)) {
                    if (!pilhaCheia(&pilha)) {
                        Peca movida = dequeue(&fila);
                        push(&pilha, movida);
                        printf("\nPeca ID %d tipo %c foi movida para a reserva!\n", movida.id, movida.tipo);
                        enqueue(&fila, gerarPeca(idAtual++)); // repõe a fila
                    } else {
                        printf("\nReserva cheia! Nao pode mover mais pecas.\n");
                    }
                } else {
                    printf("\nFila vazia!\n");
                }
                break;

            case 3:
                if (!pilhaVazia(&pilha)) {
                    Peca usada = pop(&pilha);
                    printf("\nVoce usou a peca da reserva ID %d tipo %c!\n", usada.id, usada.tipo);
                    enqueue(&fila, gerarPeca(idAtual++)); // mantém fila cheia
                } else {
                    printf("\nReserva vazia!\n");
                }
                break;

            case 4:
                trocarFrenteComTopo(&fila, &pilha);
                break;

            case 5:
                trocarTresComTres(&fila, &pilha);
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}

// ======== Implementações ========

// ----- Fila -----
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

int filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\nFila cheia!\n");
        return;
    }
    f->pecas[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
}

Peca dequeue(Fila *f) {
    Peca removida = {'-', -1};
    if (filaVazia(f)) {
        printf("\nFila vazia!\n");
        return removida;
    }
    removida = f->pecas[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return removida;
}

void mostrarFila(Fila *f) {
    printf("\n[FILA DE PECAS FUTURAS]\n");
    if (filaVazia(f)) {
        printf("(vazia)\n");
        return;
    }
    int i = f->inicio;
    for (int cont = 0; cont < f->quantidade; cont++) {
        printf("ID:%d Tipo:%c | ", f->pecas[i].id, f->pecas[i].tipo);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}

// ----- Pilha -----
void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int pilhaCheia(Pilha *pilha) {
    return pilha->topo == TAM_PILHA - 1;
}

int pilhaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

void push(Pilha *pilha, Peca pec) {
    if (pilhaCheia(pilha)) {
        printf("\nReserva cheia!\n");
        return;
    }
    pilha->pecas[++pilha->topo] = pec;
}

Peca pop(Pilha *pilha) {
    Peca removida = {'-', -1};
    if (pilhaVazia(pilha)) {
        printf("\nReserva vazia!\n");
        return removida;
    }
    removida = pilha->pecas[pilha->topo--];
    return removida;
}

void mostrarPilha(Pilha *pilha) {
    printf("\n[RESERVA - PILHA]\n");
    if (pilhaVazia(pilha)) {
        printf("(vazia)\n");
        return;
    }
    for (int i = pilha->topo; i >= 0; i--) {
        printf("ID:%d Tipo:%c | ", pilha->pecas[i].id, pilha->pecas[i].tipo);
    }
    printf("\n");
}

// ----- Gera peça aleatória -----
Peca gerarPeca(int id) {
    Peca nova;
    nova.tipo = 'A' + (rand() % 5); // tipos A até E
    nova.id = id;
    return nova;
}

// ======== Funções Avançadas - Nível Mestre ========

// Troca a peça da frente da fila com o topo da pilha
void trocarFrenteComTopo(Fila *f, Pilha *pilha) {
    if (filaVazia(f)) {
        printf("\nNao ha pecas na fila para trocar!\n");
        return;
    }
    if (pilhaVazia(pilha)) {
        printf("\nNao ha pecas na reserva para trocar!\n");
        return;
    }

    int idxFila = f->inicio;
    int idxPilha = pilha->topo;

    Peca temp = f->pecas[idxFila];
    f->pecas[idxFila] = pilha->pecas[idxPilha];
    pilha->pecas[idxPilha] = temp;

    printf("\nTrocou a peca da frente da fila (ID:%d) com o topo da pilha (ID:%d)\n",
           pilha->pecas[idxPilha].id, f->pecas[idxFila].id);
}

// Troca os 3 primeiros da fila com as 3 peças da pilha
void trocarTresComTres(Fila *f, Pilha *pilha) {
    if (pilha->topo != 2) {
        printf("\nA pilha deve ter exatamente 3 pecas para realizar a troca!\n");
        return;
    }
    if (f->quantidade < 3) {
        printf("\nA fila precisa ter pelo menos 3 pecas para realizar a troca!\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int idxFila = (f->inicio + i) % TAM_FILA;
        int idxPilha = pilha->topo - i;

        Peca temp = f->pecas[idxFila];
        f->pecas[idxFila] = pilha->pecas[idxPilha];
        pilha->pecas[idxPilha] = temp;
    }

    printf("\nTrocou as 3 primeiras pecas da fila com as 3 da pilha!\n");
}
