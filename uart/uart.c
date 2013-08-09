#include <s3c6410.h>
#include "uart.h"

void uart_putc(const char c)
{
    /* 如果TX FIFO 满等待 */
    while(UFSTAT0 & (0x1<<14));
    UTXH0 = c;
    if(c == '\n'){
	uart_putc('\r');
    }
}

char uart_getc()
{
    unsigned char c;

    /* 如果RX FIFO 空等待 */
    while(!(UFSTAT0 & 0x7f));
    c = URXH0;
    return c;
}

int uart_getc_nowait(char *c)
{
    if(!(UFSTAT0 & 0x7f)){
	return -1;
    } else {
	*c = URXH0;
	return 0;
    }
}

void uart_init()
{
    GPACON &= ~0xff;
    GPACON |= (0x2 | (0x2<<4));
    
    /* ULCON0 UCON0 UFCON0 UBRDIV0 UDIVSLOT0 */
    ULCON0 = 0x3;
    UCON0 = (0x2<<10)|(0x1<<2)|(0x1<<0);
    UFCON0 = 0x7;
    UBRDIV0 = 35;
    UDIVSLOT0 = 1;
}
