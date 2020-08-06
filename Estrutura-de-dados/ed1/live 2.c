#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

typedef struct lista{
    int conteudo;
    struct lista *prox;
}no;

void inserir(int x, no *p){
    no *novo;
    novo = malloc(sizeof(no));
    novo->conteudo = x;
    novo->prox = p->prox;
    p->prox = novo;
}

void excluir(no *p){
    no *lixo;
    lixo = p->prox;
    p->prox = lixo->prox;
    free(lixo);
}

busca (int x, no *le){
    no *p = le;
    int achou = 0;
    while (p != NULL && !achou){
        if (p->conteudo == x)
            achou = 1;
        p = p->prox;
    }
    if (achou)
        return 1;
    else
        return NULL;
}

void imprimir(no *le){
    no *p;
    for (p = le; p != NULL; p = p->prox)
        printf("%d \n", p->conteudo);
}

int main (void) {
    int valor = 10;
    no *le;
    le = malloc (sizeof (no));
    le->prox = NULL;

    printf ("Tamanho do nó = %d\n", sizeof (le));

    for (int i = 1; i <= 10; i++){
        inserir(valor*i, le);
    }
    imprimir(le);
    excluir (le);
    imprimir (le);
    printf("%d\n",busca (10, le));

    return 1;
}
