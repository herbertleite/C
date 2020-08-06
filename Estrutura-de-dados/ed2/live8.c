#include <stdio.h>
#include <stdlib.h>
#include<locale.h>

struct ARVORE {
    int num;
    struct ARVORE *esq, *dir;
};

struct ARVORE *inserir(struct ARVORE *aux, int num){
    if (aux == NULL){
        aux = malloc(sizeof(struct ARVORE));
        aux->num = num;
        aux->esq = NULL;
        aux->dir = NULL;
    }else if (num < aux->num)
        aux->esq = inserir(aux->esq, num);
    else
        aux->dir = inserir(aux->dir, num);
    return aux;
}

int consultar(struct ARVORE *aux, int num, int achou){
    if (aux != NULL && achou == 0){
        if (aux->num == num)
            achou = 1;
        else if(num < aux->num)
            achou = consultar(aux->esq, num, achou);
        else
            achou = consultar(aux->dir, num, achou);
    }
    return achou;
}

void mostraremordem(struct ARVORE *aux){
    if (aux != NULL){
        mostraremordem(aux->esq);
        printf("%d ", aux->num);
        mostraremordem(aux->dir);
    }
}

void mostrarpreordem(struct ARVORE *aux){
    if (aux != NULL){
        printf("%d ", aux->num);
        mostrarpreordem(aux->esq);
        mostrarpreordem(aux->dir);
    }
}

void mostrarposordem(struct ARVORE *aux){
    if (aux != NULL){
        mostrarposordem(aux->esq);
        mostrarposordem(aux->dir);
        printf("%d ", aux->num);
    }
}

struct ARVORE *remover(struct ARVORE *aux, int num){
    struct ARVORE *p, *p2;
    if (aux->num == num){
        if (aux->esq == aux->dir){
            free(aux);
            return NULL;
        }else if(aux->esq == NULL){
            p = aux->dir;
            free(aux);
            return p;
        }else if(aux->dir == NULL){
            p = aux->esq;
            free(aux);
            return p;
        }else{
            p2 = aux->dir;
            p = aux->dir;
            while (p->esq != NULL)
                p = p->esq;
            p->esq = aux->esq;
            free(aux);
            return p2;
        }
    }else if(aux->num < num)
        aux->dir = remover(aux->dir, num);
    else
        aux->esq = remover(aux->esq, num);
    return aux;
}

struct ARVORE *desalocar(struct ARVORE *aux){
    if (aux != NULL){
        aux->esq = desalocar(aux->esq);
        aux->dir = desalocar(aux->dir);
        free(aux);
    }
    return NULL;
}

int main(){
    setlocale(LC_ALL, "Portuguese");

    struct ARVORE *raiz = NULL;
    struct ARVORE *aux;


    int op, achou, numero;

    do{
        system("cls");
        printf("\nMENU DE OP��ES\n");
        printf("\n1. Inserir na �rvore");
        printf("\n2. Consultar um n� da �rvore");
        printf("\n3. Consultar toda a �rvore em ordem");
        printf("\n4. Consultar toda a �rvore em pr�-ordem");
        printf("\n5. Consultar toda a �rvore em p�s-ordem");
        printf("\n6. Excluir um n� da �rvore");
        printf("\n7. Esvaziar a �rvore");
        printf("\n\nDigite a op��o: ");
        scanf("%d",&op);
        if (op < 1 || op > 8)
            printf("\nOp��o inv�lida!");
        else if (op == 1){
            printf("\nDigite o n�mero a ser inserido na �rvore: ");
            scanf("%d",&numero);
            raiz = inserir(raiz, numero);
            printf("\nN�mero inserido na �rvore!");
        }else if (op==2){
            if (raiz == NULL){
                printf("\n�rvore vazia!");
            }else{
                printf("\nDigite o elemento a ser consultado: ");
                scanf("%d",&numero);
                achou = 0;
                achou = consultar(raiz, numero, achou);
                if (achou == 0)
                    printf("\nN�mero n�o encontrado na �rvore!");
                else
                    printf("\nN�mero encontrado na �rvore!");
            }
        }else if (op == 3){
            if (raiz == NULL){
                printf("\n�rvore vazia!");
            }else{
                printf("\nListando todos os elementos da �rvore em ordem\n");
                mostraremordem(raiz);
            }
        }else if (op == 4){
            if (raiz == NULL){
                printf("\n�rvore vazia!");
            }else{
                printf("\nListando todos os elementos da �rvore em pr�-ordem\n");
                mostrarpreordem(raiz);
            }
        }else if(op == 5){
            if (raiz == NULL){
                printf("\n�rvore vazia!");
            }else{
                printf("\nListando todos os elementos da �rvore em p�s-ordem\n");
                mostrarposordem(raiz);
            }
        }else if(op == 6){
            if (raiz == NULL){
                printf("\n�rvore vazia!");
            }else{
                printf("\nDigite o n�mero que deseja excluir: ");
                scanf("%d",&numero);
                achou = 0;
                achou = consultar(raiz, numero, achou);
                if (achou == 0)
                    printf("\nN�mero n�o encontrado na �rvore!");
                else{
                    raiz = remover(raiz, numero);
                    printf("\nN�mero exclu�do da �rvore");
                }
            }
        }else if(op == 7){
            if (raiz == NULL){
                printf("\n�rvore vazia!");
            }else{
                raiz = desalocar(raiz);
                printf("\n�rvore esvaziada\n");
            }
        }
        getch();
    }while(op!=8);
    raiz = desalocar(raiz);
}
