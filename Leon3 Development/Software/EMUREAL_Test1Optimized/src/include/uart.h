#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

#define U32_MAX_STRING 300

#define U32_UART_TX_FINISHED (1 << 1) | (1 << 2)
#define U32_UART_TX_COMPARE 6
#define U32_UART_RX_FINISHED (0b111111 << 26)
#define U32_UART_RX_COMPARE 0

uint32_t u32ApbuartSendString(struct apbuart_priv *pxDevice, char strStringSend[U32_MAX_STRING], uint32_t bWait);
// Função para enviar uma string pelo canal serial

uint32_t u32ApbuartReceiveString(struct apbuart_priv *pxDevice, char strStringReceive[U32_MAX_STRING], char cStopByte, uint32_t u32StringReceiveLength, uint32_t bWait);
// Função para receber uma string a partir do canal serial
// Para cntrl = 0, deve ser informado o número de bytes a serem recebidos a partir da variável stopnumBytes
// Para cntrl = 1, deve ser informado o stop byte da string a ser recebida a partir da variável stopnumBytes

void apbtToApbtString(struct apbuart_priv *pxDeviceSend, struct apbuart_priv *pxDeviceReceive, char strStringSend[U32_MAX_STRING], char strStringRecv[U32_MAX_STRING], uint32_t u32Wait);
// Função de envio e recebimento de strings entre duas APBUARTs

#endif
