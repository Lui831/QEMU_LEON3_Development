/* Inclusão de bibliotecas */

#include <stdio.h>
#include <drv/apbuart.h>
#include "include/uart.h"
#include <string.h>



/* Função main */

int main(void){

/* 	Declaração das variáveis principais */

	struct apbuart_priv* oDevices[U32_MAX_DEVICE];
	struct apbuart_config oConfigs[U32_MAX_DEVICE];
	char strSend[U32_MAX_STRING], strReceive[U32_MAX_STRING];
	
    uint32_t numTest = 1000; /*DIGITE O NÚMERO DE TESTES*/
	uint32_t numOffset = 1; /*DIGITE O OFFSET UTILIZADO NA CIFRA DE CÉSAR*/
	uint32_t u32Cont;
	uint32_t status;

/* Inicialização dos drivers das APBUARTs e inicialização das APBUARTs */

	apbuart_autoinit();

	for(u32Cont = 0; u32Cont < U32_MAX_DEVICE; u32Cont++){

       oDevices[u32Cont] = apbuart_open(u32Cont);

	}

/* Configurações das APBUARTs */

    for(u32Cont = 0; u32Cont < U32_MAX_DEVICE; u32Cont++){

	oConfigs[u32Cont].baud = 9600; /* Baud rate configurado para cada uma das APBUARTs */
	oConfigs[u32Cont].parity = APBUART_PAR_NONE; /* Desativa paridade */
	oConfigs[u32Cont].flow = 0; /* Desativa controle de fluxo */
	oConfigs[u32Cont].mode = APBUART_MODE_NONINT; /* Non blocking mode */
	oConfigs[u32Cont].rxfifobuflen = 10; /* 10 bytes para o buffer da fifo de recebimento */
	apbuart_config(oDevices[u32Cont], &(oConfigs[u32Cont]));

	}

/* Loop de recebimento, transformação e envio de strings */

    u32Cont = 0;

    while(1){

       /* Se, para a UART em questão, DR estiver pronto, então continue */


       if(apbuart_get_status(oDevices[u32Cont]) & U32_DR_MASK != U32_DR_COMPARE){

          /* Recebe string, delimitada pelo caractere de exclamação. Transforma string utilizando a cifra de César. */
          apbuartReceiveString(oDevices[u32Cont], strReceive, 1, 0x21);
		  CipherCaesar(strReceive, strSend, numOffset);
		  apbuartSendString(oDevices[u32Cont], strSend);

       }

	   u32Cont = (u32Cont + 1) % U32_MAX_DEVICE;

	}

	return 0;
}



