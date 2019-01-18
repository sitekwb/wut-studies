CC=gcc
CFLAGS=-m32

ASM=nasm
AFLAGS=-f elf32

all:result

main.o: main.c
	$(CC) $(CFLAGS) -g -c $? -Wno-format
count.o: count.asm
	$(ASM) $(AFLAGS) -g $?
huffman.o: huffman.asm
	$(ASM) $(AFLAGS) -g $?
createCodes.o: createCodes.asm
	$(ASM) $(AFLAGS) -g $? 
writeHeader.o: writeHeader.asm
	$(ASM) $(AFLAGS) -g $? 
write.o: write.asm
	$(ASM) $(AFLAGS) -g $? 
result: main.o count.o huffman.o createCodes.o writeHeader.o write.o
	$(CC) $(CFLAGS) $? -o result
clean: 
	rm *.o
	rm result
