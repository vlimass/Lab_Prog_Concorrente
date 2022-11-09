#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define NT1 3 // número de threads T1 
#define NT2 3 // número de threads T2
#define NT3 3 // número de threads T3

// base de dados compartilhada
int dados = 0;

// variáveis de estado 
int leit = 0;
int escr = 0;

// variáveis de sincronização 
pthread_mutex_t mutex;
pthread_cond_t cond_leit, cond_escr;

//entrada leitura
void InicLeit (int id, int type) {
    pthread_mutex_lock(&mutex);
    printf("T%d[%d] quer ler\n", type, id);
    while(escr > 0) {
        printf("T%d[%d] bloqueou\n", type, id);
        pthread_cond_wait(&cond_leit, &mutex);
        printf("T%d[%d] desbloqueou\n", type, id);
    }
    leit++;
    pthread_mutex_unlock(&mutex);
}

//saida leitura
void FimLeit (int id, int type) {
   pthread_mutex_lock(&mutex);
   printf("T%d[%d] terminou de ler\n", type, id);
   leit--;
   if(leit==0) pthread_cond_signal(&cond_escr);
   pthread_mutex_unlock(&mutex);
}

//entrada escrita
void InicEscr (int id, int type) {
   pthread_mutex_lock(&mutex);
   printf("T%d[%d] quer escrever\n", type, id);
   while((leit>0) || (escr>0)) {
     printf("T%d[%d] bloqueou\n", type, id);
     pthread_cond_wait(&cond_escr, &mutex);
     printf("T%d[%d] desbloqueou\n", type, id);
   }
   escr++;
   pthread_mutex_unlock(&mutex);
}

//saida escrita
void FimEscr (int id, int type) {
    pthread_mutex_lock(&mutex);
    printf("T%d[%d] terminou de escrever\n", type, id);
    escr--;
    pthread_cond_signal(&cond_escr);
    pthread_cond_broadcast(&cond_leit);
    pthread_mutex_unlock(&mutex);
}

// threads tipo 1
void *T1 (void *arg){
    int *id = (int*) arg;

    while(1){
        InicEscr(*id, 1);
        printf("T1[%d] está escrevendo\n", *id);
        
        dados++; // altera valor da base de dados

        FimEscr(*id, 1);
        sleep(1);
    }

    free(arg);
    pthread_exit(NULL);
}

// threads tipo 2
void *T2 (void *arg) {
    int *id = (int *) arg;

    while(1) {
    InicLeit(*id, 2);
    printf("T2[%d] está lendo\n", *id);

    // operação de leitura
    if(dados % 2 == 0) printf("%d é par\n", dados);
    else printf("%d é ímpar\n", dados);

    FimLeit(*id, 2);
    sleep(1);
    } 

    free(arg);
    pthread_exit(NULL);
}

// threads tipo 3
void *T3 (void *arg) {
    int *id = (int *) arg;
    int boba1, boba2;

    while(1) {
        InicLeit(*id, 3);
        printf("T3[%d] está lendo\n", *id);

        printf("Valor atual = %d\n", dados); // operação de leitura

        FimLeit(*id, 3);

        /* processamento bobo... */
        boba1=100; boba2=-100; while (boba2 < boba1) boba2++;

        InicEscr(*id, 3);
        printf("T3[%d] está escrevendo\n", *id);
        
        dados = *id; // altera valor da base de dados

        FimEscr(*id, 3);
        sleep(1);

        sleep(1);
    } 

    free(arg);
    pthread_exit(NULL);
}

//funcao principal
int main(void) {
    //identificadores das threads
    pthread_t tid[NT1 + NT2 + NT3];
    int id[NT1 + NT2 + NT3];

    //inicializa as variaveis de sincronizacao
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_leit, NULL);
    pthread_cond_init(&cond_escr, NULL);

    // cria as threads T1
    for(int i=0; i<NT1; i++) {
    id[i] = i+1;
    if(pthread_create(&tid[i], NULL, T1, (void *) &id[i])) exit(-1);
    } 

    // cria as threads T2 
    for(int i=0; i<NT2; i++) {
    id[i+NT1] = i+1;
    if(pthread_create(&tid[i+NT1], NULL, T2, (void *) &id[i+NT1])) exit(-1);
    }

    // cria as threads T3 
    for(int i=0; i<NT3; i++) {
    id[i+NT1+NT2] = i+1;
    if(pthread_create(&tid[i+NT1+NT2], NULL, T3, (void *) &id[i+NT1+NT2])) exit(-1);
    }

    pthread_exit(NULL);
    return 0;
}