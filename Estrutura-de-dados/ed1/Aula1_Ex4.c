#include<stdio.h>
#include<stdlib.h>

int main(){
    int a, b, c;
    int *p, *q;
    p = &a;
    q = &b;
    c = *p + *q;
}

