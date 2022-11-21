#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

void imprimeVetor(int vet[], int tam){
    for(int i = 0; i < tam; i++){
        printf(" %d ", vet[i]); 
    }
    printf("\n");
}


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


void mergeSort(int vet[], int inicio, int fim){
    if(inicio < (fim - 1)){
        int meio = (inicio + fim)/ 2;
        mergeSort(vet, inicio, meio);
        mergeSort(vet, meio, fim);
        merge(vet, inicio, meio, fim);
    }
}

// function to swap elements
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int partition(int array[], int low, int high) {
  
  // select the rightmost element as pivot
  int pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
    
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);
    
    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);
    
    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}

// function to print array elements
void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}


int main(int argc, char * argv[]) { 
    int * vetor;
    long long int tam; // tamanho do vetor 
    FILE * descritorArquivoEntrada, * descritorArquivoSaida; //descritores dos arquivos
    size_t retEntrada, retSaida; //retorno da funcao de leitura nos arquivos 
    double inicio, fim, delta; // gerenciadores de tempo 

    // -- INICIALIZAÇÃO -- //

    //recebe os argumentos de entrada
    if(argc < 3) {
        fprintf(stderr, "Digite: %s <arquivo vetor entrada> <arquivo vetor saida>\n", argv[0]);
        return 1;
    }

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

    // algoritmo merge sort
    mergeSort(vetor, 0, tam);
    // quickSort(vetor, 0, tam);

    GET_TIME(fim);
    delta = fim - inicio;
    printf("Tempo de ordenação: %lf\n", delta);

    // imprime vetor ordenado (descomentar se desejar visualizar!)
    // imprimeVetor(vetor, tam);

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

    return 0;
}