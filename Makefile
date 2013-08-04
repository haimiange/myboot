CC      = arm-linux-gcc
LD      = arm-linux-ld
AR      = arm-linux-ar
OBJCOPY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump

INCLUDEDIR 	:= $(shell pwd)/include
CFLAGS 		:= -Wall -Os -fno-builtin-printf 
CPPFLAGS   	:= -nostdinc -I$(INCLUDEDIR)

export 	CC AR LD OBJCOPY OBJDUMP INCLUDEDIR CFLAGS CPPFLAGS

obj := start.o main.o clock.o uart.o lib/libc.a

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

.PHONY:clean
clean:
	make clean -C lib
	rm *.o *.elf *.bin u-boot.dis
