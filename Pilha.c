#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define V int  

typedef struct {
    V* vet; 
    int top;
    int c;  
    int n;
} pilha;

pilha* criar_pilha() 
{
    pilha* p=(pilha*)malloc(sizeof(pilha));
    p->c=5;
    p->n=0;
    p->vet=malloc(sizeof(V)*p->c);
    p->top=-1; 
    return p;
}

void liberar_pilha(pilha* p) 
{
    free(p->vet);
    free(p);
}

void full(pilha* p) 
{
    int x=p->c*2; 
    V* y=(V*)malloc(sizeof(V)*x); 
    for(int i=0;i<=p->top;i++) 
    {
        y[i]=p->vet[i];
    }
    free(p->vet);
    p->vet=y;
    p->c=x;
}

void adicionar(pilha* p, V v) 
{
    if (p->top==p->c-1) 
    {
        full(p);
    }
    p->vet[++p->top]=v;
    p->n++;
}

int vazia(pilha* p) 
{
    return (p->top==-1);
}

V pop(pilha* p) 
{
    if (vazia(p)) 
    {
        printf("Pilha vazia!\n");
        return 0;
    }
    V x=p->vet[p->top--];
    p->n--;
    return x;
}

V obter_topo(pilha* p) 
{
    if (vazia(p)) 
    {
        printf("Pilha vazia!\n");
        return 0;
    }
    return p->vet[p->top];
}

void imprimir(pilha* p) 
{
    if (vazia(p)) 
    {
        printf("Pilha vazia!\n");
        return;
    }
    for (int i=p->top;i>=0;i--) 
    {
        printf("%d ",p->vet[i]);
    }
    printf("\n");
}

void decimal_binario(int x, char* sb) 
{
    pilha* p=criar_pilha();
    if (x==0) 
    {
        sb[0]='0';
        sb[1]='\0';
        return;
    }
    while (x>0) 
    {
        adicionar(p,x%2);
        x/=2;
    }
    int i=0;
    while(!vazia(p)) 
    {
        sb[i++]=pop(p)+'0';
    }
    sb[i]='\0';
    liberar_pilha(p);
}

int verificar_parentese(char* s) 
{
    pilha* p=criar_pilha();
    for (int i=0;s[i]!='\0';i++) 
    {
        if (s[i]=='(')
        {
            adicionar(p,'(');
        }
        else if(s[i]==')') 
        {
            if(vazia(p)) 
            {
                liberar_pilha(p);
                return 0;
            }
            pop(p);
        }
    }
    int r=vazia(p); 
    liberar_pilha(p);
    return r;
}
int verificar_delimitadores(char* x) 
{
    pilha* p = criar_pilha();
    for (int i=0;x[i]!='\0';i++) 
    {
        char c=x[i];
        if (c=='('||c=='['||c=='{')
        {
            adicionar(p, c);
        }
        else if (c == ')' || c == ']' || c == '}')
        {
            if (vazia(p)) 
            { 
                liberar_pilha(p);
                return 0;
            }
            char topo = pop(p);
            if ((c==')'&&topo!='(')||(c==']'&&topo!='[') |(c=='}'&&topo!='{')) 
            {
                liberar_pilha(p);
                return 0;
            }
        }
    }

    int r=vazia(p); 
    liberar_pilha(p);
    return r;
}
void inverter(pilha* p) 
{
    if (vazia(p)) return;
    pilha* aux=criar_pilha();
    pilha* iv=criar_pilha();
    while (!vazia(p)) 
    {
        adicionar(aux,pop(p));
    }
    while (!vazia(aux)) 
    {
        adicionar(iv, pop(aux));
    }
    for (int i=0;i<=iv->top;i++) 
    {
        p->vet[i]=iv->vet[i];
    }
    p->top=iv->top;
    p->n=iv->n;

    liberar_pilha(aux);
    liberar_pilha(iv);
}
pilha* clonar_pilha(pilha* p) {
    pilha* clone=criar_pilha();
    pilha* aux=criar_pilha();
    for (int i=0;i<=p->top;i++) 
    {
        adicionar(aux,p->vet[i]);
    }
    for (int i=0;i<=aux->top;i++) 
    {
        adicionar(clone,aux->vet[i]);
    }
    liberar_pilha(aux);
    return clone;
}
int precedencia(char p)
{
    if (p=='^')return 3;
    if (p=='*'||p=='/')return 2;
    if (p=='+'||p=='-')return 1;
    return 0;
}

int operador(char c) 
{
    return (c=='+'||c=='-'||c=='*'||c=='/'||c=='^');
}
int infixa_para_posfixa(char* infixa, char* posfixa) 
{
    pilha* op=criar_pilha();
    int j=0;
    for (int i=0;infixa[i]!='\0';i++) 
    {
        char c=infixa[i];
        if (c==' ')continue;
        if (c>='0'&&c<='9') 
        {
           posfixa[j++]=c;
        }
        else if (c=='(') 
        {
            adicionar(op,c);
        }
        else if (c==')') 
        {
            while (!vazia(op)&&obter_topo(op)!='(') 
            {
                posfixa[j++]=pop(op);
            }
            if (vazia(op)) 
            {
                liberar_pilha(op);
                return 0;
            }
            pop(op);
        }
        else if (operador(c)) 
        {
            while (!vazia(op)&&precedencia(obter_topo(op))>=precedencia(c)) 
            {
                posfixa[j++]==pop(op);
            }
            adicionar(op,c);
        }
        else 
        {
            liberar_pilha(op);
            return 0;
        }
    }
    while (!vazia(op)) 
    {
        char t=pop(op);
        if (t=='('||t==')') 
        { 
            liberar_pilha(op);
            return 0;
        }
        posfixa[j++]=t;
    }
    posfixa[j]='\0';
    liberar_pilha(op);
    return 1; 
}

int main() 
{
    return 0;
}
