#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define numT1 1 // número de threads T1 
#define numT2 1 // número de threads T2
#define numT3 1 // número de threads T3

// variáveis de estado 
int leit = 0;
int escr = 0;

// variáveis de sincronização 
pthread_mutex_t mutex;
pthread_cond_t cond_leit, cond_escr;

//entrada leitura
void InicLeit (int id) {
   pthread_mutex_lock(&mutex);
   printf("T[%d] quer ler\n", id);
   while(escr > 0) {
     printf("T[%d] bloqueou\n", id);
     pthread_cond_wait(&cond_leit, &mutex);
     printf("T[%d] desbloqueou\n", id);
   }
   leit++;
   pthread_mutex_unlock(&mutex);
}

//saida leitura
void FimLeit (int id) {
   pthread_mutex_lock(&mutex);
   printf("T[%d] terminou de ler\n", id);
   leit--;
   if(leit==0) pthread_cond_signal(&cond_escr);
   pthread_mutex_unlock(&mutex);
}

//entrada escrita
void InicEscr (int id) {
   pthread_mutex_lock(&mutex);
   printf("T[%d] quer escrever\n", id);
   while((leit>0) || (escr>0)) {
     printf("T[%d] bloqueou\n", id);
     pthread_cond_wait(&cond_escr, &mutex);
     printf("T[%d] desbloqueou\n", id);
   }
   escr++;
   pthread_mutex_unlock(&mutex);
}

//saida escrita
void FimEscr (int id) {
   pthread_mutex_lock(&mutex);
   printf("T[%d] terminou de escrever\n", id);
   escr--;
   pthread_cond_signal(&cond_escr);
   pthread_cond_broadcast(&cond_leit);
   pthread_mutex_unlock(&mutex);
}

void *T1 (void *arg){
    int *id = (int*) arg;
    while(1){
        InicEscr(*id);
        printf("T1 %d está escrevendo", *id);
        FimEscr(*id);
        sleep(1);
    }
    free(arg);
    pthread_exit(NULL);
}