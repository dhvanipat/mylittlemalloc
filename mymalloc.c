#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMLENGTH 512
static double memory[MEMLENGTH];

struct chunkheader {
   size_t size; //size of the payload
   int is_allocated; //chunk is allocated or not
};

void memory_block(size_t block_size) {
   //block_size = (block_size + 7) & ~7; //ensures alignment of 8 bytes

   void* memory_block = malloc(MEMLENGTH);

   //create the first chunk as a free block
   struct chunkheader* first_chunk = (struct chunkheader*) memory_block;
   first_chunk->size = MEMLENGTH - sizeof(struct chunkheader);
   first_chunk->is_allocated = 0;
}

void *mymalloc(size_t size, char *file, int line) {

}

void myfree(void *ptr, char *file, int line) {
   //edge cases (like ptr is null, never allocated, etc)
   if (ptr == NULL){
      return;
   }

   //retrieve header of chunk to be freed
   struct chunkheader* freed_chunk = (struct chunkheader*)((char*)ptr - sizeof(struct chunkheader));
   freed_chunk->is_allocated = 0;

   //coalesce -  needs to be edited
   coalesce();

}

void coalesce(void*){

}
