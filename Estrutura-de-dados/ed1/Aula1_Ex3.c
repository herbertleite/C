#include<stdio.h>
#include<stdlib.h>

typedef struct {
        int dia;
        int mes;
        int ano;
} data;

int main(){
    data x, y;
    x.ano = 2020;
    x.mes = 5;
    x.dia = 5;
    scanf("%d %d %d", &y.dia, &y.mes, &y.ano);
    printf("%d/%d/%d\n",x.dia, x.mes, x.ano);
    printf("%d/%d/%d\n", y.dia, y.mes, y.ano);
}
