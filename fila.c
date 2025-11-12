#include <stdio.h>
#include <stdlib.h>
#define V int

typedef struct
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
void liberar_fila(fila *l)
{
	free(l->vet);
	free (l);
}
void adicionar(fila* l, V v)
{
	l->vet[l->tail]=v;
    l->tail=(l->tail+1)%l->c;
	l->n++;
}
int vazia(fila* l)
{
	if(l->tail==l->head)
	{
		printf("lista vazia");
		return 1;
	}
	return 0;
}
V obter_inicio(fila* l)
{
	if(vazia(l)==1)
	{
        printf("erro fila vazia\n");
		return -1;
	}
	return l->vet[l->head];
}
V remover(fila* l)
{
	if(vazia(l)==1)
	{
		return -1;
	}
    l->vet[l->head]=NULL;
    l->head=(l->head+1)%l->c;
    l->n--;
}

int tamanho_fila(fila* l)
{
	return l->n;
}
void limpar_fila(fila* l)
{
        l->head=l->tail=0;
		l->n=0;
	
}
void imprimir(fila* l)
{
	for(int i=0;i<l->n;i++)
	{
		printf("%d ",l->vet[(l->head+i)%l->c]);
	}
    printf("\n");
}
int filas_filas(fila* a,fila* b)
{
    if(a->n==b->n)
    {
        for(int i=0;i<a->n;i++)
        {
            if(a->vet[(a->head+i)%a->c]!=b->vet[(b->head+i)%b->c])
            {
                return 0;
            }
        }
        return 1;
    }
}
void inverter(fila* l)
{
    int i=l->head;
    int f=l->tail;
    int temp;
    while(i<f)
    {
        temp=l->vet[i];
        l->vet[i]=l->vet[f];
        l->vet[f]=temp;
        i++;
        f--;
    }
}
fila clonar_fila(fila* l)
{
    fila* p=criar_fila();
    p->head=l->head;
    p->tail=l->tail;
    for(int i=0;i<l->n;i++)
    {
        p->vet[i]=l->vet[i];
    }
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
}

fila* fluxo()
{
    fila* p=criar_fila();
    int v;
    int i=0;
    printf("Se desejar parar de inserir, digite -1:\n");
    scanf("%d",&v);
    while(v!=-1)
    {
        if(p->n==p->c)
        {
            full(p);
        }
        
        adicionar(p,v);
        scanf("%d",&v);
        i++ ;
    }
    imprimir(p);
    return p;
}
fila* intercalar_fluxos(fila* p,fila* f,fila*q)
{
    fila* v=criar_fila();
    v->c=p->n+f->n+q->n;
    v->vet=malloc(sizeof(V)*v->c);
    int x=0,m=0,y=0;
    while(x<p->n || m<f->n || y<q->n)
    {
        if(x<p->n)
        {
            adicionar(v,p->vet[(p->head+x)%p->c]);
            x++;
        }
        if(m<f->n)
        {
            adicionar(v,f->vet[(f->head+m)%f->c]);
            m++;
        }
        if(y<q->n)
        {
            adicionar(v,q->vet[(q->head+y)%q->c]);
            y++;
        }
    }
    int w=1;
    int t=2;
    for(int i=0;i<v->n;i++)
	{
        if(i==0 ||i%3==0)
        {
            printf("(1,%d) ",v->vet[(v->head+i)%v->c]);
        }
        
        if(i==1 ||i==4)
        {
            printf("(2,%d) ",v->vet[(v->head+i)%v->c]);
            w=w+3;
           
        }
        if(i==2 ||i==t)
        {
            printf("(3,%d) ",v->vet[(v->head+i)%v->c]);
            t=t+3;
        }
		
	}
    printf("\n");
    printf("\n");
    
    return v;
}
void demutiplexacao()
{
    fila* p=criar_fila();
    fila* r=criar_fila();
    fila* k=criar_fila();
    
    fila* x=criar_fila();
    fila* y=criar_fila();
    int v;
    int z;
    int i=0;
    printf("digite -1 para sair. Caso queira continuar o primeiro valor informado será interpretado como identificador.");
    scanf("%d",&v);
    while(v!=-1)
    {
        if(x->n==x->c)
        {
            full(x);
        }
        if(y->n==y->c)
        {
            full(y);
        }
        printf("digite o valor:");
        scanf("%d",&z);
        adicionar(x,v);
        adicionar(y,z);
        printf("digite o identificador");
        scanf("%d",&v);
        i++ ;
    }
    for (int j = 0; j < x->n; j++)
    {
        int idx = (x->head + j) % x->c;
        int idy = (y->head + j) % y->c;

        if (x->vet[idx] == 1)
        {
            if (p->n == p->c)
            {
                full(p);
            }
            adicionar(p, y->vet[idy]);
        }
        else if (x->vet[idx] == 2)
        {
            if (r->n == r->c)
            {
                full(r);
            }
            adicionar(r, y->vet[idy]);
        }
        else if (x->vet[idx] == 3)
        {
            if (k->n == k->c)
            {
                full(k);
            }
            adicionar(k, y->vet[idy]);
        }
    }

    printf("fluxo 1:");
    imprimir(p);
    printf("fluxo 2:");
    imprimir(r);
    printf("fluxo 3:");
    imprimir(k);
}
int main()
{
    /*int x,o=1;
    fila* p=criar_fila();
    V t;
    while(o!=0)
    {
        scanf("%d",&x);
        adicionar(p,x);
        printf("fim?\n");
        scanf("%d",&o);
    }
    printf("lista:");
    imprimir(p);
    printf("\n");
    printf("tamanho da fila:%d\n",tamanho_fila(p));
    remover(p);
    printf("lista:");
    imprimir(p);
    printf("\n");
    printf("%d\n",tamanho_fila(p));
    limpar_fila(p);
    vazia(p);
    p=fluxo();
    fila* f=criar_fila();
    f=fluxo();
    fila* q=criar_fila();
    q=fluxo();
    printf("fluxo 1:");
    imprimir(p);
    printf("fluxo 2:");
    imprimir(f);
    printf("fluxo 3:");
    imprimir(q);
    fila* w=criar_fila();
    w=intercalar_fluxos(p,f,q);
    imprimir(w);
    demutiplexacao();*/

	return 0;
}
