#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"



/* Some commonly used typedefs/macros */

#define MEMLENGTH 512 // NOT the number of bytes of working memory, which is 4096
#define HEADER_SIZE sizeof(chunkheader) // size of header: 8
#define ROUNDUP8(x) (((x) + 7) & (-8))



/* Private data that should not be visible outside this library */

static double memory[MEMLENGTH];
typedef struct _chunkheader {
   unsigned int total_size; // Size of whole chunk, HEADER + PAYLOAD
   unsigned int is_allocated; // Chunk is allocated or not: 0 (not allocated), 1 (allocated)
} chunkheader;



/* Private Helper Functions */

// Creates the first chunk by setting size proportional to MEMLENGTH
static void init() {
   chunkheader* first_chunk = (chunkheader*) memory;
   first_chunk->total_size = MEMLENGTH * sizeof(double);
}

/* In: ptr to start of chunk
   Out: a pointer to the start of where the next chunk's header should be, may not be initialized */
static chunkheader* next(chunkheader* ptr) {
   char* char_ptr = (char*)ptr;
   char_ptr += ptr->total_size;
   return (chunkheader*)char_ptr;
}

/* In: ptr to start of chunk
   Out: size of payload in bytes */
static unsigned int size_of_payload(chunkheader* ptr) {
   unsigned int payload = ptr->total_size - HEADER_SIZE;
   return payload;
}

/* In: ptr to start of chunk
   Out: a pointer to the start of the chunk's payload, after the chunk header */
static chunkheader* ptr_to_payload(chunkheader* ptr) {
   return ptr + 1;
}

//DIDN'T FIND PURPOSE OF HAVING SEPARATE COALESCE
// just to make it more readable p much, like how i made some helper methods for malloc. but it's completely up to u how u want to split it. just keep it in mind bc it syas we'll be graded on clarity
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
   chunkheader* current_chunk = (chunkheader*)memory; // index pointer to iterate through memory, starts at memory[0]

   if (current_chunk->total_size == 0) {
      init();
   }

   size = ROUNDUP8(size);

   while ((void*)current_chunk < (void*)(memory + MEMLENGTH)) {                           // iterate through all chunks within the array
      if (current_chunk->is_allocated == 0 && size_of_payload(current_chunk) >= size) {   // chunk is free and big enough
         current_chunk->is_allocated = 1;
         if (size_of_payload(current_chunk) > size) {                                     // chunk is bigger than requested, split the chunk so remaining memory can be allocated to another call
            int size_both = current_chunk->total_size;
            current_chunk->total_size = HEADER_SIZE + size;

            chunkheader* new_chunk = next(current_chunk);
            new_chunk->total_size = size_both - current_chunk->total_size;
            new_chunk->is_allocated = 0;
         }
         return ptr_to_payload(current_chunk);
      }
      current_chunk = next(current_chunk);
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
   chunkheader* freed_chunk = (chunkheader*)ptr - 1;

   //not so sure if should subtract by 8 (HEADERSIZE)?
   //chunkheader* freed_chunk = (chunkheader*)(ptr - HEADER_SIZE);
   freed_chunk->is_allocated = 0;

   //coalesce -  no longer in a separate method
   chunkheader* prev_chunk = NULL;
   chunkheader* curr_chunk = (chunkheader*)memory;
   void* memoryEnd = (void*)(memory + MEMLENGTH);

   //need to make sure start < memEnd
   while ((void*)curr_chunk < memoryEnd) {
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
