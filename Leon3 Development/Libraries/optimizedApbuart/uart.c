#include <stdio.h>
#include <drv/apbuart.h>
#include <string.h>
#include "include/uart.h"

/* Mascara para saber que todos os dados foram transmitidos pela UART */
#define U32_UART_TX_FINISHED_MASK   ((1 << 1) | (1 << 2))
/* Valor do status da UART (com mascara aplicada) que indica todos os dados foram transmitidos pela UART */
#define U32_UART_TX_FINISHED_STVAL  6

/* Realiza o envio de uma sequência de caracteres pelo UART */
bool bApbuartSendString(struct apbuart_priv *pxDevice, char *strStringToSend, uint32_t u32StringLength, bool bWait)
{

    /* Inicializa as variáveis */
    bool bStatus = false;
    char cTxChar = '/0';
    uint32_t u32StringCnt = 0;

    /* Realiza um laço de repetição para envio de todos os caracteres da String */
    for (u32StringCnt = 0; u32StringCnt < u32StringLength; u32StringCnt++)
    {
        cTxChar = strStringToSend[u32StringCnt];
        /* Tenta colocar o character na FIFO de transmissão até conseguir */
        while (!apbuart_outbyte(pxDevice, cTxChar)) {}
    }

    if (bWait)
    {
        /* Aguarda a transmissão de toda a informação -> RX FIFO e Shift Register vazios */
        while (U32_UART_TX_FINISHED_STVAL != (apbuart_get_status(pxDevice)& U32_UART_TX_FINISHED_MASK)) {}
    }

    bStatus = true;

    return (bStatus);
}

/* Realiza o recebimento de uma sequência de caracteres pelo UART */
uint32_t u32ApbuartReceiveString(struct apbuart_priv *pxDevice, char *strStringToReceive, uint32_t u32StringLength, char cStringEndMarker)
{

    /* Inicializa as variáveis */
    int32_t i32RxChar = -1;
    uint32_t u32StringCnt = 0;

    /* Realiza um laço de repetição para recebimento de todos os caracteres da String (garante que o limite de caracteres será respeitado) */
    for (u32StringCnt = 0; u32StringCnt < (u32StringLength - 1); u32StringCnt++)
    {
        /* Tenta receber o character da FIFO de recepção até conseguir */
        do
            i32RxChar = apbuart_inbyte(pxDevice);
        while (-1 == i32RxChar);
        strStringToReceive[u32StringCnt] = (char)i32RxChar;
        /* Verifica se caracter de fim foi recebido */
        if (cStringEndMarker == (char)i32RxChar)
        {
            /* Sai do for e finaliza o recebimento de dados */
            u32StringCnt++
            break;
        }
    }

    strStringToReceive[u32StringCnt] = '/0';
    bStatus = true;

    return (u32StringCnt);
}
