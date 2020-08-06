#include <stdio.h>
#include <stdlib.h>
#include<locale.h>

struct ARVORE {
    int num;
    struct ARVORE *esq, *dir;
};

struct PILHA {
    struct ARVORE *num;
    struct PILHA *prox;
};

int main(){
    setlocale(LC_ALL, "Portuguese");

    struct ARVORE *raiz = NULL;
    struct ARVORE *aux;
    struct ARVORE *aux1;
    struct ARVORE *novo;
    struct ARVORE *anterior;
    struct PILHA *topo;
    struct PILHA *aux_pilha;

    int op, achou, numero;

    do{
        system("cls");
        printf("\nMENU DE OPÇÕES\n");
        printf("\n1. Inserir na árvore");
        printf("\n2. Consultar um nó da árvore");
        printf("\n3. Consultar toda a árvore em ordem");
        printf("\n4. Consultar toda a árvore em pré-ordem");
        printf("\n5. Consultar toda a árvore em pós-ordem");
        printf("\n6. Excluir um nó da árvore");
        printf("\n7. Esvaziar a árvore");
        printf("\n\nDigite a opção: ");
        scanf("%d",&op);
        if (op < 1 || op > 8)
            printf("\nOpção inválida!");
        else if (op == 1){
            printf("\nDigite o número a ser inserido na árvore: ");
            novo = malloc(sizeof(struct ARVORE));
            scanf("%d",&novo->num);
            novo->dir = NULL;
            novo->esq = NULL;
            if (raiz == NULL)
                raiz = novo;
            else{
                aux = raiz;
                achou = 0;
                while (achou == 0){
                    if (novo->num < aux->num){
                        if (aux->esq == NULL){
                            aux->esq = novo;
                            achou = 1;
                        }else
                            aux = aux->esq;
                    }else if(novo->num >= aux->num){
                        if (aux->dir == NULL){
                            aux->dir = novo;
                            achou = 1;
                        }else
                            aux = aux->dir;
                    }
                }
            }
            printf("\nNúmero inserido na árvore!");
        }else if (op==2){
            if (raiz == NULL){
                printf("\nÁrvore vazia!");
            }else{
                printf("\nDigite o elemento a ser consultado");
                scanf("%d",numero);
                achou = 0;
                aux = raiz;
                while(aux != NULL && achou == 0){
                    if (aux->num == numero){
                        printf("\nNúmero encontrado na árvore!");
                        achou = 1;
                    }else if (numero < aux->num)
                        aux = aux->esq;
                    else
                        aux = aux->dir;
                }
                if (achou == 0)
                    printf("\nNúmero não encontrado na árvore!");
            }
        }else if (op == 3){
            if (raiz == NULL){
                printf("\nÁrvore vazia!");
            }else{
                printf("\nListando todos os elementos da árvore em ordem\n");
                aux = raiz;
                topo = NULL;
                do{
                    while(aux != NULL){
                        aux_pilha = malloc(sizeof(struct PILHA));
                        aux_pilha->num = aux;
                        aux_pilha->prox = topo;
                        topo = aux_pilha;
                        aux = aux->esq;
                    }
                    if (topo != NULL){
                        aux_pilha = topo;
                        printf("%d ", aux_pilha->num->num);
                        aux = topo->num->dir;
                        topo = topo->prox;
                    }
                }while (topo != NULL || aux != NULL);
            }
        }else if (op == 4){
            if (raiz == NULL){
                printf("\nÁrvore vazia!");
            }else{
                printf("\nListando todos os elementos da árvore em pré-ordem\n");
                aux = raiz;
                topo = NULL;
                do{
                    while(aux != NULL){
                        aux_pilha = malloc(sizeof(struct PILHA));
                        printf("%d ", aux->num);
                        aux_pilha->num = aux;
                        aux_pilha->prox = topo;
                        topo = aux_pilha;
                        aux = aux->esq;
                    }
                    if (topo != NULL){
                        aux_pilha = topo;
                        topo = topo->prox;
                        aux = aux_pilha->num->dir;
                    }
                }while (topo != NULL || aux != NULL);
            }
        }else if(op == 5){
            if (raiz == NULL){
                printf("\nÁrvore vazia!");
            }else{
                printf("\nListando todos os elementos da árvore em pós-ordem\n");
                aux = raiz;
                topo = NULL;
                do{
                    do{
                        while(aux != NULL){
                            aux_pilha = malloc(sizeof(struct PILHA));
                            aux_pilha->num = aux;
                            aux_pilha->prox = topo;
                            topo = aux_pilha;
                            aux = aux->esq;
                        }
                        if (topo->num->dir != NULL){
                            aux = topo->num->dir;
                        }
                    }while(aux != NULL);
                    if (topo != NULL){
                        printf("%d ", topo->num->num);
                        if (topo->prox != NULL){
                            if (topo->prox->num->dir != NULL
                                && topo->prox->num->dir != topo->num){
                                    aux = topo->prox->num->dir;
                                    topo = topo->prox;
                            }else{
                                while(topo->prox != NULL &&
                                      topo->prox->num->dir == topo->num){
                                          topo = topo->prox;
                                          printf("%d ", topo->num->num);
                                }
                                topo = topo->prox;
                                if (topo != NULL)
                                    aux = topo->num->dir;
                                else
                                    aux = NULL;
                            }
                        }else{
                            topo = topo->prox;
                            aux = NULL;
                        }
                    }
                }while (topo != NULL || aux != NULL);
            }
        }
        getch();
    }while(op!=8);

}
