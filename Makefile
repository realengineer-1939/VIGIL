OBJ = boot.o kernel.o

all: my_os.bin

my_os.bin: $(OBJ)
	ld -m elf_i386 -T linker.ld -o my_os.bin $(OBJ)

boot.o: boot.asm
	nasm -f elf32 boot.asm -o boot.o

kernel.o: kernel.c
	gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

run: my_os.bin
	qemu-system-i386 -kernel my_os.bin

clean:
	rm -rf *.o my_os.bin
