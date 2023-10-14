#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMLENGTH 512
#define HEADER_SIZE 8 //size of header: is_allocated + size

typedef unsigned long int size_t;
static double memory[MEMLENGTH];
static void coalesce(void *ptr, char *file, int line);

typedef struct _chunkheader {
   size_t size; //size of the payload
   int is_allocated; //chunk is allocated or not
} chunkheader;

void memory_block(size_t block_size) {
   //block_size = (block_size + 7) & ~7; //ensures alignment of 8 bytes

   void* memory_block = malloc(MEMLENGTH);

   //create the first chunk as a free block
   chunkheader* first_chunk = (chunkheader*) memory_block;
   first_chunk->size = MEMLENGTH - sizeof(chunkheader);
   first_chunk->is_allocated = 0;
}

void *mymalloc(size_t size, char *file, int line) {
   return 0; //TEMP REPLACE
}

static void coalesce(void *ptr, char *file, int line){
   chunkheader* curr = (chunkheader*)memory;

   while (curr != NULL){
       if ((curr->is_allocated == 0) && (curr->size >= sizeof(chunkheader))) {
         chunkheader* next_chunk = (chunkheader*)((char*)curr + curr->size + sizeof(chunkheader));
          if (next_chunk->is_allocated == 0) {
             //merge current chunk with the next chunk
             (curr->size) += (next_chunk->size) + sizeof(chunkheader);
          }
       }
       curr = (chunkheader*)((char*)curr + (curr->size) + sizeof(chunkheader));
   }
}

void myfree(void *ptr, char *file, int line) {
   //edge cases (like ptr is null, never allocated, etc)
   if (ptr == NULL){
      return;
   }

   //retrieve header of chunk to be freed
   chunkheader* freed_chunk = (chunkheader*)((char*)ptr - sizeof(chunkheader));
   freed_chunk->is_allocated = 0;

   //coalesce -  needs to be edited
   coalesce(ptr, file, line);

}
