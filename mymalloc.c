#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"



/* Some commonly used typedefs/macros */

#define MEMLENGTH 512 // NOT the number of bytes of working memory, which is 4096
#define HEADER_SIZE sizeof(chunkheader) // size of header: 8
#define MEMORY_END (chunkheader*)(memory + MEMLENGTH)
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

/* In: a pointer to a chunk's header
   Out: ptr to the previous chunk's header */
static chunkheader* find_prev_chunk(chunkheader* ptr){
   chunkheader* current_chunk = (chunkheader*)memory;
   chunkheader* previous_chunk;

   while (current_chunk < MEMORY_END) {
      if (current_chunk == ptr) {
         return previous_chunk;
      }
      previous_chunk = current_chunk;
      current_chunk = next(current_chunk);
   }
   fprintf(stderr, "ERROR in find_prev_chunk: this function should reach the end before terminating");
   return NULL;
}

/* In: ptr to start of chunk
   Out: a pointer to the start of the chunk's payload, after the chunk header */
static chunkheader* ptr_to_payload(chunkheader* ptr) {
   return ptr + 1;
}

/* In: a pointer to a chunk's payload
   Out: ptr to the start of a chunk's header */
static chunkheader* ptr_to_header(void* ptr){
   ptr = ptr - 8;
   ptr = (chunkheader*)ptr;
   return ptr;
}

// Sends output to stderr if malloc does not have any more memory
static void not_enough_memory_error(char* file, int line, size_t size){
   errno = ENOMEM;
   fprintf(stderr, "ERROR in %s, line %d, malloc(%ld): ", file, line, size);
   perror("");
}

// Sends output to stderr if an invalid address is passed to free
static void bad_address_error(char* file, int line, void* ptr){
   errno = EFAULT;
   fprintf(stderr, "ERROR in %s, line %d, free(%p): ", file, line, ptr);
   perror("");
}

static void double_free_error(char* file, int line, void* ptr){
   errno = EFAULT;
   fprintf(stderr, "ERROR in %s, line %d, free(%p), this memory is already free: ", file, line, ptr);
   perror("");
}

static void coalesce(chunkheader* ptr) {  
   
   // merges chunks before
   char merged_prev_chunk = 0;
   do {
      merged_prev_chunk = 0;
      chunkheader* previous_chunk = find_prev_chunk(ptr);
      if (ptr != (chunkheader*)memory && previous_chunk->is_allocated == 0) { // ptr is not first chunk
         merged_prev_chunk = 1;
         previous_chunk->total_size += ptr->total_size;
         ptr = previous_chunk;
      }
   } while (merged_prev_chunk);


   // merges chunks after
   char merged_post_chunk = 0;
   do {
      merged_post_chunk = 0;
      if (next(ptr) != MEMORY_END && next(ptr)->is_allocated == 0) { // ptr is not the last chunk
         merged_post_chunk = 1;
         ptr->total_size += next(ptr)->total_size;
      }
   } while (merged_post_chunk);
   return;
}



/* Public Functions*/

void *mymalloc(size_t size, char *file, int line) {
   chunkheader* current_chunk = (chunkheader*)memory; // index pointer to iterate through memory, starts at memory[0]

   if (current_chunk->total_size == 0) {
      init();
   }

   unsigned int og_size = size;
   size = ROUNDUP8(size);

   while (current_chunk < MEMORY_END) {                           // iterate through all chunks within the array
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
   
   not_enough_memory_error(file, line, og_size);
   return NULL;
}

void myfree(void *ptr, char *file, int line) {
   if (ptr == NULL) {
      bad_address_error(file, line, ptr);
      return;
   }

   ptr = ptr_to_header(ptr);
   chunkheader* current_chunk = (chunkheader*)memory;

   while (current_chunk < MEMORY_END) {   // iterate through all chunks within the array
      if (current_chunk == ptr) {
         if(current_chunk->is_allocated == 1){
            current_chunk->is_allocated = 0;
            coalesce(ptr);
         } else {
            double_free_error(file, line, ptr);
         }
         return;
      }
      current_chunk = next(current_chunk);
   }
   bad_address_error(file, line, ptr);
   return;
}
