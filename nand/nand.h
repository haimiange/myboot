#ifndef _NAND_H_
#define _NAND_H_

extern void nand_read(unsigned int addr,unsigned char *buf,int len);
extern void nand_init();
extern void copy_from_nand(unsigned int src,unsigned int des,int len);

#endif
