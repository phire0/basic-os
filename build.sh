#!/bin/bash

echo "Building Bootloader Project"
rm -f out/*
x86_64-elf-gcc -ffreestanding -c kernel/kernel.c -o out/kernel.o
nasm boot/32-bit/kernel_entry.asm -f elf64 -o out/kernel_entry.o
x86_64-elf-ld -o out/kernel.bin -Ttext 0x1000 --oformat binary out/kernel_entry.o out/kernel.o
nasm boot/boot.asm -f bin -o out/boot.bin
cat out/boot.bin out/kernel.bin > out/os-image.bin
qemu-system-x86_64 -fda out/os-image.bin