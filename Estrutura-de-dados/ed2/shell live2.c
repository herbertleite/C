#include<stdio.h>
#include<locale.h>

void shellsort(int *x, int n, int *inc, int num) {
    int i, j, k, span, y;

    for (i = 0; i < num; i++){
        span = inc[i];

        for (j = span; j < n; j++){
            y = x[j];
            for (k = j - span; k >= 0 && y < x[k]; k-=span)
                x[k+span] = x[k];
            x[k+span] = y;
        }
    }
}

void imprimir(int x[], int n){
    int i;
    for (i = 0; i < n; i++){
        printf("%d ", x[i]);
    }
    printf("\n");
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    int arquivo[] = {25, 57, 48, 37, 12, 92, 86, 33};
    int arq[] = {5,3,1};
    int tam = sizeof(arquivo)/sizeof(int);
    int t = sizeof(arq)/sizeof(int);
    printf("Arquivo original\n");
    imprimir(arquivo, tam);
    shellsort(arquivo, tam, arq, t);
    imprimir(arquivo, tam);
}
