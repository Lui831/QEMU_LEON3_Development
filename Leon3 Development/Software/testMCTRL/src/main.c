/* Inclusão de bibliotecas */

#include <stdio.h>
#include <drv/apbuart.h>
#include "include/uart.h"
#include <string.h>



/* Função main */

int main(void){

 uint32_t u32Size = 5;
 uint32_t u32MATRIX[1000][1000];
 uint32_t u32Conti,u32Contj,MCFG1value;
 uint32_t* MCFG1;

MCFG1 = 0x80000F00;
*(MCFG1) = 0x00000180;

return 1;

}



