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

    uint64_t i = 0;
    while ((i < DATA_ARRAY_SIZE - 1))
    {   
        array[i] = (char) fgetc(fptr);
        i++;
    }
    array[i] = '\0'; /*Add end character*/

    return array;
    
}

