//{ 
#include <stdio.h>
#include <stdbool.h> //true/false
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>
/*Defines*/
#define INPS 12
#define IUR  20 
#define sindicato 1
#define pause system("pause")
#define CALCULARSALARIO true
#define beep putchar(7)


/*structs*/
typedef struct Dados{
    char nome[20];
    char NIF[20];
    char categoria[20];
    int salario;
    int Hora_Trabalhados;
}Dados;

/*Prototipos*/
int menu();
void eliminar();
void copiar( Dados * a, Dados * b );
void swap(Dados * a, Dados * b);
void imprimeDados(Dados d);
void ordenarRegistros(Dados **lista, int * ptr_nFuncionarios);
int calcularCusto ( Dados **lista, int * ptr_nFuncionarios, char * categoria );
void custoCategoria(Dados **lista, int * ptr_nFuncionarios);
void imprimirSalariosAcimaDe( Dados **lista, int * ptr_nFuncionarios, int minimo );
void limparTela(){ system("cls"); }
void gerarArquivoProva();
int calcularSalario( int nHoras, int valorHora );
void inserirFuncionarios(Dados ** lista, int *ptr_nFuncionarios);
int cargarFuncionarios( Dados **lista, int * ptr_nFuncionarios, bool liberarLista );
void imprimirRegistros(Dados **lista, int * ptr_nFuncionarios, int minimo );
void imprimirLista(Dados **lista, int * ptr_nFuncionarios, int minimo); 
void mostrar ( Dados **lista, int * ptr_nFuncionarios, char * categoria );
void imprimirCategoria(Dados **lista, int * ptr_nFuncionarios);
/*Funçoes*/

//} 

void mostrarSalario(){
    /*Se CALCULARSALARIO estiver definido como verdadero se calcula o salario automaticamente 
    antes de enviar para o arquivo de testes. Caso contrario se pedirá que insira a mão o salario */
    limparTela();
    
    char categoria[100];
    printf("Indique qual é o categiria do funcionario: ");
    scanf("%s%*c", categoria);
    
    limparTela();
    
    if ( CALCULARSALARIO == true ) {
        int valorHora = 0;
        char str[20] = {0};

        for ( int i = 0; str[i]; i++ ) {
            categoria[i] = tolower ( categoria[i] );       /*Todas as letras da string categoria passam a ser minusculas*/
        }
        
        /*Valor que cobra o funcionario dependendo da sua categoria*/
        if ( strcmp ( categoria, "diretor" ) == 0 ) {
            valorHora = 3500;
        } else if ( strcmp ( categoria, "docente" ) == 0 ) {
            valorHora = 2500;
        } else if ( strcmp ( categoria, "tecnico" ) == 0 ) {
            valorHora = 1500;
        } else {
            /*Se a categoria é incorreta voltamos ao menu principal(main)*/
            limparTela();
            printf ( "Não existe essa categoria!\n" );
            pause;
            return;
        }
        
        /*calculamos o salario do funcionario*/
        printf("O salario do funcionario é: %.1f",  (float)calcularSalario ( 8, valorHora ));
        getchar();
        
    }
    
}

int main(){
    setlocale(LC_ALL, "portuguese");
    Dados* lista = NULL;
    int nFuncionarios = 0;
    int sair = false;

    
    while ( sair != true ) { //Por enquanto não queremos sair....
        
        switch ( menu() ) {
            case 1:  inserirFuncionarios( &lista, &nFuncionarios);        break;
            case 2:  imprimirRegistros  ( &lista, &nFuncionarios, 0);     break;
            case 3:  imprimirCategoria  ( &lista, &nFuncionarios);        break;
            case 4:  custoCategoria     ( &lista, &nFuncionarios);        break;
            case 5:  mostrarSalario     ();                               break;
            case 6:  ordenarRegistros   ( &lista, &nFuncionarios);        break;
            case 7:  imprimirRegistros  ( &lista, &nFuncionarios, 75000); break;
            case 8:  eliminar();                                          break;
            case -1: gerarArquivoProva ();                                break;            
            case 0: sair = true;                                          break;
            default:                                                      break;
        }
    }
    free(lista);
    return 0;
}//MAIN


