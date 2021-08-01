//
// Created by eugen on 31/07/2021.
//


#include <stdint.h>


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

#define NR_STATES 2
#define NR_EVENTS 2

#define EVENTO_0   0
#define EVENTO_1   1

#define ESTADO_0   0
#define ESTADO_1   1

const FSM_STATE_TABLE StateTable [NR_STATES][NR_EVENTS] = {
                NULL, ESTADO_0, NULL, ESTADO_1,
                NULL, ESTADO_1, NULL, ESTADO_0
        };

uint8_t recebe_evento(void){
    static uint8_t ev = 0;
    ev = ~ev;
    return (ev?EVENTO_1:EVENTO_0);
}

/* main para simular o uso da maquina de estados */
void main(void){
    uint8_t evento;
    uint8_t ActState = ESTADO_0;

    while(1)
    {
        evento = recebe_evento();
        if (StateTable[ActState][evento].ptrFunc != NULL)
            StateTable[ActState][evento].ptrFunc();

        ActState = StateTable[ActState][evento].NextState;
    }
}