My Little Malloc Project

    Collaborators
    - Dhvani Patel (dgp69)
    - Ananya Balaji (ab2389)

    Makefile

    1) Performance Testing
    make memgrind
    ./memgrind
    This was implemented to find time of each case running 50 times in terminal

    2) Correctness Testing:
    make err
    ./ err with the case number (from 1 to 3)

    3) Edge Case Testing:
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






    Descriptions of our Test Programs
    - include any arguments they take

    Any Design Notes Worth Pointing Out







*delete this before submitting*

to be implemented:
- test files
    - come up with 1 more stress test for memgrind
- last: project README



questions:
- malloc(0) returns null or a pointer?
- is it ok to use unsigned int instead of size_t for size?
- i did the timing for memgrind slightly differently using cpu time instead of wall clock time is this ok
- do we put the executables in the final tar submission?
- coalesce: are we graded on time complexity?
