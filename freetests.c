#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"

int main(int argc, char **argv)
{
    print("tests for some edge cases \n");

    //test 1 allocates 0 bytes 
    print("Test 1: Allocates 0 bytes\n");

    int *a = malloc(sizeof(char) * 0);
    if (a == NULL){
         printf("Passed Case\n\n");
    } else {
         printf("Case Not Passed\n\n");
    }

   //test 2 allocate bytes that exceeds the size 
   printf("Test 2: Allocates Bytes That Exceeds\n")
   int *b = malloc(sizeof(char) * 4097);
   if (b == NULL) {
         printf("Passed Case\n\n");
   } else {
         printf("Case Not Passed\n\n");
   }

  //test 3 trying to free when no allocation/pointers not belong in memory
  printf("Test 3: Trying to free when no allocations/pointers not belong in the memory w/ diff pointers")
  char c;
  int d;
  free(&c);
  free(&d);

  return EXIT_SUCCESS;
} 

