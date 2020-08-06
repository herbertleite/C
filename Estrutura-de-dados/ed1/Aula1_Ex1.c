#include<stdio.h>

int main(){

    typedef struct {
        int dia, mes, ano;
    } data;
    int i = 1234;

    printf ("sizeof (data) = %d\n", sizeof (data));
    printf (" i = %d\n", i);
    printf ("&i = %ld\n", (long int) &i);
    printf ("&i = %p\n", (void *) &i);

    return 1;
}


