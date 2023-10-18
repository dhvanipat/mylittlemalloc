CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -fsanitize=address,undefined

memgrind: memgrind.o mymalloc.o iterate_chunks.o
	$(CC) $(CFLAGS) memgrind.o mymalloc.o iterate_chunks.o -o memgrind
	./memgrind

memgrind.o: memgrind.c mymalloc.h iterate_chunks.h
	$(CC) $(CFLAGS) -c memgrind.c

memgrind_from_hackmd: memgrind_from_hackmd.o mymalloc.o iterate_chunks.o
	$(CC) $(CFLAGS) memgrind_from_hackmd.o mymalloc.o iterate_chunks.o -o memgrind_from_hackmd
	./memgrind_from_hackmd

memgrind_from_hackmd.o: memgrind_from_hackmd.c mymalloc.h iterate_chunks.o
	$(CC) $(CFLAGS) -c memgrind_from_hackmd.c

memtest: memtest.o mymalloc.o iterate_chunks.o
	$(CC) $(CFLAGS) memtest.o mymalloc.o iterate_chunks.o -o memtest
	./memtest

memtest.o: memtest.c mymalloc.h iterate_chunks.h
	$(CC) $(CFLAGS) -c memtest.c

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