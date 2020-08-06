#include<stdio.h>
#include<locale.h>

void insercao(int *x, int n){
    int i, k, y;

    for (k = 1;k < n; k++){
        y = x[k];
        for (i = k-1; i >= 0 && y < x[i]; i--)
            x[i+1] = x[i];
        x[i+1] = y;
    }
}

void imprimir(int *x, int n){
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", x[i]);
    printf("\n\n");
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    int arquivo[] = {25, 57, 48, 37, 12, 92, 86, 33};
    int tam = sizeof(arquivo)/sizeof(int);
    printf("Arquivo original\n");
    imprimir(arquivo, tam);
    insercao(arquivo, tam);
    imprimir(arquivo, tam);
}
