/*
 * Copyright (c) 2018, Cobham Gaisler AB
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * This example prints a message on the second UART.
 */

/*
 * 0: scan devices using ambapp
 * 1: use GR716 static driver tables
 */
#include <bcc/capability.h>
#ifdef BCC_BSP_gr716
 #define CFG_TARGET_GR716 1
#else
 #define CFG_TARGET_GR716 0
#endif

/*
 * 0: no FIFO debug. Connect a terminal to the external UART pins.
 * 1: APBUART debug FIFO. use with GRMON:
 *      grmon3> foward enable uart1
 */
#ifndef  CFG_FIFO_DEBUG
 #define CFG_FIFO_DEBUG 0
#endif

#ifndef  CFG_UART_INDEX
 #define CFG_UART_INDEX 1
#endif

#ifndef  CFG_UART_BAUD
 #define CFG_UART_BAUD 38400
#endif

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <drv/apbuart.h>
#include <drv/gr716/apbuart.h>




void sendmsg(struct apbuart_priv *dev, const char *str)
{
        while (*str) {
                while (0 == apbuart_outbyte(dev, *str));
                str++;
        }
}

void writemsg(struct apbuart_priv *dev, const char *str)
{
        size_t n = 0;
        size_t count;

        count = strlen(str);
        while (n < count) {
                n += apbuart_write(dev, (const uint8_t *) &str[n], count-n);
        }
}



