#include <stdio.h>
#include <stdlib.h>
#define V int



/*typedef struct
{	
	V* vet;
	int c;
	int n;
    int head;
    int tail;
}fila;
fila* criar_fila()
{
	fila* l= malloc(sizeof(fila));
	l->n=0;
    l->head=0;
    l->tail=0;
	l->c=6;
	l->vet=malloc(sizeof(V)*l->c);
	return l;
}
void adicionar_fila(fila* l, V v)
{
	l->vet[l->tail]=v;
    l->tail=(l->tail+1)%l->c;
	l->n++;
}
void full(fila* l)
{
    int c=l->c;
    l->c=l->c*2;
    V* v = malloc(sizeof(V)*l->c);
    for (int i=0;i<l->n;i++)
    {
        v[i]=l->vet[(l->head+i)%c];
    }

    free(l->vet);
    l->vet=v;
    l->head=0;
    l->tail=l->n;
}*/
typedef struct
{	
	V* vet;
	int c;
	int n;
    
}fila_prioridade;

fila_prioridade* criar()
{
    fila_prioridade* p=malloc(sizeof(fila_prioridade));
    p->c=5;
    p->n=0;
    p->vet=malloc(sizeof(V)*p->c);
    return p;

}
void liberar_fila(fila_prioridade* p)
{
    free(p->vet);
    p->vet=NULL;
    p->c=0;
    p->n=0;
}

int pai(int i) 
{ 
    return(i-1)/2; 
}
int left(int i) 
{ 
    return(2*i)+1; 
}
int right(int i) 
{ 
    return(2*i)+2; 
}

void up(fila_prioridade* f, int i)
{
    while (i>0)
    {
        int p=pai(i);

        if (f->vet[i]<f->vet[p])
        {
            int aux=f->vet[i];
            f->vet[i]=f->vet[p];
            f->vet[p]=aux;
            i=p; 
        }
        if(f->vet[i]<f->vet[i-1])
        {
            int aux=f->vet[i];
            f->vet[i]=f->vet[i-1];
            f->vet[i-1]=aux;
        }
        else
        {
            break;
        }
    }
}
void down(fila_prioridade* f, int i)
{
    while (1)
    {
        int e=left(i);
        int r=right(i);
        int menor=i;
        if (e<f->n&&f->vet[e]<f->vet[menor])
        {
            menor=e;
        }
        if (r<f->n&&f->vet[r]<f->vet[menor])
        {
            menor=r;
        }
        if (menor==i)
        {
            break;
        }
        int aux=f->vet[i];
        f->vet[i]=f->vet[menor];
        f->vet[menor]=aux;
        i = menor;
    }
}
void cheia(fila_prioridade* f)
{
    f->c=f->c*2;
    V* v=malloc(sizeof(V)*f->c);
    for(int i=0;i<f->n;i++)
    {
        v[i]=f->vet[i];
    }
    free(f->vet);
    f->vet=v;
}
int vazia(fila_prioridade*f)
{
     if(f->n==0)
    {
        return 1;
    }
    return 0;
}
void adici(fila_prioridade*f, V v)
{
    if(f->n==f->c)
    {
        cheia(f);
    }
    f->vet[f->n]=v;
    up(f,f->n);
    f->n++;
    int x=f->n-1;
    while(f->vet[x]<f->vet[x-1]&&x>0)
    {

        up(f,x);
        x--;
    }
}
V obter_inicio(fila_prioridade* f)
{
    if(vazia(f)==1)
    {
        printf("fila vazia\n");
        return 1;
    }
    return f->vet[0];
}
V remover(fila_prioridade* f)
{
    if(vazia(f)==1)
    {
        printf("fila vazia\n");
        return 1;
    }
    V x=f->vet[0];
    f->vet[0]=f->vet[f->n-1];
    down(f,0);
    f->n--;
    return x;

}
int tamanho(fila_prioridade* f)
{
    return f->n;
}
void limpar(fila_prioridade* f)
{
    f->n==0;

}
void imprimir(fila_prioridade* f)
{
    if(vazia(f)==1)
    {
        printf("fila vazia\n");
    }
    for(int i=0;i<f->n;i++)
    {
        printf("%d ",f->vet[i]);
    }
    printf("\n");
}
int filas_iguais(fila_prioridade* f, fila_prioridade* p)
{
    if (f->n!=p->n)
    {
        return 0;
    }
    int usado[p->n];
    for (int i=0;i<p->n;i++)
    {
        usado[i]=0;
    }
    for (int i=0;i<f->n;i++)
    {
        int k=0;
        for (int j=0;j<p->n;j++)
        {
            if (!usado[j]&&f->vet[i]==p->vet[j])
            {
                usado[j]=1; 
                break;
            }
        }
        if (!k)
        {
            return 0;
        } 
    }
    return 1;
}
fila clonar_fila(fila_prioridade* f)
{
    fila* v=criar_fila();
    for(int i=0;i<f->n;i++)
    {
        if(v->n==v->c)
        {
            full(v);
        }
        adici(v,f->vet[i]);
    }
}
int main()
{
    fila_prioridade* p=criar();
    for(int i=0;i<p->c;i++)
    {
        int x;
        scanf("%d",&x);
        adici(p,x);
    }
    imprimir(p);
    int n=obter_inicio(p);
    printf("%d\n",n);
    remover(p);
    imprimir(p);
    printf("%d\n",tamanho(p));
    return 0;
}