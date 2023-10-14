#include <stdlib.h>
#include "mymalloc.h"


/* Some commonly used typedefs/macros */

#define MEMLENGTH 512 // NOT the number of bytes of working memory, which is 4096
#define HEADER_SIZE sizeof(chunkheader) // size of header: 8
#define ROUNDUP8(x) (((x) + 7) & (-8))

/* Private data that should not be visible outside this library */

static double memory[MEMLENGTH];

int is_initialized = 0; // is this allowed? unsure
typedef struct _chunkheader {
   unsigned int total_size; // Size of whole chunk, HEADER + PAYLOAD
   unsigned int is_allocated; // Chunk is allocated or not: 0 (not allocated), 1 (allocated)
} chunkheader;


/* Private Helper Functions */

// Create the first chunk as a free block
static void init() {
   chunkheader* first_chunk = (chunkheader*) memory;
   first_chunk->total_size = MEMLENGTH * sizeof(double);
   first_chunk->is_allocated = 0;

   is_initialized = 1;
}

//DIDN'T FIND PURPOSE OF HAVING SEPARATE COALESCE
// Combines any free chunks before or after this chunk when it is freed
//static void coalesce(void *ptr, char *file, int line){
//   chunkheader* curr = (chunkheader*)memory;
//
//   while (curr != NULL){
//       if ((curr->is_allocated == 0) && (curr->total_size >= sizeof(chunkheader))) {
//         chunkheader* next_chunk = (chunkheader*)((char*)curr + curr->total_size + sizeof(chunkheader));
//          if (next_chunk->is_allocated == 0) {
//             //merge current chunk with the next chunk
//             (curr->total_size) += (next_chunk->total_size) + sizeof(chunkheader);
//          }
//       }
//       curr = (chunkheader*)((char*)curr + (curr->total_size) + sizeof(chunkheader));
//   }
//}


/* Public Functions*/

void *mymalloc(size_t size, char *file, int line) {
   if (is_initialized == 0) {
      init();
   }

   size = ROUNDUP8(size);

   chunkheader* current_chunk = (chunkheader*)memory; // index pointer to iterate through memory, starts at memory[0]
   while ((void*)current_chunk < (void*)(memory + MEMLENGTH)) {  // iterate through all chunks within the array
      if (current_chunk->is_allocated == 0 && current_chunk->total_size - HEADER_SIZE >= size) {
         // chunk is free and big enough
         if (current_chunk->total_size - HEADER_SIZE == size) {
            // chunk is the exact amount requested, do not have to split the chunk
            current_chunk->is_allocated = 1;
            return current_chunk + 1;
         } else {
            // chunk is bigger than requested, split the chunk so remaining memory can be allocated to another call
            chunkheader* new_chunk = current_chunk + 1 + size/8;
            new_chunk->total_size = current_chunk->total_size - HEADER_SIZE - size;
            new_chunk->is_allocated = 0;

            current_chunk->total_size = current_chunk->total_size - new_chunk->total_size;
            current_chunk->is_allocated = 1;

            return current_chunk + 1;
         }
      }
      // next available chunk, may not exist
      current_chunk += (current_chunk->total_size)/HEADER_SIZE;
   }
   // printf("ERROR: either no chunks of large enough space or all chunks being used\n"); //update this eventually, error not enough memory
   return NULL;
}

void myfree(void *ptr, char *file, int line) {

   // Edge cases (like ptr is null, never allocated, etc)
   if (ptr == NULL){
      return;
   }

   // Retrieve header of chunk to be freed
   chunkheader* freed_chunk = (chunkheader*)(ptr - HEADER_SIZE);
   freed_chunk->is_allocated = 0;

   //coalesce -  no longer in a separate method
   chunkheader* prev_chunk = NULL;
   chunkheader* curr_chunk = (chunkheader*)memory;

   while (curr_chunk != NULL) {
      if (curr_chunk->is_allocated == 0) {

         //merge with the previous chunk (if it exists)
         if (prev_chunk != NULL && prev_chunk->is_allocated == 0) {
             prev_chunk->total_size += (curr_chunk->total_size + HEADER_SIZE);
         }

         //merge with the next chunk (if it exists)
         chunkheader* next_chunk = (chunkheader*)((char*)curr_chunk + curr_chunk->total_size + HEADER_SIZE);
         if (next_chunk != NULL && next_chunk->is_allocated == 0) {
            curr_chunk->total_size += (next_chunk->total_size + HEADER_SIZE);
         }
     }
     //move to the next chunk to check (iterate across)
     prev_chunk = curr_chunk;
     curr_chunk = (chunkheader*)((char*)curr_chunk + curr_chunk->total_size + HEADER_SIZE);
   }
}
