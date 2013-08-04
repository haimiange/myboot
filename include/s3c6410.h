#ifndef _S3C6410_H_
#define _S3C6410_H_

/* GPIO */
#define GPACON         (*(volatile unsigned long *)0x7f008000)
#define GPADAT         (*(volatile unsigned char *)0x7f008004)
#define GPAPUD         (*(volatile unsigned short *)0x7f008008)

/* LED */
#define GPMCON         (*(volatile unsigned long *)0x7f008820)
#define GPMDAT         (*(volatile unsigned char *)0x7f008824)
#define GPMPUD         (*(volatile unsigned short *)0x7f008828)

/* NAND */
#define MEM_SYS_CFG    (*(volatile unsigned short *)0x7e00f120)
#define NFCONF         (*(volatile unsigned long *)0x70200000)
#define NFCONT         (*(volatile unsigned long *)0x70200004)
#define NFCMMD         (*(volatile unsigned char *)0x70200008)
#define NFADDR         (*(volatile unsigned char *)0x7020000c)
#define NFDATA         (*(volatile unsigned char *)0x70200010)
#define NFSTAT         (*(volatile unsigned char *)0x70200028)

/* UART */
#define ULCON0         (*(volatile unsigned char *)0x7F005000)
#define UCON0          (*(volatile unsigned short *)0x7F005004)
#define UFCON0         (*(volatile unsigned char *)0x7F005008)
#define UMCON0         (*(volatile unsigned char *)0x7F00500C)
#define UTRSTAT0       (*(volatile unsigned char *)0x7F005010)
#define UERSTAT0       (*(volatile unsigned char *)0x7F005014)
#define UFSTAT0        (*(volatile unsigned short *)0x7F005018)
#define UMSTAT0        (*(volatile unsigned char *)0x7F00501C)
#define UTXH0          (*(volatile unsigned char *)0x7F005020)
#define URXH0          (*(volatile unsigned char *)0x7F005024)
#define UBRDIV0        (*(volatile unsigned short *)0x7F005028)
#define UDIVSLOT0      (*(volatile unsigned short *)0x7F00502C)
#define UINTP0         (*(volatile unsigned char *)0x7F005030)
#define UINTSP0        (*(volatile unsigned char *)0x7F005034)
#define UINTM0         (*(volatile unsigned char *)0x7F005038)

#endif
