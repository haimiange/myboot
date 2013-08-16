#include <s3c6410.h>
#include "irq.h"

void eint0_3_irq()
{
    int i;

    printf("eint0_3_irq: \n");
    for(i = 0; i < 4;i++){
	if(EINT0PEND & (1<<i)){
	    if(GPNDAT & (1<<i)){
		printf("K%d release\n",i+1);
	    } else {
		printf("K%d pressed\n",i+1);
	    }
	}
    }
}

void eint4_11_irq()
{
    int i;

    printf("eint4_11_irq: \n");
    for(i = 0; i < 4;i++){
	if(EINT0PEND & (1<<i)){
	    if(GPNDAT & (1<<i)){
		printf("K%d release\n",i+4);
	    } else {
		printf("K%d pressed\n",i+4);
	    }
	}
    }
}

void key_irq_init()
{
    /* 设置按键为中断方式 */
    GPNCON &= ~(0xfff);
    GPNCON |= 0xaaa;

    /* 设置为双边缘触发 */
    EINT0CON0 &= ~(0xfff);
    EINT0CON0 |= 0x777;

    /* 使能按键中断 */
    EINT0MASK &= ~(0x3f);

    /* 使能中断控制器中的按键中断 */
    VIC0INTENABLE |= (0x3);

    VIC0VECTADDR0 = eint0_3_irq;
    VIC0VECTADDR1 = eint4_11_irq;
}

void uart_irq()
{
    /* 调用UART中断处理函数 */
    do_uart_irq();
    /* 清空UART中断 */
    VIC1ADDRESS = 0;
}

void uart_irq_init()
{
    /* 使能UART中断 */
    VIC1INTENABLE |= (1<<5);
    /* 设置中断处理函数 */
    VIC1VECTADDR5 = uart_irq;
}

void irq_init()
{
    key_irq_init();
    uart_irq_init();
}

void do_irq()
{
    void (*the_isr)(void);

    if(VIC0IRQSTATUS != 0){
	the_isr = VIC0ADDRESS;
	the_isr();
	EINT0PEND = 0x3f;
	VIC0ADDRESS = 0;
    } else if(VIC1IRQSTATUS != 0){
    	the_isr = VIC1ADDRESS;
    	the_isr();
    }
}

