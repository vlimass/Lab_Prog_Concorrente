#include<stdio.h>
#include<stdlib.h>

// valor máximo de um elemento do vetor
#define MAX 1000


// Função para mostrar log do vetor
void imprimeVetor(int vet[], int tam){
    for(int i = 0; i < tam; i++){
        printf(" %d ", vet[i]); 
    }
    printf("\n");
}


// Fluxo principal
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
    for(long int i=0; i<tam; i++) {
        *(vetor+i) = i+1;
    }

    //imprimir na saida padrao o vetor gerado (descomentar se desejar visualizar!)
    imprimeVetor(vetor, tam);

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