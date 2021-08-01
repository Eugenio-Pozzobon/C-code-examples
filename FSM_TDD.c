/*
 * Autor: Eugenio Pozzobon
 * Data: 08/06/2021
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

// Estados da maquina na leitura do protocolo
typedef enum{
    STX_STATE	= 0b000,
    QTD_STATE	= 0b001,
    DATA_STATE	= 0b010,
    CHK_STATE	= 0b011,
    ETX_STATE	= 0b100
} machine_state;

// TDD
uint32_t testes_executados = 0;
static char * executa_testes(void);

// Variaveis da execucao

int main(){

    char *resultado = executa_testes();
    if (resultado != 0){
        printf("%s\n", resultado);
    }else{
        printf("TODOS OS TESTES PASSARAM\n");
    }
    printf("Testes executados: %d\n", testes_executados);
    getch();

    return resultado != 0;
}

/***********************************************/
/** Funcao que retorna o calculo do CHECKSUM com base nos dados recebidos
 * @param datain: vetor de dados para calcular CHECKSUM.
 * @return chksum: resultado do somatOrio
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

unsigned char error[1] = {0};

/** Funcao que retorna os dados recebidos no buffer do protocolo
 * @param buffer: vetor recebido.
 * @return data: ou um dado simbolico que indica erro (valor 0)
 */
unsigned char* getRxData (unsigned char *buffer){
    unsigned char *rxdata;
    unsigned char QTD;
    unsigned char CHK;

    machine_state state = STX_STATE;

    int i = 0;
    for(i = 0; i<MAX_BUFFER; i ++){
        switch(state){
            case STX_STATE:
                if(buffer[i] == STX){
                    state = QTD_STATE;
                }else{
                    return error;
                }
                break;


            case QTD_STATE:
                QTD = buffer[i];
                state = DATA_STATE;
                break;

            case DATA_STATE:
                rxdata = getData(buffer, QTD);
                i = i + (QTD) - 1;
                state = CHK_STATE;
                break;

            case CHK_STATE:
                if(checkData(rxdata, QTD) != buffer[i]){
                    return error;
                }
                state = ETX_STATE;
                break;

            case ETX_STATE:
                if(buffer[i] == ETX){
                    return rxdata;
                }else{
                    return error;
                }
                state = STX_STATE;
                break;
        }
    }
    return error;
}

/** Funcao que gera o buffer de transmissao do protocolo de comunicacao
 *
 * @param txMsg vetor com valores de 0 a 255
 * @param QTX tamanho do vetor. Usar sizeof() gera problemas
 * 	para valores mais baixos como vetores de 1 ou 2 posicoes
 *
 * @return tx buffer
 */
unsigned char* getTxBuffer (unsigned char *txMsg, int QTX){
    unsigned char buffer[QTX + 4];
    machine_state state = STX_STATE;

    int i = 0;
    int j = 2;
    for(i = 0; i<MAX_BUFFER; i ++){
        switch(state){
            case STX_STATE:
                buffer[0] = STX;
                state = QTD_STATE;
                break;


            case QTD_STATE:
                buffer[1] = QTX;
                state = DATA_STATE;
                break;

            case DATA_STATE:
                for(j = 2; j < QTX +2 ; j ++){
                    buffer[j] = txMsg[j - 2];
                    i++;
                }
                state = CHK_STATE;
                break;

            case CHK_STATE:
                buffer[QTX + 2] = checkData(txMsg, QTX);
                state = ETX_STATE;
                break;

            case ETX_STATE:
                buffer[QTX + 3] = ETX;
                return buffer;
                state = STX_STATE;
                break;
        }
    }
}

/*
 * Rotinas de teste
 */
static char * teste_chkdata(void){
    unsigned char data[5] = {1,2,3,4,15};
    verifica("erro: deveria retornar 25",
             checkData(data,5) == (unsigned char)25);

    unsigned char data2[2] = {1,5};
    verifica("erro: deveria retornar 6",
             checkData(data2,2) == (unsigned char)6);


    unsigned char data3[1] = {5};
    verifica("erro: deveria retornar 6",
             checkData(data3,1) == (unsigned char)5);

    return 0;
}