int menu() {
    int op = 0;
    system("cls");
    system ( "COLOR 0F" ); //Menu
    printf ( "\n\n\t\t\t\t---> SISTEMA DE REGISTO E CONTROLE DE FUNCIONÁRIO \n\n" );
    printf ( "\n\t\t* 1 ------- INSERIR OS FUNCIONÁRIOS E ENVIA-LOS PARA O FICHEIRO ------------------------ *\n" );
    printf ( "\n\t\t* 2 ------- IMPRIMIR A LISTA DOS FUNCIONÁRIOS DO FICHEIRO ------------------------------ *\n" );
    printf ( "\n\t\t* 3 ------- IMPRIMIR OS FUNCIONÁRIOS POR CATEGORIA ------------------------------------- *\n" );
    printf ( "\n\t\t* 4 ------- GASTO DA UNIVERSIDADE COM OS FUNCIONÁRIOS ---------------------------------- *\n" );
    printf ( "\n\t\t* 5 ------- CALCULAR O SALÁRIO DE UM FUNCIONÁRIO X EM FUNÇÃO DO SEU SALÁRIO POR HORA --- *\n" );
    printf ( "\n\t\t* 6 ------- ORDENAR FUNCIONÁRIO NA ORDEM CRESCENTE ------------------------------------- *\n" );
    printf ( "\n\t\t* 7 ------- IMPRIMIR OS FUNCIONÁRIOS COM SALÁRIO MAIOR QUE 75000$ ---------------------- *\n" );
    printf ( "\n\t\t* 8 ------- ELIMINAR UM FUNCIONÁRIO A PARTIR DO Nº DO NIF ------------------------------ *\n" );
    printf ( "\n\t\t* 0 ------- Sair\n\n" );
    printf ( "\n\tEscolha uma opcao: " );
    scanf ( "%d%*c", &op );
    return op;
}


/*Função que gera um arquivo de funcionarios.txt para realizar testes automaticamente*/
void gerarArquivoProva() {
    limparTela();
    int i;
    
    /*Criando arquivo de teste e comprovando erros*/
    FILE * file = fopen ( "funcionarios.txt", "w" );
    if ( file == NULL ) {
        perror ( "Não gerou o arquivo de teste" );
        getchar();
        return;
    
    } else { /*Se não teve erros ao gerar o arquivo procedemos a enviar os dados dos funcionarios ao arquivo*/
        
        /*Lista de funcionarios que serão guardados no arquivo de teste*/
        Dados d[10] = {
            { "Saul", "123332002", "Docente", 0, 8 },
            { "Loli", "123332010", "Tecnico", 0, 1 },
            { "Suzi", "123332007", "Tecnico", 0, 1 },
            { "Fred", "123332001", "Docente", 0, 8 },
            { "Juli", "123332003", "Docente", 0, 8 },
            { "Rosi", "123332006", "Docente", 0, 8 },
            { "Jose", "123332004", "Docente", 0, 8 },
            { "Raul", "123332005", "Diretor", 0, 6 },
            { "Beto", "123332009", "Docente", 0, 8 },
            { "Jaco", "123332008", "Tecnico", 0, 4 }
        };
        
        /*Gerando arquivo de testes*/
        for ( i = 0; i < 10; i++ ){ /*Para cada funcionario da lista de testes...*/
            
            /*Se CALCULARSALARIO estiver definido como verdadero se calcula o salario automaticamente antes de enviar para o arquivo de testes.*/
            if(CALCULARSALARIO == true){
                int valorHora = 0;
                char str[20]={0};
                
                
                strcpy( str, d[i].categoria );    /*Copiamos a categoria do funcionario para a string str, para processa-la(convertir em minusculas)*/
                
                for ( int i = 0; str[i]; i++ ) { /*Todas as letras da string str passam a ser minusculas*/
                    str[i] = tolower ( str[i] );
                }
                
                /*Valor que cobra o funcionario dependendo da sua categoria*/
                if ( strcmp( str, "diretor" ) == 0 ){
                    valorHora = 3500;
                }else if (strcmp( str, "docente" ) == 0 ){
                    valorHora = 2500;
                }else if ( strcmp( str, "tecnico" ) == 0 ){
                    valorHora = 1500;
                }else{
                    /*Se a categoria é incorreta voltamos ao menu principal(main)*/
                    limparTela();
                    printf("Não existe essa categoria!\n");
                    fclose(file);
                    file = NULL;
                    pause;
                    return;
                }
    
                /*calculamos o salario do funcionario*/
                d[i].salario = calcularSalario( d[i].Hora_Trabalhados  , valorHora );

            }
            /*Enviamos dados do funcionario ao arquivo de testes*/
            fprintf ( file, "%s %s %s %d %d\n", d[i].nome, d[i].NIF, d[i].categoria, d[i].salario, d[i].Hora_Trabalhados );
        }
        
        fclose ( file );
        printf ( "Arquivo gerado\n\n" );
        getchar();
    }
}

