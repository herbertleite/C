#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct dl_elementoLista{
    char *dado;
    struct dl_elementoLista *anterior;
    struct dl_elementoLista *seguinte;
} dl_elemento;

typedef struct dl_ListaDetectada{
    dl_elemento *inicio;
    dl_elemento *fim;
    int tamanho;
} dl_Lista;

/* inicialização da lista */
void inicializacao (dl_Lista * lista);
dl_elemento *aloc (dl_elemento * novo_elemento);

/* INSERÇÃO */
int ins_em_uma_lista_vazia (dl_Lista * lista, char *dado);
int ins_inicio_lista (dl_Lista * lista, char *dado);
int ins_fim_lista (dl_Lista * lista, char *dado);
int ins_depois (dl_Lista * lista, char *dado, int pos);
int ins_antes (dl_Lista * lista, char *dado, int pos);


/* REMOÇÃO */
int REMOV(dl_Lista *lista, int pos);
void exibe (dl_Lista * lista);

/**************************/
void exibe_inv (dl_Lista * lista);
void destruir (dl_Lista * lista);

void inicializacao (dl_Lista * lista){
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
}

int insercao_em_uma_lista_vazia (dl_Lista * lista, char *dado){
    dl_elemento *novo_elemento;
    if ((novo_elemento = aloc(novo_elemento))==NULL)
        return -1;
    strcpy(novo_elemento->dado, dado);
    novo_elemento->anterior = NULL;
    novo_elemento->seguinte = NULL;
    lista->inicio = novo_elemento;
    lista->fim = novo_elemento;
    lista->tamanho++;
    return 0;
}

int ins_inicio_lista (dl_Lista * lista, char *dado){
    dl_elemento *novo_elemento;
    if ((novo_elemento = aloc(novo_elemento))==NULL)
        return -1;
    strcpy(novo_elemento->dado, dado);
    novo_elemento->anterior = NULL;
    novo_elemento->seguinte = lista->inicio;
    lista->inicio->anterior = novo_elemento;
    lista->inicio = novo_elemento;
    lista->tamanho++;
    return 0;
}

int ins_fim_lista (dl_Lista * lista, char *dado){
    dl_elemento *novo_elemento;
    if ((novo_elemento = aloc(novo_elemento))==NULL)
        return -1;
    strcpy(novo_elemento->dado, dado);
    novo_elemento->seguinte = NULL;
    novo_elemento->anterior = lista->fim;
    lista->fim->seguinte = novo_elemento;
    lista->fim = novo_elemento;
    lista->tamanho++;
    return 0;

}

/*
int ins_depois (dl_Lista * lista, char *dado, int pos){

}
*/
/*
int ins_antes (dl_Lista * lista, char *dado, int pos){

}
*/

int remov(dl_Lista *lista, int pos){
    int i;
    dl_elemento *remov_elemento, *em_andamento;
    if (lista->tamanho == 0)
        return -1;
    if (pos == 1){
        remov_elemento = lista->inicio;
        lista->inicio = lista->inicio->seguinte;
        if(lista->inicio == NULL)
            lista->fim = NULL;
        else
            lista->inicio->anterior=NULL;
    }else if(pos == lista->tamanho){
        remov_elemento = lista->fim;
        lista->fim->anterior->seguinte = NULL;
        lista->fim = lista->fim->anterior;
    }else{
        em_andamento = lista->inicio;
        for (i = 1; i < pos; ++i)
            em_andamento = em_andamento->seguinte;
        remov_elemento = em_andamento;
        em_andamento->anterior->seguinte = em_andamento->seguinte;
        em_andamento->seguinte->anterior = em_andamento->anterior;
    }
    free(remov_elemento->dado);
    free(remov_elemento);
    lista->tamanho--;
    return 0;
}

void destruir(dl_Lista *lista){

}

dl_elemento *aloc (dl_elemento * novo_elemento){

}


int remov(dl_Lista *lista, int pos);

void exibe(dl_Lista *lista){

}