static char * teste_getdata(void){
    unsigned char buffer[5] = {STX,1,5,5,ETX};
    unsigned char dataTeste[1] = {5};
    verifica("erro: deveria retornar os dados",
             memcmp(getData(buffer, 1), dataTeste, sizeof(dataTeste)) == 0);

    unsigned char buffer2[6] = {STX,2,1,2,3,ETX};
    unsigned char dataTeste2[2] = {1,2};
    verifica("erro: deveria retornar os dados 2",
             memcmp(getData(buffer2, 2), dataTeste2,
                    sizeof(dataTeste2)) == 0);

    unsigned char buffer3[7] = {STX,3,1,2,3,6,ETX};
    unsigned char dataTeste3[3] = {1,2,3};
    verifica("erro: deveria retornar os dados 3",
             memcmp(getData(buffer3, 3), dataTeste3,
                    sizeof(dataTeste3)) == 0);

    unsigned char buffer4[8] = {STX,4,1,2,3,4,10,ETX};
    unsigned char dataTeste4[4] = {1,2,3,4};
    verifica("erro: deveria retornar os dados 4",
             memcmp(getData(buffer4, 4), dataTeste4,
                    sizeof(dataTeste4)) == 0);

    unsigned char buffer5[9] = {STX,5,1,2,3,4,5,15,ETX};
    unsigned char dataTeste5[5] = {1,2,3,4,5};
    verifica("erro: deveria retornar os dados 5",
             memcmp(getData(buffer5, 5), dataTeste5,
                    sizeof(dataTeste5)) == 0);

    return 0;
}

static char * teste_rxProtocolo(void){
    unsigned char buffer[5] = {STX,1,10,10,ETX};
    unsigned char dataTeste[1] = {10};
    verifica("erro: protocolo nao funciona 1",
             memcmp(getRxData(buffer),dataTeste,sizeof(dataTeste)) == 0);

    unsigned char buffer2[6] = {STX,2,10,20,30,ETX};
    unsigned char dataTeste2[2] = {10,20};
    verifica("erro: protocolo nao funciona 2",
             memcmp(getRxData(buffer),dataTeste,sizeof(dataTeste)) == 0);

    unsigned char buffer3[7] = {STX,3,10,20,30,60,ETX};
    unsigned char dataTeste3[3] = {10,20,30};
    verifica("erro: protocolo nao funciona 3",
             memcmp(getRxData(buffer),dataTeste,sizeof(dataTeste)) == 0);

    unsigned char buffer4[8] = {STX,4,10,20,30,40,100,ETX};
    unsigned char dataTeste4[4] = {10,20,30,40};
    verifica("erro: protocolo nao funciona 4",
             memcmp(getRxData(buffer),dataTeste,sizeof(dataTeste)) == 0);

    unsigned char buffer5[9] = {STX,5,10,20,30,40,50,150,ETX};
    unsigned char dataTeste5[5] = {10,20,30,40,50};
    verifica("erro: protocolo nao funciona 5",
             memcmp(getRxData(buffer5),dataTeste5,sizeof(dataTeste5)) == 0);

    return 0;
}

static char * teste_rxProtocolo_failSTX(void){
    unsigned char buffer[5] = {ETX,1,10,10,ETX};
    verifica("erro STX: protocolo nao funciona 1", error[0] == getRxData(buffer)[0]);

    unsigned char buffer2[6] = {0,2,10,20,30,ETX};
    verifica("erro STX: protocolo nao funciona 2", error[0] == getRxData(buffer)[0]);

    return 0;
}


static char * teste_rxProtocolo_failQtd(void){
    unsigned char buffer[5] = {STX,0,10,10,ETX};
    verifica("erro QTX: protocolo nao funciona 1",
             error[0] == getRxData(buffer)[0]);

    unsigned char buffer2[6] = {STX,5,10,20,30,ETX};
    verifica("erro QTX: protocolo nao funciona 2",
             error[0] == getRxData(buffer)[0]);

    unsigned char buffer3[7] = {STX,30,10,20,30,60,ETX};
    verifica("erro QTX: protocolo nao funciona 3",
             error[0] == getRxData(buffer)[0]);

    unsigned char buffer4[8] = {STX,2,10,20,30,40,100,ETX};
    verifica("erro QTX: protocolo nao funciona 4",
             error[0] == getRxData(buffer)[0]);

    unsigned char buffer5[9] = {STX,1,10,20,30,40,50,150,ETX};
    verifica("erro QTX: protocolo nao funciona 5",
             error[0] == getRxData(buffer)[0]);

    return 0;
}

