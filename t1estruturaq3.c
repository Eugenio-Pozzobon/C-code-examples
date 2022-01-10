//
// Created by eugen on 19/12/2021.
//

/*  Desenvolver um programa que possua a função alteraValores() para realizar a troca dos
    valores de duas variáveis. Essa função recebe os endereços das variáveis passadas pela
    função main(), armazenando-os nos ponteiros p1 e p2. Dentro da função, trocam-se os
    conteúdos dos endereços, retornando para a função chamadora, onde deverão ser
    impressos.
*/

#include <stdio.h>

int n1 = 3, n2 = 9;

void alteraValores(int *ponteiro1, int *ponteiro2){

    // variável auxiliar armazena valor de uma das variáveis
    int ponteiroAux = *ponteiro2;

    //alteram-se os valores das variáveis por meio de seus ponteiros
    *ponteiro2 = *ponteiro1;
    *ponteiro1 = ponteiroAux;

}

int main(){

    alteraValores(&n1, &n2);
    printf("n1: %d, n2: %d", n1, n2);

    return 1;
}

