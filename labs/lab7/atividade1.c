#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#define N 5 // dim do Buffer
#define P 2 // num de threads produtoras
#define C 2 // num de threads consumidoras 

// variaveis globais 
int Buffer[N];
int elemProd = 0; // qntd de elementos produzidos no buffer

sem_t slotCheio, slotVazio; // condição
sem_t mutex; // exclusão mútua com apenas um mutex para possibilitar a verificação dos logs

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

    while(elemProd < N){
        printf("P[%d] quer produzir\n", id);

        // verificação para não extrapolar o elemProd
        while(elemProd >= 5){;}
    
        //aguarda slot vazio
        sem_wait(&slotVazio);
        //exclusao mutua entre produtores
        sem_wait(&mutex);
        Buffer[in] = item;
        in = (in + 1) % N;
        printf("P[%d] produziu\n", id);
        elemProd++;
        printf("elementos produzidos = %d\n", elemProd);
        // imprime buffer
        ImprimeBuffer(N);

        sem_post(&mutex);
    }

    //sinaliza um slot cheio se produzir tudo 
    sem_post(&slotCheio);
    
}


int Retira(int id){
    int item;
    static int out=0;

    printf("C[%d] quer consumir\n", id);
    while(elemProd < N){
        ;
    }
    //aguarda slot cheio
    sem_wait(&slotCheio);
    //exclusao mutua entre consumidores
    sem_wait(&mutex);
    item = Buffer[out];
    Buffer[out] = 0;
    out = (out + 1) % N;
    elemProd--;
    printf("elementos produzidos = %d\n", elemProd);
    printf("C[%d] consumiu %d\n", id, item);

    // imprime buffer
    ImprimeBuffer(N); 

    sem_post(&mutex);
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
    sem_init(&mutex, 0, 1);
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