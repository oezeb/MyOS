ASM_FLAGS= -m32 --pipe -Wall -fasm -g -O1 -fno-stack-protector

run:
	make clean
	make header.bin
	qemu-system-i386 -kernel header.bin
	make clean

header.bin: header.S
	gcc -c ${ASM_FLAGS} header.S -o header.o 
	ld -n -T header.ld header.o -o header.bin

clean:
	rm -rf header.bin header.o
