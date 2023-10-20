CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -fsanitize=address,undefined

# executables of test programs
memgrind: memgrind.o mymalloc.o iterate_chunks.o
	$(CC) $(CFLAGS) memgrind.o mymalloc.o iterate_chunks.o -o memgrind
	./memgrind

memtest: memtest.o mymalloc.o iterate_chunks.o
	$(CC) $(CFLAGS) memtest.o mymalloc.o iterate_chunks.o -o memtest
	./memtest

test: test.o mymalloc.o
	$(CC) $(CFLAGS) test.o mymalloc.o -o test

err: err.o mymalloc.o
	$(CC) $(CFLAGS) err.o mymalloc.c -o err 

#test object files
memgrind.o: memgrind.c mymalloc.h iterate_chunks.h
	$(CC) $(CFLAGS) -c memgrind.c


memtest.o: memtest.c mymalloc.h iterate_chunks.h
	$(CC) $(CFLAGS) -c memtest.c

# include iterate chunks?
err.o: err.c mymalloc.h
	$(CC) $(CFLAGS) -c err.c

# include iterate chunks?
test.o: test.c mymalloc.h
	$(CC) $(CFLAGS) -c test.c

#library object files
iterate_chunks.o: iterate_chunks.h iterate_chunks.c
	$(CC) $(CFLAGS) -c iterate_chunks.c

mymalloc.o: mymalloc.h mymalloc.c
	$(CC) $(CFLAGS) -c mymalloc.c

#other
clean:
	rm *.o err memgrind memtest test