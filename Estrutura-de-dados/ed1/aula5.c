#include<stdio.h>
#include<stdlib.h>

typedef struct pilha {
   char        conteudo;
   struct pilha *prox;
} no;

no *pi;

void criapilha (void) {
    pi = malloc(sizeof(no));
    pi->prox = NULL;
}

void empilha (char y) {
    no *nova;
    nova = malloc(sizeof(no));
    nova->conteudo = y;
    nova->prox = pi->prox;
    pi->prox = nova;
}

char desempilha (void) {
    no *p;
    p = pi->prox;
    char x = p->conteudo;
    pi->prox = p->prox;
    free(p);
    return x;
}

void imprimir () {
    no *p;
    p = pi->prox;
    for (; p != NULL; p = p->prox)
        printf("%c\n", p->conteudo);
}

main(){
    char v;
    criapilha();
    empilha('a');
    empilha('b');
    empilha('c');
    imprimir();
    printf("\nDesempilhou %c\n\n", desempilha());
    imprimir();
    return 1;
}