/*Função que calcula o salario em base ao numero de horas multiplicado por 30. Logo se aplica imporstos*/
int calcularSalario( int nHoras, int valorHora ){
    int salarioLiquido = (nHoras * valorHora) * 30;                    /*Salario sem aplicar impostos*/
    int impostos       = (INPS+IUR+sindicato) * salarioLiquido / 100; /*calculando o 33% do salarioLiquido(33% == INPS+IUR+sindicato)*/
    int salario        = salarioLiquido - impostos;                  /*Obtemos salario*/
    return salario;    
}

/*Função que imprime a lista de funcionarios que recebe por parâmetros*/
void imprimirLista(Dados **lista, int * ptr_nFuncionarios, int minimo){
    int i;
    for ( i=0; i < *ptr_nFuncionarios; i++) {
        if ( (*lista)[i].salario >= minimo ){
        // para obter dados e armazenar no arquivo
            printf ( "Funcionário: %s\n\n"               , (*lista)[i].nome            );
            printf ( "NIF.........................: %s\n", (*lista)[i].NIF             );
            printf ( "Categoria...................: %s\n", (*lista)[i].categoria       );
            printf ( "Salario.....................: %d\n", (*lista)[i].salario         );
            printf ( "Numero de horas trabalhados.: %d\n", (*lista)[i].Hora_Trabalhados);
            printf ("###########################################\n");
        }
    }    
}


/* Função que carrega os funcionarios do arquivo para a lista dinâmica*/
int cargarFuncionarios( Dados **lista, int * ptr_nFuncionarios, bool liberarLista ){
    int i;
    *ptr_nFuncionarios = 0;
    char c;
    
    /*abrimos arquivo em modo leitura e comprovamos erros*/
    FILE * file = fopen ( "funcionarios.txt", "r" );
    if ( file == NULL ) {
        //Se o arquivo n abriu
        perror ( "Erro ao tentar abrir funcionarios.txt" );
        pause;
        return 0;
    }
    
    
    /*Contamos o numero de funcionarios no arquivo funcionarios txt(Contador de linhas)*/
        while ( fscanf(file,"%c", &c) != EOF ){ 
            fscanf(file,"%*[^\n]%*c");
        if( c != ' ' ){
            (*ptr_nFuncionarios)++;  
        }
    }


    /* Reserva memoria para a lista e lê o arquivo. 
        Reserva conforme o numero de usuarios contados no arquivo. Se não existe o arquivo, ou n 
        tem funcionarios nele, não reserva, volta para o menu.
    */
    if( *ptr_nFuncionarios > 0 ){
        *lista = malloc( sizeof(Dados) * *ptr_nFuncionarios );
        /*lê o arquivo se não tem erros*/
        if( *lista != NULL && file != NULL ){ 
            rewind(file);
            /*Cargamos os usuarios do arquivo na lista*/
            for ( i=0; i < *ptr_nFuncionarios; i++) {
                fscanf ( file, "%s %s %s %d %d", (*lista)[i].nome, (*lista)[i].NIF, (*lista)[i].categoria, &(*lista)[i].salario, &(*lista)[i].Hora_Trabalhados );    
            }
        }
        
    
    }else 
        return 0;
    
    /*liberamos recursos...
        Só libera a lista se liberarLista == true. Pode que tenha que processa-la depois(Pode se 
        dar o caso de precisar processar lista fora da função, no qual não se deve liberar a lista 
        antes de sair).
    */
    if ( liberarLista == true ) {  
        if ( *lista != NULL ) {
            free ( *lista );
            *lista = NULL;
        }
    }
    
    /*Fechamos o arquivo*/
    if ( file   != NULL ) { fclose ( file );  file  = NULL; }

    return *ptr_nFuncionarios;
    
}

