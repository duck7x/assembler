assembler:	assembler.o assembler_phase.o pre_assembler.o
	gcc -g -Wall -ansi -pedantic -o assembler assembler.o assembler_phase.o pre_assembler.o
assembler.o:	assembler.c assembler.h assembler_phase.h pre_assembler.h
	gcc -c -g -Wall -ansi -pedantic -o assembler.o assembler.c
assembler_phase.o:	assembler_phase.c assembler_phase.h
	gcc -c -g -Wall -ansi -pedantic -o assembler_phase.o assembler_phase.c
pre_assembler.o:	pre_assembler.c pre_assembler.h
	gcc -c -g -Wall -ansi -pedantic -o pre_assembler.o pre_assembler.c