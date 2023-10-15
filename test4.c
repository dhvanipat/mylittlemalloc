#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include "iterate_chunks.h"

int main(){
    void* my_ptr = malloc(0);
    // for(int i = 0; i < 64; i++){
    //     malloc(8);
    // }
    void* ptr_2 = malloc(8);
    void* ptr_3 = malloc(40);

    display_all_chunks(my_ptr);
    free(my_ptr);    
    display_all_chunks(my_ptr);
    free(ptr_2);    
    display_all_chunks(my_ptr);
    free(ptr_3);    
    display_all_chunks(my_ptr);
}