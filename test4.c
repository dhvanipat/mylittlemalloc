#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include "iterate_chunks.h"

int main(){
    void* my_ptr = malloc(0);
    for(int i = 0; i < 200; i++){
        malloc(i);
    }

    display_all_chunks(my_ptr);
}