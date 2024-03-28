#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "brainfuck_helper.h"
#include <stdio.h>

char* get_input_prog(char* input_filename)
{
    char *array = malloc(DATA_ARRAY_SIZE * sizeof(char));

    /*Opened file in read mode*/
    FILE *fptr;
    fptr = fopen(input_filename, "r"); 
    if (fptr == NULL){
        fprintf(stderr, "Failed to open the file");
        return NULL;
    }

    uint32_t i = 0;
    int c;
    while ((i < DATA_ARRAY_SIZE - 1) && ((c = fgetc(fptr)) != EOF))
    {   
        array[i] = (char) c;
        i++;
    }
    array[i] = '\0'; /*Add end character*/

    return array;
    
}

void free_input_prog(char* input_prog)
{
    if (input_prog == NULL){
        return;
    }
    free(input_prog);
}


void* build_loops(char* input_prog) {
  // Calculate initial capacity considering potential odd size
  uint32_t loops_capacity = DATA_ARRAY_SIZE / 2 + (DATA_ARRAY_SIZE % 2 != 0);
  uint32_t loops_count = 0;

  // Allocate memory for loops with initial capacity
  struct Loop* loops = malloc(loops_capacity * sizeof(struct Loop));
  if (loops == NULL) {
    fprintf(stderr, "Failed to allocate space for loop array");
    return NULL; // Handle allocation failure
  }

  // Allocate memory for stack with initial capacity
  uint32_t* stack = malloc(loops_capacity * sizeof(uint32_t));
  if (stack == NULL) {
    fprintf(stderr, "Failed to allocate space for stack array");
    free(loops); // Free previously allocated memory
    return NULL; 
  }

  uint32_t top_stack = 0;
  char current;
  uint32_t i = 0;

  while ((current = input_prog[i]) != '\0') {

    if (current == '[') {
      stack[top_stack] = i;
      top_stack++;
    } 
    else if (current == ']') {
      if (top_stack == 0) {
        // Handle unmatched closing bracket
        // (you might want to return an error or handle it differently)
        fprintf(stderr, "Unmatched closing bracket");
        free(loops);
        free(stack);
        return NULL;
      }
      
      struct Loop new_loop = {.start = stack[top_stack - 1], .end = i};
      loops[loops_count] = new_loop;
      loops_count++;
      top_stack--;
    }
    i++;
  }

  // Add end marker loop
  struct Loop last_loop = {.start = -1, .end = -1};
  loops[loops_count] = last_loop;
  loops_count++;

  // Reallocate memory to fit actual loop count (optional optimization)
  uint32_t final_size = loops_count * sizeof(struct Loop);
  if (final_size < loops_capacity * sizeof(struct Loop)) {
    struct Loop* tmp_loop = realloc(loops, final_size);
    if (tmp_loop != NULL) {
      loops = tmp_loop;
    }
  }

  free(stack); // Free stack memory after use

  return loops;
}
