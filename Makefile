CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -fsanitize=address,undefined

# executables
memgrind: memgrind.o mymalloc.o iterate_chunks.o
	$(CC) $(CFLAGS) memgrind.o mymalloc.o iterate_chunks.o -o memgrind
	./memgrind

memtest: memtest.o mymalloc.o iterate_chunks.o
	$(CC) $(CFLAGS) memtest.o mymalloc.o iterate_chunks.o -o memtest
	./memtest

#test object files
memgrind.o: memgrind.c mymalloc.h iterate_chunks.h
	$(CC) $(CFLAGS) -c memgrind.c


memtest.o: memtest.c mymalloc.h iterate_chunks.h
	$(CC) $(CFLAGS) -c memtest.c

#library object files
iterate_chunks.o: iterate_chunks.h iterate_chunks.c
	$(CC) $(CFLAGS) -c iterate_chunks.c

mymalloc.o: mymalloc.h mymalloc.c
	$(CC) $(CFLAGS) -c mymalloc.c

#other
clean:
	rm *.o