#include <s3c6410.h>
#include "uart.h"

#define TX_BUF_LEN   2048
#define RX_BUF_LEN   2048

static unsigned char txbuf[2048];
static unsigned int r_tx_idx = 0;
static unsigned int w_tx_idx = 0;

void uart_tx_int_enable(void)
{
    UINTM0 &= ~(1<<2);	
}

void uart_tx_int_disable(void)
{
    UINTM0 |= (1<<2);	
}

static int is_tx_full(void)
{
    if ((w_tx_idx + 1) % TX_BUF_LEN == r_tx_idx)
	return 1;
    else
	return 0;
}

static int is_tx_empty(void)
{
    return (w_tx_idx == r_tx_idx);
}

static int tx_put_data(unsigned char data)
{
    if (is_tx_full()){
	return -1;
    } else {
	txbuf[w_tx_idx] = data;
	w_tx_idx = (w_tx_idx + 1) % TX_BUF_LEN;
	return 0;
    }
}

static int tx_get_data(unsigned char *pdata)
{
    if (is_tx_empty()){
	return -1;
    } else {
	*pdata = txbuf[r_tx_idx];
	r_tx_idx = (r_tx_idx + 1) % TX_BUF_LEN;
	return 0;
    }
}

void uart_putc(const char c)
{
    tx_put_data(c);
    lcd_putc(c);
    if(c == '\n'){
    	tx_put_data('\r');
	lcd_putc('\r');
    }
    uart_tx_int_enable();
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
    GPACON |= 0x22;
	
    /* ULCON0 */
    ULCON0 = 0x3;
    UCON0  = 0x5 | (1<<9);
    /* FIFO enable, tx fifo trigger level = 16 bytes */
    UFCON0 = 0x07 | (1<<6);
    UMCON0 = 0;
	
    /* DIV_VAL = (PCLK / (bps x 16 ) ) - 1 
     * bps = 57600
     * DIV_VAL = (66500000 / (115200 x 16 ) ) - 1 
     *         = 35.08
     */
    UBRDIV0   = 35;

    /* x/16 = 0.08
     * x = 1
     */
    UDIVSLOT0 = 0x1;
}

void do_uart_irq(void)
{
    int i;
    int cnt;
    unsigned char c;
	
    if(UINTP0 & (1<<2)){
	if(is_tx_empty()){
	    uart_tx_int_disable();
	} else {
	    cnt = (UFSTAT0 >> 8) & 0x3f;
	    cnt = 64 - cnt;
	    for(i = 0; i < cnt; i++){
		if(tx_get_data(&c) == 0){
		    UTXH0 = c;
		} else {
		    break;
		}
	    }
	}
    } else if(UINTP0 & (1<<0)){
        
    }

    UINTP0 = 0xf;
}
