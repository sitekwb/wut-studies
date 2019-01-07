CC=gcc
CFLAGS=-m32

ASM=nasm
AFLAGS=-f elf32

all:result

main.o: main.c
	$(CC) $(CFLAGS) -g -c main.c
count.o: count.asm
	$(ASM) $(AFLAGS) -g count.asm
result: main.o count.o
	$(CC) $(CFLAGS) main.o count.o -o result
clean: 
	rm *.o
	rm result
