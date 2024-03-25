#include <stdlib.h>
#include <stdint.h>
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

void* build_loops(char* input_prog)
{
    uint32_t loops_capacity = 100;
    uint32_t loops_count = 0;
    struct Loop* loops = malloc(loops_capacity * sizeof(struct Loop));
    
    char current;
    uint32_t i = 0;
    while ((current = input_prog[i]) != '\0')
    {
        if (current == '['){
            if (loops_count == loops_capacity){
                loops_capacity *= 2;
                loops = realloc(loops, loops_capacity * sizeof(struct Loop));
            }
            struct Loop new_loop = { .start = i, .end = 0 };
            loops[loops_count] = new_loop;
            loops_count++;
            
        }
        else if (current == ']'){
            loops[loops_count - 1].end = i;
        }

        i++;

    }
    return loops;
}