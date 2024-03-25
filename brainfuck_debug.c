#include <stdio.h>
#include <stdint.h>
#include "brainfuck_debug.h"

void display_buffer(char* buffer){
    uint32_t i = 0;
    char current;
    while((i < DATA_ARRAY_SIZE) && ((current=buffer[i]) != '\0')){
        printf("%c", current);
        i ++;
    }
}