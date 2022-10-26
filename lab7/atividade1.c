#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#define N 5 // dim do Buffer
#define P 3 // num de threads produtoras
#define C 3 // num de threads consumidoras 

// variaveis globais 
int Buffer[N];
int count = 0;

sem_t slotCheio, slotVazio; // condição
sem_t mutexProd, mutexCons; // exclusão mútua

// inicializa o buffer
void IniciaBuffer(int n) {
  int i;
  for(i=0; i<n; i++)
    Buffer[i] = 0;
}

// imprime o buffer
void ImprimeBuffer(int n) {
  int i;
  for(i=0; i<n; i++)
    printf("%d ", Buffer[i]);
  printf("\n");
}

// funções para produzir e consumir 
void Insere(int item, int id){
    static int in=0;

    printf("P[%d] quer produzir\n", id);
    //aguarda slot vazio
    if(count > N) printf("P[%d] bloqueou\n", id);
    sem_wait(&slotVazio);
    printf("P[%d] desbloqueou\n", id);
    //exclusao mutua entre produtores
    sem_wait(&mutexProd);
    Buffer[in] = item;
    in = (in + 1) % N;
    count++;
    printf("P[%d] produziu\n", id);

    // imprime buffer
    for(int i = 0; i < N; i++)
        printf("%d ", Buffer[i]);
    printf("\n");

    sem_post(&mutexProd);
    //sinaliza um slot cheio
    sem_post(&slotCheio);
}


int Retira(int id){
    int item;
    static int out=0;

    printf("C[%d] quer consumir\n", id);
    //aguarda slot cheio
    if(count == 0) printf("C[%d] bloqueou\n", id);
    sem_wait(&slotCheio);
    printf("C[%d] desbloqueou\n", id);
    //exclusao mutua entre consumidores
    sem_wait(&mutexCons);
    item = Buffer[out];
    Buffer[out] = 0;
    out = (out + 1) % N;
    count--;
    printf("C[%d] consumiu %d\n", id, item);

    // imprime buffer
    for(int i = 0; i < N; i++)
        printf("%d ", Buffer[i]);
    printf("\n");

    sem_post(&mutexCons);
    //sinaliza um slot vazio
    sem_post(&slotVazio);

    return item;
}


// threads produtoras e consumidoras
void * produtor(void * arg){
    int *id = (int *) arg;
    while(1){
        // produzindo o item
        Insere(*id, *id);
        sleep(1);
    }
    free(arg);
    pthread_exit(NULL);
}

void * consumidor(void * arg){
    int *id = (int *) arg;
    int item;
    while(1){
        // consumindo o item 
        item = Retira(*id);
        sleep(1); // faz o processamento do item 
    }

    free(arg);
    pthread_exit(NULL);
}


int main(void){
    // identificadores das threads
    pthread_t tid[P + C];
    int *id[P + C];

    // aloca espaco para os IDs das threads
    for(int i = 0; i < P + C; i++) {
        id[i] = malloc(sizeof(int));
        if(id[i] == NULL) exit(-1);
        *id[i] = i+1;
    } 

    // inicializa o Buffer 
    IniciaBuffer(N);

    // inicializa os semaforos
    sem_init(&mutexProd, 0, 1);
    sem_init(&mutexCons, 0, 1);
    sem_init(&slotCheio, 0, 0);
    sem_init(&slotVazio, 0, N);

    //cria as threads produtoras
    for(int i = 0; i < P; i++) {
        if(pthread_create(&tid[i], NULL, produtor, (void *) id[i])) exit(-1);
    } 
    
    //cria as threads consumidoras
    for(int i = 0; i < C; i++) {
        if(pthread_create(&tid[i+P], NULL, consumidor, (void *) id[i])) exit(-1);
    } 

    pthread_exit(NULL);
    return 1;
}