#include <stdio.h>
#include <drv/apbuart.h>
#include <string.h>
#include "include/uart.h"

void apbuartSendString(struct apbuart_priv *device, char strSend[MAX_STRING]){

/* Inicializa as variáveis */

	uint32_t strLen, cont, confirm, statsRegister;
	const uint32_t mask = (1 << 1) | (1 << 2);

/* Contabiliza o número de bytes da string */

	strLen = strlen(strSend);

/* Realiza um laço de repetição para envio de byte a byte */

	for(cont = 0;cont < strLen;cont++){

          confirm = 0;

          while(confirm != 1) confirm = apbuart_outbyte(device, strSend[cont]); // Enquanto o byte não for enviado, continua no laço de repetição

	}

/* Aguarda a transmissão da informação -> FIFO e Shift Register vazios */

        do{

          statsRegister = apbuart_get_status(device);
          
          statsRegister = statsRegister & mask;

        }while(statsRegister != 6);

	return;
}


void apbuartReceiveString(struct apbuart_priv *device, char strReceive[MAX_STRING], uint32_t cntrl, uint32_t stopnumBytes){

/* Inicializa as variáveis */

	uint32_t cont = 0, confirm, statsRegister;
    const uint32_t mask = (0b111111 << 26);

    strcpy(strReceive,"");

/* Dita a maneira de recebimento da string a partir da variável 'control' */

	switch(cntrl){

/* Para o caso 0, limita o recebimento da string pelo número de bytes informado */

	  case 0:

	     	for(cont=0;cont < stopnumBytes;cont++){

          	  confirm = -1;

          	  while(confirm == -1){
          		 confirm = apbuart_inbyte(device);
          		 strReceive[cont] = confirm;
          	  }
		}

	     	break;

/* Para o caso 1, limita o recebimento da string pelo stopbyte informado */

	  case 1:

	     	do{

          	  confirm = -1;

          	  while(confirm == -1) confirm = apbuart_inbyte(device);

                  strReceive[cont] = confirm;

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





