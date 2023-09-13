#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

#define MAX_STRING 300

void apbuartSendString(struct apbuart_priv *device, char strSend[MAX_STRING]);
// Função para enviar uma string pelo canal serial

void apbuartReceiveString(struct apbuart_priv *device, char strReceive[MAX_STRING], uint32_t cntrl, uint32_t stopnumBytes);
// Função para receber uma string a partir do canal serial
// Para cntrl = 0, deve ser informado o número de bytes a serem recebidos a partir da variável stopnumBytes
// Para cntrl = 1, deve ser informado o stop byte da string a ser recebida a partir da variável stopnumBytes

void apbtToApbtStringRecv(struct apbuart_priv *deviceSend, struct apbuart_priv *deviceRecv, char strSend[STRING_MAX], char strReceive[STRING_MAX]){

#endif
