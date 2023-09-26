#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

#define U32_MAX_STRING 300
#define U32_MAX_DEVICE 6

#define U32_DR_MASK 1
#define U32_DR_COMPARE 1

void apbuartSendString(struct apbuart_priv *device, char strSend[U32_MAX_STRING]);
/* Função para enviar uma string pelo canal serial */

void apbuartReceiveString(struct apbuart_priv *device, char strReceive[U32_MAX_STRING], uint32_t cntrl, uint32_t stopnumBytes);
/* Função para receber uma string a partir do canal serial
 Para cntrl = 0, deve ser informado o número de bytes a serem recebidos a partir da variável stopnumBytes
 Para cntrl = 1, deve ser informado o stop byte da string a ser recebida a partir da variável stopnumBytes */

void apbtToApbtString(struct apbuart_priv *deviceSend, struct apbuart_priv *deviceRecv, char strSend[U32_MAX_STRING], char strRecv[U32_MAX_STRING]);
/* Função de envio e recebimento de strings entre duas APBUARTs */

int iFindChar(char str[U32_MAX_STRING], char chr);
/* Função utilizada para o "achamento" do índice de algum caractere em uma string. Utilizada na CipherCaesar */

void CipherCaesar(char str[U32_MAX_STRING], char strTransformed[U32_MAX_STRING], int numOffset);
/* Função que transforma uma string em outra a partir da Cifra de César*/

#endif
