CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -g
ENGINECFLAGS =-Wall -O0 -g
CC = gcc

engine:
	$(CC) $(ENGINECFLAGS) -c extra/engine.c -o engine.o

tp2: engine
	$(CC) $(CFLAGS) main.c src/*.c engine.o -o tp2

pruebas_tp2: engine
	$(CC) $(CFLAGS) pruebas/pruebas_alumno.c src/*.c engine.o -o pruebas_tp2

clean:
	rm -f engine.o tp2 pruebas_tp2