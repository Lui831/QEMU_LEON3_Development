#include <stdio.h>
#include <drv/apbuart.h>
#include "include/uart.h"

void apbuartSendString(struct apbuart_priv *device, char strSend[U32_MAX_STRING]){

/* Inicializa as variáveis */

	uint32_t strLen, cont, confirm, statsRegister;
	const uint32_t mask = (1 << 1) | (1 << 2);

/* Contabiliza o número de bytes da string */

	strLen = strlen(strSend);

/* Realiza um laço de repetição para envio de byte a byte */

	for(cont = 0 ;cont < strLen;cont++){

          confirm = 0;

/* Enquanto o byte não for enviado, continua no laço de repetição*/

          while(confirm != 1){
			
			 confirm = apbuart_outbyte(device, strSend[cont]);
			 
			 }

	}

}

void apbuartReceiveString(struct apbuart_priv *device, char strReceive[U32_MAX_STRING], uint32_t cntrl, uint32_t stopnumBytes){

/* Inicializa as variáveis */

	uint32_t cont = 0, statsRegister;
	int32_t confirm;
    const uint32_t mask = (0b111111 << 26);

/* Dita a maneira de recebimento da string a partir da variável 'control' */

	switch(cntrl){

/* Para o caso 0, limita o recebimento da string pelo número de bytes informado */

	  case 0:

	     	for(cont=0;cont < stopnumBytes;cont++){

          	  confirm = -1;

/* Enquanto não recebe o byte, continua no laço de repetição*/

          	  while(confirm == -1){

          		 confirm = apbuart_inbyte(device);

          	  }

/* Adiciona os byte à string pela passagem por referência*/

	         *(strReceive + strlen(strReceive) + 1) = '\0';

	         *(strReceive + strlen(strReceive)) = (char) confirm;
		}

	     	break;

/* Para o caso 1, limita o recebimento da string pelo stopbyte informado */

	  case 1:

	     	while(1){

          	  confirm = -1;
			  
/* Enquanto não recebe o byte, continua no laço de repetição*/			  

          	  while(confirm == -1){
				
			     confirm = apbuart_inbyte(device);

			  }

/* Se o byte recebido for o do stopbyte, para o recebimento e não inclui o stopbyte na string */

			  if((char) confirm == (char) stopnumBytes){

                 break;

			  }

/* Adiciona o byte à string pela passagem por referência*/

              *(strReceive + strlen(strReceive) + 1) = '\0';

	          *(strReceive + strlen(strReceive)) = (char) confirm;

              cont++;

			};

	     	break;

	}

	return;    
}

void apbtToApbtString(struct apbuart_priv *deviceSend, struct apbuart_priv *deviceRecv, char strSend[U32_MAX_STRING], char strRecv[U32_MAX_STRING]){

/* Inicializa as variáveis */

   uint32_t cont;
   int32_t confirm;

/* Envio e recebimento de cada caractere */

   for(cont = 0; cont < strlen(strSend); cont++){

      confirm = 0;

/* Enquanto o caractere não é enviado, repete a função de envio de dados */

      while(confirm == 0){

         confirm = apbuart_outbyte(deviceSend, strSend[cont]);

      }

	  confirm = -1;

/* Enquanto o caractere não é recebido, repete a função de recebimento de dados */

	  while(confirm == -1){

         confirm = apbuart_inbyte(deviceRecv);

	  }

/* Insere o caractere recebido na string de recebimento */

      strRecv[cont] = confirm;

   }

	return;
}

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








