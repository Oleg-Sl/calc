CC=gcc
CFLAGS= -c -Wall -Werror -Wextra


all: start

start: start.o colections.o
	$(CC) -o a.out colections.o start.o -lm

start.o: start.c
	$(CC) $(CFLAGS) -o start.o start.c

colections.o: collections/stack.c collections/stack.h
	$(CC) $(CFLAGS) -o colections.o collections/stack.c


clean:
	rm -rf *.o a.out

rebuild: clean all



