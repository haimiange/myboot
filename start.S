.extern main
.section .text
.globl _start
_start:
	/* Peri port setup */
	ldr	r0, =0x70000000
	orr	r0, r0, #0x13
	mcr	p15,0,r0,c15,c2,4       @ 256M (0x70000000 - 0x7fffffff)

	@ disable watchdog
	ldr r0,=0x7e004000
	ldr r1,=0x0
	str r1,[r0]
	
	bl clock_init
	mov sp,#0x2000
	bl sdram_init

	@ 将nand中的数据拷贝到sdram中
	adr r0,_start		@获得_start的当前地址，对应在nand中的地址
	ldr r1,=_start		@_start的链接地址
	ldr r2,=bss_start	@bss段的起始地址
	sub r2,r2,r1		@拷贝数据的长度

	cmp r0,r1
	beq clean_bss		@程序已经在SDRAM中了，无需拷贝

	bl copy2ddr

/*	adr r0, _start
	ldr r1, =_start
	
	ldr r2, =bss_start
	
	cmp r0,r1
	beq clean_bss
	
copy_loop:
	ldr r3, [r0], #4
	str r3, [r1], #4
	cmp r1, r2
	bne copy_loop
*/	
clean_bss:
	ldr r0,=bss_start
	ldr r1,=bss_end
	mov r3,#0
	cmp r0,r1
	beq on_ddr
clean_loop:
	str r3,[r0],#4
	cmp r0,r1
	bne clean_loop
on_ddr:	
	ldr pc,=main
halt:
	b halt
