CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -fsanitize=address,undefined

# test program executables
memgrind: memgrind.o mymalloc.o iterate_chunks.o
	$(CC) $(CFLAGS) memgrind.o mymalloc.o iterate_chunks.o -o memgrind
	./memgrind

memtest: memtest.o mymalloc.o iterate_chunks.o
	$(CC) $(CFLAGS) memtest.o mymalloc.o iterate_chunks.o -o memtest
	./memtest

edge_cases: edge_cases.o mymalloc.o iterate_chunks.o
	$(CC) $(CFLAGS) edge_cases.o mymalloc.o iterate_chunks.o -o edge_cases
	./edge_cases

detectable_errors: detectable_errors.o mymalloc.o iterate_chunks.o
	$(CC) $(CFLAGS) detectable_errors.o mymalloc.c iterate_chunks.o -o detectable_errors 
	./detectable_errors

# test program object files
memgrind.o: memgrind.c mymalloc.h iterate_chunks.h
	$(CC) $(CFLAGS) -c memgrind.c


memtest.o: memtest.c mymalloc.h iterate_chunks.h
	$(CC) $(CFLAGS) -c memtest.c

detectable_errors.o: detectable_errors.c mymalloc.h
	$(CC) $(CFLAGS) -c detectable_errors.c

edge_cases.o: edge_cases.c mymalloc.h
	$(CC) $(CFLAGS) -c edge_cases.c

# library object files
iterate_chunks.o: iterate_chunks.h iterate_chunks.c
	$(CC) $(CFLAGS) -c iterate_chunks.c

mymalloc.o: mymalloc.h mymalloc.c
	$(CC) $(CFLAGS) -c mymalloc.c

# other
clean:
	rm *.o detectable_errors memgrind memtest edge_cases