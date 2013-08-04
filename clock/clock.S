.section .text
	.globl clock_init
clock_init:
	#define OTHERS 0x7e00f900
	ldr r0,=OTHERS
	ldr r1,[r0]
	bic r1,#0xc		/*设置时钟为异步模式，清除other的6，7位*/
	str r1,[r0]		/*设置SYNCMODE和SYNCMUXSEL*/

	/* 等待设置生效 */
wait_for_syncack:
	ldr r0,=OTHERS
	ldr r1,[r0]
	and r1,#0xf00
	cmp r1,#0
	bne wait_for_syncack

	@ 设置时钟锁定时间
	ldr r0,=0x7e00f000
	ldr r1,=0xffff
	str r1,[r0]		@APLL_LOCK
	str r1,[r0,#4]		@MPLL_LOCK	
	str r1,[r0,#8]		@EPLL_LOCK

	@ 设置分频系数
	#define CLK_DIV0 0x7e00f020
	#define ARM_RATIO 	0
	#define HCLKX2_RATIO 	1
	#define HCLK_RATIO 	1
	#define PCLK_RATIO	3
	#define MPLL_RATIO	0
	ldr r0,=CLK_DIV0
	ldr r1,=(ARM_RATIO|(HCLKX2_RATIO<<9)|(HCLK_RATIO<<8)|(PCLK_RATIO<<12)|(MPLL_RATIO<<4))
	str r1,[r0]

	@ 设置APLL和MPLL
	#define APLL_CON 0x7e00f00c
	#define MPLL_CON 0x7e00f010
	#define CON_VAL ((1<<31)|(266<<16)|(3<<8)|(1<<0))
	ldr r0,=APLL_CON
	ldr r1,=CON_VAL
	str r1,[r0]

	ldr r0,=MPLL_CON
	ldr r1,=CON_VAL
	str r1,[r0]

	@ 选择时钟源
	#define CLK_SRC 0x7e00f01c
	ldr r0,=CLK_SRC
	ldr r1,=0x3
	str r1,[r0]

	mov pc,lr
