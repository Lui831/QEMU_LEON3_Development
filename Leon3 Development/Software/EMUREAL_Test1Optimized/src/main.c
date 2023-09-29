/* Inclusão de bibliotecas */

#include <stdio.h>
#include <drv/apbuart.h>
#include <string.h>
#include "include/uart.h"




/* Protótipos de funções importantes ao código */

int iFindChar(char str[U32_MAX_STRING], char chr);

void CipherCaesar(char str[U32_MAX_STRING], char strTransformed[U32_MAX_STRING], int numOffset);




/* Função main */

int main(void){

    /* Declaração das variáveis principais */
	struct apbuart_priv *pxDevice;
	struct apbuart_config pcConfig;
	char strStringSend[U32_MAX_STRING], strStringReceive[U32_MAX_STRING];
	uint32_t u32Cont = 0, u32StringReceiveLength, u32Confirm;

    uint32_t u32NumTest = 1000; /*DIGITE O NÚMERO DE TESTES*/
	uint32_t u32NumOffset = 18; /*DIGITE O OFFSET UTILIZADO NA CIFRA DE CÉSAR*/
	uint32_t u32NumBytes = 10; /*DIGITE O NÚMERO DE BYTES A SEREM ENVIADOS/RECEBIDOS POR TESTE*/

    /* Inicialização dos drivers da APBUART e inicialização da APBUART 0 */
	
	apbuart_autoinit();

	pxDevice = apbuart_open(0);

	if (!pxDevice)
	{
		printf("DEVICE ERROR\n");
		return -1;
	}

    /* Configurações da APBUART */

	pcConfig.baud = 115200;
	pcConfig.parity = APBUART_PAR_NONE;
	pcConfig.flow = 0;
	pcConfig.mode = APBUART_MODE_NONINT;

	apbuart_config(pxDevice, &pcConfig);

    /* Loop de recebimento, transformação e envio de strings */

    for(u32Cont = 0; u32Cont < u32NumTest; u32Cont++){

       u32StringReceiveLength = u32ApbuartReceiveString(pxDevice, strStringReceive,'!',u32NumBytes,1);

       CipherCaesar(strStringReceive, strStringSend, 0);

	   u32Confirm = u32ApbuartSendString(pxDevice, strStringSend, 1);

	}

	apbuart_close(pxDevice);

	return 0;
}




/* Definição de funções importantes ao código */


int iFindChar(char str[U32_MAX_STRING], char chr){
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

void CipherCaesar(char str[U32_MAX_STRING], char strTransformed[U32_MAX_STRING], int numOffset){
/* Desc: Função utilizada para transformar uma string por meio da Cifra de César.
   Return: (-)
   Parameters: str --> String a ser transformada.
               strTransformed --> String onde será armazenada a string transformada.
			   numOffset --> Offset usado na Cifra de César.
*/
 
    char characters[U32_MAX_STRING] = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	int cont = 0, iChar, tIChar;

	strcpy(strTransformed, "");

/* Aplica a cifra de César para cada caractere*/

    for(cont = 0; cont < strlen(str); cont++){

/* Encontra a posição do caractere na string de caracteres*/

       iChar = iFindChar(characters, str[cont]);

/* Aplica o offset sobre a posição*/

	   tIChar = (iChar + numOffset) % strlen(characters);

/* Insere o o caracter transformado na string transformada*/

	   *(strTransformed + strlen(strTransformed) + 1) = '\0';

	   *(strTransformed + strlen(strTransformed)) = characters[tIChar];

	}

	return;
}


