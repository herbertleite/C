#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

typedef struct lista{
    int conteudo;
    struct lista *prox;
}no;

//conteudo e no por parametro
void inserir(int x, no *p){
	//cria o novo no
    no *novo;
    //coloca o tamanho do no
    novo = malloc(sizeof(no));
    //coloca o conteudo dentro do novo no
    novo->conteudo = x;
    //no vai receber o que ta no proximo que é o nulo
    novo->prox = p->prox;
    //esse cara (le->prox = NULL;) que está em main não é mais null ele vai receber o novo entao
    //agora ele vai receber o enderço desse novo no
    p->prox = novo;
}
//recebe a lista inteira como parametro
void excluir(no *p){
	//vamos chamar o no que sera excluido de lixo
    no *lixo;
    //ele vai receber  o proximo que é nulo
    lixo = p->prox;
    //o proximo vai receber o endereco que esta em lixo para nao perder a linealidade
    p->prox = lixo->prox;
    //elimina ele da memoria
    free(lixo);
}

busca(int x, no *le){
	no *p = le;
	int achou = 0;
	while(p!=NULL && !achou){
		if (p->conteudo==x)
		achou =1;
		p = p->prox;
	}
	if (achou)
	return 1;
	else
	return NULL;
}

void imprimir(no *le){
	no *p;
	for(p=le; p !=NULL;p=p->prox)
	printf("%d\n",p->conteudo);
}

int main (void) {
    int valor = 10;
    no *le;
    le = malloc (sizeof (no));
    le->prox = NULL;

    printf ("Tamanho do nó = %d\n", sizeof (le));

    for (int i = 1; i <= 10; i++){
        inserir(valor*i, le);
    }
    imprimir(le);
    excluir (le);
    imprimir (le);
    printf("%d\n",busca (10, le));

    return 1;
}