/*Função que carrega os funcionarios do arquivo para a lista e imprime a lista*/
void imprimirRegistros ( Dados **lista, int * ptr_nFuncionarios, int minimo ) {
    /*carga/mos o/s funcionario/s na lista se tiver 1 ou mais funcionario/s no arquivo*/
    int n = cargarFuncionarios ( &*lista, &*ptr_nFuncionarios, false );
    if (  n > 0 ) { /*Se tiver um ou mais funcionario no arquivo entramos no if, e imprimimos.*/
        
        /*Imprimimos a lista*/
        limparTela();
        imprimirLista ( &(*lista),  & (*ptr_nFuncionarios), minimo );
        
        /*Liberando recursos*/
        if ( *lista != NULL ) {
            free ( *lista );
            *lista = NULL;
        }
        
    }else{
        /*Se entramos aqui pode não haver funcionarios no arquivo.*/
        puts("Não encontrou funcionarios no arquivo para listar");
    }
    
    pause; /*pausamos para poder ver o resultado*/    
}

/*Função que mostra somente os dados por categoria recebida por parâmetros de uma lista dinâmica*/
void mostrar ( Dados **lista, int * ptr_nFuncionarios, char * categoria ) {
    int i, z;
    char str[20];
    for ( i = 0; i < *ptr_nFuncionarios; i++ ) {
        
        /*Passa a categoria a letras minusculas*/
        strcpy ( str, ( *lista ) [i].categoria );
        for ( z = 0; str[z]; z++ ) {
            str[z] = tolower( (*lista)[i].categoria[z] );
        }
        
        /*Imprime só quem tiver a categoria indicada nos parâmetros da função*/
        if ( strcmp ( str, categoria ) == 0 ) {
            printf ( "Funcionário: %s\n\n", ( *lista ) [i].nome );
            printf ( "NIF.........................: %s\n", ( *lista ) [i].NIF );
            printf ( "Categoria...................: %s\n", ( *lista ) [i].categoria );
            printf ( "Salario.....................: %d\n", ( *lista ) [i].salario );
            printf ( "Numero de horas trabalhados.: %d\n", ( *lista ) [i].Hora_Trabalhados );
            printf ( "###########################################\n" );
        }
    }
}

/*Função que carga os funcionarios do arquivo para a lista dinâmica e passa a lista para a função "mostrar", 
  para que imprima os funcionarios por categoria
*/
void imprimirCategoria(Dados **lista, int * ptr_nFuncionarios){
    /*carga/mos o/s funcionario/s na lista se tiver pelo menos um, ou mais funcionario/s no arquivo*/
    int n = cargarFuncionarios ( &*lista, &*ptr_nFuncionarios, false );
    if (  n > 0 ) { 
        limparTela();
        
        //Imprimimos a lista por categoria:
        puts("\n***Diretor***\n");
        mostrar( &*lista, &*ptr_nFuncionarios, "diretor");/*imprime funcionarios pela categoria de Diretor*/
        puts("\n***Docente***\n");
        mostrar( &*lista, &*ptr_nFuncionarios, "docente");/*imprime funcionarios pela categoria de Docente*/
        puts("\n***Tecnico***\n");
        mostrar( &*lista, &*ptr_nFuncionarios, "tecnico");/*imprime funcionarios pela categoria de tecnico*/
        
        
        /*Liberando recrusos*/
        if ( *lista != NULL ) {
            free ( *lista );
            *lista = NULL;
        }
        
    }else{
        /*Se entramos aqui pode não haver funcionarios no arquivo.*/
        puts("Não encontrou usuarios no arquivo");
    }
    
    pause; /*pausamos para poder ver o resultado*/  
}

/*copia a em b*/
void copiar( Dados * a, Dados * b ){
    /*Copia dados da struct a para a struct b um a um*/
    strcpy (  b->nome     , a->nome     );
    strcpy (  b->NIF      , a->NIF      );
    strcpy (  b->categoria, a->categoria);
    b->salario            = a->salario;
    b->Hora_Trabalhados   = a->Hora_Trabalhados;
}

/*intercambia valores entre a e b*/
void swap(Dados * a, Dados * b){
    Dados aux;
    copiar( a, &aux);   /*copia a em aux*/
    copiar( b, a  );   /*copia b em a*/
    copiar( &aux, b); /*copia aux em b*/
}

