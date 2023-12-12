/* Inclusão de bibliotecas */

#include <stdio.h>
#include <drv/apbuart.h>
#include "include/uart.h"
#include <string.h>



/* Função main */

int main(void){

/* 	Declaração das variáveis principais */

	struct apbuart_priv* oDevice;
	struct apbuart_config oConfig;
	char strSend[U32_MAX_STRING], strReceive[U32_MAX_STRING];
	
	uint32_t iAddress;
	uint32_t iNum;
	uint32_t *iPont;
	uint32_t status;

/* Inicialização dos drivers das APBUARTs e inicialização das APBUARTs */

	apbuart_autoinit();
    oDevice = apbuart_open(0);

/* Configurações das APBUARTs */

	oConfig.baud = 115200; /* Baud rate configurado para cada uma das APBUARTs */
	oConfig.parity = APBUART_PAR_NONE; /* Desativa paridade */
	oConfig.flow = 0; /* Desativa controle de fluxo */
	oConfig.mode = APBUART_MODE_NONINT; /* Non blocking mode */
	oConfig.rxfifobuflen = 10; /* 10 bytes para o buffer da fifo de recebimento */
	apbuart_config(oDevice, &oConfig);

/* Loop de recebimento, transformação e envio de strings */

    while(1){

    	status = apbuart_get_status(oDevice);
       /* Se, para a UART em questão, DR estiver pronto, então continue */
       if((apbuart_get_status(oDevice)) & (U32_DR_MASK) != U32_DR_COMPARE){

          /* Recebe string, a qual representa o endereço a ser armazenado. */
          apbuartReceiveString(oDevice, strReceive, 1, 0x21);
          /* Tranforma string recebida de endereço a ser armazenado */
          iAddress = (uint32_t)atoi(strReceive);
          /* Recebe string, a qual representa o valor a ser armazenado */
          apbuartReceiveString(oDevice, strReceive, 1, 0x21);
          /* Transforma a string recebida de valor a ser armazenado */
          iNum = (uint32_t)atoi(strReceive);
          /* Armazena o número no endereço indicado */
          iPont = (uint32_t*)iAddress;
          *iPont = iNum;
          /* Cria uma string de envio para o código de teste */
          sprintf(strSend, "%li!%li", *iPont, iNum);
          /* Envia strSend para o código de teste */
          apbuartSendString(oDevice, strSend);

       }

	}

	return 0;
}



