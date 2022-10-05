#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define NTHREADS 4

// Variáveis globais
int aux_msg1 = 0;
int aux_msg4 = 0;
pthread_mutex_t mutex;
pthread_cond_t cond_msg4, free_msg1;


// thread 1
void *msg1 (void *arg) {
    pthread_mutex_lock(&mutex);
    // Verificação se foi mostrado "Fique a vontade" e "Sente-se por favor"
    if(aux_msg1 < 2){
        pthread_cond_wait(&free_msg1, &mutex);
    }
    printf("Volte sempre!\n");
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

// thread 2
void *msg2 (void *arg) {
    pthread_mutex_lock(&mutex);
    // Verificação se foi mostrado "Seja bem-vindo"
    if(!aux_msg4){   
        pthread_cond_wait(&cond_msg4, &mutex);
    }
    printf("Fique a vontade.\n");

    // Liberação após mostrar "Fique a vontade"
    aux_msg1++; 
    if(aux_msg1 == 2){
        pthread_cond_signal(&free_msg1);
    }

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

// thread 3 
void *msg3 (void *arg) {
    pthread_mutex_lock(&mutex);
    // Verificação se foi mostrado "Seja bem-vindo"
    if(!aux_msg4){
        pthread_cond_wait(&cond_msg4, &mutex);
    }
    printf("Sente-se por favor.\n");

    // Liberação após mostrar "Sente-se por favor"
    aux_msg1++; 
    if(aux_msg1 == 2){
        pthread_cond_signal(&free_msg1);
    }

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);    
}

// thread 4
void *msg4 (void *arg) {
    printf("Seja bem-vindo!\n");

    pthread_mutex_lock(&mutex);
    // Liberação após mostrar "Seja bem-vindo"
    aux_msg4 = 1;
    if(aux_msg4){
        pthread_cond_broadcast(&cond_msg4);    
    }
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);    
}

int main (int argc, char *argv[]){
    pthread_t threads[NTHREADS];

    // Inicializa o mutex (lock de exclusão mútua) e variáveis de condição
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&free_msg1, NULL);
    pthread_cond_init(&cond_msg4, NULL);

    // Cria threads
    pthread_create(&threads[0], NULL, msg1, NULL);
    pthread_create(&threads[2], NULL, msg3, NULL);
    pthread_create(&threads[3], NULL, msg4, NULL);
    pthread_create(&threads[1], NULL, msg2, NULL);

    // Espera as threads finalizarem    
    for(int i = 0; i < NTHREADS; i++){
        pthread_join(threads[i], NULL);
    }

    // Desaloca variáveis e finaliza 
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&free_msg1);
    pthread_cond_destroy(&cond_msg4);
}