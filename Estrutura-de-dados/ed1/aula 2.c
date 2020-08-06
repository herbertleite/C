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
