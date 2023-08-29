#include <stdio.h>
#include <drv\apbuart.h>

int apbuart_nonint_example()
{
 struct apbuart_priv *device;
 int count;
 int i;
 int data;
 struct apbuart_config cfg;
 count = apbuart_dev_count();
 printf("%d APBUART devices present\n", count);
 device = apbuart_open(0);
 if (!device)
 return -1; /* Failure */
 cfg.baud = 38400;
 cfg.parity = APBUART_PAR_NONE;
 cfg.flow = 0;
 cfg.mode = APBUART_MODE_NONINT;
 /* SW FIFO parameters are not used in non-interrupt mode. */
 apbuart_config(device, &cfg);
 i = 0;
 do {
 i = apbuart_outbyte(device, 'a');
 } while (1 != i);
 do {
 data = apbuart_inbyte(device);
 } while (data < 0);
 printf("Received 0x%x\n", data);
 apbuart_close(device);
 return 0; /* success */
}