/*Imprime uma struct Dados que receber por parametros*/
void imprimeDados(Dados d){
    printf ( "Funcionário: %s\n\n"               , d.nome            );
    printf ( "NIF.........................: %s\n", d.NIF             );
    printf ( "Categoria...................: %s\n", d.categoria       );
    printf ( "Salario.....................: %d\n", d.salario         );
    printf ( "Numero de horas trabalhados.: %d\n", d.Hora_Trabalhados);
    printf ("###########################################\n");
}

/*Elimina um funcionario do arquivo indicando o nif*/
void eliminar(){
    Dados d = {0};
    long lugar;
    char nif[20]="none";
    char linha[1024]; 
    bool sair = false;
    
    
    /*abrimos arquivo e comprovamos erros*/
    FILE * file = fopen ( "funcionarios.txt", "r+" );
    if ( file == NULL ) {
        /*Se o arquivo n abriu*/
        perror ( "Erro ao tentar abrir funcionarios.txt" );
        pause;
        return;
    }
    
    /*Pedimos o nif para pesquisar*/
    limparTela();
    printf("Informe nif que deseja pesquisar: ");
    scanf("%s", nif);
    
    
    /*Anotamos o inicio de cada linha antes de ler a linha, porque depois de ler avançamos até a seguinte linha*/
    lugar = ftell ( file );
    while ( fscanf ( file, "%s %s %s %d %d%*c", d.nome, d.NIF, d.categoria, &d.salario, &d.Hora_Trabalhados ) != EOF && sair != true ) {
        
        /*
            Se a primeira letra do nome é diferente de um espaço, isso quer dizer que tem dados 
            nesta linha(não é um funcionario eliminado) e podemos ler. caso contrario saltamos para a seguinte linha com else, e 
            voltamos a comprovar se tem um espaço na primeira letra do nome.... 
        */
        if ( d.nome[0] != ' ' ) {
            
            /*se o nif recebido por parametros concorda com o do funcionario lido entramos ao if.*/
            if ( strcmp ( d.NIF, nif ) == 0 ) {
                int opt = 0;
                
                /*Perguntamos o que fazer com esse registro do funcionario*/
                limparTela();
                printf ( "Encontrado! Que deseja fazer?\n1-Eliminar do arquivo\n0-Voltar ao menu principal.\n Escolha uma opção: " );
                scanf ( "%d%*c", &opt );
                
                switch ( opt ) {
                    case 1:/*Eliminar registro de funcionario no arquivo*/
                    
                        limparTela();
                        
                        fseek ( file, lugar, SEEK_SET );
                        fscanf ( file, "%[^\n]", linha );
                        
                        
                        fseek ( file, lugar, SEEK_SET );
                        fprintf ( file, "%*s", ( int ) strlen ( linha ), "" );
                        
                        fclose ( file );
                        sair = true;
                        printf ( "Funcionario com NIF \"%s\" eliminado corretamente. ", d.NIF );
                        pause;
                        break;
                        
                    case 0:/*Volta para o menu(cae no default porque não tem break)*/
                    default:
                        /*Liberando e saindo da função*/
                        fclose ( file );
                        file = NULL;
                        limparTela();
                        return;
                }
                
            }
        }else{
            /*Se a primeira letra do nome é um espaço terminamos de ler a linha do arquivo ignorando todos os espaços(passamos a seguinte linha)*/
            fscanf(file, "%*[^\n]%*c");
        }
        
        /*Anotamos o a linha onde estamos antes de voltar a ler um registro do arquivo*/
        lugar = ftell ( file );
        
        
    }
    


    

}


