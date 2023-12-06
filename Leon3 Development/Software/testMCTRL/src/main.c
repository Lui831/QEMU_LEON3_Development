/* Inclusão de bibliotecas */

#include <stdio.h>



/* Função main */

int main(void){

/* Definição de algum ponteiro para a região da memória da ahbram definida */
uint32_t *u32pont1 = 0xA0000000;
uint32_t *u32pont2 = 0xA0000004;
uint32_t *u32pont3 = 0xA0000008;
uint32_t *u32pont4 = 0xA000000C;
uint32_t *u32pont5 = 0xA0000010;
uint32_t *u32pont6 = 0xA0000014;
uint32_t *u32pont7 = 0xA0000018;
uint32_t *u32pont8 = 0xA000001C;
uint32_t *u32pont9 = 0xA0000020;



/* Input de algum valor arbitrário naquele endereço de memória */
*(u32pont1) = 0xF;
*(u32pont2) = 0xA;
*(u32pont3) = 0xC;
*(u32pont4) = 0xC;
*(u32pont5) = 0xF;
*(u32pont6) = 0xA;
*(u32pont7) = 0xC;
*(u32pont8) = 0xC;
*(u32pont9) = 0xF;

return 1;

}



