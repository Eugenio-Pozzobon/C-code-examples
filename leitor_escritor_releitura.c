// Autor Eugenio Pozzobon
// Matricula 2021510175
// Sistemas Operacionais em Tempo Real
// Data: 26/07/2021

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>

#define BUFFER_SIZE 8

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t varCond = PTHREAD_COND_INITIALIZER;

bool isWriting = true;
int livro = 0;

// função do produtor
_Noreturn void *escritor() {
    isWriting = false;
    while (livro<255) {
        pthread_mutex_lock(&mutex);
        isWriting = true;
        printf("\nWriting\n");
        livro +=1;
        pthread_mutex_unlock(&mutex);
    }
    printf("Not Writing\n");
    isWriting = false;
}

// função do consumidor
_Noreturn void *leitor() {
    int data = 0 ;
    while (true) {
        if(!isWriting) {
            pthread_mutex_lock(&mutex);
            data = livro;
            printf("\nLivro Lido = %d \n", livro);
            pthread_mutex_unlock(&mutex);
        }
    }
}

int main(int argc, char **argv) {

    // cria as threads
    pthread_t pthEscritor, pthLeitor;

    pthread_create(&pthLeitor, NULL, leitor, NULL);
    pthread_create(&pthEscritor, NULL, escritor, NULL);

    // chama as threads
    pthread_join(pthLeitor, NULL);
    pthread_join(pthEscritor, NULL);

    return 0;
}