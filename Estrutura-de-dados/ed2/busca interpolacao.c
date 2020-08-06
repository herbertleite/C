#include<stdio.h>
#include<locale.h>

int busca_interpolacao(int *v, int n, int x){
    int ini = 0;
    int meio;
    int fim = n - 1;
    while (ini <= fim){
        meio = ini + ((fim-ini)*(x-v[ini]))/
        (v[fim]-v[ini]);
        printf("\nO indice %d\n",meio);
        if (x < v[meio]){
            fim = meio -1;
        }else if (x > v[meio]){
            ini = meio+1;
        }else{
            return meio;
        }
    }
    return -1;
}

 int main(){
    setlocale(LC_ALL, "Portuguese");
    int arquivo[] = {12, 25, 33, 37, 48, 57, 86, 92};
    int valor;
    int tam = sizeof(arquivo)/sizeof(int);
    printf("Valor procurado: ");
    scanf("%d", &valor);
    printf("\nRetorno: %d", busca_interpolacao(arquivo, tam, valor));
}
