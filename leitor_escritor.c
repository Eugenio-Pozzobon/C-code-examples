// Autor Eugenio Pozzobon
// Matricula 2021510175
// Data: 26/07/2021
// Sistemas Operacionais em Tempo Real


/* Problema:
 * Leitores / Escritores
    • Leitores: Lêem enquanto não existir escritor
    • Escritores: Escrevem com acesso exclusivo
    • Escritores terão preferência
 */

/* Observação:
 * Para efetivamente testar se a solução funcionou, implementei várias threads de escrita para verificar
 * se os escritores mantêm sua prioridade mutua. Porém inseri um limitador com timer, APENAS PARA FINS DE TESTE,
 * para dispensar todos os escritores e verificar se os leitores passam a ter acesso.
 * E se depois desse mesmo intervalo retomar os escritores para testar se eles conseguem opter a prioridade.
 */

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define BUFFER_SIZE 8

// tempo máximo em que escritores podem concorrer e sobrepor leitores
// também é usado para limitar o tempo em que só existem leitores acessando
#define MAX_WRITE_TIME 5 // segundos

// mutex que bloqueia os leitores
pthread_mutex_t mutexLeitor = PTHREAD_MUTEX_INITIALIZER;

// mutex que bloqueia os escritores
pthread_mutex_t mutexEscritor = PTHREAD_MUTEX_INITIALIZER;

int numEscritores = 0; // indica quantos escritores estão tentando acessar o livro
int writingCounter = 0; // posição de escrita no vetor
int readingCounter = 0; // posição de leitura no vetor
int livro[BUFFER_SIZE]; // vetor de escrita e leitura

clock_t begin;

// função do escritor
_Noreturn void *escritor() {
    while (true) {
        if((clock()-begin)/CLOCKS_PER_SEC < MAX_WRITE_TIME) {
            if (numEscritores == 0) {
                // bloqueia leitores caso o estado anterior fosse de zero escritores
                // afinal de contas a thread foi iniciada o que significa que um escritor irá escrever
                pthread_mutex_lock(&mutexLeitor);
            }

            pthread_mutex_lock(&mutexEscritor); // bloqueia o contator para atualização
            numEscritores++; // incrementa
            pthread_mutex_unlock(&mutexEscritor); // libera contador

            printf("\nNovo escritor #%d escrevendo \n", numEscritores);

            pthread_mutex_lock(&mutexEscritor); // bloqueia o livro e o contador para escrita/atualização
            writingCounter++;
            writingCounter = writingCounter % (BUFFER_SIZE);
            livro[writingCounter] = writingCounter;

            numEscritores--;
            if (numEscritores == 0) {
                pthread_mutex_unlock(&mutexLeitor); // libera leitores caso não haja mais escritores
            }
            pthread_mutex_unlock(&mutexEscritor); // libera
        }
    }
}

// função do leitor
_Noreturn void *leitor() {
    int data = 0;
    while (true) {
        // trava os leitores
        pthread_mutex_lock(&mutexLeitor);

        if ((clock()-begin)/CLOCKS_PER_SEC > MAX_WRITE_TIME*2){ //libera o timer para reiniciar os escritores
            begin = clock();
        }

        // acessa e imprime os dados
        readingCounter ++;
        readingCounter = readingCounter%(BUFFER_SIZE);
        data = livro[readingCounter];
        printf("\nLivro Lido = %d \n", data);

        // libera próximo leitor
        pthread_mutex_unlock(&mutexLeitor);
    }
}


int main(int argc, char **argv) {

    begin = clock();

    // cria as threads
    pthread_t pthEscritor[2], pthLeitor;

    pthread_create(&pthLeitor, NULL, leitor, NULL);

    pthread_create(&pthEscritor[0], NULL, escritor, NULL);
    pthread_create(&pthEscritor[1], NULL, escritor, NULL);

    // chama as threads
    pthread_join(pthLeitor, NULL);
    pthread_join(pthEscritor[0], NULL);
    pthread_join(pthEscritor[1], NULL);

    return 0;
}