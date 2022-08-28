AS=nasm
GCC=i686-elf-gcc
CFLAGS=-ffreestanding -O2 -Wall -Wextra -fno-exceptions -I./include
QEMU=qemu-system-i386
SOURCES=kernel.c $(wildcard lib/*/*.c)
QEMUFLAGS=-drive file=Wordle.iso,format=raw,index=0,media=disk -serial file:/dev/stdout -display sdl

build:
	for file in $(SOURCES); do \
		$(GCC) -c $$file -o `basename $$file .c`.o $(CFLAGS) ; \
	done
	$(AS) -felf32 boot.asm -o boot.o
	$(GCC) -T link.ld -o iso/boot/wordle.bin -ffreestanding -O2 -nostdlib *.o -lgcc
	grub-file --is-x86-multiboot iso/boot/wordle.bin
	grub-mkrescue -o Wordle.iso iso

run:
	@$(QEMU) $(QEMUFLAGS)

clean:
	rm -f *.o Wordle.iso iso/boot/wordle.bin
