#include <stdio.h>
#include <drv/apbuart.h>
#include "include/uart.h"

uint32_t u32ApbuartSendString(struct apbuart_priv *pxDevice, char strStringSend[U32_MAX_STRING], uint32_t u32Wait){

/* Inicializa as variáveis */

	uint32_t u32StrLen, u32Cont, u32Confirm, u32StatusRegister;
   uint32_t u32Tries = 0;
   uint32_t u32SendTrue;

/* Contabiliza o número de bytes da string */

	u32StrLen = sizeof(strStringSend);

/* Realiza um laço de repetição para envio de byte a byte */

	for(u32Cont = 0; u32Cont < u32StrLen; u32Cont++){

/* Enquanto o byte não for enviado, continua no laço de repetição*/

       while(!apbuart_outbyte(pxDevice, strStringSend[u32Cont])){

          u32Tries++;

		  if(u32Tries == U32_MAX_STRING){

             return 0;

		  }

	   }

	}

/* Aguarda a transmissão da informação -> FIFO e Shift Register vazios, caso bWait seja setado */

    if(u32Wait){

       do{

          u32StatusRegister = apbuart_get_status(pxDevice);
          
          u32StatusRegister = u32StatusRegister & U32_UART_TX_FINISHED;

        }while(statsRegister != U32_UART_TX_COMPARE);

	}

	return 1;
}


// uint32_t u32ApbuartReceiveString(struct apbuart_priv *pxDevice, char strStringReceive[U32_MAX_STRING], char cStopByte, uint32_t u32StringReceiveLength, bool bWait){

//     /* Inicializa as variáveis */
// 	uint32_t u32Cont = 0, u32StatusRegister;
// 	int32_t i32Confirm;

//     /* Limpa a string de recebimento */
//     strcpy(strStringReceive,"");

//     /* Se o tamanho da string a ser recebida for maior que o estipulado pelo código, retorna 0*/
//     if(u32StringReceiveLength > U32_MAX_STRING){

// 		return (0);

// 	}

//     /* Laço de repetição de recebimento de cada caractere*/
// 	for(u32Cont = 0; u32Cont < u32StringReceiveLength; u32Cont++){

//        /* Pulling para recebimento de um único caractere */
//        do{

//           i32Confirm = apbuart_inbyte(pxDevice);

// 	   } while(i32Confirm == -1);

//        /* Se o caractere for o stopByte passado na função, então para o recebimento de caracteres*/
// 	   if((char) i32Confirm == cStopByte){

//           break;

// 	   }
    
// 	   /* Adiciona o caractere recebido à string de recebimento*/
//       *(strStringReceive + strlen(strStringReceive) + 1) = '\0';
// 	   *(strStringReceive + strlen(strStringReceive)) = (char) i32Confirm;

// 	}

//     /* Se bWait for setado, aguarda o recebimento de toda a informação antes do término da função */
//     if(bWait){

//        do{

//           u32StatusRegister = apbuart_get_status(pxDevice);
          
//           u32StatusRegister = u32StatusRegister & U32_UART_RX_FINISHED;

//        }while(u32StatusRegister != U32_UART_RX_COMPARE);

// 	}

//     /* Retorna o tamanho da string recebida */
// 	return (u32Cont);
// }

// void apbtToApbtString(struct apbuart_priv *pxDeviceSend, struct apbuart_priv *pxDeviceReceive, char strStringSend[U32_MAX_STRING], char strStringRecv[U32_MAX_STRING], bool bWait){

//    /* Inicializa as variáveis */
//    uint32_t u32Cont, u32StatusRegister;
//    int32_t i32Confirm;

//    /* Envio e recebimento de cada caractere */
//    for(u32Cont = 0; u32Cont < strlen(strStringSend); u32Cont++){

//       /* Enquanto o caractere não é enviado, repete a função de envio de dados */
//       while(apbuart_outbyte(pxDeviceSend, strStringSend)){}

