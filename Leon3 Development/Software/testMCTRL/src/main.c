/* Inclusão de bibliotecas */

#include <stdio.h>



/* Função main */

int main(void){

/* Definição de algum ponteiro para a região da memória da ahbram definida */
uint32_t *u32pont1 = 0xA0000000;
uint32_t *u32pont2 = 0xA0000004;


/* Input de algum valor arbitrário naquele endereço de memória */
*(u32pont1) = 0xF;
*(u32pont2) = 0xA;

*(u32pont1) = *(u32pont2);

/* Debuggando, pode-se verificar se o valor foi capaz de ser armazenado ou não */

return 1;

}



