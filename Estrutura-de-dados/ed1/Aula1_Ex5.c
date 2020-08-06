#include<stdio.h>
#include<stdlib.h>

int main(){
    int *v;
    v = malloc (100 * sizeof (int));
    *(v+0) = 700;
    printf("%d\n", v[0]);
    v[0] = 500;
    printf("%d\n", *(v+0));
}
