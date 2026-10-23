.PHONY: all link run clean

PROGRAM  = stykkevis
CFLAGS   = -Wall -Wextra -I. -g
CC       = gcc
PROGRAM_ARGS = -bs 1010

all: run

run: compile
	./$(PROGRAM) $(PROGRAM_ARGS)

compile: main.c utils.c
	$(CC) -o $(PROGRAM) utils.c main.c $(CFLAGS)

clean:
	rm -f *.o $(PROGRAM)

deep-clean: clean
	rm -f vgcore*

