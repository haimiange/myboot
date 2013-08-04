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
	bl main
loop1:
	b loop1
