/* Mascara para saber que todos os dados foram transmitidos pela UART */
#define U32_UART_TX_FINISHED_MASK   ((1 << 1) | (1 << 2))
/* Valor do status da UART (com mascara aplicada) que indica todos os dados foram transmitidos pela UART */
#define U32_UART_TX_FINISHED_STVAL  6


bool bApbuartSendString(struct apbuart_priv *pxDevice, char *strStringToSend, uint32_t u32StringLength, bool bWait);
/* Desc: Realiza o envio de uma sequência de caracteres pelo UART
Paramaters: pxDevice -> Ponteiro para a estrutura representando a UART onde será enviada a string
            strStringToSend -> String a ser enviada
            u32StringLength -> Tamanho da string a ser enviada
            bWait -> True: aguarda a transmissão de toda a informação
                     False: não aguarda a transmissão da informação
Return: valor booleano (-)


/* Realiza o recebimento de uma sequ�ncia de caracteres pelo UART */
uint32_t u32ApbuartReceiveString(struct apbuart_priv *pxDevice, char *strStringToReceive, uint32_t u32StringLength, char cStringEndMarker);
/* Desc: realiza o recebimento de uma sequência de caracteres pela UART 
Parameters: pxDevice -> Ponteiro para a estrutura representando a UART onde será recebida a string
            strStringToReceive -> String a ser recebida (passagem por referência)
            u32StringLength -> Tamanho da string a ser recebida
            cStringEndMarker -> Caractere limitador de recebimento da string
Return: valor natural que representa o tamanho efetivo da string recebida
*/
