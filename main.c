#include <stdio.h>
#include <types.h>
#include <string.h>
#include "uart/uart.h"
#include "nand/nand.h"

void nand_write_test()
{
    char buf[100];
    unsigned long addr;
    unsigned long size;

    printf("Enter the start address: ");
    scanf("%lu",&addr);
    printf("\nEnter the string: ");
    scanf("%s",buf);
    size = strlen(buf) + 1;
    nand_write_page(addr,buf,size);
}

void nand_read_test()
{
    int i;
    unsigned long addr;
    char buf[100];
    unsigned long size;

    printf("Enter the start address: ");
    scanf("%lu",&addr);
    printf("\nRead address: 0x%x\n",addr);
    printf("Enter the read size(<=100): ");
    scanf("%lu",&size);
    printf("\nRead size: %d\n",size);
    if(size > 100){
	size = 100;
    }
    nand_read(addr,buf,size);
    printf("The datas: \n");
    for(i = 0;i < size;i++){
	printf("%02x ",buf[i]);
	if((i+1)%16 == 0){
	    printf("\n");
	}
    }
    printf("\n");
}

void nand_erase_test()
{
    unsigned long addr;

    printf("Input the start adddress: ");
    scanf("%lu",&addr);
    nand_erase_block(addr);
}

void write_file()
{
    unsigned long len = 0;
    int have_begin = 0;
    unsigned char* buf = (unsigned char*)0x52000000;
    int nodata_time = 0;
    unsigned char c;

    printf("Use minicom to send file.\n");
    while(1){
	if(uart_getc_nowait(&buf[len]) == 0){
	    have_begin = 1;
	    nodata_time = 0;
	    len++;
	} else {
	    if(have_begin){
		nodata_time++;
	    }
	}
	if(nodata_time == 1000){
	    break;
	}
    }
    printf("Have get %d bytes data\n",len);
    printf("Press y to program: ");
    c = uart_getc();
    if(c == 'y' || c == 'Y'){
	nand_erase_block(0);
	nand_write_page(0,buf,len);
	printf("\nUpdate program successful\n");
    } else {
	printf("\nUpdate program cancel\n");
    }
}

void run_program()
{
    unsigned char* buf = (unsigned char*)0x52000000;
    unsigned long len = 0;
    int have_begin = 0;
    int nodata_time = 0;
    void (*the_program)(void);

    printf("Use minicom to send file.\n");
    while(1){
	if(uart_getc_nowait(&buf[len]) == 0){
	    have_begin = 1;
	    nodata_time = 0;
	    len++;
	} else {
	    if(have_begin){
		nodata_time++;
	    }
	}
	if(nodata_time == 1000){
	    break;
	}
    }
    printf("Have get %d bytes data\n",len);
    printf("Jump to 0x52000000 to run it\n");
    the_program = (void(*)(void))0x52000000;
    the_program();
}

int main()
{
    char c;

    uart_init();
    printf("\n------------MYBOOT LIUJIANG--------------\n");
    while(1){
	printf("\n[w] write data to the nand flash\n");
	printf("[r] read the nand flash\n");
	printf("[e] erase the nand flash\n");
	printf("[g] get file, and write to nand flash 0 block\n");
	printf("[x] get file to SDRAM(0x52000000), run it\n\n");
	c = uart_getc();
	printf("%c\n\n",c);
	switch(c){
	case 'w':case 'W':
	    nand_write_test();break;
	case 'r':case 'R':
	    nand_read_test();break;
	case 'e':case 'E':
	    nand_erase_test();break;
	case 'g':case 'G':
	    write_file();break;
	case 'x':case 'X':
	    run_program();break;
	}
    }
    return 0;
}
