#include <s3c6410.h>
#include "nand.h"

#define TACLS  7
#define TWRPH0 7
#define TWRPH1 7
#define PAGESIZE 2048


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

void nand_deselect()
{
    NFCONT |= (1<<1);
}

void nand_write_addr(unsigned int addr)
{
    /* 4K page */
    /* NFADDR = addr & 0xff; */
    /* NFADDR = ((addr >> 8) & 0x1f); */
    /* NFADDR = ((addr >> 13) & 0xff); */
    /* NFADDR = ((addr >> 21) & 0xff); */
    /* NFADDR = ((addr >> 29) & 0x7); */

    /* 2K page */
    NFADDR = addr & 0xff;	/* a0-a7 */
    NFADDR = ((addr >> 8) & 0x7); /* a8-a10 页的大小为2K所以页寻址为11根地址线 */
    NFADDR = ((addr >> 11) & 0xff);
    NFADDR = ((addr >> 19) & 0xff);
    NFADDR = ((addr >> 27) & 0xff);
    
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
    nand_deselect();
}

void nand_read(unsigned int start_addr,unsigned char* buf,int len)
{
    int i = start_addr % PAGESIZE;
    
    nand_select();
    while(len > 0){
	nand_cmd(0x0);
	nand_write_addr(start_addr);
	nand_cmd(0x30);
	nand_ready();
	for(;i < PAGESIZE && len > 0;i++){
	    *buf = read_data();
	    buf++;
	    len--;
	    start_addr++;
	}
	i = 0;
    }
    nand_deselect();
}

int nand_write_page(unsigned int start_addr,unsigned char* buf,int len)
{
    int i = start_addr % PAGESIZE;

    if(i != 0){
	return -1;
    }
    nand_select();
    while(len > 0){
	nand_cmd(0x80);
	nand_write_addr(start_addr);
	for(;i < PAGESIZE && len > 0;i++){
	    write_data(*buf);
	    buf++;
	    start_addr++;
	    len--;
	}
	nand_cmd(0x10);
	nand_ready();
	i = 0;
    }
    nand_deselect();
    
    return 0;
}

int nand_erase_block(unsigned int start_addr)
{
    unsigned int page = 0;

    page = start_addr / PAGESIZE;
    if((start_addr % (PAGESIZE * 128)) != 0){
	return -1;
    }
    nand_select();
    nand_cmd(0x60);
    
    NFADDR = page & 0xff;
    NFADDR = (page >> 8) & 0xff;
    NFADDR = (page >> 16) & 0xff;
    
    nand_cmd(0xd0);
    nand_ready();
    nand_deselect();

    return 0;
}

void nand_init()
{
    /* Xm0CSn[2]引脚设为 nand flash cs0 片选,使用 memory subsystem 端口0 */
    MEM_SYS_CFG &= ~(1<<1);
    NFCONF &= ~((7<<4)|(7<<8)|(7<<12)|(1<<30));
    NFCONF |= ((TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4));
    NFCONT |= 1;
    reset();
}

void copy2ddr(unsigned int src,unsigned int des,int len)
{
    nand_init();
    nand_read(src,des,len);
}