static char * teste_rxProtocolo_failChkSum(void){
    unsigned char buffer[5] = {STX,1,10,101,ETX};
    verifica("erro CHECKSUM: protocolo nao funciona 1",
             error[0] == getRxData(buffer)[0]);

    unsigned char buffer2[6] = {STX,2,10,20,301,ETX};
    verifica("erro CHECKSUM: protocolo nao funciona 2",
             error[0] == getRxData(buffer)[0]);

    unsigned char buffer3[7] = {STX,3,10,20,30,61,ETX};
    verifica("erro CHECKSUM: protocolo nao funciona 3",
             error[0] == getRxData(buffer)[0]);

    unsigned char buffer4[8] = {STX,4,10,20,30,40,101,ETX};
    verifica("erro CHECKSUM: protocolo nao funciona 4",
             error[0] == getRxData(buffer)[0]);

    unsigned char buffer5[9] = {STX,5,10,20,30,40,50,140,ETX};
    verifica("erro CHECKSUM: protocolo nao funciona 5",
             error[0] == getRxData(buffer)[0]);

    return 0;
}

static char * teste_rxProtocolo_failETX(void){
    unsigned char buffer[5] = {STX,1,10,10,STX};
    verifica("erro ETX: protocolo nao funciona 1", error[0] == getRxData(buffer)[0]);

    unsigned char buffer2[6] = {STX,2,10,20,30,0};
    verifica("erro ETX: protocolo nao funciona 2", error[0] == getRxData(buffer)[0]);

    return 0;
}

static char * teste_txProtocolo(void){
    unsigned char msg[1] = {5};
    verifica("erro teste_txProtocolo : deveria retornar STX",
             getTxBuffer(msg,1)[0] == STX);
    verifica("erro teste_txProtocolo : deveria retornar QTX",
             getTxBuffer(msg,1)[1] == 1);
    verifica("erro teste_txProtocolo : deveria retornar MSG0",
             getTxBuffer(msg,1)[2] == msg[0]);
    verifica("erro teste_txProtocolo : deveria retornar CHCKSUM",
             getTxBuffer(msg,1)[3] == msg[0]);
    verifica("erro teste_txProtocolo : deveria retornar ETX",
             getTxBuffer(msg,1)[4] == ETX);

    unsigned char msg2[2] = {110,170};
    verifica("erro teste_txProtocolo2 : deveria retornar STX",
             getTxBuffer(msg2,2)[0] == STX);
    verifica("erro teste_txProtocolo2 : deveria retornar QTX",
             getTxBuffer(msg2,2)[1] == 2);
    verifica("erro teste_txProtocolo2 : deveria retornar MSG0",
             getTxBuffer(msg2,2)[2] == msg2[0]);
    verifica("erro teste_txProtocolo2 : deveria retornar MSG1",
             getTxBuffer(msg2,2)[3] == msg2[1]);
    verifica("erro teste_txProtocolo2 : deveria retornar CHCKSUM",
             getTxBuffer(msg2,2)[4] == (unsigned char)(msg2[0] + msg2[1]));
    verifica("erro teste_txProtocolo2 : deveria retornar ETX",
             getTxBuffer(msg2,2)[5] == ETX);

    unsigned char msg3[3] = {50,200,5};
    verifica("erro teste_txProtocolo3 : deveria retornar STX",
             getTxBuffer(msg3,3)[0] == STX);
    verifica("erro teste_txProtocolo3 : deveria retornar QTX",
             getTxBuffer(msg3,3)[1] == 3);
    verifica("erro teste_txProtocolo3 : deveria retornar MSG0",
             getTxBuffer(msg3,3)[2] == msg3[0]);
    verifica("erro teste_txProtocolo3 : deveria retornar MSG1",
             getTxBuffer(msg3,3)[3] == msg3[1]);
    verifica("erro teste_txProtocolo3 : deveria retornar MSG2",
             getTxBuffer(msg3,3)[4] == msg3[2]);
    verifica("erro teste_txProtocolo3 : deveria retornar CHCKSUM",
             getTxBuffer(msg3,3)[5] == (unsigned char)(msg3[0] + msg3[1] + msg3[2]));
    verifica("erro teste_txProtocolo3 : deveria retornar ETX",
             getTxBuffer(msg3,3)[6] == ETX);
    return 0;
}

/*
 * Funcao que executa todas as funcoes acima, uma a uma.
 */
static char * executa_testes(void){
    executa_teste(teste_chkdata);
    executa_teste(teste_getdata);
    executa_teste(teste_rxProtocolo);
    executa_teste(teste_rxProtocolo_failChkSum);
    executa_teste(teste_rxProtocolo_failQtd);
    executa_teste(teste_rxProtocolo_failSTX);
    executa_teste(teste_rxProtocolo_failETX);
    executa_teste(teste_txProtocolo);
    return 0;
}