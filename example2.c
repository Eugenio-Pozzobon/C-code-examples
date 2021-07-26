//autor eugenio pozzobon
//data 12/02/2021

/* Proposta: 
O objetivo deste trabalho � implementar um programa multithread que imprime informa��es estat�sticas sobre uma lista de n�meros. O programa deve ler da entrada padr�o uma lista de n�meros (m�x. 100) e em seguida criar 3 threads concorrentes.

Cada uma das 3 threads tem uma fun��o bem definida, em qualquer ordem:
	Uma thread deve calcular a m�dia dos n�meros
	Uma thread deve encontrar o valor m�ximo
	Uma thread deve encontrar o valor m�nimo
	
Use vari�veis globais para guardar a lista de n�meros, e representar os valores de m�dia, m�nimo e m�ximo. Os passos que o programa deve seguir s�o:

	Antes de criar as threads, o programa deve ler a lista de valores digitados pelo usu�rio da entrada padr�o (stdin em C ou std::cin em C++).
	Somente ap�s ler os valores as threads podem ser criadas.
	Quando as threads terminarem de calcular os valores, a thread principal pode imprimir os valores calculados.
*/


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// Variáveis globais
int input[100];
int maior;
int menor;
float media = 0;
int n_counter = 0; //contador de variáveis inseridas pelo usuário

// Função para calcular a média
void *funcMedia(void* a){

	for(int i = 0; i< n_counter; i++){
		media += (float)input[i]/n_counter;
	}
	pthread_exit(NULL); //return
}

// Função para verificar o maior valor da lista
void *funcMax(void* a){
	
	maior = input[0];
	for(int i = 0; i<n_counter; i++){
		
		if(input[i]>maior){
			maior = input[i];
		}
	}
	pthread_exit(NULL); //return
}

// Função para verificar o menor valor da lista
void *funcMin(void* a){

	menor = input[0];
	for(int i = 0; i<n_counter; i++){
		
		if(input[i]<menor){
			menor = input[i];
		}
	}
	pthread_exit(NULL); //return
}


int main(int argc, char** argv){

	pthread_t threads[3]; // cria as threads
	
	int n = 0; // valor a ser inserido pelo usuário
	int i = 0;
	
	for(i = 0; i<100; i++){
		printf("Digite um numero: (negativos para encerrar): ");
		scanf("%d", &n);
		if(n<0){  // se o número for negativo, encerra a leitura
			break;
		}
		input[n_counter] = n;
		n_counter++;
	}
	
	// chama as threads
	pthread_create(&threads[0], NULL, funcMedia, NULL);
	pthread_create(&threads[1], NULL, funcMax, NULL);
	pthread_create(&threads[2], NULL, funcMin, NULL);

	// retorna para o usuário os valores calculados
	printf("A media e: %.2f \n", media);
	printf("O minimo e: %d \n", menor);
	printf("O maximo e: %d \n", maior);
	

	return 0;
}
