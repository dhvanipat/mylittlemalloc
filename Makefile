CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -fsanitize=address,undefined

#IMPLEMENT THIS INSTEAD??
#CFLAGS = -g -Wall -Wvla -Werror

# executables of test + err
test: test.o mymalloc.o
	$(CC) $(CFLAGS) -o test test.o mymalloc.o

err: err.o mymalloc.o
	$(CC) $(CFLAGS) -o err err.o mymalloc.c

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

err.o: mymalloc.c err.c mymalloc.h
	$(CC) $(CFLAGS) - c err.c

test.o: test.o mymalloc.o
	$(CC) $(CFLAGS) - c test.c

#library object files
iterate_chunks.o: iterate_chunks.h iterate_chunks.c
	$(CC) $(CFLAGS) -c iterate_chunks.c

mymalloc.o: mymalloc.h mymalloc.c
	$(CC) $(CFLAGS) -c mymalloc.c

#other
clean:
	rm *.o

#clean v2 with testing  - IMPLEMENT THIS??
#clean:
#	rm -f *.o err memgrind mymalloc test
