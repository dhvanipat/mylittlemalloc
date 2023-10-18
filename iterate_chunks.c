/* test program: iterate_chunks

this program is a library meant to be used in multiple test file executables

parameter: it's supposed to take a pointer to the payload of the first chunk created by malloc
when executed it displays the info of all chunks currently stored in memory
will go out of bounds if it's not called on the first chunk
 
*/

#include "iterate_chunks.h"
#define MEMORY_AVAILABLE 4096

void print_chunk_info(unsigned int* ptr) {
    if(ptr == NULL){
        fprintf(stderr, "error null pointer\n");
    } else {
        unsigned int size = *(ptr - 2), is_allocated = *(ptr - 1);
        printf("\tchunk %p\t\tis_allocated %i\t\tsize %i\n", ptr, is_allocated, size);
    }
    return;
}

void display_all_chunks(unsigned int* first){
    if(first == NULL){
        fprintf(stderr, "ERROR NULL PTR\n");
        return;
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