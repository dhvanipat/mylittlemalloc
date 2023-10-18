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

    time /= 50;
    return time;
}

static void task_1() {
    for(int i = 0; i < 120; i++){
        void* x = malloc(1);
        free(x);
    }
}

static void task_2() {
    void* objects[120];
    for(int i = 0; i < sizeof(objects)/sizeof(objects[0]); i++){
        objects[i] = malloc(1);
    }
    for(int i = 0; i < sizeof(objects)/sizeof(objects[0]); i++){
        free(objects[i]);
    }
}

static void task_3() {
    void* objects[120];
    int allocations = 0, index = 0;

    while(allocations < 120) {
        if (rand() % 2 == 0) { // allocating
            objects[index] = malloc(1);
            allocations++;
            index++;
        } else { // freeing
            if (index > 0) {
                index--;
            }
            free(objects[index]);   // done on purpose to see what free does if it's given a pointer that (A) has never been allocated, or (B) has already been freed           
        }
    }

    while(index > 0) {
        index--;
        free(objects[index]);
    }
}

static void task_4() { // tests if malloc can handle chunks of varying sizes, if chunks will coalesce in random order
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


static void task_5() {

}


int main() {
    chunk_iterator = malloc(0);
    free(chunk_iterator);
    display_all_chunks(chunk_iterator);

    double average_time[5] = {run_50_times(task_1), run_50_times(task_2), run_50_times(task_3), run_50_times(task_4), 0};

    task_5();

    for(int i = 0; i < 5; i++) {
        printf("Task %d: \t Average Time: %lf\n", i + 1, average_time[i]);        
    }
}