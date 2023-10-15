#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mymalloc.h"
#include "iterate_chunks.h"


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

static void task_4() { // tests coalesce, tests if malloc can handle chunks of varying sizes, malloc can handle requests when memory is full
    void* objects[120];

    // allocates 120 objects of random size and then frees from back to front to test coalesce
    for(int i = 0; i < 120; i++) {
        objects[i] = malloc(rand() % 100);
    }

    for(int i = 119; i >= 0; i--) {
        free(objects[i]);
        //display_all_chunks(placeholder);
    }

    // allocates 120 objects of random size and then frees from front to back to test coalesce
    for(int i = 0; i < 120; i++) {
    objects[i] = malloc(rand() % 100);
    }

    for(int i = 0; i < 120; i++) {
        free(objects[i]);
        //display_all_chunks(placeholder);
    }

    // allocates 120 objects of random size and then frees at random to see if chunks will coalesce when freed in no order, free has adequate error handling for invalid addresses
    for(int i = 0; i < 120; i++) {
        objects[i] = malloc(rand() % 100);
    }

    for(int i = 0; i < 120; i++) {
        free(objects[rand() % 120]);
        //display_all_chunks(placeholder);
    }

    for(int i = 0; i < 120; i++) {
        free(objects[i]);
        //display_all_chunks(placeholder);
    }
}

static void task_5() {

}


int main() {
    //void* placeholder = malloc(0);

    double average_time[5] = {run_50_times(task_1), run_50_times(task_2), run_50_times(task_3), run_50_times(task_4), 0};

    task_5();

    for(int i = 0; i < 5; i++) {
        printf("Task %d: \t Average Time: %lf\n", i + 1, average_time[i]);        
    }
}