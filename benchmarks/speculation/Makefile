CC=clang
CFLAGS=-O3 -Rpass-analysis=speculative-execution -Rpass-missed=speculative-execution 

all: program

program: main.c
	$(CC) $(CFLAGS) -o program main.c

clean:
	rm -f program
