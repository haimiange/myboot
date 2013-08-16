CC      = arm-linux-gcc
LD      = arm-linux-ld
AR      = arm-linux-ar
OBJCOPY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump

INCLUDEDIR 	:= $(shell pwd)/include
CFLAGS 		:= -Wall -Os -fno-builtin-printf 
CPPFLAGS   	:= -nostdinc -I$(INCLUDEDIR)

export 	CC AR LD OBJCOPY OBJDUMP INCLUDEDIR CFLAGS CPPFLAGS

obj := start.o main.o clock.o uart.o sdram.o nand.o lib/libc.a irq.o

u-boot.bin:$(obj)
	${LD} -T u-boot.lds -g $(obj) -o u-boot.elf
	${OBJCOPY} -O binary -S u-boot.elf u-boot.bin
	${OBJDUMP} -D u-boot.elf > u-boot.dis

.PHONY:lib/libc.a
lib/libc.a:
	cd lib; make; cd ..
%.o:%.S
	${CC} $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
%.o:%.c
	${CC} $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
clock.o:clock/clock.S
	${CC} $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
uart.o:uart/uart.c
	${CC} $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
sdram.o:sdram/sdram.c
	${CC} $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
nand.o:nand/nand.c
	${CC} $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
irq.o:irq/irq.c
	${CC} $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

led_program:led.o sleep.o led_program.o
	${LD} -Ttext 0x52000000 led_program.o led.o sleep.o -o led_program.elf
	${OBJCOPY} -O binary led_program.elf led_program.bin
	${OBJDUMP} -D led_program.elf > led_program.dis
led.o:led/led.c
	${CC} $(CPPFLAGS) -c -o $@ $<
sleep.o:sleep/sleep.c
	${CC} $(CPPFLAGS) -c -o $@ $<
led_program.o:led_program.c
	${CC} $(CPPFLAGS) -c -o $@ $< 

.PHONY:clean
clean:
	make clean -C lib
	rm *.o *.elf *.bin *.dis
