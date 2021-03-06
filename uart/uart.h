#ifndef _UART_H_
#define _UART_H_

extern void uart_putc(const char c);
extern char uart_getc();
extern void uart_init();
extern int uart_getc_nowait(char *c);

#endif
