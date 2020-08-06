#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

typedef struct vertice {
    int num;
    struct vertice *prox;
} no;

typedef struct listaadj {
    no *listav;
} lista;

no *v;
lista *l;

void mostrar_adj(lista adj[], int tam){
    int i;
    for (i = 1; i <= tam; i++){
        v = adj[i].listav;
        printf("\n Entrada %d", i);
        while (v != NULL){
            printf("( %d, %d )", i, v->num);
            v = v->prox;
        }
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    l = NULL;
    no *novo;
    int i, tam, org, dest, op, num, tipo;

    printf("\nTipo de grafo\n"
           "\n1.  não orientado\n2. orientado\n>:");
    scanf("%d",&tipo);

    printf("\nNúmero de vértices: ");
    scanf("%d",&tam);

    l = malloc(sizeof(no));
    for (i = 0; i <= tam; i++){
        l->listav = NULL;
    }

    printf("\nArestas do grafo: \n"
           "Vértice de origem (-1 para): ");
    scanf("%d",&org);
    printf("\nArestas do grafo: \n"
           "Vértice de destino (-1 para): ");
    scanf("%d",&dest);

    while(org != -1 && dest != -1){
        novo = malloc(sizeof(no));
        novo->num = dest;
        novo->prox = l[org].listav;
        l[org].listav = novo;

        if (tipo == 1){
            novo = malloc(sizeof(no));
            novo->num = org;
            novo->prox = l[dest].listav;
            l[dest].listav = novo;
        }
        printf("\nArestas do grafo: \n"
           "Vértice de origem (-1 para): ");
        scanf("%d",&org);
        printf("\nArestas do grafo: \n"
           "Vértice de destino (-1 para): ");
        scanf("%d",&dest);
    }

    do{
        printf("Menu de opções: \n"
               "1. Mostrar lista de adjacências\n"
               "0. Sair\n");
        scanf("%d",&op);
        if (op == 1){
            print("Lista de adjacências\n");
            mostrar_adj(l, tam);
        }
    }

    return 0;
}


