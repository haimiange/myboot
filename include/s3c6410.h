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

/* IRQ */
#define GPNCON     (*((volatile unsigned long *)0x7F008830))
#define GPNDAT     (*((volatile unsigned long *)0x7F008834))
#define EINT0CON0  (*((volatile unsigned long *)0x7F008900))
#define EINT0MASK  (*((volatile unsigned long *)0x7F008920))
#define EINT0PEND  (*((volatile unsigned long *)0x7F008924))
#define PRIORITY    (*((volatile unsigned long *)0x7F008280))
#define SERVICE     (*((volatile unsigned long *)0x7F008284))
#define SERVICEPEND (*((volatile unsigned long *)0x7F008288))
#define VIC0IRQSTATUS  (*((volatile unsigned long *)0x71200000))
#define VIC0FIQSTATUS  (*((volatile unsigned long *)0x71200004))
#define VIC0RAWINTR    (*((volatile unsigned long *)0x71200008))
#define VIC0INTSELECT  (*((volatile unsigned long *)0x7120000c))
#define VIC0INTENABLE  (*((volatile unsigned long *)0x71200010))
#define VIC0INTENCLEAR (*((volatile unsigned long *)0x71200014))
#define VIC0PROTECTION (*((volatile unsigned long *)0x71200020))
#define VIC0SWPRIORITYMASK (*((volatile unsigned long *)0x71200024))
#define VIC0PRIORITYDAISY  (*((volatile unsigned long *)0x71200028))
#define VIC0VECTADDR0      (*((volatile unsigned long *)0x71200100))
#define VIC0VECTADDR1      (*((volatile unsigned long *)0x71200104))
#define VIC0ADDRESS        (*((volatile unsigned long *)0x71200f00))
#define VIC1IRQSTATUS  (*((volatile unsigned long *)0x71300000))
#define VIC1VECTADDR5      (*((volatile unsigned long *)0x71300114))
#define VIC1INTENABLE  (*((volatile unsigned long *)0x71300010))
#define VIC1ADDRESS        (*((volatile unsigned long *)0x71300f00))

/* LCD */
#define GPECON  (*((volatile unsigned long *)0x7F008080))
#define GPEDAT  (*((volatile unsigned long *)0x7F008084))
#define GPFCON  (*((volatile unsigned long *)0x7F0080A0))
#define GPFDAT  (*((volatile unsigned long *)0x7F0080A4))
#define GPICON  (*((volatile unsigned long *)0x7F008100))
#define GPJCON  (*((volatile unsigned long *)0x7F008120))

/* display controller */
#define MIFPCON     (*((volatile unsigned long *)0x7410800C))
#define SPCON         (*((volatile unsigned long *)0x7F0081A0))
#define VIDCON0      (*((volatile unsigned long *)0x77100000))
#define VIDCON1      (*((volatile unsigned long *)0x77100004))
#define VIDTCON0     (*((volatile unsigned long *)0x77100010))
#define VIDTCON1     (*((volatile unsigned long *)0x77100014))
#define VIDTCON2     (*((volatile unsigned long *)0x77100018))
#define WINCON0      (*((volatile unsigned long *)0x77100020))
#define VIDOSD0A      (*((volatile unsigned long *)0x77100040))
#define VIDOSD0B      (*((volatile unsigned long *)0x77100044))
#define VIDOSD0C      (*((volatile unsigned long *)0x77100048))
#define VIDW00ADD0B0      (*((volatile unsigned long *)0x771000A0))
#define VIDW00ADD1B0      (*((volatile unsigned long *)0x771000D0))
#define VIDW00ADD2      (*((volatile unsigned long *)0x77100100))

#endif
