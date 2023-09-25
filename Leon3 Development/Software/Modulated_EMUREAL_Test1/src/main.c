/* Inclusão de bibliotecas */

#include <stdio.h>
#include <drv/apbuart.h>
#include <string.h>
#include "include/uart.h"


int iFindChar(char str[MAX_STRING], char chr);

void CipherCaesar(char str[MAX_STRING], char strTransformed[MAX_STRING], int numOffset);


/* Função main */


int main(void){

/* 	Declaração das variáveis principais */

	struct apbuart_priv *device;
	struct apbuart_config cfg;
	char strSend[U32_MAX_STRING], strReceive[U32_MAX_STRING];
	
    uint32_t numTest = 1000; /*DIGITE O NÚMERO DE TESTES*/
	uint32_t numOffset = 1; /*DIGITE O OFFSET UTILIZADO NA CIFRA DE CÉSAR*/
	uint32_t numBytes = 5; /*DIGITE O NÚMERO DE BYTES A SEREM ENVIADOS/RECEBIDOS POR TESTE*/
	uint32_t u32Cont = 0;

	uint32_t cont = 0;

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
	cfg.parity = APBUART_PAR_NONE;
	cfg.flow = 0;
	cfg.mode = APBUART_MODE_NONINT;

	apbuart_config(device, &cfg);

/* Loop de recebimento, transformação e envio de strings */

	struct apbuart_priv* pxDevice[] = {device, NULL, NULL, NULL, NULL, NULL};

    while(1){

    	if(pxDevice[u32Cont] != NULL){

    		if(apbuart_get_status(device) && U32_UART_DR == U32_UART_DR_COMPARE){

    			u32ApbuartReceiveString(pxDevice[u32Cont], strReceive, '!', U32_MAX_STRING, 0);


    		}

    	}



    	else u32Cont = 0;

    }

	apbuart_close(device);

	return 0;
}


