# My Little Malloc Project

Collaborators
- Dhvani Patel, dgp69
- Ananya Balaji, ab2389

## Design
### Some Design Decisions
- Edge case malloc(0)
    - Since the behavior of malloc(0) is implementation-defined, we decided to return a pointer to a chunk with no payload when malloc(0) is called, instead of returning null. This is tested in edge_cases.c.
- Error handling
    - We used <errno.h> to set errno and then print to stderr when there is invalid behavior in malloc or free. Each error is contained within a helper method in mymalloc.c
    - malloc
        - Errors when there is not enough memory available to complete the user's request. Prints file, line, and size parameter along with the error messgage "Cannot allocate memory"
        - Ex: ERROR in edge_cases.c, line 29, malloc(4097): Cannot allocate memory
    - free
        - Errors when free() does not match a chunk to the pointer passed as a parameter for whatever reason. Prints file, line, and pointer passed to free along with the error messgage "Bad address" Could error because:
            - The pointer does not point to memory allocated by malloc()
            - The pointer does not point to the beginning of the payload
            - The pointer has already been freed
            - The pointer is null
        - General case: Throws bad address exception
        Ex: ERROR in edge_cases.c, line 42, free(0x7ffca074a4e8): Bad address

        - Double free case: Throws bad address exception, adds "this memory is already free"
        Ex: ERROR in detectable_errors.c, line 31, free(0x560063e64900), this memory is already free: Bad address



### Project Structure
Implementation of Malloc
- mymalloc.c
    - contains implementation of mymalloc() and myfree()
    - holds memory array
    - additional helper methods and macros
- mymalloc.h
    - header file for the public interface of mymalloc library

Test Files (See below for a more detailed explanation of our testing)
- iterate_chunks.c  
    - helper library meant to be included in multiple test file executables
    - prints diagnostic info about chunks and/or memory array for debugging and testing
- iterate_chunks.h
    - header file for include_chunks.c, contains two publicly accessible methods
    - display_all_chunks(ptr)
        - displays the current state of memory, all chunks in it
    - print_chunk_info(ptr)
        - displays information about a chunk like it's position in memory[], size, and whether it is in use
- memgrind.c
    - performance test of mymalloc() and free()
- memtest.c
    - correctness test of mymalloc()
- edge_cases.c
    - tests some edge cases of mymalloc() and free()
- detectable_errors.c
    - correctness test of myfree()

Other
- Makefile
    - compiles source files, runs executables, cleans working directory
    - We have 4 test executables: memgrind, memtest, edge_cases, and detectable_errors
    - How to use:
        - make memgrind

            ./memgrind

        - make memtest

            ./memtest
        - make edge_cases

            ./edge_cases

        - make detectable_errors

            ./detectable_errors 1

            ./detectable_errors 2

            ./detectable_errors 3
        
        - make clean

            deletes everything but source files (stray object files and test executables)

## Testing

Descriptions of our Test Programs
- include any arguments they take

### Performance Testing

- memgrind.c
    - runs five tests 50 times each and prints average time of each
    - Test 1
        - malloc() and immediately free() a 1-byte chunk, 120 times
    - Test 2
        - Use malloc() to allocate memory for 120 1-byte objects, storing the pointers in an array, then use free() to deallocate the chunks
    - Test 3
        - Create an array of 120 pointers. Repeatedly make a random choice between allocating a 1-byte object and adding the pointer to the array and deallocating a previously allocated object (if any), until you have allocated 120 times. Deallocate any remaining objects.
    - Test 4
        - Create an array of 120 objects using malloc(), and a separate indexes array which will indicate the order in which the chunks are freed. Shuffle up the indexes array, and use it on objects to (randomly) free the chunks.
    - Test 5
        - Allocate a 4000 byte chunk and free it, then use a ptr5 array to store all 120 allocations, then free everything. After it, the process is repeated with storing 120 allocations and then they are all freed.

### Correctness Testing:
- memtest.c
    - same memtest.c given in canvas
    - tests if malloc will properly allocate bytes that can be used to store user data
- detectable_errors.c
    - correctness test of myfree()
    - 3 correctness tests as described in section 2 of the project writeup, titled detectable_errors
    - tests if myfree() has working error handling
    - Test 1: Calling free() with an address not obtained from malloc()
    - Test 2: Calling free() with an address not at the start of a chunk
    - Test 3: Calling free() a second time on the same pointer.

### Edge Case Testing:
- edge_cases.c
    - Test 1
        - Applying malloc() on a zero-byte chunk, which should return the address of a chunk with no payload (therefore a size of 8 bytes)
    - Test 2
        - Use malloc() to allocate memory for a chunk size of 4097, which is greater than the the array's MEMSIZE
    - Test 3
        - Attempt to free two different pointers when there exists no allocations or pointers in memory. 

