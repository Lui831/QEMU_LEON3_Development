#include <stdio.h>
#include <drv/apbuart.h>
#include <string.h>
#include "include/uart.h"

bool bApbuartSendString(struct apbuart_priv *pxDevice, char strStringSend[U32_MAX_STRING], bool bWait){

/* Inicializa as variáveis */

	uint32_t u32StrLen, u32Cont, u32Confirm, u32StatusRegister, u32Tries = 0;
    bool bSendTrue;

/* Contabiliza o número de bytes da string */

	u32StrLen = strlen(strStringSend);

/* Realiza um laço de repetição para envio de byte a byte */

	for(u32Cont = 0; u32Cont < u32StrLen; u32Cont++){

/* Enquanto o byte não for enviado, continua no laço de repetição*/

       while(!apbuart_outbyte(pxDevice, strStringSend[u32Cont])){

          u32Tries++;

		  if(u32Tries == MAX_STRING){

             return false;

		  }

	   }

	}

/* Aguarda a transmissão da informação -> FIFO e Shift Register vazios, caso bWait seja setado */

    if(bWait){

       do{

          u32StatusRegister = apbuart_get_status(pxDevice);
          
          u32StatusRegister = u32StatusRegister & U32_UART_TX_FINISHED;

        }while(statsRegister != U32_UART_TX_COMPARE);

	}

	return true;
}


uint32_t u32ApbuartReceiveString(struct apbuart_priv *pxDevice, char strStringReceive[U32_MAX_STRING], char cStopByte, uint32_t u32StringReceiveLength, bool bWait){

    /* Inicializa as variáveis */
	uint32_t u32Cont = 0, u32StatusRegister;
	int32_t i32Confirm;

    /* Limpa a string de recebimento */
    strcpy(strStringReceive,"");

    /* Se o tamanho da string a ser recebida for maior que o estipulado pelo código, retorna 0*/
    if(u32StringReceiveLength > U32_MAX_STRING){

		return (0);

	}

    /* Laço de repetição de recebimento de cada caractere*/
	for(u32Cont = 0; u32Cont < u32StringReceiveLength; u32Cont++){

       /* Pulling para recebimento de um único caractere */
       do{

          i32Confirm = apbuart_inbyte(pxDevice);

	   } while(i32Confirm == -1);

       /* Se o caractere for o stopByte passado na função, então para o recebimento de caracteres*/
	   if((char) i32Confirm == cStopByte){

          break;

	   }
    
	   /* Adiciona o caractere recebido à string de recebimento*/
       *(strStringReceive + strlen(strStringReceive) + 1) = '\0';
	   *(strStringReceive + strlen(strStringReceive)) = (char) i32Confirm;

	}

    /* Se bWait for setado, aguarda o recebimento de toda a informação antes do término da função */
    if(bWait){

       do{

          u32StatusRegister = apbuart_get_status(pxDevice);
          
          u32StatusRegister = u32StatusRegister & U32_UART_RX_FINISHED;

       }while(u32StatusRegister != U32_UART_RX_COMPARE);

	}

    /* Retorna o tamanho da string recebida */
	return (u32Cont);
}

void apbtToApbtString(struct apbuart_priv *deviceSend, struct apbuart_priv *deviceRecv, char strSend[U32_MAX_STRING], char strRecv[U32_MAX_STRING]){

/* Inicializa as variáveis */

   uint32_t cont;
   int32_t confirm;

/* Envio e recebimento de cada caractere */

   for(cont = 0; cont < strlen(strSend); cont++){

      confirm = 0;

/* Enquanto o caractere não é enviado, repete a função de envio de dados */

      while(confirm == 0){

         confirm = apbuart_outbyte(deviceSend, strSend[cont]);

      }

	  confirm = -1;

/* Enquanto o caractere não é recebido, repete a função de recebimento de dados */

	  while(confirm == -1){

         confirm = apbuart_inbyte(deviceRecv);

	  }

/* Insere o caractere recebido na string de recebimento */

      strRecv[cont] = confirm;

   }

	return;
}








