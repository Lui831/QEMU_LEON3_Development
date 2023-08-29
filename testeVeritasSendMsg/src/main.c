#include <stdio.h>
#include <drv/apbuart.h>
#include "include/uart.h"

int main(void){

	struct apbuart_priv *device;
	struct apbuart_priv *device2;
	int count;
	int data;
	struct apbuart_config cfg;
	struct apbuart_config cfg2;

	printf("VERISTAS_POC2\n\n");


	apbuart_autoinit();

	count = apbuart_dev_count();
	printf("%d APBUART devices present\n\n", count);

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

	///SEND
	printf("SEND\n");
	sendmsg(device, "Teste Device 1 - NSEE-IMT - Projeto Veritas - POC2\n\r");
	apbuart_drain(device);

	///SEND TEST DEVICE 2
	printf("SEND\n");
	sendmsg(device2, "Teste Device 1 - NSEE-IMT - Projeto Veritas - POC2\n\r");
	apbuart_drain(device2);

	//RECEIVE
	printf("\n");
	printf("RECEIVE\n");

	do {
		data = -1;
		do {data = apbuart_inbyte(device);} while (data < 0);
		printf("0x%x [1]\n", data);
		data = -1;
		do {data = apbuart_inbyte(device2);} while (data < 0);
		printf("0x%x [2]\n", data);
	} while (data != 0x55);

	//ENDOFTEST
	printf(".\n");
	printf("ENDOFTEST\n");
	apbuart_close(device);
	apbuart_close(device2);

	return 0; /* success */
}
