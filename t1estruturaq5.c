//
// Created by eugen on 19/12/2021.
//

/*  Desenvolva um algoritmo que contenha uma função para somar os valores
armazenados na lista encadeada. A lista deve permitir a inserção dinâmica de
elementos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct lista {
    int info;
    struct lista *prox;
};

typedef struct lista Lista;

Lista *insere(Lista *l, int i){
    Lista *novo;
    novo = (Lista*) malloc(sizeof(Lista));
    novo -> info = i;
    novo -> prox = l;
    return novo;
}

void imprime (Lista *l){
    Lista *p;
    for (p=l; p!=NULL; p=p->prox){
        printf("%d - ", p->info);
    }
}

int soma (Lista *l){
    Lista *p; // variável auxiliar, que recebe o valor da lista l, igual é feito na função de imprimir
    int soma = 0; //variável auxiliar para incrementar a soma conforme lê cada dado da lista
    for (p=l; p!=NULL; p=p->prox){
        soma += p->info;
    }
    return soma;
}

int main(){

    Lista *l;
    l = NULL;

    int valor, contagem = 0 ;
    // loop infinito para receber valores do usuário até que ele digite um valor igual a 0
    while(1) {
        printf("\nDigite o valor %d da lista 1 (insira 0 para parar): ", contagem);
        scanf("%d", &valor);

        if (valor == 0) {
            break;
        }

        // se os valores forem válidos, insere na lista encadeada
        l = insere(l, valor);
        contagem++;
    }
    imprime(l);
    printf("\nsoma = %d", soma(l));
    return 0;
}