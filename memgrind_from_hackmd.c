#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mymalloc.h"
#include "iterate_chunks.h"

void* placeholder;

void test1() {
    for(int i = 0; i < 120; i++) {
        char *ptr = malloc(1);  // Allocate 1 byte of memory
        free(ptr);  // Release the memory
    }

    display_all_chunks(placeholder);
    printf("MemClear?: \n");  // Check if memory is cleared
}

void test2() {
    char *ptrArray[120];  // Array to store 120 pointers

    for(int i = 0; i < 120; i++) {
        ptrArray[i] = malloc(1);  // Allocate 1 byte of memory and store the address
    }

    for(int i = 0; i < 120; i++) {
        free(ptrArray[i]);  // Release the memory
    }

    display_all_chunks(placeholder);
    printf("MemClear?: \n");  // Check if memory is cleared
}

void test3() {
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

    display_all_chunks(placeholder);
    printf("MemClear?: \n");  // Check if memory is cleared
}

int main(){
    placeholder = malloc(0);
    display_all_chunks(placeholder);

    test1();
    test2();
    test3();
}