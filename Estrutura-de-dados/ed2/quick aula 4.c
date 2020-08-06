#include <stdio.h>
#include <locale.h>

void troca (int *x, int i, int j){
    int aux;
    aux = x[i];
    x[i] = x[j];
    x[j] = aux;
}

int particao(int *x, int p, int r){
    int pivo, i, j;
    pivo = x[(p+r)/2];
    i = p-1;
    j = r+1;
    while (i < j){
        do{
            j--;
        }while (x[j] > pivo);
        do{
            i++;
        }while (x[i] < pivo);
        if (i < j)
            troca(x, i, j);
    }
    return j;
}

void quicksort(int x, int p, int r){
    int q;
    if (p < r){
        q = particao(x, p, r);
        quicksort(x, p, q);
        quicksort(x, q+1, r);
    }
}

void imprimir(int *x, int n){
    int i;
    for (i = 0; i < n; i++){
        printf("%d ", x[i]);
    }
    printf("\n");
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    int arquivo[] = {25, 37, 48, 57, 12, 33, 86, 92};
    int tam = sizeof(arquivo)/sizeof(int);
    printf("Arquivo original\n");
    imprimir(arquivo, tam);
    quicksort(arquivo, 0, tam-1);
    imprimir(arquivo, tam);
}
