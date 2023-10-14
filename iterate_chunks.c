/* test program: iterate_chunks

this program is a library meant to be used in multiple test files

it displays the info of a chunk created by malloc and all chunks after it, if any
it's supposed to be used with the first chunk created by malloc so that when executed it displays all chunks in our array of memory
*/

#include "iterate_chunks.h"
#define MEMORY_AVAILABLE 4096

void print_chunk_info(unsigned int* ptr) {
    if(ptr == NULL){
        printf("null pointer\n");
    } else {
        unsigned int size = *(ptr - 2), is_allocated = *(ptr - 1);
        printf("\tchunk %p\t\tis_allocated %i\t\tsize %i\n", ptr, is_allocated, size);
    }
    return;
}

void display_all_chunks(unsigned int* first){
    if(first == NULL){
        printf("ERROR NULL PTR");
    }
    int bytes_left = MEMORY_AVAILABLE;

    printf("--START--\n");
    do{
        printf("%i\t: ", MEMORY_AVAILABLE - bytes_left);
        print_chunk_info(first);
        unsigned int size = *(first - 2);

        bytes_left -= size;
        first = (unsigned int*)((char*)first + size);
        if(bytes_left == 0){
            printf("--END--\n");
        }else if(bytes_left < 0){
            printf("Something is wrong with display_all_chunks!");
        }
    }while(bytes_left > 0);
}