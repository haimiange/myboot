	.section .text
	.globl _start
_start:
	b reset
	b halt			@未定义指令中断向量
	ldr pc, _vector_swi	@切换到SVC模式中断向量
	b halt			@ldr pc, _prefetch_abort
	b halt			@ldr pc, _data_abort
	b halt			@ldr pc, _not_used
	ldr pc, _irq		@中断向量
	b halt			@快速中断向量

_vector_swi:
	.word vector_swi
	
vector_swi:
	ldr sp, = 0x56000000
	stmdb sp!,{r0-r12,lr}
	
	mrs r0,cpsr
	ldr r1,=swi_str
	bl print_cpsr
	
	ldmia sp!,{r0-r12,pc}^

_irq:
	.word vector_irq
	
vector_irq:
	ldr sp, = 0x54000000
	sub lr,lr,#4
	stmdb sp!,{r0-r12,lr}
	bl do_irq
	ldmia sp!,{r0-r12,pc}^
	
reset:	
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
	
	ldr pc,=on_ddr
on_ddr:
	bl uart_init
	bl irq_init

	mrs r0,cpsr
	bic r0,r0,#0x9f
	orr r0,r0,#0x10
	msr cpsr,r0

	ldr sp,=0x57000000

	ldr r1,=usr_str
	bl print_cpsr

	swi 0
	
	ldr pc,=main
halt:
	b halt

usr_str:
	.word 0x00727375  /* usr */
swi_str:	
	.word 0x00697773  /* swi */
