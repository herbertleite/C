#include <stdio.h>
#include <locale.h>

void intercala(int *x, int inicio, int fim, int meio){
   int poslivre, inicio_v1, inicio_v2, i;
   int aux[fim];
   inicio_v1 = inicio;
   inicio_v2 = meio+1;
   poslivre = inicio;

   while (inicio_v1 <= meio && inicio_v2 <= fim){
        if (x[inicio_v1] <= x[inicio_v2]){
            aux[poslivre] = x[inicio_v1];
            inicio_v1 += 1;
        }else{
            aux[poslivre] = x[inicio_v2];
            inicio_v2 += 1;
        }
        poslivre++;
   }
   for (i = inicio_v1; i <= meio; i++){
        aux[poslivre] = x[i];
        poslivre++;
   }
   for (i = inicio_v2; i <= fim; i++){
        aux[poslivre] = x[i];
        poslivre++;
   }
   for (i = inicio; i <= fim; i++)
    x[i] = aux[i];

}

void merge(int *x, int inicio, int fim){
    int meio;
    if (inicio < fim){
        meio = (inicio+fim)/2;
        merge(x,inicio,meio);
        merge(x,meio+1, fim);
        intercala(x,inicio, fim, meio);
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
    int arquivo[] = {25, 57, 48, 37, 12, 92, 86, 33};
    int tam = sizeof(arquivo)/sizeof(int);
    printf("Arquivo original\n");
    imprimir(arquivo, tam);
    merge(arquivo,0,tam-1);
    imprimir(arquivo, tam);
}

