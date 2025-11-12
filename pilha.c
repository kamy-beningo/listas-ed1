#include <stdio.h>
#include <stdlib.h>

#define V int  // tipo dos elementos da pilha

typedef struct {
    V* vet;   // vetor com os elementos
    int topo; // índice do topo
    int cap;  // capacidade atual
} pilha;

// ------------------------------------------------------------
// Cria uma pilha vazia com capacidade inicial = 5
pilha* criar_pilha() {
    pilha* p = (pilha*) malloc(sizeof(pilha));
    p->cap = 5;
    p->vet = (V*) malloc(sizeof(V) * p->cap);
    p->topo = -1;
    return p;
}

// ------------------------------------------------------------
// Desaloca a pilha
void liberar_pilha(pilha* p) {
    free(p->vet);
    free(p);
}

// ------------------------------------------------------------
// Aumenta a capacidade da pilha manualmente (sem realloc)
void aumentar_capacidade(pilha* p) {
    int nova_cap = p->cap * 2;                  // dobra capacidade
    V* novo_vetor = (V*) malloc(sizeof(V) * nova_cap); // cria novo vetor

    // copia todos os elementos antigos
    for (int i = 0; i <= p->topo; i++) {
        novo_vetor[i] = p->vet[i];
    }

    // libera o vetor antigo
    free(p->vet);

    // atualiza ponteiro e capacidade
    p->vet = novo_vetor;
    p->cap = nova_cap;
}

// ------------------------------------------------------------
// Insere um elemento no topo (push)
void push(pilha* p, V v) {
    if (p->topo == p->cap - 1) {
        aumentar_capacidade(p);
    }
    p->vet[++p->topo] = v;
}

// ------------------------------------------------------------
// Retorna o valor do topo (sem remover)
V obter_topo(pilha* p) {
    if (p->topo == -1) {
        printf("Erro: pilha vazia!\n");
        return -1; // valor simbólico de erro
    }
    return p->vet[p->topo];
}

// ------------------------------------------------------------
// Remove e retorna o elemento do topo (pop)
V pop(pilha* p) {
    if (p->topo == -1) {
        printf("Erro: pilha vazia!\n");
        return -1;
    }
    return p->vet[p->topo--];
}

// ------------------------------------------------------------
// Retorna quantidade de elementos
int tamanho_pilha(pilha* p) {
    return p->topo + 1;
}

// ------------------------------------------------------------
// Retorna 1 se estiver vazia, 0 caso contrário
int pilha_vazia(pilha* p) {
    return (p->topo == -1);
}

// ------------------------------------------------------------
// Esvazia a pilha (sem liberar memória)
void limpar_pilha(pilha* p) {
    p->topo = -1;
}

// ------------------------------------------------------------
// Função auxiliar: imprime a pilha
void imprimir_pilha(pilha* p) {
    if (pilha_vazia(p)) {
        printf("Pilha vazia\n");
        return;
    }

    printf("Pilha (topo -> base): ");
    for (int i = p->topo; i >= 0; i--) {
        printf("%d ", p->vet[i]);
    }
    printf("\n");
}

// ------------------------------------------------------------
// Teste principal
int main() {
    pilha* p = criar_pilha();

    for (int i = 1; i <= 10; i++) {
        push(p, i * 10);
    }

    imprimir_pilha(p);
    printf("Topo: %d\n", obter_topo(p));
    printf("Desempilhado: %d\n", pop(p));
    imprimir_pilha(p);

    printf("Tamanho: %d\n", tamanho_pilha(p));
    printf("Está vazia? %d\n", pilha_vazia(p));

    limpar_pilha(p);
    imprimir_pilha(p);

    liberar_pilha(p);
    return 0;
}
