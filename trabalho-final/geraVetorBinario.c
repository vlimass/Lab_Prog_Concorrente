#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// valor máximo de um elemento do vetor
#define MAX 1000000000

//descomentar o define abaixo caso deseje imprimir uma versao truncada da matriz gerada no formato texto
#define TEXTO 1

int main(int argc, char*argv[]) {
    int *vetor; // vetor que será gerado
    long long int tam; //qtde de elementos do vetor
    FILE * descritorArquivo; //descritor do arquivo de saida
    size_t ret; //retorno da funcao de escrita no arquivo de saida

    //recebe os argumentos de entrada
    if(argc < 3) {
        fprintf(stderr, "Digite: %s <tamanho> <arquivo saida>\n", argv[0]);
        return 1;
    }

    tam = atoi(argv[1]); 

    //aloca memoria para o vetor
    vetor = (int*) malloc(sizeof(int) * tam);
    if(!vetor) {
        fprintf(stderr, "Erro de alocao da memoria do vetor\n");
        return 2;
    }

    //preenche o vetor com valores inteiros aleatorios
    //randomiza a sequencia de numeros aleatorios
    srand(time(NULL));
    for(long int i=0; i<tam; i++) {
        *(vetor+i) = rand() % MAX;
    }

    //imprimir na saida padrao o vetor gerado
    #ifdef TEXTO
    for(int i=0; i<tam; i++) {
        fprintf(stdout, " %d ", vetor[i]);
    }
    fprintf(stdout, "\n");
    #endif

    //escreve o vetor no arquivo
    //abre o arquivo para escrita binaria
    descritorArquivo = fopen(argv[2], "wb");
    if(!descritorArquivo) {
        fprintf(stderr, "Erro de abertura do arquivo\n");
        return 3;
    }

    //escreve o tamanho do vetor
    ret = fwrite(&tam, sizeof(long long int), 1, descritorArquivo);
    //escreve os elementos do vetor
    ret = fwrite(vetor, sizeof(float), tam, descritorArquivo);
    if(ret < tam) {
        fprintf(stderr, "Erro de escrita no  arquivo\n");
        return 4;
    }

    //finaliza o uso das variaveis
    fclose(descritorArquivo);
    free(vetor);
    return 0;
}