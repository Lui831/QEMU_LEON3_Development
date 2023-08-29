#include <stdio.h>
#include <drv/apbuart.h>
#include "include/uart.h"
#include <string.h>

#define MAX_STRING 100


int main(void){

	struct apbuart_priv *device;
	struct apbuart_priv *device2;
	int count;
	int data;
	int i;
	struct apbuart_config cfg;
	struct apbuart_config cfg2;
	char string_send[MAX_STRING], string_receive[MAX_STRING];

	apbuart_autoinit();

	count = apbuart_dev_count();

	device = apbuart_open(0);  // PORTA 0 - UART 0
	device2 = apbuart_open(1); // PORTA 1 - UART 1

	if (!device)
	{
		printf("DEVICE ERROR\n");
		return -1; /* Failure */
	}

	if (!device2)
	{
		printf("DEVICE 2 ERROR\n");
		return -1; /* Failure */
	}

	/* Device 1 */
	cfg.baud = 9600;
	cfg.parity = APBUART_PAR_NONE; // UART_PAR_NONE
	cfg.flow = 0;
	cfg.mode = APBUART_MODE_NONINT; //UART_MODE_NONINT
	/* SW FIFO parameters are not used in non-interrupt mode. */
	apbuart_config(device, &cfg);

	/* Device 2 */
	cfg2.baud = 9600;
	cfg2.parity = APBUART_PAR_NONE; // UART_PAR_NONE
	cfg2.flow = 0;
	cfg2.mode = APBUART_MODE_NONINT; //UART_MODE_NONINT
	/* SW FIFO parameters are not used in non-interrupt mode. */
	apbuart_config(device2, &cfg2);

	//SEND AND RECEIBE BITES

	strcpy(string_send, "\n\r TESTE VERITAS - UART 1 PARA 2 - POC2");

	for(i = 0; i < strlen(string_send); i++){

		data = 0;

		while(data != 1) data = apbuart_outbyte(device,string_send[i]);

		data = -1;

	    while(data == -1) data = apbuart_inbyte(device2);

	    string_receive[i] = data;

	}

	sprintf(string_send,"\n\r STRING RECEIVED: %s",string_receive);

	for(i = 0; i < strlen(string_send); i++){

		data = 0;

		while(data != 1) data = apbuart_outbyte(device2,string_send[i]);

		data = -1;

	    while(data == -1) data = apbuart_inbyte(device);

	    string_receive[i] = data;

	}

	getchar();

	//ENDOFTEST
	apbuart_close(device);
	apbuart_close(device2);


	return 0; /* success */
}


