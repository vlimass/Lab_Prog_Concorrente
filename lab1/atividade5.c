#include<stdio.h>
#include<pthread.h>

// Uso de variável global
double arr[10000];

// Função que a thread secundária vai executar
void * tarefa(void * arg) {
    int index_inicio = * (int *) arg;

    for(int i = index_inicio; i < (index_inicio + 5000); i++){
        arr[i] = i * 1.1; // Preencher posições do vetor com novo valor
    }

    pthread_exit(NULL);
}

// Função de teste com programa sequencial
int teste(void){
    double arr_sequencial[10000];
    int somador_teste = 0;
 
    for(int i = 0; i < 10000; i++){
        arr_sequencial[i] = i * 1.1;

        if(arr_sequencial[i] - arr[i] == 0){
            somador_teste++;
        }
    }

    if(somador_teste == 10000) return 1;    
    else return 0;
}

// Função do fluxo principal
int main(void) {
    int index_t1 = 0;
    int index_t2 = 5000;

    pthread_t tid[2]; // Identificador da thread nova

    // Inicializa o vetor
    for(int i = 0; i < 10000; i++) {
        arr[i] = i;
    }

    // Cria primeira thread 
    if(pthread_create(&tid[0], NULL, tarefa, (void *) &index_t1)) {
        printf("ERRO --- pthread_create\n");
    }

    // Cria segunda thread
    if(pthread_create(&tid[1], NULL, tarefa, (void *) &index_t2)) {
        printf("ERRO --- pthread_create\n");
    }
    
    // Espera as threads finalizarem sua execução 
    for(int i = 0; i < 2; i++){
        if(pthread_join(tid[i], NULL)) {
            printf("ERRO --- pthread_join\n");
        }
    }

    // Teste de verificação com programa sequencial 
    if(teste()){
        printf("Sucesso!\n");
    } else {
        printf("Falha no programa :(\n");
    }

    pthread_exit(NULL); // Desvincula o término da main do término do programa
    return 0;
}

