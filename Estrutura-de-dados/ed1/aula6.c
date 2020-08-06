//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Constantes
#define tamanho 5

//Estrutura da Fila
struct tfila {
    int dados[tamanho];
    int ini;
    int fim;
};

//Variáveis globais
struct tfila fila;
int op;

//Protipação
void fila_entrar();
void fila_sair();
void fila_mostrar();
void menu_mostrar();

//Função principal
int main(){
    setlocale(LC_ALL, "Portuguese");
    op = 1;
    fila.ini = 0;
    fila.fim = 0;
    while (op != 0) {
        system("cls");
        fila_mostrar();
        menu_mostrar();
        scanf("%d", &op);
        switch (op) {
            case 1:
                fila_entrar();
                break;
            case 2:
                fila_sair();
                break;
        }
    }
    return(0);
}

//Adicionar um elemento no final da Fila
void fila_entrar(){
    if (fila.fim == tamanho){
        printf("Fila está cheia\n");
        system("pause");
    }else{
        printf("Digite um valor: ");
        scanf("%d", &fila.dados[fila.fim]);
        fila.fim++;
    }

}

//Retirar o primeiro elemento da Fila
void fila_sair() {
    if(fila.ini == fila.fim){
        printf("Fila está vazia\n");
        system("pause");
    }else{
        int i;
        for(i = 0; i < tamanho; i++){
            fila.dados[i] = fila.dados[i+1];
        }
        fila.dados[fila.fim]=0;
        fila.fim--;
    }

}

//Mostrar o conteúdo da Fila
void fila_mostrar() {
    int i;
    for (i = 0; i < tamanho; i++)
        printf("%d ", fila.dados[i]);
    printf("\n");
}

//Mostrar o menu de opções
void menu_mostrar() {
    printf("\nEscolha uma opção:\n");
    printf("1 - Incluir na Fila\n");
    printf("2 - Excluir da Fila\n");
    printf("0 - Sair\n\n");
}
