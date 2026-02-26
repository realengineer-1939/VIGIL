# --- DIRECTORIES ---
VCORE_DIR  = V-Core
INFRA_DIR  = Infra-Stack
CACHE_DIR  = Neural-Cache

# --- TOOLS & FLAGS ---
CC      = gcc
AS      = nasm
LD      = ld
CFLAGS  = -m32 -ffreestanding -fno-stack-protector -Wall -Wextra
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

# --- OBJECTS (Order is crucial for the Boot Passport) ---
OBJ = $(INFRA_DIR)/boot.o \
      $(CACHE_DIR)/gdt_asm.o \
      $(VCORE_DIR)/kernel.o

all: kernel.bin

# Linker Stage
kernel.bin: $(OBJ)
	$(LD) $(LDFLAGS) -o kernel.bin $(OBJ)

# 1. Infra-Stack: Bootloader
$(INFRA_DIR)/boot.o: $(INFRA_DIR)/boot.asm
	$(AS) $(ASFLAGS) $(INFRA_DIR)/boot.asm -o $(INFRA_DIR)/boot.o

# 2. Neural-Cache: GDT Assembly Bridge
$(CACHE_DIR)/gdt_asm.o: $(CACHE_DIR)/gdt.asm
	$(AS) $(ASFLAGS) $(CACHE_DIR)/gdt.asm -o $(CACHE_DIR)/gdt_asm.o

# 3. V-Core: Main Logic
$(VCORE_DIR)/kernel.o: $(VCORE_DIR)/kernel.c
	$(CC) $(CFLAGS) -c $(VCORE_DIR)/kernel.c -o $(VCORE_DIR)/kernel.o

# --- COMMANDS ---
run: kernel.bin
	qemu-system-i386 -kernel kernel.bin

clean:
	rm -f $(INFRA_DIR)/*.o $(CACHE_DIR)/*.o $(VCORE_DIR)/*.o kernel.bin *.o
