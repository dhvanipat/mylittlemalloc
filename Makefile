CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -fsanitize=address,undefined

memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) memgrind.o mymalloc.o -o memgrind
	./memgrind

memgrind.o: memgrind.c mymalloc.h
	$(CC) $(CFLAGS) -c memgrind.c

test_dump: test_dump.o mymalloc.o
	$(CC) $(CFLAGS) test_dump.o mymalloc.o -o test_dump
	./test_dump

test_dump.o: test_dump.c mymalloc.c
	$(CC) $(CFLAGS) -c test_dump.c

mymalloc.o: mymalloc.h mymalloc.c
	$(CC) $(CFLAGS) -c mymalloc.c

clean:
	rm *.o