//       /* Enquanto o caractere não é recebido, repete a função de recebimento de dados */
//       i32Confirm = -1;

// 	   while(i32Confirm == -1){

//          i32Confirm = apbuart_inbyte(pxDeviceReceive);

// 	   }

//       /* Insere o caractere recebido na string de recebimento */
//       *(strStringReceive + strlen(strStringReceive) + 1) = '\0';
// 	   *(strStringReceive + strlen(strStringReceive)) = (char) i32Confirm;

//    }

//    /* Se o bWait estiver setado, então aguarda a transmissão e recebimento da string */
//    if(bWait){

//       do{

//          u32StatusRegister = apbuart_get_status(pxDeviceSend);
          
//          u32StatusRegister = u32StatusRegister & U32_UART_TX_FINISHED;

//       }while(u32StatusRegister != U32_UART_TX_COMPARE);

//       do{

//          u32StatusRegister = apbuart_get_status(pxDeviceReceive);
          
//          u32StatusRegister = u32StatusRegister & U32_UART_RX_FINISHED;

//       }while(u32StatusRegister != U32_UART_RX_COMPARE);

// 	}

// 	return;

// }

char chrCipherCaesar(char charOriginal, uint32_t u32NumOffset){

   /* Definição de variáveis úteis à função */
   int u32Cont = 0;
   int u32CharIndex;

   /* Definição do array de caracteres a serem usados na cifra de César */
   char strCharacters[] = {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9'};

   /* 'Achamento' do índice na string strCharacters do charOriginal */
   while(strCharacters[u32Cont] != charOriginal){

      u32Cont++;

   }

   /* Armazenamento do índice encontrado na variável u32CharIndex */
   u32CharIndex = u32Cont;

   /* 'Achamento' do charTransf a partir do índice, da string de caracteres e do u32NumOffset informado */
   charTransf = strCharacters[(u32CharIndex + u32NumOffset) % (u32int_t) sizeof(strCharacters)]


   return (charTransf);
}

void CicleLoopTransf(struct apbuart_priv *pxDevice[U32_MAX_DEVICE]){

   /* Definição de variáveis úteis à função */
   char charStopByte = '!';
   char charReceive, charBuffer[U32_MAX_DEVICE][U32_MAX_STRING];
   uint32_t u32Cont = 0;
   uint32_t u32BufferCont[U32_MAX_DEVICE], u32StopByteFalse;

   /* Preenchimento do contador de buffer de cada device com zeros */
   for(u32Cont = 0; u32Cont < U32_MAX_DEVICE; u32Cont++){

      u32BufferCont[u32Cont] = 0;

   }
 
   /* Reset da variável de contagem da função e da variável booleana de stopbyte */
   u32Cont = 0;

   /* Ciclo de recebimento e bufferização dos dados*/
   while(1){

      if(pxDevice[u32Cont] != NULL){ /* Se o ponteiro onde o contador estiver representando uma estrutura designada */

         charReceive = apbuart_inbyte(pxDevice[u32Cont]); /* Recebe um caractere armazenado na FIFO da APBUART */

         if(charReceive == charStopByte){ /* Se o caractere for o charStopByte, então não armazena no buffer, envia dados armazenados, reseta contador de buffer do device e continua */

            u32ApbuartSendString(pxDevice[u32Cont], charBuffer[u32Cont], 0);
            u32BufferCont[u32Cont] = 0;
            u32Cont = (u32Cont + 1) % U32_MAX_DEVICE

         }

         else{ /* Se o caractere não for o charStopByte, então armazena o caractere no buffer da APBUART atual, aumenta o contador do buffer e aumenta o contador da APBUART*/

            charBuffer[u32Cont] = (char) charReceive;
            u32BufferCont[u32Cont]++;
            u32Cont = (u32Cont + 1) % U32_MAX_DEVICE

         }

      }

      else{ /* Se o ponteiro onde o contador estiver não estiver representando uma APBUART designada, reinicia a contagem */

         u32Cont = 0;

      }

}


}








