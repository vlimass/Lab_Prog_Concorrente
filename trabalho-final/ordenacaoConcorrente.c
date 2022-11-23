#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "timer.h"

int * vetor;
int numThreads; // número de threads
long long int tam; // tamanho do vetor 
int aux = 1; // variável auxiliar para verificar subdivisão do vetor no merge


// função para impressão do vetor 
void imprimeVetor(int vet[], int tam){
    for(int i = 0; i < tam; i++){
        printf(" %d ", vet[i]); 
    }
    printf("\n");
}


// parte do merge sort 
void merge(int vet[], int inicio, int meio, int fim){
    //criando um vetor auxiliar e copiando o vetor original
    int *tmp;
    tmp = (int*)malloc(sizeof(int) * (fim - inicio));

    int i = inicio;
    int j = meio;
    int pos = 0;

    while(i < meio && j < fim){
        if(vet[i] <= vet[j]){
            tmp[pos++] = vet[i++];
        } else{
            tmp[pos++] = vet[j++];
        }
    }

    while(i < meio){
        tmp[pos++] = vet[i++];
    }

    while(j < fim){
        tmp[pos++] = vet[j++];
    }

    for(i = inicio; i < fim; i++){
        vet[i] = tmp[i - inicio];
    }

    free(tmp);
}

// algoritmo merge sort 
void mergeSort(int vet[], int inicio, int meio, int fim){
    // if(inicio < (fim - 1)){
    //     int meio = (inicio + fim)/ 2; 
    //     mergeSort(vet, inicio, meio);
    //     mergeSort(vet, meio, fim);
    //     merge(vet, inicio, meio, fim);
    // }
    imprimeVetor(vet, tam);

    if(fim <= tam){ 
        merge(vet, inicio, meio, fim);
        mergeSort(vet, inicio, fim, fim + tam/numThreads);
    }

}

// function to swap elements
void troca(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}


// parte do quick sort
int particiona(int vet[], int inicio, int fim){
    //pivot randomico
    int p = inicio + rand()%(fim - inicio + 1);
    troca(&vet[inicio], &vet[p]);
    
    int pivot = vet[inicio];
    int i = inicio;
    int j = fim ;
    
    while(i < j){
        while(i < fim && vet[i] <= pivot){
            i++;
        }
        while(j > inicio && vet[j] >= pivot){
            j--;
        }
        if(i < j){
            troca(&vet[i], &vet[j]);
        }
    }
    vet[inicio] = vet[j];
    vet[j] = pivot;

    return j; 
}

// algoritmo quick sort 
void quick_sort(int vet[], int inicio, int fim){
    if(inicio < fim){
        int pivot = particiona(vet, inicio, fim);
        quick_sort(vet, inicio, pivot - 1);
        quick_sort(vet, pivot + 1, fim);
    }
}


// fluxo das threads
void * ordena (void * arg) {
    int id = *(int *) arg;
    // printf("thread: %d\n", id);
    int inicio = (tam / numThreads) * (id-1);
    int fim = (tam / numThreads) * id;

    quick_sort(vetor, inicio, fim-1);
    
    // imprimeVetor(vetor, tam);

    // free(arg);
    pthread_exit(NULL);
}


// fluxo principal
int main (int argc, char * argv[]) { 
    FILE * descritorArquivoEntrada, * descritorArquivoSaida; //descritores dos arquivos
    size_t retEntrada, retSaida; //retorno da funcao de leitura nos arquivos 
    double inicio, fim, delta; // gerenciadores de tempo 

    // pthread_t *tid; // identificadores das threads 

    // -- INICIALIZAÇÃO -- //

    //recebe os argumentos de entrada
    if(argc < 4) {
        fprintf(stderr, "Digite: %s <arquivo vetor entrada> <arquivo vetor saida> <numero threads>\n", argv[0]);
        return 1;
    }

    // recebe o número de threads
    numThreads = atoi(argv[3]);
    //printf("%d\n", numThreads);

    //abre o arquivo para leitura binaria do vetor de entrada
    descritorArquivoEntrada = fopen(argv[1], "rb");
    if(!descritorArquivoEntrada) {
        fprintf(stderr, "Erro de abertura do arquivo\n");
        return 2;
    }

    //le o tamanho do vetor de entrada
    retEntrada = fread(&tam, sizeof(long long int), 1, descritorArquivoEntrada);
    if(!retEntrada) {
        fprintf(stderr, "Erro de leitura do tamanho do vetor de entrada\n");
        return 2;
    }

    //aloca memoria para o vetor
    vetor = (int*) malloc(sizeof(int) * tam);
    if(!vetor) {
        fprintf(stderr, "Erro de alocao da memoria do vetor de entrada\n");
        return 2;
    }

    // carrega o vetor de elementos inteiros do arquivo de entrada
    retEntrada = fread(vetor, sizeof(int), tam, descritorArquivoEntrada);
    if(retEntrada < tam) {
        fprintf(stderr, "Erro de leitura dos elementos do vetor de entrada\n");
        return 2;
    }


    // -- ORDENAÇÃO -- //

    GET_TIME(inicio);

    // imprimeVetor(vetor, tam);

    pthread_t tid[numThreads];
    int ident[numThreads];
    for(int i = 0; i < numThreads; i++){
        ident[i] = i+1;
        if(pthread_create(&tid[i], NULL, ordena, (void *)&ident[i]))
            printf("ERRO -- pthread_create\n");
    }

    for(int thread=0; thread<numThreads; thread++){
        if(pthread_join(tid[thread], NULL)){
            printf("--ERRO: pthread_join()"); 
            exit(-1);
        }
    }

    // Merge dos pedaços
    mergeSort(vetor, 0, tam/numThreads, 2 * (tam / numThreads));

    GET_TIME(fim);
    delta = fim - inicio;
    printf("Tempo de ordenação: %lf\n", delta);

    // imprime vetor ordenado (descomentar se desejar visualizar!)
    imprimeVetor(vetor, tam);

    // -- FINALIZAÇÃO -- //

    //abre o arquivo para escrita binaria
    descritorArquivoSaida = fopen(argv[2], "wb");
    if(!descritorArquivoSaida) {
        fprintf(stderr, "Erro de abertura do arquivo de saida\n");
        return 3;
    }

    //escreve o tamanho do vetor de saída
    retSaida = fwrite(&tam, sizeof(long long int), 1, descritorArquivoSaida);

    // escreve os elementos da matriz
    retSaida = fwrite(vetor, sizeof(int), tam, descritorArquivoSaida);
    if(retSaida < tam) {
        fprintf(stderr, "Erro de escrita no arquivo de saida\n");
        return 3;
    }

    //finaliza o uso das variaveis
    fclose(descritorArquivoEntrada);
    fclose(descritorArquivoSaida);
    free(vetor);
    // free(tid);

    return 0;
}