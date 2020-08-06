#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct Agencia{
    char Nome[100];
    char Endereco[100];
    char Telefone[100];
    char Hr_atendimento[100];
    double Lat;
    double Log;
};
void troca(struct Agencia *a, struct Agencia *b){
    struct Agencia aux;
    aux = *a;
    *a = *b;
    *b = aux;
}
int main(){
    setlocale(LC_CTYPE, "Portuguese");
    int contador = 0, i= 0,z=0;
    struct Agencia *lista;
    FILE *arq;
    arq = fopen("correios.csv", "r");
    if( arq == NULL ){
        perror("Erro ao abrir correios.csv");
        getchar();
        exit(-1);
    }
    while( fscanf(arq, " %*[^\n]") != EOF)
        contador++;
    lista = (struct Agencia*)malloc(contador * (sizeof( *lista)));

    rewind(arq);
    char descartaprimeiralinha[300];
     fscanf(arq,"%[^\n]\n",descartaprimeiralinha);
     contador--;
    for(i=0; i<contador; i++)
        fscanf(arq, " %[^;];%[^;];%[^;];%[^;];%lf;%lf;%*[^\n]\n",lista[i].Nome, lista[i].Endereco,lista[i].Telefone,lista[i].Hr_atendimento,&lista[i].Lat,&lista[i].Log);


        for (i = 0; i < contador-1; i++){
              for (z = i+1; z < contador; z++){
                    if (strcmp(lista[i].Nome, lista[z].Nome) >  0){
                    	 troca(&lista[i], &lista[z]);
 }}}

    for(i=0; i<contador; i++)
   printf("Nome:%s\nEndereco:%s\nTelefone:%s\nHorario de Atendimento:%s\nLatitude:%lf\nLongitude:%lf\n \n",lista[i].Nome, lista[i].Endereco,lista[i].Telefone,lista[i].Hr_atendimento,lista[i].Lat,lista[i].Log);
	fclose(arq);
    free(lista);

    getchar();
    return 0;
}


