//
// Created by eugen on 19/12/2021.
//

/*  Crie um programa que contenha duas listas encadeadas com o mesmo número de
valores inteiros armazenados. Faça uma função que multiplique o primeiro elemento da
lista 1 pelo primeiro de lista 2 e armazene o resultado em uma terceira lista. Ao final,
apresentar os valores existentes na lista 3.
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

Lista *produto (Lista *l1, Lista *l2){
    Lista *p, *aux1, *aux2;
    // passa as listas para listas auxiliares, da mesma forma que é feito na função imprime,

    aux1 = l1;
    aux2 = l2;

    for (; aux1!=NULL; aux1=aux1->prox){
        // realiza a multiplicação pegando os valores da lista
        // na posição a ser lida atualmente
        p = insere(p,aux1->info*aux2->info);

        // avança na lista 2
        aux2=aux2->prox;
    }
    return p;
}

int main(){

    Lista *l1, *l2;
    l1 = NULL;
    l2 = NULL;
    int valorL1, valorL2, contagem = 0 ;

    // loop infinito para receber valores do usuário até que ele digite um valor igual a 0
    while(1) {
        printf("\nDigite o valor %d da lista 1 (insira 0 para parar): ", contagem);
        scanf("%d", &valorL1);
        printf("\nDigite o valor %d da lista 2: ", contagem);
        scanf("%d", &valorL2);

        if ((valorL1 == 0) || (valorL2 == 0)) {
            break;
        }

        // se os valores forem válidos, insere na lista encadeada
        l1 = insere(l1, valorL1);
        l2 = insere(l2, valorL2);
        contagem++;
    }

    imprime(l1); printf("\n");
    imprime(l2); printf("\n");
    imprime(produto(l1,l2));

    return 0;
}