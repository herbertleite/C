#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

struct vertice{
    int num;
    struct vertice *prox;
};

struct listaadj{
    struct vertice *listav;
};

struct queue{
    int numv;
    struct queue *prox;
};

void empilhar(struct queue *pilha, int n){
    struct queue *novo = malloc(sizeof(struct queue));
    novo->numv = n;
    novo->prox = pilha;
    pilha = novo;
}

void desempilhar(struct queue *pilha, int v){
    if (pilha->numv == v){
        struct queue* aux;
        aux = pilha;
        pilha = pilha->prox;
        free(aux);
    }
}

void buscaprof(struct listaadj Adj[], int tam, int v,
              int marcado[], struct queue* pilha){
    int w;
    struct vertice *vert;
    marcado[v] = 1;

    empilhar(pilha, v);

    for (int i = 1; i <= tam;i++){
        vert = Adj[v].listav;
        while (vert != NULL){
            w = vert->num;
            if (marcado[w] != 1){
                printf("%d ",w);
                buscaprof(Adj, tam, w, marcado, pilha);
            }
            vert = vert->prox;
        }
    }
    desempilhar(pilha, v);
}

void mostrar_adj(struct listaadj Adj[], int tam){
    struct vertice *v;
    int i;
    for (i = 1; i <= tam; i++){
        v = Adj[i].listav;
        printf("\n Entrada %d ", i);
        while (v != NULL){
            printf("(%d, %d) ",i, v->num);
            v = v->prox;
        }
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese");

    struct queue *pilha = NULL;
    int *marcado = NULL;
    struct listaadj *Adj = NULL;
    struct vertice *novo, *aux;
    int tam, org, dest, op, num, tipo;

    printf("\nTipo do grafo \n"
           "1- não orientado\n"
           "2- orientado\n"
           ">> ");
    scanf("%d",&tipo);

    printf("\nDigite o número de vértices do grafo: ");
    scanf("%d",&tam);

    Adj = malloc(sizeof(struct listaadj[tam+1]));
    marcado = malloc(sizeof(marcado[tam+1]));

    for (int i = 0; i <= tam; i++){
        marcado[i] = 0;
        Adj[i].listav = NULL;
    }

    printf("\nArestas dos grafo: Vértice de origem "
           "(-1 para parar): ");
    scanf("%d",&org);
    printf("\nArestas dos grafo: Vértice de destino "
           "(-1 para parar): ");
    scanf("%d",&dest);

    while (org != -1 && dest != -1){
        novo = malloc(sizeof(struct vertice));
        novo->num = dest;

        novo->prox = Adj[org].listav;
        Adj[org].listav = novo;

        if (tipo = 1){
            novo = malloc(sizeof(struct vertice));
            novo->num = org;

            novo->prox = Adj[dest].listav;
            Adj[dest].listav = novo;
        }
        printf("\nArestas dos grafo: Vértice de origem "
           "(-1 para parar): ");
        scanf("%d",&org);
        printf("\nArestas dos grafo: Vértice de destino "
           "(-1 para parar): ");
        scanf("%d",&dest);
    }
    do{
        printf("\n1- Busca em profundidade"
               "\n2- Mostrar lista de adjacências"
               "\n3- Sair"
               "\nDigite sua opção: ");
        scanf("%d",&op);
        if (op == 1){
            printf("\nDigite um vértice de partida da busca: ");
            scanf("%d",&num);
            printf(" %d ",num);
            buscaprof(Adj, tam, num, marcado, pilha);

            for (int i= 1; i <= tam; i++)
                marcado[i] = 0;
        }else if (op == 2){
            mostrar_adj(Adj, tam);
        }
    }while (op != 3);

    free(marcado);
    for (int i = 1; i <= tam; i++){
        while(Adj[i].listav != NULL){
            aux = Adj[i].listav;
            Adj[i].listav = Adj[i].listav->prox;
            free(aux);
        }
    }
    free(Adj);
}
