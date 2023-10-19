#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mymalloc.h"
#include "iterate_chunks.h"

void* chunk_iterator;

static double run_50_times(void (*task)()) {
    double time = 0;
    clock_t start, end;

    for(int i = 0; i < 50; i++){
        start = clock();
        (*task)();
        end = clock();
        time += ((double)end - start) / CLOCKS_PER_SEC;
    }

    display_all_chunks(chunk_iterator);
    time /= 50;
    return time;
}

static void test1() {
    for(int i = 0; i < 120; i++){
        void* x = malloc(1);
        free(x);
    }
}

static void test2() {
    void* objects[120];
    for(int i = 0; i < sizeof(objects)/sizeof(objects[0]); i++){
        objects[i] = malloc(1);
    }
    for(int i = 0; i < sizeof(objects)/sizeof(objects[0]); i++){
        free(objects[i]);
    }
}

static void test3() {
    char *ptrArray[120];  // Array to store 120 pointers
    int allocated[120] = {0};  // Initialize the memory allocation status array
    int loc = 0;  // Current location

    for(int i = 0; i < 120; i++) {
        if(loc == 0 || (rand() % 2 == 0 && loc < 120)) {
            // Allocate 1 byte of memory and store the address
            printf("alloc loc=%d\n", loc);
            ptrArray[loc] = malloc(1);
            allocated[loc] = 1;
            loc++;
        } else {
            // Release the memory
            loc--;
            printf("free loc=%d\n", loc);
            free(ptrArray[loc]);
            allocated[loc] = 0;
        }
    }

    printf("Process is done.\n");

    // Clean up any unreleased memory
    for(int i = 0; i < 120; i++) {
        if(allocated[i] == 1) {
            free(ptrArray[i]);
        }
    }
}

static void test4() { // tests if malloc can handle chunks of varying sizes, if chunks will coalesce in random order
    void* objects[120];
    int indexes[120]; // will indicate order in which chunks are freed

    // allocates 120 objects of random size
    for(int i = 0; i < 120; i++) {
        objects[i] = malloc(rand() % 24);
        indexes[i] = i;
    }

    // shuffles indexes
    for(int i = 0; i < 120; i++){
        int x = rand() % 120, y = rand() % 120;
        int temp = indexes[x];
        indexes[x] = indexes[y];
        indexes[y] = temp;
    }

    // frees chunks pseudorandomly
    for(int i = 0; i < 120; i++) {
        free(objects[indexes[i]]);
    }

    // if test worked, there should be one free chunk of memlength
    display_all_chunks(chunk_iterator);
}


static void test5() {

}


int main() {
    chunk_iterator = malloc(0);
    free(chunk_iterator);
    display_all_chunks(chunk_iterator);

    double average_time[5] = {run_50_times(test1), run_50_times(test2), run_50_times(test3), run_50_times(test4), run_50_times(test5)};

    for(int i = 0; i < 5; i++) {
        printf("Task %d: \t Average Time: %lf\n", i + 1, average_time[i]);        
    }
}
