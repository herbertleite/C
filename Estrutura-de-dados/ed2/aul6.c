#include<stdio.h>
#include<locale.h>

int busca_binaria(int *v, int n, int x){
    int inf = 0, sup = n-1, meio;

    while (inf <= sup){
        meio = (inf + sup)/2;
        if (x == v[meio])
            return 1;
        else if(x<v[meio])
            sup = meio - 1;
        else
            inf = meio+1;
    }
    return 0;
}

 int main(){
    setlocale(LC_ALL, "Portuguese");
    int arquivo[] = {12, 25, 33, 37, 48, 57, 86, 92};
    int valor;
    int tam = sizeof(arquivo)/sizeof(int);
    printf("Valor procurado: ");
    scanf("%d", &valor);
    printf("\nRetorno: %d", busca_binaria(arquivo, tam, valor));
}
