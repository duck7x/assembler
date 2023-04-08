assembler:	assembler.o assembler_phase.o pre_assembler_phase.o assembler_phase_functions.o pre_assembler_functions.o general_functions.o utils.o structures.o
	gcc -g -Wall -ansi -pedantic -o assembler assembler.o assembler_phase.o pre_assembler_phase.o assembler_phase_functions.o pre_assembler_functions.o general_functions.o utils.o structures.o
assembler.o:	assembler.c assembler.h assembler_phase.h pre_assembler_phase.h
	gcc -c -g -Wall -ansi -pedantic -o assembler.o assembler.c -lm
assembler_phase.o:	assembler_phase.c assembler_phase.h assembler_phase_functions.h
	gcc -c -g -Wall -ansi -pedantic -o assembler_phase.o assembler_phase.c -lm
assembler_phase_functions.o:	assembler_phase_functions.c assembler_phase_functions.h general_functions.h utils.h
	gcc -c -g -Wall -ansi -pedantic -o assembler_phase_functions.o assembler_phase_functions.c -lm
pre_assembler_phase.o:	pre_assembler_phase.c pre_assembler_phase.h pre_assembler_functions.h
	gcc -c -g -Wall -ansi -pedantic -o pre_assembler_phase.o pre_assembler_phase.c
pre_assembler_functions.o:	pre_assembler_functions.c pre_assembler_functions.h general_functions.h utils.h
	gcc -c -g -Wall -ansi -pedantic -o pre_assembler_functions.o pre_assembler_functions.c
general_functions.o:	general_functions.c general_functions.h utils.h
	gcc -c -g -Wall -ansi -pedantic -o general_functions.o general_functions.c
utils.o:	utils.c utils.h structures.h
	gcc -c -g -Wall -ansi -pedantic -o utils.o utils.c
structures.o:	structures.c structures.h utils.h
	gcc -c -g -Wall -ansi -pedantic -o structures.o structures.c