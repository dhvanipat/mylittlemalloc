#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

static void print_chunk_info(int*);

int main(){
    void* my_ptr = malloc(5);
    print_chunk_info(my_ptr);
    // void* another_ptr = malloc(5);
    // print_chunk_info(another_ptr);
}

static void print_chunk_info(int* ptr) {
    if(ptr == NULL){
        printf("null pointer");
    } else {
        printf("Chunk Address: %p\n", ptr);
        printf("Chunk Size: %d\n", *(ptr - 8));
        printf("Chunk is allocated: %d\n", *(ptr - 4));        
    }
    return;
}