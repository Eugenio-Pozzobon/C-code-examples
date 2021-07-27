// Autor Eugenio Pozzobon
// Matricula 2021510175
// Data: 26/07/2021
// Sistemas Operacionais em Tempo Real

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>

#define BUFFER_SIZE 8

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t varCond = PTHREAD_COND_INITIALIZER;

int posicao = 0; // posicao de escrita e leitura no vetor
int buffer[BUFFER_SIZE];

// função do produtor
_Noreturn void *prod() {
    while (true) {
        pthread_mutex_lock(&mutex);
        /* A estrutura abaixo de liberação e trava da thread precisou ser implementada
         * no começo e no fim da função pois eventualmente ocorriam falhas de sincronismo
         * então repetindo a condição antes da atualização da variável posicao é possível
         * evitar esses bugs que ocorriam durante alguns testes.
        */

        //libera a thread de consumo
        if (posicao == BUFFER_SIZE) {
            pthread_cond_signal(&varCond);
        }
        // trava a thread de produção
        while (posicao == BUFFER_SIZE) {
            printf("\nProdutor Esperando\n");
            pthread_cond_wait(&varCond, &mutex);
        }


        buffer[posicao % (BUFFER_SIZE + 1)] = posicao;   //rand() % 255;
        posicao++;
        printf("Escrevendo\t");


        // libera a thread de consumo
        if (posicao == BUFFER_SIZE) {
            pthread_cond_signal(&varCond);
        }
        // trava a thread de produção
        while (posicao == BUFFER_SIZE) {
            printf("\nProdutor Esperando\n");
            pthread_cond_wait(&varCond, &mutex);
        }

        pthread_mutex_unlock(&mutex);
    }
}


// função do consumidor
_Noreturn void *cons() {
    int data = 0;
    while (true) {
        pthread_mutex_lock(&mutex);

        if (posicao == 0) {
            pthread_cond_signal(&varCond);
        }
        // trava a thread de consumo
        while (posicao == 0) {
            printf("\nConsumidor Esperando \n");
            pthread_cond_wait(&varCond, &mutex);
        }


        posicao--;
        printf("Pos Lida = %d \t", posicao);
        data = buffer[posicao % (BUFFER_SIZE + 1)];


        // Libera a thread de produção
        if (posicao == 0) {
            pthread_cond_signal(&varCond);
        }
        // trava a thread de consumo
        while (posicao == 0) {
            printf("\nConsumidor Esperando \n");
            pthread_cond_wait(&varCond, &mutex);
        }


        pthread_mutex_unlock(&mutex);
    }
}


int main(int argc, char **argv) {

    // cria as threads
    pthread_t pthProd, pthCons;

    pthread_create(&pthProd, NULL, prod, NULL);
    pthread_create(&pthCons, NULL, cons, NULL);

    // chama as threads
    pthread_join(pthCons, NULL); //bloqueia antes de começar a escrita
    pthread_join(pthProd, NULL);

    return 0;
}