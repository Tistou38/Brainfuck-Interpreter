#include <stdio.h>
#include <stdint.h>
#include "brainfuck_debug.h"

void display_buffer(char* buffer){
    size_t buffer_size = sizeof(buffer);
    for (uint32_t i = 0 ; i < buffer_size ; i++){
        printf("%c\n", buffer[i]);
    }
}