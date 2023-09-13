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

	struct apbuart_priv *device1, *device2, *device3;
	struct apbuart_config cfg1, cfg2, cfg3;
	char strSend[MAX_STRING], strReceive[MAX_STRING];
	int numTest = 25, numOffset = 18, cont;

/* Inicialização dos drivers da APBUART e inicialização da APBUART 0 */

	apbuart_autoinit();

	device1 = apbuart_open(0);
	device2 = apbuart_open(1);
	device3 = apbuart_open(2);

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

	if (!device3)
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

	cfg3.baud = 9600;
	cfg3.parity = APBUART_PAR_NONE; // UART_PAR_NONE
	cfg3.flow = 0;
	cfg3.mode = APBUART_MODE_NONINT; //UART_MODE_NONINT

	apbuart_config(device1, &cfg1);
	apbuart_config(device2, &cfg2);
	apbuart_config(device3, &cfg3);

/* Loop de recebimento pela APBUART 2, envio pela APBUART 1, recebimento e transformação pela APBUART 0 e reenvio pela APBUART 2 */

    for(cont = 0; cont < numTest; cont++){

       /* APBUART 2 recebe a informação vinda pelo adaptador serial */

       apbuartReceiveString(device1, strReceive, 0, 50);
	   strcpy(strSend, strReceive);

       /* APBUART 1 envia informação recebida para APBUART 0*/

	   apbtToApbtStringRecv(device2, device3, strSend, strReceive);
	   CipherCaesar(strReceive, strSend, numOffset);
	   apbtToApbtStringRecv(device3, device2, strSend, strReceive);

	   strcpy(strSend, strReceive);

       /* APBUART 2 envia informação novamente para o adaptador serial */

	   apbuartSendString(device1, strSend);

	}

/* Close das 3 APBUARTs em execução*/

	apbuart_close(device1);
	apbuart_close(device2);
	apbuart_close(device3);

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

	   *(strTransformed + strlen(strTransformed) + 1) = '\0';

	   *(strTransformed + strlen(strTransformed)) = characters[tIChar];

	}

	return;
}

