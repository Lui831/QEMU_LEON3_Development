/* Inclusão de bibliotecas */

#include <stdio.h>
#include <drv/apbuart.h>
#include <string.h>
#include "include/uart.h"

int main(void){

/* 	Declaração das variáveis principais */

	struct apbuart_priv *device1, *device2;
	struct apbuart_config cfg1, cfg2;
	char strSend[MAX_STRING], strReceive[MAX_STRING];

	uint32_t u32NumTest = 25;
    uint32_t u32NumBytes = 50;
	uint32_t u32Cont;

/* Inicialização dos drivers da APBUART e inicialização da APBUART 0 */

	apbuart_autoinit();

	device1 = apbuart_open(0);
	device2 = apbuart_open(1);

	if (!device1)
	{
		printf("DEVICE ERROR\n");
		return -1;
	}

	if (!device2)
	{
		printf("DEVICE ERROR\n");
		return -1;
	}

/* Configurações das APBUARTS */

	cfg1.baud = 9600;
	cfg1.parity = APBUART_PAR_NONE; // UART_PAR_NONE
	cfg1.flow = 0;
	cfg1.mode = APBUART_MODE_NONINT; //UART_MODE_NONINT

	cfg2.baud = 9600;
	cfg2.parity = APBUART_PAR_NONE; // UART_PAR_NONE
	cfg2.flow = 0;
	cfg2.mode = APBUART_MODE_NONINT; //UART_MODE_NONINT

	apbuart_config(device, &cfg1);
	apbuart_config(device, &cfg2);

/* Loop de recebimento de envio de informações */

    for(cont = 0; cont < numTest; cont++){

       apbuartReceiveString(device1, strReceive, 0, u32NumBytes);
	   strcpy(strSend, strReceive);

	   apbuartSendString(device2, strSend);

	}

/* Close das 3 APBUARTs em execução*/

	apbuart_close(device1);
	apbuart_close(device2);

	return 0;
}