/*
void exibe_inv(dl_Lista *lista){

}
*/
int menu (dl_Lista *lista){
    int escolha;
    if (lista->tamanho == 0){
        printf ("1. Adição do 1° elemento\n");
        printf ("2. Fechar\n");
    } else{
        printf ("1. Adição no início da lista\n");
        printf ("2. Adição no final da lista\n");
        printf ("3. Adição antes da posição especificada\n");
        printf ("4. Adição depois da posição especificada\n");
        printf ("5. Remoção da posição especificada\n");
        printf ("6. Destruir a lista\n");
        printf ("7. Fechar\n");
    }
    printf ("\n\nFaça sua escolha: ");
    scanf ("%d", &escolha);
    getchar();
    if(lista->tamanho == 0 && escolha == 2)
        escolha = 7;
    return escolha;
}

int main (void) {
    setlocale(LC_ALL, "Portuguese");
    int escolha = 0, pos;
    char *dado;
    dado = malloc(50);
    dl_Lista *lista;
    dl_elemento *pilote = NULL;
    lista = (dl_Lista *) malloc (sizeof(dl_Lista));
    inicializacao(lista);
    while( escolha!= 7){
        escolha = menu(lista);
        switch(escolha){
            case 1:
                printf("Entre um elemento: ");
                scanf("%s",dado);
                getchar();
                if(lista->tamanho == 0)
                    insercao_em_uma_lista_vazia(lista,dado);
                else
                    ins_inicio_lista (lista, dado);
                printf("%d elementos: início=%s,fim=%s ",
                       lista->tamanho,
                       lista->inicio->dado,
                       lista->fim->dado);
                exibe(lista);
                break;
            case 2:
                printf("Entre um elemento: ");
                scanf("%s",dado);
                getchar();
                ins_fim_lista (lista, dado);
                printf("%d elementos: início=%s,fim=%s ",
                       lista->tamanho,
                       lista->inicio->dado,
                       lista->fim->dado);
                exibe(lista);
                break;
            case 3:
                if(lista->tamanho == 1){
                    printf("Utilizar a inserção no início ou no fim (Entrar Menu: 1 ou 2)\n");
                    break;
                }
                printf("Entre um elemento:");
                scanf("%s",dado);
                getchar();
                do{
                    printf("Entre a posição:");
                    scanf("%d",&pos);
                }while (pos < 1 || pos > lista-> tamanho);
                getchar();
                ins_antes(lista,dado,pos);
                printf("%d elementos: início=%s fim=%s ",
                       lista->tamanho,
                       lista->inicio->dado,
                       lista->fim->dado);
                exibe(lista);
                break;
            case 4:
                if(lista->tamanho == 1){
                    printf("Utilizar a inserção no início ou no fim (Entrar Menu: 1 ou 2)\n");
                    break;
                }
                printf("Entre um elemento : ");
                scanf("%s",dado);
                getchar();
                do{
                    printf("Entre a posição: ");
                    scanf("%d",&pos);
                }while (pos < 1 || pos > lista->tamanho);
                getchar();
                ins_depois(lista,dado,pos);
                printf("%d elementos: início=%s,fim=%s ",
                       lista->tamanho,
                       lista->inicio->dado,
                       lista->fim->dado);
                exibe(lista);
                break;
            case 5:
                do{
                    printf("Entre a posição: ");
                    scanf("%d",&pos);
                }while (pos < 1 || pos > lista->tamanho);
                getchar();
                remov(lista,pos);
                if(lista->tamanho != 0)
                    printf("%d elementos: início=%s,fim=%s ",
                           lista->tamanho,
                           lista->inicio->dado,
                           lista->fim->dado);
                else
                    printf("posição vazia: %d elementos",
                           lista->tamanho);
                exibe(lista);
                break;
            case 6:
                destruir(lista);
                printf("a posição foi destruída: %d elementos\n",
                       lista->tamanho);
                break;
        }
    }
    return 0;
}

