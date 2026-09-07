.PHONY: all link run clean

PROGRAM  = stykkevis
CFLAGS   = -Wall -Wextra -I.
CC       = gcc

all: run

run: compile
	./$(PROGRAM)

compile: main.c
	$(CC) -o $(PROGRAM) main.c $(CFLAGS)

clean:
	rm -f *.o $(PROGRAM)

deep-clean: clean
	rm -f vgcore*

