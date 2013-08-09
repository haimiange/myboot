#ifndef _NAND_H_
#define _NAND_H_

extern int nand_write_page(unsigned int start_addr,unsigned char* buf,int len);
extern int nand_erase_block(unsigned int start_addr);
extern void nand_read(unsigned int addr,unsigned char *buf,int len);
extern void nand_init();
extern void copy2ddr(unsigned int src,unsigned int des,int len);

#endif
