CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -fsanitize=address,undefined

memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) memgrind.o mymalloc.o -o memgrind
	./memgrind

memgrind.o: memgrind.c mymalloc.h
	$(CC) $(CFLAGS) -c memgrind.c

test4: iterate_chunks.o mymalloc.o test4.o
	$(CC) $(CFLAGS) iterate_chunks.o mymalloc.o test4.o -o test4
	./test4

test4.o: test4.c mymalloc.h iterate_chunks.h
	$(CC) $(CFLAGS) -c test4.c

iterate_chunks.o: iterate_chunks.h iterate_chunks.c
	$(CC) $(CFLAGS) -c iterate_chunks.c

mymalloc.o: mymalloc.h mymalloc.c
	$(CC) $(CFLAGS) -c mymalloc.c

clean:
	rm *.o