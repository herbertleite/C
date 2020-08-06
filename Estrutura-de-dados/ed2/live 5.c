#include <stdio.h>
#include <locale.h>

int x[11];

int main(){
    setlocale(LC_ALL, "Portuguese");
    int i, qtde;
    for (i = 1; i <= 10; i++){
        printf("Digite o %dº número: ", i);
        scanf("%d", &x[i]);
    }
    qtde = 10;
    transforma_heap(qtde);
    heapsort(qtde);
    imprimir();
}

void imprimir(){
    int i;
    for (i = 1; i < 11; i++){
        printf("%d ", x[i]);
    }
    printf("\n");
}

void transforma_heap(int qtde){
    int i;
    for (i = qtde/2; i >= 1; i--)
        fila_prioridade(i, qtde);
}

void fila_prioridade(int i, int qtde){
    int f_esq, f_dir, maior;
    maior = i;
    if (2*i+1 <= qtde){
        f_esq = 2*i+1;
        f_dir = 2*i;
        if(x[f_esq] >= x[f_dir]
           && x[f_esq] > x[i])
            maior = 2*i+1;
        else if (x[f_dir] > x[f_esq]
            && x[f_dir] > x[i])
            maior = 2*i;
    }else if(2*i <= qtde){
        f_dir = 2*i;
        if (x[f_dir] > x[i])
            maior = 2*i;
    }
    if (maior != i){
        troca(i, maior);
        fila_prioridade(maior, qtde);
    }
}

void heapsort(int qtde){
    int i, ultima_pos;
    for (i = qtde; i >= 2; i--){
        troca(1, i);
        ultima_pos = i-1;
        fila_prioridade(1, ultima_pos);
    }
}

void troca (int i, int j){
    int aux;
    aux = x[i];
    x[i] = x[j];
    x[j] = aux;
}
