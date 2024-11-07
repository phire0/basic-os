C_SOURCES = $(wildcard kernel/*.c drivers/*.c stdlib/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h stdlib/*.h)

# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o}

# Change this if your cross-compiler is somewhere else
CC = /opt/homebrew/bin/x86_64-elf-gcc
GDB = /opt/homebrew/bin/x86_64-elf-gdb

# -g: Use debugging symbols in gcc
CFLAGS = -g -Wstrict-prototypes -Wextra -Wall -Wundef -Wshadow -Wunreachable-code

# First rule is run by default
os-image.bin: boot/boot.bin kernel.bin
	cat $^ > os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${OBJ}
	x86_64-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary -melf_i386

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJ}
	x86_64-elf-ld -o $@ -Ttext 0x1000 $^ -melf_i386

boot/kernel_entry.o: boot/32-bit/kernel_entry.asm
	nasm $^ -f elf32 -o $@

run: os-image.bin
	qemu-system-x86_64 -fda os-image.bin

# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	qemu-system-x86_64 -s -fda os-image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -m32 -c $< -o $@

%.o: %.asm
	nasm $< -f elf32 -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o stdlib/*.o