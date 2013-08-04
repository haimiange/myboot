#include "s3c6410.h"
#include "led.h"

void led_on(int num)
{
    GPMDAT &= ~(0x1<<num);
}

void led_off(int num)
{
    GPMDAT |= (0x1<<num);
}

void led_init()
{
    unsigned int tmp1 = 0;
    unsigned short tmp2 = 0;
    unsigned char tmp3 = 0;
    
    tmp1 = GPMCON;
    tmp1 &= ~0xffff;
    tmp1 |= ((0x1<<0)|(0x1<<4)|(0x1<<8)|(0x1<<12));
    GPMCON = tmp1;

    tmp2 = GPMPUD;
    tmp2 &= ~0xff;
    tmp2 |= ((0x2<<0)|(0x2<<2)|(0x2<<4)|(0x2<<6));
    GPMPUD = tmp2;

    tmp3 = GPMDAT;
    tmp3 &= 0xf;
    GPMDAT = tmp3;
}
