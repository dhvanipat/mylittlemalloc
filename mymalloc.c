#include <stdio.h> // Remove when done
#include <stdlib.h>
#include "mymalloc.h"


/* Some commonly used typedefs/macros */

#define MEMLENGTH 512 // length of working memory usable by malloc
#define HEADER_SIZE 8 // size of header: is_allocated + size
typedef unsigned long int size_t;


/* Private data that should not be visible outside this library */

static double memory[MEMLENGTH];
int is_initialized = 0; // is this allowed? unsure
typedef struct _chunkheader {
   size_t total_size; // Size of whole chunk, HEADER + PAYLOAD
   int is_allocated; // Chunk is allocated or not: 0 (not allocated), 1 (allocated)
} chunkheader;


/* Private Helper Functions */

// Create the first chunk as a free block
static void init() {
   //block_size = (block_size + 7) & ~7; //ensures alignment of 8 bytes
   // wha

   chunkheader* first_chunk = (chunkheader*) memory;
   first_chunk->total_size = MEMLENGTH;
   first_chunk->is_allocated = 0;

   is_initialized = 1;
}

// pads extra bytes for header alignment
static int pad(size_t size){
   if(size % HEADER_SIZE != 0) {
      size = size / HEADER_SIZE * HEADER_SIZE;
      size += HEADER_SIZE;
   }

   return size;
}

// Combines any free chunks before or after this chunk when it is freed
static void coalesce(void *ptr, char *file, int line){
   chunkheader* curr = (chunkheader*)memory;

   while (curr != NULL){
       if ((curr->is_allocated == 0) && (curr->total_size >= sizeof(chunkheader))) {
         chunkheader* next_chunk = (chunkheader*)((char*)curr + curr->total_size + sizeof(chunkheader));
          if (next_chunk->is_allocated == 0) {
             //merge current chunk with the next chunk
             (curr->total_size) += (next_chunk->total_size) + sizeof(chunkheader);
          }
       }
       curr = (chunkheader*)((char*)curr + (curr->total_size) + sizeof(chunkheader));
   }
}


/* Public Functions*/

void *mymalloc(size_t size, char *file, int line) {
   if(is_initialized == 0){
      init();
   }
   
   size = pad(size);

   chunkheader* current_chunk = (chunkheader*)memory;
   while(current_chunk < (chunkheader*) memory + MEMLENGTH) {  //iterate through all chunks within MEMLENGTH
      if(current_chunk->is_allocated == 0 && current_chunk->total_size - HEADER_SIZE >= size){   // chunk is free
         //void* ptr = current_chunk + HEADER_SIZE;
         printf("%p\n", current_chunk + HEADER_SIZE);
         printf("%p\n", &current_chunk->total_size);
         printf("%ld\n", current_chunk + HEADER_SIZE - (chunkheader*)&current_chunk->total_size);
         //printf("%ld", *((long unsigned int*)ptr));
         return current_chunk + HEADER_SIZE;
      }
      current_chunk += current_chunk->total_size;      
   }
   printf("ERROR: either no chunks of large enough space or all chunks being used\n"); //update this eventually, error not enough memory
   return NULL;

   // printf("%d\n", *current_chunk - HEADER_SIZE);
   // printf("%d\n", *((int*)memory));
   // printf("%p, end of memory: %p", memory, memory + MEMLENGTH);
}

void myfree(void *ptr, char *file, int line) {
   // Edge cases (like ptr is null, never allocated, etc)
   if (ptr == NULL){
      return;
   }

   // Retrieve header of chunk to be freed
   chunkheader* freed_chunk = (chunkheader*)(ptr - HEADER_SIZE);
   freed_chunk->is_allocated = 0;

   //coalesce -  needs to be edited
   coalesce(ptr, file, line);

}