/*Função que ordena o funcionarios.txt por salario de maior a menor e joga esses dados a outro arquivo chamado ordenar_funcionarios.txt*/
void ordenarRegistros(Dados **lista, int * ptr_nFuncionarios){
    *ptr_nFuncionarios = 0;
    int i , z;    
    
    /*Abrimos o arquivo em modo leitura e verificamos erros*/
    FILE * file = fopen ( "funcionarios.txt", "r" );
    if ( file == NULL ) {/*Se o arquivo n abriu*/
        perror ( "Erro ao tentar abrir funcionarios.txt" );
        printf("Não foi possivel ordenar o arquivo de funcionarios.\n");
        pause;
        return;
    }

    
    /*Cargamos os funcionarios na lista*/
    cargarFuncionarios(&*lista, &*ptr_nFuncionarios, false);

    /*Ordenando a lista*/
    for ( i=0; i <  ((*ptr_nFuncionarios) - 1); i++) {
        for( z=(i+1); z < *ptr_nFuncionarios; z++){
            //if ( strcmp( (*lista)[i].nome, (*lista)[z].nome ) > 0 ){ //Ordena por nome
           if ( (*lista)[i].salario < (*lista)[z].salario ){        
                swap( &(*lista)[z], &(*lista)[i]);
            }
        }
    }
    
    
    /*Fechamos o ponteiro para reaproveita-lo*/
    if ( file   != NULL ) { fclose ( file );  file  = NULL; }
    
    /*Reabrimos em modo escritura*/
    file = fopen ( "ordenar_funcionarios.txt", "w" );
    if ( file == NULL ) { 
        perror ( "Erro ao tentar criar ordenar_funcionarios.txt" );
        printf("Não foi possivel salvar a lista no arquivo ordenar_funcionarios.txt.\n");
        if ( *lista != NULL ) { free ( *lista ); *lista = NULL; }
        if ( file   != NULL ) { fclose ( file );  file  = NULL; beep;beep;}
        pause;
        return;
    }

    
    /*Salvando a lista no arquivo ordenado*/
    for ( i = 0; i < *ptr_nFuncionarios; i++ ){
        fprintf ( file, "%s %s %s %d %d\n", (*lista)[i].nome, (*lista)[i].NIF, (*lista)[i].categoria, (*lista)[i].salario, (*lista)[i].Hora_Trabalhados );

    }
    
    
    /*Liberando recursos*/
    if ( *lista != NULL ) { free ( *lista ); *lista = NULL; }
    if ( file   != NULL ) { fclose ( file );  file  = NULL; }
}

/*Função que calcula a soma de salarios dos funcionarios de uma determinada categoria*/
int calcularCusto ( Dados **lista, int * ptr_nFuncionarios, char * categoria ) {
    int i, z;
    int somatoria = 0;
    char str[20];
    
    /*Soma todos os salarios dos funcionarios da lista quetenham a mesma categoria e retorna a somatoria*/
    for ( i = 0; i < *ptr_nFuncionarios; i++ ) {
        
        /*Pasa a minuscula a categoria*/
        strcpy ( str, ( *lista ) [i].categoria );
        for ( z = 0; str[z]; z++ ) {
            str[z] = tolower( (*lista)[i].categoria[z] );
        }
        
        /*somando salarios da mesma categoria*/
        if ( strcmp ( str, categoria ) == 0 ) {
            somatoria += (*lista)[i].salario;
        }
    }
    
    return somatoria;
  
}


/*Calcular quanto gasta a universidade com os funcionários por categoria*/
void custoCategoria(Dados **lista, int * ptr_nFuncionarios){
    //carga/mos o/s funcionario/s na lista se tiver 1 ou mais funcionario/s no arquivo
    int n = cargarFuncionarios ( &*lista, &*ptr_nFuncionarios, false );
    if (  n > 0 ) { //Se tiver mais de zero funcionario no arquivo entramos no if e imprimimos.
        limparTela();
        
        /*Imprime salarios de todos funcionarios somados da lista por categoria.*/
        printf ("Custo por salarios de diretores: %d\n", calcularCusto( &*lista, &*ptr_nFuncionarios, "diretor") );
        printf ("Custo por salarios de docentes : %d\n", calcularCusto( &*lista, &*ptr_nFuncionarios, "docente") );
        printf ("Custo por salarios de tecnicos : %d\n", calcularCusto( &*lista, &*ptr_nFuncionarios, "tecnico") );
        
        /*Liberando recrusos*/
        if ( *lista != NULL ) {
            free ( *lista );
            *lista = NULL;
        }
        
    }else{
        /*Se entramos aqui pode não haver funcionarios no arquivo.*/
        puts("Não encontrou usuarios no arquivo");
    }
    
    if(*lista != NULL){ free(*lista); *lista = NULL; }
    pause; /*pausamos para poder ver o resultado*/ 
}

/*Imprime todos os funcionários com salario maior que int minimo*/
void imprimirSalariosAcimaDe( Dados **lista, int * ptr_nFuncionarios, int minimo ){
    imprimirRegistros(&*lista,&*ptr_nFuncionarios, minimo);
}

