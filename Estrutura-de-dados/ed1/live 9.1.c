#include <stdio.h>
#include <stdlib.h>
#include<locale.h>

struct vertice{
    int num;
    struct vertice *prox;
};

struct listaadj{
    struct vertice *listav;
};

struct fila{
    int numv;
    struct fila *prox;
};

void inserir(struct fila* inicio, struct fila* fim, int n){
    struct fila *novo = malloc(sizeof(struct fila));
    novo->numv = n;
    novo->prox = NULL;

    if (inicio == NULL)
        inicio = fim = novo;
    else{
        fim->prox = novo;
        fim = novo;
    }
}

int remover(struct fila* inicio, struct fila* fim){
    if (inicio != NULL){
        int vert;
        if (inicio == fim)
            fim = NULL;
        vert = inicio->numv;
        inicio = inicio->prox;
        return vert;
    }
    printf("\nLista vaziz");
    return 0;
}

void buscalargura(struct listaadj Adj[], struct fila* inicio,
                  struct fila* fim, int tam, int v,
                  int marcado[], int dist[]){
    struct vertice *listavert;
    int w;
    int vertice;
    marcado[v] = 1;
    dist[v] = 0;
    inserir(inicio, fim, v);
    while (inicio != NULL){
        vertice = remover(inicio, fim);
        for (int i = 1; i <= tam; i++){
            listavert = Adj[vertice].listav;
            while (listavert != NULL){
                w = listavert->num;
                if (marcado[w] == 0){
                    marcado[w] = 1;
                    dist[w] = dist[vertice]+1;
                    inserir(inicio, fim, w);
                }
                listavert = listavert->prox;
            }
        }
    }
};

void mostrar_Adj(struct listaadj Adj[], int tam){
    struct vertice *v;
    for (int i = 1; i <= tam; i++){
        v = Adj[i].listav;
        printf("\nEntrada ", i);
        while(v != NULL){
            printf("(%d, %d) ", i, v->num);
            v = v->prox;
        }
    }
}

void mostrar_dist(int dist[], int tam, int or){
    printf("\nDistância da orgiem %d para os demais vértices\n");
    for (int i = 1; i <= tam; i++)
        printf("\nVértice %d - %d", i, dist[i]);
}

int main(){
    setlocale(LC_ALL, "Portuguese");

    struct fila *inicio = NULL;
    struct fila *fim = NULL;
    struct fila *temp;
    int *marcado;
    int *dist;
    struct listaadj *Adj;

    struct vertice *novo, *aux;

    int tam, org, dest, op, num=0, tipo, flag=0;

    printf("\nTipo do grafo \n"
           "1- não orientado\n"
           "2- orientado\n"
           ">> ");
    scanf("%d",&tipo);

    printf("\nDigite o número de vértices do grafo: ");
    scanf("%d",&tam);

    Adj = malloc(sizeof(struct listaadj[tam+1]));
    marcado = malloc(sizeof(marcado[tam+1]));
    dist = malloc(sizeof(dist[tam+1]));

    for (int i = 1; i <= tam; i++){
        Adj[i].listav = NULL;
        marcado[i] = 0;
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
        printf("\n1- Busca em largura"
               "\n2- Mostrar lista de adjacências"
               "\n3- Menor distância a partir do vértice de origem"
               "\n4- Sair"
               "\nDigite sua opção: ");
        scanf("%d",&op);
        if (op == 1){
            printf("\nDigite um vértice de partida da busca: ");
            scanf("%d",&num);

            for (int i= 1; i <= tam; i++){
                marcado[i] = 0;
                dist[i] = 0;
            }
            buscalargura(Adj, inicio, fim, tam,
                         num, marcado, dist);
            flag = 1;

        }else if (op == 2){
            mostrar_Adj(Adj, tam);
        }else if (op == 3){
            if (flag == 0)
                printf("\nÉ necessário realizar a busca primeiro");
            else
                mostrar_dist(dist, tam, num);
        }
        getch();
    }while (op != 4);

    free(marcado);
    free(dist);
    for (int i = 1; i <= tam; i++){
        while(Adj[i].listav != NULL){
            aux = Adj[i].listav;
            Adj[i].listav = Adj[i].listav->prox;
            free(aux);
        }
    }
    free(Adj);

    while (inicio != NULL){
        temp = inicio;
        inicio = inicio->prox;
        free(temp);
    }
}
