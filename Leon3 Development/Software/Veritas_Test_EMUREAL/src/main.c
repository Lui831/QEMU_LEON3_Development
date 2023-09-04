/* Inclusão de bibliotecas */

#include <stdio.h>
#include <drv/apbuart.h>
#include <string.h>
#include "include/uart.h"

int main(void){

/* 	Declaração das variáveis principais */

	struct apbuart_priv *device;
	struct apbuart_config cfg;
	char strSend[MAX_STRING], strReceive[MAX_STRING], strAdd[] = "Hello again!";

/* Inicialização dos drivers da APBUART e inicialização da APBUART 0 */

	apbuart_autoinit();

	device = apbuart_open(0);

	if (!device)
	{
		printf("DEVICE ERROR\n");
		return -1;
	}

/* Configurações da APBUART */

	cfg.baud = 9600;
	cfg.parity = APBUART_PAR_NONE; // UART_PAR_NONE
	cfg.flow = 0;
	cfg.mode = APBUART_MODE_NONINT; //UART_MODE_NONINT

	apbuart_config(device, &cfg);

/* Recebimento dos dados */

   apbuartReceiveString(device,strReceive,1,0x21);

/* Transformação da massa de dados recebida */

    sprintf(strSend, "%s , %s", strReceive, strAdd);

/* Reenvio da massa de dados transformada */

    apbuartSendString(device,strSend);

/* Fechamento do APBUART aberta */

	apbuart_close(device);

	return 0;
}


