# My Little Malloc Project

Collaborators
- Dhvani Patel, dgp69
- Ananya Balaji, ab2389

## Design
### Some Design Decisions
- Edge case malloc(0)
    - Since the behavior of malloc(0) is implementation-defined, we decided to return a pointer to a chunk with no payload when malloc(0) is called, instead of returning null. This is tested in edge_cases.c.

Any Design Notes Worth Pointing Out


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
    - correctness test of mymalloc() and free()
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

memgrind.c
    - runs five tests 50 times each and prints average time of each

    - Test 1

This was implemented to find time of each case running 50 times in terminal

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

make test
./test
every case along with itself is printed in the console 


to compile all together
make all
then run ./memgrind /test ./err (with the case number 1 - 3)

make clean
available for cleaning source file 
rm -f *.o err memgrind mymalloc test

Test Plan
1) Performance Testing
File: memgrind.c
Purpose: We check the performance of the code under different stress conditions. We do a total of 5 tests.

memgrind test #1:
1)  malloc() and immediately free() a 1-byte chunk, 120 times.

Time Taken to Count to 10^5:
Average Time:


memgrind test #2:
2) Use malloc() to get 120 1-byte objects, storing the pointers in an array, then use free() to deallocate the chunks.

Time Taken to Count to 10^5:
Average Time:




memgrind test #3:
3) Create an array of 120 pointers. Repeatedly make a random choice between allocating a 1-byte object and 
adding the pointer to the array and deallocating a previously allocated object (if any), until you have 
allocated 120 times. Deallocate any remaining objects.

Time Taken to Count to 10^5:
Average Time:



memgrind test #4:
4) **add description here**

Time Taken to Count to 10^5:
Average Time:




memgrind test #5:
5) Allocate a 4000 byte chunk and free it, then use a ptr5 array to store all 120 allocations, then
free everything. After it, the process is repeated with storing 120 allocations and then they are all freed.

Time Taken to Count to 10^5:
Average Time:




Unit Tests for some Edge Cases
Test 1 Allocates 0 Bytes
Output:

Test 2 Allocates 0 Bytes
Output:

Test 3 Tries to free when there are no allocations/pointers in memory, with different pointers.
Output:














*delete this before submitting*

to be implemented:
- test files make sure all cases are covered

check detectable_errors