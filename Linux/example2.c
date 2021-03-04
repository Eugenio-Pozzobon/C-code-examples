//autor eugenio pozzobon
//data 12/02/2021

/* Proposta: 
O objetivo deste trabalho é implementar um programa multithread que imprime informações estatísticas sobre uma lista de números. O programa deve ler da entrada padrão uma lista de números (máx. 100) e em seguida criar 3 threads concorrentes.

Cada uma das 3 threads tem uma função bem definida, em qualquer ordem:
	Uma thread deve calcular a média dos números
	Uma thread deve encontrar o valor máximo
	Uma thread deve encontrar o valor mínimo
	
Use variáveis globais para guardar a lista de números, e representar os valores de média, mínimo e máximo. Os passos que o programa deve seguir são:

	Antes de criar as threads, o programa deve ler a lista de valores digitados pelo usuário da entrada padrão (stdin em C ou std::cin em C++).
	Somente após ler os valores as threads podem ser criadas.
	Quando as threads terminarem de calcular os valores, a thread principal pode imprimir os valores calculados.
*/


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// VariÃ¡veis globais
int input[100];
int maior;
int menor;
float media = 0;
int n_counter = 0; //contador de variÃ¡veis inseridas pelo usuÃ¡rio

// FunÃ§Ã£o para calcular a mÃ©dia
void *funcMedia(void* a){

	for(int i = 0; i< n_counter; i++){
		media += (float)input[i]/n_counter;
	}
	pthread_exit(NULL); //return
}

// FunÃ§Ã£o para verificar o maior valor da lista
void *funcMax(void* a){
	
	maior = input[0];
	for(int i = 0; i<n_counter; i++){
		
		if(input[i]>maior){
			maior = input[i];
		}
	}
	pthread_exit(NULL); //return
}

// FunÃ§Ã£o para verificar o menor valor da lista
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
	
	int n = 0; // valor a ser inserido pelo usuÃ¡rio
	int i = 0;
	
	for(i = 0; i<100; i++){
		printf("Digite um numero: (negativos para encerrar): ");
		scanf("%d", &n);
		if(n<0){  // se o nÃºmero for negativo, encerra a leitura
			break;
		}
		input[n_counter] = n;
		n_counter++;
	}
	
	// chama as threads
	pthread_create(&threads[0], NULL, funcMedia, NULL);
	pthread_create(&threads[1], NULL, funcMax, NULL);
	pthread_create(&threads[2], NULL, funcMin, NULL);

	// retorna para o usuÃ¡rio os valores calculados
	printf("A media e: %.2f \n", media);
	printf("O minimo e: %d \n", menor);
	printf("O maximo e: %d \n", maior);
	

	return 0;
}
