/*
 * uart.h
 *
 *  Created on: 12 de mai. de 2023
 *      Author: NSEE
 */

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

void sendmsg(struct apbuart_priv *dev, const char *str);
void writemsg(struct apbuart_priv *dev, const char *str);

#endif /* INCLUDE_UART_H_ */
