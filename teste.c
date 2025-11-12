#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Estrutura de um processo
typedef struct {
    int id;
    int numJanelas;
    int inicio;
    int progresso;
} Processo;

// Estrutura da fila (usando vetor)
typedef struct {
    Processo itens[MAX];
    int inicio;
    int fim;
    int tamanho;
} Fila;

// Funções da fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = -1;
    f->tamanho = 0;
}

int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

int filaCheia(Fila *f) {
    return f->tamanho == MAX;
}

void enfileirar(Fila *f, Processo p) {
    if (filaCheia(f)) {
        printf("Erro: fila cheia!\n");
        return;
    }
    f->fim = (f->fim + 1) % MAX;
    f->itens[f->fim] = p;
    f->tamanho++;
}

Processo desenfileirar(Fila *f) {
    Processo vazio = {-1, -1, -1, -1};
    if (filaVazia(f)) return vazio;
    Processo p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->tamanho--;
    return p;
}

Processo* primeiro(Fila *f) {
    if (filaVazia(f)) return NULL;
    return &f->itens[f->inicio];
}

int main() {
    FILE *entrada = fopen("entrada.txt", "r");
    if (!entrada) {
        printf("Erro ao abrir entrada.txt!\n");
        return 1;
    }

    Processo lista[MAX];
    int n = 0;

    // Lê os processos do arquivo
    while (fscanf(entrada, "%d %d %d", &lista[n].id, &lista[n].numJanelas, &lista[n].inicio) == 3) {
        lista[n].progresso = 0;
        n++;
    }
    fclose(entrada);

    FILE *saida = fopen("saida.txt", "w");
    if (!saida) {
        printf("Erro ao criar saida.txt!\n");
        return 1;
    }

    Fila fila;
    inicializarFila(&fila);

    int tempo = 1;
    int processosRestantes = n;

    // Loop principal da simulação
    while (processosRestantes > 0 || !filaVazia(&fila)) {

        // Adiciona novos processos no tempo atual
        for (int i = 0; i < n; i++) {
            if (lista[i].inicio == tempo) {
                fprintf(saida, "Janela: %03d | NOVO PROCESSO | Process ID: %d | Janelas necessárias: %d\n",
                        tempo, lista[i].id, lista[i].numJanelas);
                enfileirar(&fila, lista[i]);
            }
        }

        // Executa o processo da frente da fila
        Processo *p = primeiro(&fila);
        if (p != NULL) {
            p->progresso++;
            fprintf(saida, "Janela: %03d | ESCALONAMENTO | Process ID: %d | Progresso: %d/%d\n",
                    tempo, p->id, p->progresso, p->numJanelas);

            // Se terminou, remove da fila
            if (p->progresso == p->numJanelas) {
                desenfileirar(&fila);
                processosRestantes--;
            }
        }

        tempo++;
    }

    fclose(saida);
    printf("Simulação concluída! Arquivo 'saida.txt' gerado com sucesso.\n");
    return 0;
}
