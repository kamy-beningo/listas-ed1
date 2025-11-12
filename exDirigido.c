// kamilly benigno de paula
// Grazieli da silva

#include <stdio.h>
#include <stdlib.h>
#define MAX 100 

typedef struct 
{
    int id;   
    int jn;   
    int jc;   
    int pc;   
} socorro;

typedef struct 
{
    socorro vet[MAX];
    int head;
    int tail;
    int c;
} fila;



void criar_fila(fila *f) 
{
    f->head = 0;
    f->tail = -1;
    f->c = 0;
}

int vazia(fila *f) 
{
    return f->c == 0;
}

int cheia(fila *f) 
{
    return f->c == MAX;
}

void adicionar(fila *f, socorro v) 
{
    if (cheia(f)) 
    {
        printf("Fila cheia! Hellooo?\n");
        return;
    }
    f->tail = (f->tail + 1) % MAX;
    f->vet[f->tail] = v;
    f->c++;
}

socorro remover(fila *f) 
{
    socorro vazio = {-1, -1, -1, -1};
    if (vazia(f)) 
    {
        printf("Fila vazia! Hellooo?\n");
        return vazio;
    }
    socorro v = f->vet[f->head];
    f->head = (f->head + 1) % MAX;
    f->c--;
    return v;
}

socorro *primeiro(fila *f) 
{
    if (vazia(f))
        return NULL;
    return &f->vet[f->head];
}


int main() 
{
    FILE *entrada = fopen("entrada.txt", "r");
    if (!entrada) 
    {
        printf("Erro ao abrir o arquivo entrada.txt!\n");
        return 1;
    }

    socorro lista[MAX];
    int n = 0;

    
    while (fscanf(entrada, "%d %d %d", &lista[n].id, &lista[n].jn, &lista[n].jc) == 3) 
    {
        lista[n].pc = 0;  
        n++;
    }
    fclose(entrada);

    FILE *saida = fopen("saida.txt", "w");
    if (!saida) 
    {
        printf("Erro ao criar saida.txt!\n");
        return 1;
    }

    fila f;
    criar_fila(&f);

    int time = 1;
    int resto = n;

    
    while (resto > 0 || !vazia(&f)) 
    {
        
        for (int i = 0; i < n; i++) 
        {
            if (lista[i].jc == time) 
            {
                fprintf(saida, "Janela: %03d | NOVO PROCESSO | Process ID: %d | Janelas necessárias: %d\n",
                        time, lista[i].id, lista[i].jn);
                adicionar(&f, lista[i]);
            }
        }

        
        socorro *p = primeiro(&f);
        if (p != NULL) 
        {
            p->pc++;
            fprintf(saida, "Janela: %03d | ESCALONAMENTO | Process ID: %d | Progresso: %d/%d\n",
                    time, p->id, p->pc, p->jn);

            if (p->pc == p->jn) 
            {
                remover(&f);
                resto--;
            }
        }

        time++;
    }

    fclose(saida);
    printf("Fim! Glória a DEUUUS 🙌\n");
    return 0;
}
