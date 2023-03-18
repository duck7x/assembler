assembler:	assembler.o
	gcc -g -Wall -ansi -pedantic -o assembler assembler.o
assembler.o:	assembler.c assembler.h
	gcc -c -g -Wall -ansi -pedantic -o assembler.o assembler.c