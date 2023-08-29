#include <stdio.h>
#include <unistd.h>
#include <drv/apbuart.h>
#include "include/uart.h"
#include <string.h>


#define MAX_STRING 100


int main(void){

	struct apbuart_priv *device;
	int data;
	int i;
	uint32_t status;
	struct apbuart_config cfg;
	char string_send[MAX_STRING];

	apbuart_autoinit(); // Inicializa os drivers referentes às APBUARTs

	device = apbuart_open(0);  // Abre a UART 0 disponível na placa

	if (!device)
	{
		printf("DEVICE ERROR\n");
		return -1; /* Failure */
	}

	/* Device 1 */
	cfg.baud = 9600;
	cfg.parity = APBUART_PAR_NONE; // UART_PAR_NONE
	cfg.flow = 0;
	cfg.mode = APBUART_MODE_NONINT; //UART_MODE_NONINT
	/* SW FIFO parameters are not used in non-interrupt mode. */
	apbuart_config(device, &cfg);

	// O programa envia cada letra por vez da string a ser enviada

	strcpy(string_send, "\n\r TESTE VERITAS - UART 1 PARA 2 - POC2");

	for(i = 0; i < strlen(string_send); i++){

		data = 0;

		while (data != 1) {
			data = apbuart_outbyte(device,string_send[i]);
		}

	}

	while(((apbuart_get_status(device) & 0x00000006) >> 1) != 0x00000003){}

	apbuart_close(device);

	return 0; /* success */

}


