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

