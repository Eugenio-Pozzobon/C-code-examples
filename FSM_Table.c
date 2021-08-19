/*
 * Autor: Eugênio Pozzobon, 2021510175
 * Data: 02/08/2021
 */

/* Professor, eu tentei realizar essa atividade várias vezes, tanto que estou entregando bem fora do prazo,
 * mas tive dificuldade em todas as tentativas e eu realmente não sei o que está acontecendo de errado (ou certo!).
 * Se o sr puder, libere a resolução no moodle pois não estou conseguindo entender o que falta...
 * Também não entendi como reaproveitar as macros do exercício anterior com esse esqueleto de código.
 * O que consta abaixo é o que consegui realizar e entender.
 *
 * Grato desde já,
 * Eugênio
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* macros de testes - baseado em minUnit: www.jera.com/techinfo/jtns/jtn002.html */
#define verifica(mensagem, teste) do { if (!(teste)) return mensagem; } while (0)
#define executa_teste(teste) do { char *mensagem = teste(); testes_executados++; \
                                if (mensagem) return mensagem; } while (0)

#define	STX	(0x02)
#define	ETX	(0x03)
#define MAX_BUFFER 255

//****************************************************************************//
// State table typedef
//****************************************************************************//
typedef struct{
    void (*ptrFunc) (void);
    uint8_t NextState;
} FSM_STATE_TABLE;


/*
Tabela estados/eventos, func/prox = funcao (pode ser NULL)
e proximo estado (pode ser o atual)
formato:
			evento 0  - evento 1 - ... - evento N
estado 0 - func/prox - func/prox - ...- func/prox
...
estado N - func/prox - func/prox - ...- func/prox
*/

#define NR_STATES 5
#define NR_EVENTS 2

#define EVENTO_0   0
#define EVENTO_1   1

#define STX_STATE 0

struct machine_state {
    unsigned char buffer[MAX_BUFFER];
    unsigned char *rxdata;
    unsigned char qtdBuf;
} ms;

/***********************************************/
/** Funcao que retorna o calculo do CHECKSUM com base nos dados recebidos
 * @param datain: vetor de dados para calcular CHECKSUM.
 * @return chksum: resultado do somatório
 */
unsigned char checkData (unsigned char *datain, unsigned char q){
    int i = 0;
    unsigned char chksum = 0;
    for(i = 0; i<q; i++){
        chksum = chksum + datain[i];
    }
    return chksum;
}

/** Funcao que retorna os dados recebidos no buffer do protocolo
 com base nos dados do protocolo
 * @param buffer: vetor recebido.
 * @param q: tamanho do vetor de dadis a ser lido
 * @return data: dados esperados dentro do buffer
 */
unsigned char* getData(unsigned char *buf, unsigned char q){
    unsigned char data [q];
    int i = 0;
    for(i = 0; i < q ; i++ ){
        data[i] = buf[i + 2];
    }
    return data;
}

//uint8_t recebe_evento(void){
    //static uint8_t ev = 0;
    //ev = ~ev;
    //return (ev?EVENTO_1:EVENTO_0);
//}

void errorEvent(void) {
    printf("Erro!");
}

void stxFunc(void){
    if(ms.buffer[0] == STX){
        //state = QTD_STATE;
    }
}

void qtdFunc(void){
    ms.qtdBuf = ms.buffer[1];
}

void dtFunc(void){
    ms.rxdata = getData(ms.buffer, ms.qtdBuf);
}

void chkFunc(void){
    if(checkData(ms.rxdata, ms.qtdBuf) != ms.buffer[ms.qtdBuf + 1]){
        errorEvent();
    }
}

void etxFunc(void){
    if(ms.buffer[ms.qtdBuf + 2] == ETX){
    }else{
        errorEvent();
    }
}

const FSM_STATE_TABLE StateTable [NR_STATES][NR_EVENTS] = {
        stxFunc,  NULL,
        qtdFunc,  NULL,
        dtFunc,   NULL,
        chkFunc,  NULL,
        etxFunc,  NULL,
};


/* main para simular o uso da maquina de estados */
void main(void){
    uint8_t evento;
    uint8_t ActState = STX_STATE;

    ms.buffer[0] = STX;
    ms.buffer[1] = 2;
    ms.buffer[2] = 1;
    ms.buffer[3] = 2;
    ms.buffer[4] = 3;
    ms.buffer[5] = ETX;
    ms.qtdBuf = 0;


    while(1)
    {
        evento = 0;//recebe_evento();
        if (StateTable[ActState][evento].ptrFunc != NULL)
            StateTable[ActState][evento].ptrFunc();

        ActState = StateTable[ActState][evento].NextState;

        printf("Current State: %d\n", ActState);
    }
}


