/* Inclusão de bibliotecas */

#include <stdio.h>
#include <drv/apbuart.h>
#include <string.h>
#include "include/uart.h"

/* Protótipos de funções importantes ao código */

int iFindChar(char str[MAX_STRING], char chr);

void CipherCaesar(char str[MAX_STRING], char strTransformed[MAX_STRING], int numOffset);

int main(void){

/* 	Declaração das variáveis principais */

	struct apbuart_priv *device;
	struct apbuart_config cfg;
	char strSend[MAX_STRING], strReceive[MAX_STRING];
	int numTest = 10, cont;

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

/* Loop de recebimento, transformação e envio de strings */

    for(cont = 0; cont < numTest; cont++){

       apbuartReceiveString(device, strReceive, 0, 10);

       CipherCaesar(strReceive, strSend, 0);

	   apbuartSendString(device, strReceive);

	}

	apbuart_close(device);

	return 0;
}

/* Definição de funções importantes ao código */

int iFindChar(char str[MAX_STRING], char chr){
/* Desc: Função utilizada para encontrar a primeira ocorrência de um caractere em uma string.
   Return: index onde o caracter foi encontrado.
   Parameters: str --> String onde o caracter será procurado.
               chr --> Caractere a ser procurado

*/

    int cont = 0;
	int index;

	for(cont = 0; cont < strlen(str) ; cont++){

       if(str[cont] == chr){

          index = cont;

		  break;

	   }


	}

	return index;
}

void CipherCaesar(char str[MAX_STRING], char strTransformed[MAX_STRING], int numOffset){
/* Desc: Função utilizada para transformar uma string por meio da Cifra de César.
   Return: (-)
   Parameters: str --> String a ser transformada.
               strTransformed --> String onde será armazenada a string transformada.
			   numOffset --> Offset usado na Cifra de César.
*/
 
    char characters[MAX_STRING] = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	int cont = 0, iChar, tIChar;

	strcpy(strTransformed, "");

    for(cont = 0; cont < strlen(str); cont++){

       iChar = iFindChar(characters, str[cont]);

	   tIChar = (iChar + numOffset) % strlen(characters);
	   
	   sprintf(strTransformed,"%s%c", strTransformed, characters[tIChar]);

	}

	return;
}


