#include <include/s3c6410.h>
#include "nand.h"

#define TACLS  7
#define TWRPH0 7
#define TWRPH1 7


void nand_select()
{
    NFCONT &= ~(1<<1);
}

void nand_cmd(unsigned char cmd)
{
    NFCMMD = cmd;
}

void nand_ready()
{
    while(!(NFSTAT & 1));
}

void nand_unselect()
{
    NFCONT |= (1<<1);
}

void nand_write_addr(unsigned int addr)
{
    unsigned int colum = 0;
    unsigned int page = 0;

    colum = addr % 4096;
    page = addr / 4096;
    NFADDR = (colum & 0xff);
    NFADDR = ((colum >> 8)&0xff);
    NFADDR = (page & 0xff);
    NFADDR = ((page >> 8)&0xff);
    NFADDR = ((page >> 16)&0xff);
}

unsigned char read_data()
{
    return NFDATA;
}

void write_data(unsigned char c)
{
    NFDATA = c;
}

void reset()
{
    nand_select();
    nand_cmd(0xff);
    nand_ready();
    nand_unselect();
}

void nand_read(unsigned int start_addr,unsigned char* buf,int len)
{
    int i = start_addr%4096;
    
    nand_select();
    while(len > 0){
	nand_cmd(0x0);
	nand_write_addr(start_addr);
	nand_cmd(0x30);
	nand_ready();
	for(;i < 4096 && len > 0;i++){
	    *buf = read_data();
	    buf++;
	    len--;
	    start_addr++;
	}
	i = 0;
    }
    nand_unselect();
}

int nand_write_page(unsigned int start_addr,unsigned char* buf)
{
    int i = start_addr%4096;

    if(i != 0){
	return -1;
    }
    nand_select();
    nand_cmd(0x80);
    nand_write_addr(start_addr);
    for(i = 0;i < 4096;i++){
	write_data(*buf);
	buf++;
    }
    nand_cmd(0x10);
    nand_ready();
    nand_unselect();
    
    return 0;
}

int nand_erase_block(unsigned int start_addr)
{
    unsigned int page = 0;

    page = start_addr/4096;
    if((start_addr%(4096*128)) != 0){
	return -1;
    }
    nand_select();
    nand_cmd(0x60);
    NFADDR = page&0xff;
    NFADDR = (page >> 8)&0xff;
    NFADDR = (page >> 16)&0xff;
    nand_cmd(0xd0);
    nand_ready();
    nand_unselect();

    return 0;
}

void nand_init()
{
    /* Xm0CSn[2]引脚设为 nand flash cs0 片选,使用 memory subsystem 端口0 */
    MEM_SYS_CFG &= ~(1<<1);
    NFCONF &= ~((3<<4)|(3<<8)|(3<<12)|(1<<30));
    NFCONF |= ((TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4));
    NFCONT |= 1;
    reset();
}

void copy_from_nand(unsigned int src,unsigned int des,int len)
{
    nand_init();
    nand_read(src,des,len);
}
