//Bibliotecas
#include <stdio.h>
#include <stdlib.h>

//Constantes
#define tamanho 100
#define E 0
#define D 1
#define R -1

//Estrutura
struct str_no {
    char dado;
    int esquerda;
    int direita;
    int pai;
};

//Variáveis
struct str_no arvore[tamanho];
int lado,indice=0;
int opt=-1;
char pai, no;

//Prototipação
void arvore_insere(int pai, char dado, int lado);
int arvore_procura(char dado);
void menu_mostrar(void);

//Função principal
int main(void){
    int temp;
    do {
        menu_mostrar();
        scanf("%d", &opt);
        switch (opt){
            case 1:
                printf("\nDigite o valor do PAI: ");
                scanf("%c",&pai);
                //scanf("%c",&pai);
                printf("Digite o valor do NO: ");
                scanf("%c",&no);
                //scanf("%c",&no);
                printf("Digite o lado da subarvore ",
                       "(E=%d/D=%d/R=%d): ",E,D,R);
                scanf("%d",&lado);
                temp = arvore_procura(pai);
                arvore_insere(temp,no,lado);
                break;
            case 2:
                printf("Digite o valor do NO: ");
                scanf("%c",&no);
                //scanf("%c",&no);
                temp = arvore_procura(no);
                printf("No %c\nFilho Esquerda: %c ",
                       "\nFilho Direita: %c\n\n",
                       arvore[temp].dado,
                       arvore[arvore[temp].esquerda].dado,
                       arvore[arvore[temp].direita].dado);
                system("pause");
                break;
        }
    }while (opt!=0);
    system("pause");
    return(0);
}

//Inserir nó
void arvore_insere(int pai, char dado, int lado){
    switch(lado){
        case E:
            arvore[pai].esquerda = indice;
            arvore[indice].dado = dado;
            arvore[indice].pai = pai;
            arvore[indice].esquerda = -1;
            arvore[indice].direita = -1;
            indice++;
            break;
        case D:
            arvore[pai].direita = indice;
            arvore[indice].dado = dado;
            arvore[indice].esquerda = -1;
            arvore[indice].direita = -1;
            indice++;
            break;
        case R:
            arvore[indice].dado = dado;
            arvore[indice].pai = -1;
            arvore[indice].esquerda = -1;
            arvore[indice].direita = -1;
            indice++;
            break;
    }

}

//Procura nó
int arvore_procura(char dado){
     if (indice != 0){
        for (int i = 0; i<indice; i++){
            if (arvore[i].dado == dado) {
                return (i);
            }
        }
    } else {
        return (0);
    }
}

//Desenha o menu na tela
void menu_mostrar(void){
    system("cls");
    for (int i = 0; i < indice; i++){
        printf("| %c ",arvore[i].dado);
    }
    printf("\n1 - Inserir um NO na arvore");
    printf("\n2 - Pesquisar um NO na arvore");
    printf("\n0 - Sair...\n\n");
}