/*Funcion que gera o arquivo funcionarios.txt e pede os dados de todos os funcionarios*/
void inserirFuncionarios(Dados ** lista, int *ptr_nFuncionarios){
    int i;

    /*Pedir numero de funcionarios que serão inseridos*/
    limparTela();
    printf("\n\n\n\t\tDigite o numero de Funcionarios que pretende registrar: ");
    scanf ( "%d%*c", &*ptr_nFuncionarios );
    
    /*Reserva de memoria para inserir os funcionarios*/
    *lista = malloc(  sizeof(Dados) * (*ptr_nFuncionarios) );
    
    /*Pedindo dados dos funcionarios é guardamos em uma lista dinâmica.*/
    system ( "COLOR 0B" );
    limparTela();
    for ( int i=0; i<*ptr_nFuncionarios; i++) {
        printf("Registro número %d/%d\n", i+1, *ptr_nFuncionarios);
        printf ( "Nome..............:" ); scanf ( "%s%*c",  (*lista)[i].nome             );
        printf ( "NIF...............:" ); scanf ( "%s%*c",  (*lista)[i].NIF              );
        printf ( "Categoria.........:" ); scanf ( "%s%*c",  (*lista)[i].categoria        );
        printf ( "Horas trabalhadas.:" ); scanf ( "%d%*c", &(*lista)[i].Hora_Trabalhados );
        
        /*Se CALCULARSALARIO estiver definido como verdadero se calcula o salario automaticamente 
        antes de enviar para o arquivo de testes. Caso contrario se pedirá que insira a mão o salario*/
        if(CALCULARSALARIO == true){
            int valorHora = 0;
            char str[20]={0};
            
            strcpy( str, (*lista)[i].categoria );   /*Copiamos a categoria do funcionario para a string str, para processa-la(convertir em minusculas)*/
            for ( int i = 0; str[i]; i++ ) {       
                str[i] = tolower ( str[i] );       /*Todas as letras da string str passam a ser minusculas*/
            }
            
            /*Valor que cobra o funcionario dependendo da sua categoria*/
            if ( strcmp( str, "diretor" ) == 0 ){
                valorHora = 3500;
            }else if (strcmp( str, "docente" ) == 0 ){
                valorHora = 2500;
            }else if ( strcmp( str, "tecnico" ) == 0 ){
                valorHora = 1500;
            }else{
                /*Se a categoria é incorreta voltamos ao menu principal(main)*/
                limparTela();
                printf("Não existe essa categoria!\n");
                printf("Liberando memoria...\n");
                free(*lista);
                *lista = NULL;
                pause;
                return;
            }
            
            /*calculamos o salario do funcionario*/
            printf("valor da hora a %d\n", valorHora);
            (*lista)[i].salario = calcularSalario( (*lista)[i].Hora_Trabalhados  , valorHora );
            pause;
            
        }else{
            
            /*Se CALCULARSALARIO estiver definido como falso o salario se pedi manualmente para cada funcionario antes de inserir os dados no arquivo*/
            printf ( "Salario...........:" ); scanf ( "%d%*c", &(*lista)[i].salario );
        }
        
        limparTela();
    }
    
    /*Guardando lista de dados dos funcionarios no arquivo funcionarios.txt*/
    FILE * file = fopen ( "funcionarios.txt", "w" );
    if ( file == NULL || *lista == NULL ) { /*Se a lista com os dados não foi criada ou o arquivo funcionarios.txt não abriu abortamos*/
        /*Se o arquivo não abriu liberamos e voltamos ao menu*/
        if( *lista != NULL ){ free(*lista); *lista = NULL; }
        perror ( "Não gerou o arquivo funcionarios.txt" );
        getchar();
        return;
    }else{
        //Se abriu o arquivo salvamos os dados
        for ( i = 0; i < *ptr_nFuncionarios; i++ )
            fprintf ( file, "%s %s %s %d %d\n", (*lista)[i].nome, (*lista)[i].NIF, (*lista)[i].categoria, (*lista)[i].salario, (*lista)[i].Hora_Trabalhados );
        
        fclose(file);
        if( *lista != NULL  ){
            free(*lista);
            *lista = NULL;
        }
    }
    
}













