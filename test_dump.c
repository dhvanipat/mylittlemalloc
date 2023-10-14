#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#define ROUNDUP8(x) (((x) + 7) & (-8))


static void print_chunk_info(unsigned int*);
//static int pad(size_t);

int main(){


    void* my_ptr = malloc(4096-8-8);
    print_chunk_info(my_ptr);

    void* another_ptr = malloc(8);
    print_chunk_info(another_ptr);

    void* another_ptr_ = malloc(0);
    print_chunk_info(another_ptr_);
}


static void print_chunk_info(unsigned int* ptr) {
    if(ptr == NULL){
        printf("null pointer\n");
    } else {
        printf("Chunk Address: %p\n", ptr);
        printf("Chunk Size: %i\n", *(ptr - 2));
        printf("Chunk is allocated: %i\n", *(ptr - 1));        
    }
    return;
}

/*
static int pad(size_t size){
   if(size % 8 != 0) {
      size = size / 8 * 8;
      size += 8;
   }

   return size;
}
*/