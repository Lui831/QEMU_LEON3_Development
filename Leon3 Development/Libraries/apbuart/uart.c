#include <stdio.h>
#include <drv/apbuart.h>
#include <string.h>
#include "include/uart.h"

bool bApbuartSendString(struct apbuart_priv *pxDevice, char strStringSend[MAX_STRING], bool bWait){

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


void apbuartReceiveString(struct apbuart_priv *device, char strReceive[MAX_STRING], uint32_t cntrl, uint32_t stopnumBytes){

/* Inicializa as variáveis */

	uint32_t cont = 0, statsRegister;
	int32_t confirm;
    const uint32_t mask = (0b111111 << 26);

    strcpy(strReceive,"");

/* Dita a maneira de recebimento da string a partir da variável 'control' */

	switch(cntrl){

/* Para o caso 0, limita o recebimento da string pelo número de bytes informado */

	  case 0:

	     	for(cont=0;cont < stopnumBytes;cont++){

          	  confirm = -1;

/* Enquanto não recebe o byte, continua no laço de repetição*/

          	  while(confirm == -1){

          		 confirm = apbuart_inbyte(device);

          	  }

/* Adiciona os byte à string pela passagem por referência*/

	         *(strReceive + strlen(strReceive) + 1) = '\0';

	         *(strReceive + strlen(strReceive)) = (char) confirm;
		}

	     	break;

/* Para o caso 1, limita o recebimento da string pelo stopbyte informado */

	  case 1:

	     	do{

          	  confirm = -1;
			  
/* Enquanto não recebe o byte, continua no laço de repetição*/			  

          	  while(confirm == -1){
				
			     confirm = apbuart_inbyte(device);

			  }

/* Adiciona o byte à string pela passagem por referência*/

              *(strReceive + strlen(strReceive) + 1) = '\0';

	          *(strReceive + strlen(strReceive)) = (char) confirm;

              cont++;

	        }while(confirm != stopnumBytes);

	     	break;

	}

/* Aguarda o recebimento da informação -> FIFO e Shift Register vazios */


        do{

          statsRegister = apbuart_get_status(device);
          
          statsRegister = statsRegister & mask;

        }while(statsRegister != 0);
	

	return;    
}

void apbtToApbtString(struct apbuart_priv *deviceSend, struct apbuart_priv *deviceRecv, char strSend[MAX_STRING], char strRecv[MAX_STRING]){

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








