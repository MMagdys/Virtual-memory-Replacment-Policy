CC=gcc
CFLAGS=-I.
DEPS = FIFO.h CLOCK.h LRU.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

memory_man : main.c FIFO.c CLOCK.c LRU.c
	gcc -o memory_man main.c FIFO.c CLOCK.c LRU.c
