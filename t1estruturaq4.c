//
// Created by eugen on 19/12/2021.
//

/*  Utilizando ponteiros, faça um algoritmo que leia um vetor de 10 elementos na função
    principal. Depois, chame uma função para modificar o vetor de modo que o primeiro
    elemento passe para a última posição, e desloque todos os outros para uma posição a
    esquerda. Imprima o vetor modificado na função main
*/

#include <stdio.h>
int test[10];

void deslocarVetor(int *vector){

    int aux = vector[0];

    for(int i = 0; i < 10-1; i++){
        vector[i] = vector[i+1];
    }
    vector[9] = aux;

}

int main(){

    for(int i = 0; i <10; i++){
        printf("\nDigite o valor [%d]: ", i);
        scanf("%d", &test[i]);
    }

    deslocarVetor(test);
    for(int i = 0; i<10; i++){
        printf("%d ", test[i]);
    }

    return 1;
}