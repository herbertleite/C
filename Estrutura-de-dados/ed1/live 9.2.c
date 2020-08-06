#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<locale.h>

struct ListaPrior{
    int *vet;
    int tam;
};

struct vertice{
    int num;
    int peso;
    struct vertice *prox;
};

struct listaadj{
    struct vertice *listav;
};

int Pai(int x){
    return x/2;
}

void inserirListaPrior(struct ListaPrior lista, int num,
                       int dist[], int tam){
    int ind;
    if (lista.tam < tam-1){
        lista.tam++;
        ind = lista.tam;
        while(ind > 1 && dist[lista.vet[Pai(ind)]] > dist[num]){
            lista.vet[ind] = lista.vet[Pai(ind)];
            ind = Pai(ind);
        }
        lista.vet[ind] = num;
    }
}

void heap_fica(struct ListaPrior lista, int i, int qtde, int dist[]){
    int f_esq, f_dir, menor, aux;
    menor = i;
    if (2*i + 1 <= qtde){
        f_esq = 2*i;
        f_dir = 2*i+1;
        if (dist[lista.vet[f_esq]] <
            dist[lista.vet[f_dir]] &&
            dist[lista.vet[f_esq]] <
            dist[lista.vet[i]])
            menor = 2*i;
        else if (dist[lista.vet[f_dir]] <
                 dist[lista.vet[f_esq]] &&
                 dist[lista.vet[f_dir]] <
                 dist[lista.vet[i]])
            menor = 2*i+1;
    }else if (2*i <= qtde){
        f_esq = 2*i;
        if (dist[lista.vet[f_esq]] <
            dist[lista.vet[i]])
            menor = 2*i;
    }
    if (menor != i){
        aux = lista.vet[i];
        lista.vet[i] = lista.vet[menor];
        lista.vet[menor] = aux;
        heap_fica(lista, menor, qtde, dist);
    }
}

void constroiheap(struct ListaPrior lista, int dist[]){
    for (int i = lista.tam/2; i >= 1; i--)
        heap_fica(lista, i, lista.tam, dist);
}

int remover(struct ListaPrior lista, int dist[]){
    if (lista.tam == 0)
        printf("\nLista vazia!");
    else{
        int menor_prior = lista.vet[1];
        lista.vet[1] = lista.vet[lista.tam];
        lista.tam--;
        heap_fica(lista, 1, lista.tam, dist);
        return menor_prior;
    }
    return 0;
}

void imprimir(struct ListaPrior lista){
    for (int i = 1; i <= lista.tam; i++)
        printf(" %d", lista.vet[i]);
}

void relax(int u, int v, int peso, int pai[], int dist[]){
    if (dist[v] > dist[u]+peso){
        dist[v] = dist[u]+peso;
        pai[v]=u;
    }
}

void dijkstra(struct listaadj Adj[], int tam, int v,
              int pai[], int dist[]){
    int i, w;
    int *C = malloc(sizeof(C[tam]));
    int tamC = 0;
    struct ListaPrior lista;

    lista.vet = malloc(sizeof(lista.vet[tam+1]));
    lista.tam = 0;

    dist[v]=0;
    inserirListaPrior(lista,v, dist, tam);
    for (i = 1; i <= tam; i++){
        if (i != v){
            dist[i] = HUGE_VAL;
            pai[i] = 0;
            inserirListaPrior(lista, i, dist, tam);
        }
    }
    while(lista.tam != 0){
        w = remover(lista, dist);
        C[tamC] = w;
        tamC++;

        struct vertice *x = Adj[w].listav;
        while (x != NULL){
            relax(w, x->num, x->peso, pai, dist);
            x = x->prox;
        }
        constroiheap(lista,dist);
    }
}

void mostrar_Adj(struct listaadj Adj[], int tam){
    struct vertice *v;
    for (int i=1; i <= tam; i++){
        v = Adj[i].listav;
        printf("\nEntrada %d ",i);
        while (v != NULL){
            printf("(%d, %d) ",i, v->num);
            v = v->prox;
        }
    }
}

void mostrar_dist(int tam, int or, int dist[]){
    printf("\nDistância da origem %d para os demais vértices\n",or);
    for(int i=1; i <= tam; i++)
        printf("\nVértice %d - %d",i,dist[i]);
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    int *marcado;
    int *pai;
    int *dist;
    struct listaadj *Adj;
    struct vertice *novo;

    int tam, org, dest, op, num = 0, flag = 0, peso = 0;

    printf("\nDigite o número de vértices do grafo orientado: ");
    scanf("%d",&tam);

    Adj = malloc(sizeof(struct listaadj[tam+1]));
    marcado = malloc(sizeof(marcado[tam+1]));
    pai = malloc(sizeof(pai[tam+1]));
    dist = malloc(sizeof(dist[tam+1]));

    for (int i = 1; i <= tam; i++){
        Adj[i].listav = NULL;
        marcado[i] = 0;
    }
    printf("\nArestas do grafo: VérticeOrigem"
           "(-1 para parar):");
    scanf("%d",&org);
    printf("\nArestas do grafo: VérticeDestino"
           "(-1 para parar):");
    scanf("%d",&dest);

    while(org != -1 && dest != -1){
        printf("\nPeso da aresta: ");
        scanf("%d",&peso);
        novo = malloc(sizeof(struct vertice));
        novo->num = dest;
        novo->peso = peso;
        novo->prox = Adj[org].listav;
        Adj[org].listav = novo;

        printf("\n\nArestas do grafo: VérticeOrigem"
           "(-1 para parar):");
        scanf("%d",&org);
        printf("\nArestas do grafo: VérticeDestino"
           "(-1 para parar):");
        scanf("%d",&dest);
    }
    do{
        system("cls");
        printf("\n1 Caminho Mínimo"
               "\n2 Mostrar lista de adjacências"
               "\n3 Mostrar distâncias"
               "\n4 Sair"
               "\n\nDigite sua opção: ");
        scanf("%d",&op);
        if (op == 1){
            printf("\nDigite um vértice de origem: ");
            scanf("%d",&num);

            for (int i = 1; i <= tam; i++){
                marcado[i] = 0;
                dist[i] = 0;
            }
            dijkstra(Adj, tam, num, pai, dist);
            flag = 1;
        }else if (op == 2){
            mostrar_Adj(Adj, tam);
        }else if (op == 3){
            if (flag == 0)
                printf("\nÉ necessário realizar a busca primeiro");
            else
                mostrar_dist(tam, num, dist);
        }
        getch();
    }while (op != 4);
}
