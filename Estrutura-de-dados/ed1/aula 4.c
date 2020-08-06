#include <stdio.h>
#include <stdlib.h>

struct item
{
    int info;
    struct item * prox;
};

void insereCircularLista(struct item **p0, int x){
    struct item *p;
    p = (struct item *) malloc(sizeof(struct item));
    p->info = x;
    if (*p0 == NULL)
        p->prox = p;
    else{
        p->prox = (*p0)->prox;
        (*p0)->prox = p;
    }
    *p0 = p;
}

void leiaLista(struct item **p0){
    int i, n, val;
    scanf("%d", &n);
    for(i = 1; i <= n; i++){
        scanf("%d", &val);
        insereCircularLista(p0, val);
    }
    if (*p0 != NULL)
        *p0 = (*p0)->prox;
}

void imprimaLista(struct item *p0)
{
    struct item *p;
    if (p0 != NULL)
    {
        p = p0;
        do{
            printf("%6d ", p->info);
            p = p->prox;
        }while (p != p0);
    }
    putchar('\n');
}

void invertaLista(struct item **p0){
   struct item *pa, *pb, *pc;
   if (*p0 != NULL){
    pa = *p0;
    pb = pa->prox;
    pc = pb->prox;
    do{
        pb->prox = pa;
        pa = pb;
        pb = pc;
        pc = pc->prox;
    }while (pa != *p0);
    *p0 = (*p0)->prox;
   }
}

int main(void)
{
    struct item *lista = NULL;
    leiaLista(&lista);
    imprimaLista(lista);
    invertaLista(&lista);
    imprimaLista(lista);
    return 0;
}
