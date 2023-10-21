#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"
#include "iterate_chunks.h"

int main(int argc, char **argv)
{
      unsigned int* foo = malloc(0);
      free(foo);

      display_all_chunks(foo);

      printf("tests for some edge cases \n");

      // test 1: successfully allocates empty chunk of size 8 when 0 bytes requested
      printf("Test 1: Allocates 0 bytes\n");

      int *a = malloc(0);
      display_all_chunks(foo);
      if (*(a-2) == 8){
            printf("Passed Case\n\n");
      } else {
            printf("Case Not Passed\n\n");
      }

      //test 2 allocate bytes that exceeds the size
      printf("Test 2: Allocates Bytes That Exceeds\n");
      int *b = malloc(sizeof(char) * 4097);
      display_all_chunks(foo);
      if (b == NULL) {
            printf("Passed Case\n\n");
      } else {
            printf("Case Not Passed\n\n");
      }


      //test 3 trying to free when no allocation/pointers not belong in memory
      printf("Test 3: Trying to free when no allocations/pointers not belong in the memory w/ diff pointers\n");
      char c;
      int d;
      free(&c);
      free(&d);
      display_all_chunks(foo);

      return EXIT_SUCCESS;
}
